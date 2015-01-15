/**
 * \file ParticleSystem.cpp
 *
 * \author Yiming Li
 */

#include "stdafx.h"
#include "ParticleSystem.h"
#include "Picture.h"
#include <vector>
using namespace::Gdiplus;

/**
 * \brief Constructor
 */
CParticleSystem::CParticleSystem()
{
	for (int i = 0; i < 1000; i++){
		std::shared_ptr<CSnowflake> snowflake = std::make_shared<CSnowflake>();
		mInactive.Insert(snowflake);
	}
}


/**
 * \brief Destructor
 */
CParticleSystem::~CParticleSystem()
{
}


/** \brief Draw the snowflakes in the linked list
* \param graphics The device context to draw on
* \param brush The color to draw with
*/
void CParticleSystem::Draw(Gdiplus::Graphics *graphics/*, Gdiplus::SolidBrush *brush*/){
	for (int i = 0; i <= 10; i++){
		auto flake = mInactive.Popfront();
		flake->SetPosition(rand() % mWidth, 0);
		mActive.Insert(flake);
	}

	auto snowflake = mActive.GetHead();
	while (snowflake != mActive.GetTail()){
		snowflake->Draw(graphics/*, brush*/);
		snowflake = snowflake->GetNext();
	}
}


/**
 * \brief The update function to update each fleak in the linked list
 * \param elapsed The time between two updates
 */
void CParticleSystem::Update(double elapsed){
	for (int i = 0; i <= 10; i++){
		std::shared_ptr<CSnowflake> temp = std::make_shared<CSnowflake>();
		mInactive.Insert(temp);
	}

	auto snowflake = mActive.GetHead();
	std::vector<std::shared_ptr<CSnowflake>> Vec;
	while (snowflake != nullptr){
		snowflake->Update(elapsed);
		if (snowflake->GetPositionY() >= mHeight)
		{
			Vec.push_back(snowflake);
		}
		snowflake = snowflake->GetNext();
	}
	for (int i = 0; i < Vec.size(); i++){
		mActive.Remove(Vec[i]);
	}
}