//------------------------------------------------------------------------------
/*!
\file	GameObject.cpp
\author	Ash (a.blankenship), Riti (r.bhatwal), Zak (zak.s), Rey (rey.rosario)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "GameObject.h"
#include "framework.h"
#include "ComponentCollider.h"
#include "ComponentGraphics.h"
#include "ComponentPhysics.h"
#include "ComponentTransform.h"
#include "ComponentFreeze.h"

#include <stdlib.h>
#include "JsonLoader.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
 
GameObject::GameObject()
{
	this->Collider = NULL;
	this->isDestroyed = false;
	this->Physics = NULL;
	this->Graphic = NULL;
	this->ParticleGraphic = NULL;
	this->Transform =  new ComponentTransform();
	this->Transform->SetParent(this);
	this->Freeze = NULL;
	this->OverlaySprites = NULL;
	this->Parent = NULL;
	this->Child = NULL;
	this->LightSource = NULL;
	this->DrawInUISpace = false;
	this->Visible = true;
	//this->ParticleSystem = new ComponentParticleSystem();
	//this->ParticleSystem->SetParent(this);


    LastAnimation = -1;
}



void GameObject::Read(Stream stream)
{

}

 ComponentPhysicsPtr GameObject::GetPhysics() const
{
	if (this->Physics)
	{
		return this->Physics;
	}
	else
	{
		return NULL;
	}
}
 ComponentSpritePtr GameObject::GetSprite() const
 {
	 if (this->Sprite)
	 {
		 return this->Sprite;
	 }
	 else
	 {
		 return NULL;
	 }
 }
 ComponentGraphicPtr GameObject::GetGraphic() const
 {
	 if (this->Graphic)
	 {
		 return this->Graphic;
	 }
	 else
	 {
		 return NULL;
	 }
 }

 ComponentGraphicPtr GameObject::GetParticleGraphic() const
 {
	 if (this->ParticleGraphic)
	 {
		 return this->ParticleGraphic;
	 }
	 else
	 {
		 return NULL;
	 }
 }

 ComponentBehaviorPtr GameObject::GetBehavior() const
 {
	 if (this->Behavior)
	 {
		 return this->Behavior;
	 }
	 else
	 {
		 return NULL;
	 }
 }

 ComponentParticleSystemPtr GameObject::GetParticleSystem() const
 {
	 if (this->ParticleSystem)
	 {
		 return this->ParticleSystem;
	 }
	 else
	 {
		 return NULL;
	 }
 }
 animationPtr GameObject::GetAnimation() const
 {
	 if (this->animation)
	 {
		 return this->animation;
	 }
	 else
	 {
		 return NULL;
	 }
 }
ComponentColliderPtr GameObject::GetCollider() const
{
	if (this->Collider)
	{
		return this->Collider;
	}
	else
	{
		return NULL;
	}
}
ComponentTransformPtr GameObject::GetTransform() const
{
	if (this->Transform)
	{
		return this->Transform;
	}
	else
	{
		return NULL;
	}
}

ComponentFreeze* GameObject::GetFreeze() const
{
	if (this->Freeze)
	{
		return this->Freeze;
	}
	else
	{
		return NULL;
	}
}

void GameObject::SetFreeze(ComponentFreeze* Freeze)
{
	this->Freeze = Freeze;
	Freeze->SetParent(this);
}

ComponentOverlaySprites* GameObject::GetOverlaySprites() const
{
	if (this->OverlaySprites)
	{
		return this->OverlaySprites;
	}
	else
	{
		return NULL;
	}
}

void GameObject::SetOverlaySprites(ComponentOverlaySprites* OverlaySprites)
{
	this->OverlaySprites = OverlaySprites;
	OverlaySprites->SetParent(this);
}

const char* GameObject::GetName()
{
		return this->name.c_str();

}
void GameObject::SetPhysics(ComponentPhysicsPtr physics)
{
	this->Physics = physics;
	physics->SetParent(this);
}

void GameObject::SetCollider(ComponentColliderPtr collider)
{
	this->Collider = collider;
	collider->SetParent(this);
}
void GameObject::SetTransform(ComponentTransformPtr transform)
{
	this->Transform = transform;
	transform->SetParent(this);
}
void GameObject::SetGraphic(ComponentGraphicPtr graphic)
{
	this->Graphic = graphic;
	//Graphic->SetParent(this);
}

void GameObject::SetParticleGraphic(ComponentGraphicPtr graphic)
{
	this->ParticleGraphic = graphic;
}

void GameObject::SetSprite(ComponentSpritePtr sprite)
{
	this->Sprite = sprite;
}

void GameObject::SetParent(GameObject* Parent)
{
	this->Parent = Parent;
	if (Parent)
	{
		Parent->Child = this;
	}
}
GameObject* GameObject::GetParent()
{
	return this->Parent;
}


void GameObject::SetChild(GameObject* Child)
{
	this->Child = Child;
	if (Child)
	{
		Child->Parent = this;
	}
}
GameObject* GameObject::GetChild()
{
	return this->Child;
}
void GameObject::SetParticleSystem(ComponentParticleSystemPtr particle)
{
	this->ParticleSystem = particle;
}

void GameObject::SetAnimation(animationPtr animation) {
	this->animation = animation;
	animation->Parent(this);
}



std::vector<AnimationData> GameObject::GetAnimationList() const
{
	return AnimationDataList;
}

int GameObject::GetCurrentAnimationIndexInList() const
{
	return LastAnimation;
}

void GameObject::CreateAndAddAnimation(const char* AnimationFileName, const char* SpriteSourceFileName, ImageManager* ImgManager, Shader* shader)
{
	Animation* NewAnimation = new Animation;


	//Step one: building a unique string for image data ID
	std::stringstream ss;
	ss << "Animation file name" << AnimationFileName << " ID name " << NewAnimation; //writes the address of this new animation as a string
	std::string UniqueImageDataID = ss.str();

	ImageData* Data = ImgManager->GetImageFromDrawingSystem(UniqueImageDataID.c_str());
	if (!Data)
	{
		Data = ImgManager->AddImageToDrawingSystem(true, SpriteSourceFileName, UniqueImageDataID.c_str(), false, true);
	}
	NewAnimation->ReadAniJson(AnimationFileName);
	NewAnimation->Parent(this);

	AnimationData AnimData;
	AnimData.AnimComponent = NewAnimation;
	AnimData.ImageDataID = Data->ImageDataID;


	AnimationDataList.push_back(AnimData);
	this->ImgManager = ImgManager;

}

void GameObject::SetCurrentAnimation(int AniIndex)
{
	if (LastAnimation != AniIndex)
	{
		if (AniIndex < AnimationDataList.size())
		{
			ImageData* Data = ImgManager->GetImageFromDrawingSystem(AnimationDataList[AniIndex].ImageDataID);
			if (Data)
			{
				SetGraphic(Data->Graphic);
				SetSprite(Data->Sprite);
				SetAnimation(AnimationDataList[AniIndex].AnimComponent);

				//AnimationDataList[AniIndex].AnimComponent->Reset();
				AnimationDataList[AniIndex].AnimComponent->Play();
				LastAnimation = AniIndex;
			}
		}
	}
}

bool GameObject::HasAnimations()
{
	if (AnimationDataList.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	//returns false if there are no animations attached to this game object
}

void GameObject::SetBehavior(ComponentBehaviorPtr behavior) {
	this->Behavior = behavior;
	behavior->setParent(this);
}
void GameObject::SetName(std::string name)
{
	this->name = name;
}
void GameObject::SetName(std::string name, int format)
{
	this->name = name;
}
void GameObject::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}
bool GameObject::CheckDestroyed() const
{
	return this->isDestroyed;
}

void GameObject::Destroy()
{
    isDestroyed = true;
}

void GameObject::SetDrawInUISpace(bool flag)
{
	DrawInUISpace = flag;
}
bool GameObject::IsInUISpace()
{
	return DrawInUISpace;
}

void GameObject::SetVisible(bool flag)
{
    Visible = flag;
}
bool GameObject::IsVisible()
{
	return Visible;
}
void GameObject::EmmitLight(float Radius, float Intensity)
{
	if (!LightSource)
	{
		LightSource = new ComponentLight(Radius, Intensity);
	}
}

ComponentLight* GameObject::GetLightComponent()
{
	return LightSource;
}

GameObject::~GameObject()
{
	delete(this->Collider);//this calls the collider destructor
	this->isDestroyed = true;
	delete(this->Physics);//this calls the physics destructor
	delete(this->Transform);//this calls the transform destructor
	for (int i = 0; i < AnimationDataList.size(); i++)
	{
		delete(AnimationDataList[i].AnimComponent);
		//delete(AnimationDataList[i].AnimGraphicComponent);
		//delete(AnimationDataList[i].AnimSprComponent);
	}
	AnimationDataList.clear();
	delete(this->Behavior);
	delete(Freeze);
	delete(OverlaySprites);
	if (Child)
	{
		Child->Destroy();
	}
	if (LightSource)
	{
		delete (LightSource);
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

