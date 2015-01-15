/**
 * \file Knife.cpp
 *
 * \author Yiming Li
 */

#include "stdafx.h"
#include "Knife.h"
#include "Actor.h"
#include "Timeline.h"

#include <sstream>
#include <iomanip>

using namespace Gdiplus;
using namespace std;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/** \brief Constructor for a knife object
* \param name The drawable name to use
* \param filename The filename for the image to use
*/
CKnife::CKnife(const std::wstring &name, const std::wstring &filename) : CImageDrawable(name, filename)
{
}


/**
 * \brief Destructor
 */
CKnife::~CKnife()
{
}

/**
* \brief Set the actor. This is where we set the channel name
* \param actor Actor to set
*/
void CKnife::SetActor(CActor *actor)
{
	CImageDrawable::SetActor(actor);

	// Set the channel name
	mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");

}

/**
* \brief Set the timeline. The tells the channel the timeline
* \param timeline Timeline to set
*/
void CKnife::SetTimeline(CTimeline *timeline)
{
	CImageDrawable::SetTimeline(timeline);

	timeline->AddChannel(&mPositionChannel);
}

/** \brief Set the keyframe based on the current status.
*/
void CKnife::SetKeyframe()
{
	CImageDrawable::SetKeyframe();

	mPositionChannel.SetKeyframe(GetPosition());
}

/** \brief Get the current channel from the animation system.
*/
void CKnife::GetKeyframe()
{
	CImageDrawable::GetKeyframe();

	if (mPositionChannel.IsValid())
		SetPosition(mPositionChannel.GetPoint());
}

/**
* \brief Draw the head
* \param graphics Graphics context to draw on
*/
void CKnife::Draw(Gdiplus::Graphics *graphics)
{
	CImageDrawable::Draw(graphics);
}

