/**
 * \file ParticleSystem.h
 *
 * \author Yiming Li
 *
 * \brief Class for particle syystem of snow operation
 */

#pragma once
#include "LinkedList.h"
#include "Snowflake.h"
class CPictur;

/**
 * \brief The ParticleSystem to implement the snow draw and update
 */
class CParticleSystem
{
public:
	CParticleSystem();
	/** \brief Copy constructor disabled */
	CParticleSystem(const CParticleSystem &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CParticleSystem &) = delete;
	~CParticleSystem();
	void Draw(Gdiplus::Graphics *graphics/*, Gdiplus::SolidBrush *brush*/);
	void CParticleSystem::Update(double elapsed);
	/**
	* \brief Set the width of the snow
	*/
	void SetWidth(int w){ mWidth = w; }
	/**
	* \brief Set the height of the snow
	*/
	void SetHeight(int h){ mHeight = h; }
private:
	///The linked list to store the inactive snow flakes
	CLinkedList mInactive;
	///The linked list to store the active snow flakes
	CLinkedList mActive;
	///The height of the window to check if the snow flakes
	///fly out of the window
	int mHeight;
	///The weight of the window to check if the snow flakes
	///fly out of the window
	int mWidth;
};

