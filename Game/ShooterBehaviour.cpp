#include "ShooterBehaviour.h"
#include<iostream>
#include"GameInstances.h"
#include "RowButtons.h"
#include "PeaBehaviour.h"
#include"../GameObject.h"

void ShooterBehaviour::Start()
{
}

void ShooterBehaviour::Update(float deltaTime)
{

    if (owner->Health <= 0)
    {
        for (auto& [key, value] : owner->_AnimationController.Parts)
        {
            value->isActive = false;
            Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(value);
        }

        return;
    }
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
            std::cout << "Rwo" << " " << RowNo << std::endl;
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

    CheckPeaHit();

    ShootingTimer -= deltaTime;
    if (ShootingTimer <= 0)
    {
        Shoot();
        ShootingTimer = ShootingInterval;
    }
    std::cout << isShooting << " shoot \n";
}

void ShooterBehaviour::CheckPeaHit()
{
    
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
        pea->AddBehaviour<PeaBehaviour>();
        pea->GetBehaviour<PeaBehaviour>()->Instances = Instances;
        Peas["Pea_" + std::to_string(PeaCount)] = pea;

        //isShooting = false;
    }
}
