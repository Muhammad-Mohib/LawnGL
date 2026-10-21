#include "PeaBehaviour.h"
#include<iostream>
#include"../GameObject.h"
#include "GameInstances.h"
#include "ZombieBehaviour.h"

void PeaBehaviour::Start()
{
}

void PeaBehaviour::Update(float deltaTime)
{
	owner->transform.position += glm::vec2(200 * deltaTime, 0);

	if (owner->transform.position.x > 800) //800 screen width
	{
		Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(owner);
	}
    if (isSnowPal)
    {
        glm::vec4 frozen = { 0.3f, 0.5f, 1.0f, 1.0f };
        owner->GameObject_SpriteRenderer.Tint = frozen;
    }

    auto& myPosition = owner->transform.position;

    for (auto& zombie : Instances->_SpawnManager->Zombies)
    {
        if ((*zombie)->IsDestroyed || !(*zombie)->isActive) continue;

        constexpr float PEA_Y_OFFSET = 55.0f;   // pea.y - zombie.y = 55

        glm::vec2 zombiePos = (*zombie)->_AnimationController.Origin;

        bool sameRow = std::abs(myPosition.y - (zombiePos.y + PEA_Y_OFFSET)) < 20.0f;
        bool touching = myPosition.x >= zombiePos.x - 20.0f &&
            myPosition.x <= zombiePos.x + 80.0f;

        if (sameRow && touching)
        {
            (*zombie)->Health -= 10;

            if (isSnowPal)
            {
                (*zombie)->GetBehaviour<ZombieBehaviour>()->Speed = 9.0f;
                glm::vec4 frozen = { 0.55f, 0.75f, 1.0f, 1.0f };
                (*zombie)->GameObject_SpriteRenderer.Tint = frozen;
                for (const auto& entry : (*zombie)->_AnimationController.Parts)
                {
                    if (entry.second)
                        entry.second->GameObject_SpriteRenderer.Tint = frozen;
                }

                owner->GameObject_SpriteRenderer.Tint = frozen;
            }

            Instances->_SceneManager->GetCurrentScene()->DestroyGameObject(owner);
            break;
        }
    }
}
