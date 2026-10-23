// TextRenderer.h - single-file OpenGL text rendering for a 2D engine
//
// Requirements
//   - An OpenGL 3.3+ core context, with your loader (glad, GLEW, ...) included BEFORE this file
//   - stb_truetype.h (https://github.com/nothings/stb) on your include path
//   - A .ttf font file
//
// Usage
//   #include <glad/glad.h>
//   #include "TextRenderer.h"
//
//   TextRenderer text;
//   if (!text.init("assets/fonts/Roboto-Regular.ttf", 32.0f, windowWidth, windowHeight)) {
//       // font missing or shader failed; details are printed to stderr
//   }
//
//   // Every frame, after drawing the scene:
//   text.draw("Sun: 150", 20, 20);                        // white, top-left corner at (20, 20)
//   text.draw("Wave 3", 20, 60, 1.0f, 0.85f, 0.2f);       // tinted
//
//   // Centering a label horizontally:
//   float w = text.measureWidth("Game Over");
//   text.draw("Game Over", (windowWidth - w) * 0.5f, 200);
//
//   // On window resize:
//   text.setScreenSize(newWidth, newHeight);
//
//   // Before destroying the OpenGL context:
//   text.shutdown();
//
// Notes
//   - Coordinates are screen pixels, origin at the top-left, y pointing down.
//   - (x, y) is the top-left of the first line; '\n' starts a new line.
//   - Printable ASCII only (32-126); other characters are drawn as '?'.
//   - One TextRenderer = one font at one pixel size. Create another instance for another size.
//   - draw() saves and restores the GL state it touches, so it will not disturb your sprite renderer.
//   - stb_truetype is compiled with STBTT_STATIC here, so this header can be included from
//     several .cpp files without duplicate-symbol link errors.

#pragma once

#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

// stb_truetype's unused static functions would otherwise trigger dozens of -Wall warnings
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4505)
#endif

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

class TextRenderer {
public:
    TextRenderer() = default;
    ~TextRenderer() { shutdown(); }
    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    // Loads the font, bakes the glyph atlas, and creates the GPU resources.
    bool init(const char* fontPath, float pixelHeight, int screenWidth, int screenHeight) {
        shutdown();
        if (!loadFont(fontPath, pixelHeight)) return false;
        if (!createShader()) { shutdown(); return false; }
        createBuffers();
        setScreenSize(screenWidth, screenHeight);
        return true;
    }

    // Rebuilds the screen-space projection. Call on window resize.
    void setScreenSize(int width, int height) {
        // Column-major orthographic matrix: left=0, right=width, top=0, bottom=height, near=-1, far=1
        for (float& v : projection_) v = 0.0f;
        projection_[0]  =  2.0f / (float)width;
        projection_[5]  = -2.0f / (float)height;
        projection_[10] = -1.0f;
        projection_[12] = -1.0f;
        projection_[13] =  1.0f;
        projection_[15] =  1.0f;
    }

    // Draws text with its top-left corner at (x, y). Colour components are 0..1.
    void draw(const std::string& text, float x, float y,
              float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) {
        if (!texture_ || text.empty()) return;
        buildVertices(text, x, y);
        if (vertices_.empty()) return;

        GLState saved = saveState();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);   // UI text always sits on top
        glDisable(GL_CULL_FACE);    // the y-flip makes the quads clockwise

        glUseProgram(program_);
        glUniformMatrix4fv(uProjection_, 1, GL_FALSE, projection_);
        glUniform4f(uColor_, r, g, b, a);
        glUniform1i(uAtlas_, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices_.size() * sizeof(float)),
                     vertices_.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(vertices_.size() / 4));

        restoreState(saved);
    }

    // Width in pixels of the widest line of the text.
    float measureWidth(const std::string& text) const {
        float widest = 0.0f, penX = 0.0f, penY = 0.0f;
        for (unsigned char c : text) {
            if (c == '\n') {
                if (penX > widest) widest = penX;
                penX = 0.0f;
                continue;
            }
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(glyphs_, atlasSize_, atlasSize_, glyphIndex(c), &penX, &penY, &q, 1);
        }
        return penX > widest ? penX : widest;
    }

    // Vertical distance between consecutive lines, in pixels.
    float lineHeight() const { return lineHeight_; }

    // Frees GPU resources. Call before the OpenGL context is destroyed.
    void shutdown() {
        if (vbo_)     { glDeleteBuffers(1, &vbo_);      vbo_ = 0; }
        if (vao_)     { glDeleteVertexArrays(1, &vao_); vao_ = 0; }
        if (texture_) { glDeleteTextures(1, &texture_); texture_ = 0; }
        if (program_) { glDeleteProgram(program_);      program_ = 0; }
    }

