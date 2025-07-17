#include "actor.h"
#include "component.h"
#include "game.h"

Actor::Actor(Game* game)
    : mState(EActive), mPosition(Vector2::Zero), mScale(1.0f), mRotation(0.0f), mGame(game) {
    mGame->AddActor(this);
}

Actor::~Actor() {
    mGame->RemoveActor(this);

    while (!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime) {
    if (mState == EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (auto comp : mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::AddComponent(Component* component) {
    int order = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter) {
        if (order < (*iter)->GetUpdateOrder()) {
            break;
        }
    }

    mComponents.erase(iter);
}

void Actor::RemoveComponent(Component* component) {
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end()) {
        mComponents.erase(iter);
    }
}
