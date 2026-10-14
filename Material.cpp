#include "Material.h"
#include "Shader.h"

Material::Material(std::string MaterialName, Shader* MaterialShader)
{
	Name = MaterialName;
	MatShader = MaterialShader;
}