private:
    static constexpr int FIRST_CHAR = 32;   // ' '
    static constexpr int NUM_CHARS  = 95;   // ' ' .. '~'

    struct GLState {
        GLint program, vao, arrayBuffer, activeTexture, texture2D;
        GLint blendSrcRGB, blendDstRGB, blendSrcAlpha, blendDstAlpha;
        GLboolean blend, depthTest, cullFace;
    };

    GLuint program_ = 0, vao_ = 0, vbo_ = 0, texture_ = 0;
    GLint  uProjection_ = -1, uColor_ = -1, uAtlas_ = -1;
    stbtt_bakedchar glyphs_[NUM_CHARS] = {};
    int   atlasSize_  = 0;
    float ascent_     = 0.0f;
    float lineHeight_ = 0.0f;
    float projection_[16] = {};
    std::vector<float> vertices_;

    static int glyphIndex(unsigned char c) {
        if (c < FIRST_CHAR || c >= FIRST_CHAR + NUM_CHARS) c = '?';
        return c - FIRST_CHAR;
    }

    bool loadFont(const char* path, float pixelHeight) {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            std::fprintf(stderr, "TextRenderer: cannot open font '%s'\n", path);
            return false;
        }
        std::vector<unsigned char> ttf((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());

        stbtt_fontinfo info;
        if (ttf.empty() || !stbtt_InitFont(&info, ttf.data(), stbtt_GetFontOffsetForIndex(ttf.data(), 0))) {
            std::fprintf(stderr, "TextRenderer: '%s' is not a valid TrueType font\n", path);
            return false;
        }

        // Line metrics, so draw() can take a top-left position and handle '\n'
        float scale = stbtt_ScaleForPixelHeight(&info, pixelHeight);
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
        ascent_     = ascent * scale;
        lineHeight_ = (ascent - descent + lineGap) * scale;

        // Bake glyphs into the smallest square atlas they fit in
        std::vector<unsigned char> bitmap;
        int size = 256;
        for (; size <= 4096; size *= 2) {
            bitmap.assign((size_t)size * size, 0);
            if (stbtt_BakeFontBitmap(ttf.data(), 0, pixelHeight, bitmap.data(), size, size,
                                     FIRST_CHAR, NUM_CHARS, glyphs_) > 0)
                break;
        }
        if (size > 4096) {
            std::fprintf(stderr, "TextRenderer: font size %.0f is too large to bake\n", pixelHeight);
            return false;
        }
        atlasSize_ = size;

        // Upload as a single-channel texture
        GLint prevAlignment, prevTexture;
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTexture);

        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   // 1 byte per pixel, rows are not 4-byte aligned
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, size, size, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);
        glBindTexture(GL_TEXTURE_2D, (GLuint)prevTexture);
        return true;
    }

    static GLuint compileStage(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        GLint ok = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
        if (!ok) {
            char log[1024];
            glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
            std::fprintf(stderr, "TextRenderer: shader compile error:\n%s\n", log);
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    bool createShader() {
        static const char* vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            layout(location = 1) in vec2 aUV;
            uniform mat4 uProjection;
            out vec2 vUV;
            void main() {
                vUV = aUV;
                gl_Position = uProjection * vec4(aPos, 0.0, 1.0);
            }
        )";
        static const char* fragmentSrc = R"(
            #version 330 core
            in vec2 vUV;
            uniform sampler2D uAtlas;
            uniform vec4 uColor;
            out vec4 FragColor;
            void main() {
                float coverage = texture(uAtlas, vUV).r;
                FragColor = vec4(uColor.rgb, uColor.a * coverage);
            }
        )";

        GLuint vs = compileStage(GL_VERTEX_SHADER, vertexSrc);
        GLuint fs = compileStage(GL_FRAGMENT_SHADER, fragmentSrc);
        if (!vs || !fs) {
            if (vs) glDeleteShader(vs);
            if (fs) glDeleteShader(fs);
            return false;
        }

        program_ = glCreateProgram();
        glAttachShader(program_, vs);
        glAttachShader(program_, fs);
        glLinkProgram(program_);
        glDeleteShader(vs);
        glDeleteShader(fs);

        GLint ok = GL_FALSE;
        glGetProgramiv(program_, GL_LINK_STATUS, &ok);
        if (!ok) {
            char log[1024];
            glGetProgramInfoLog(program_, sizeof(log), nullptr, log);
            std::fprintf(stderr, "TextRenderer: shader link error:\n%s\n", log);
            return false;
        }

        uProjection_ = glGetUniformLocation(program_, "uProjection");
        uColor_      = glGetUniformLocation(program_, "uColor");
        uAtlas_      = glGetUniformLocation(program_, "uAtlas");
        return true;
    }

    void createBuffers() {
        GLint prevVao, prevBuffer;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVao);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevBuffer);

        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        // 4 floats per vertex: x, y, u, v
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray((GLuint)prevVao);
        glBindBuffer(GL_ARRAY_BUFFER, (GLuint)prevBuffer);
    }

    void buildVertices(const std::string& text, float x, float y) {
        vertices_.clear();
        vertices_.reserve(text.size() * 24);

        float penX = x;
        float penY = y + ascent_;   // stb positions glyphs relative to the baseline
        for (unsigned char c : text) {
            if (c == '\n') {
                penX = x;
                penY += lineHeight_;
                continue;
            }
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(glyphs_, atlasSize_, atlasSize_, glyphIndex(c), &penX, &penY, &q, 1);
            if (q.x1 <= q.x0 || q.y1 <= q.y0) continue;   // spaces advance the pen but draw nothing

            const float quad[24] = {
                q.x0, q.y0, q.s0, q.t0,   q.x1, q.y0, q.s1, q.t0,   q.x1, q.y1, q.s1, q.t1,
                q.x0, q.y0, q.s0, q.t0,   q.x1, q.y1, q.s1, q.t1,   q.x0, q.y1, q.s0, q.t1,
            };
            vertices_.insert(vertices_.end(), quad, quad + 24);
        }
    }

    static GLState saveState() {
        GLState s;
        glGetIntegerv(GL_CURRENT_PROGRAM, &s.program);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &s.vao);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &s.arrayBuffer);
        glGetIntegerv(GL_ACTIVE_TEXTURE, &s.activeTexture);
        glActiveTexture(GL_TEXTURE0);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &s.texture2D);
        glGetIntegerv(GL_BLEND_SRC_RGB, &s.blendSrcRGB);
        glGetIntegerv(GL_BLEND_DST_RGB, &s.blendDstRGB);
        glGetIntegerv(GL_BLEND_SRC_ALPHA, &s.blendSrcAlpha);
        glGetIntegerv(GL_BLEND_DST_ALPHA, &s.blendDstAlpha);
        s.blend     = glIsEnabled(GL_BLEND);
        s.depthTest = glIsEnabled(GL_DEPTH_TEST);
        s.cullFace  = glIsEnabled(GL_CULL_FACE);
        return s;
    }

    static void setEnabled(GLenum cap, GLboolean on) {
        if (on) glEnable(cap); else glDisable(cap);
    }

    static void restoreState(const GLState& s) {
        glUseProgram((GLuint)s.program);
        glBindVertexArray((GLuint)s.vao);
        glBindBuffer(GL_ARRAY_BUFFER, (GLuint)s.arrayBuffer);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (GLuint)s.texture2D);
        glActiveTexture((GLenum)s.activeTexture);
        glBlendFuncSeparate((GLenum)s.blendSrcRGB, (GLenum)s.blendDstRGB,
                            (GLenum)s.blendSrcAlpha, (GLenum)s.blendDstAlpha);
        setEnabled(GL_BLEND, s.blend);
        setEnabled(GL_DEPTH_TEST, s.depthTest);
        setEnabled(GL_CULL_FACE, s.cullFace);
    }
};
