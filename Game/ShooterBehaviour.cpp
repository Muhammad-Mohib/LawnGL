#include "ShooterBehaviour.h"
#include<iostream>
#include"GameInstances.h"
#include "RowButtons.h"

void ShooterBehaviour::Start()
{
}

void ShooterBehaviour::Update(float deltaTime)
{
    if (RowNo == 1)
    {
        if (Instances->_RowButtons->First)
        {
            isShooting = true;
        }
        else
        {
            isShooting = false;
        }
    }
    else if (RowNo == 2)
    {
        if (Instances->_RowButtons->Second)
        {
            isShooting = true;
        }
        else
        {
            isShooting = false;
        }
    }
    else if (RowNo == 3)
    {
        if (Instances->_RowButtons->Third)
        {
            isShooting = true;
        }
        else
        {
            isShooting = false;
        }
    }
    else if (RowNo == 4)
    {
        if (Instances->_RowButtons->Fourth)
        {
            isShooting = true;
        }
        else
        {
            isShooting = false;
        }
    }
    else if (RowNo == 5)
    {
        if (Instances->_RowButtons->Fifth)
        {
            isShooting = true;
        }
        else
        {
            isShooting = false;
        }
    }

    if (!isShooting) return;

    ShootingTimer -= deltaTime;
    if (ShootingTimer <= 0)
    {
        Shoot();
        ShootingTimer = ShootingInterval;
    }

    for (auto& pea : Peas)
    {
        pea.second->transform.position += glm::vec2(200*deltaTime,0);
    }
}

void ShooterBehaviour::Shoot()
{
    if (isShooting)
    {
        static unsigned int PeaCount = 0;
        std::cout << "Shooooting.." << "\n";
        auto* scene = Instances->_SceneManager->GetCurrentScene();
        auto* pea = scene->CreateGameObject("Pea_" + std::to_string(PeaCount++),
            "Plant", "Pea", "Default", "");
        pea->transform.position = owner->transform.position;
        glm::vec2 texSize = { (float)pea->GameObject_SpriteRenderer.Sprite->textureSize[0], (float)pea->GameObject_SpriteRenderer.Sprite->textureSize[1] };
        glm::vec2 unitySize = texSize / 100.0f;
        pea->transform.position = owner->_AnimationController.Origin + glm::vec2(40.0f, 35.0f);
        pea->transform.scale = texSize * 0.6f;
        std::cout << "tex: " << texSize.x << ", " << texSize.y
            << "  scale: " << pea->transform.scale.x << ", " << pea->transform.scale.y << "\n";

        Peas["Pea_" + std::to_string(PeaCount)] = pea;

        //isShooting = false;
    }
}
