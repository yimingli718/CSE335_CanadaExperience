/**
 * \file TextBubbleDrawable.cpp
 *
 * \author Yiming Li
 */

#include "stdafx.h"
#include "TextBubbleDrawable.h"
#include "Timeline.h"
#include "Actor.h"

using namespace std;
using namespace Gdiplus;


/**
 * \brief Default constructor
 * \param name of the bubble
 */
CTextBubbleDrawable::CTextBubbleDrawable(const std::wstring &name) : CDrawable(name)
{
}


/**
 * \brief Destructor
 */
CTextBubbleDrawable::~CTextBubbleDrawable()
{
}


/**
 * \brief The draw function to draw the text bubble
 * \param graphics 
 */
void CTextBubbleDrawable::Draw(Gdiplus::Graphics *graphics){
	mTextBubble.SetBubblePosition(mPlacedPosition.X, mPlacedPosition.Y);
	mTextBubble.DrawMe(graphics);
}


/**
 * \brief The Histest function to check if the click is inside the text 
 *  bubble.
 * \param pos The click function 
 * \returns the bool value true or not
 */
bool CTextBubbleDrawable::HitTest(Gdiplus::Point pos)
{
	return mTextBubble.IsPointInside(pos.X, pos.Y);
}


/**
 * \brief Set the text value in the text bubble
 * \param str the text value
 */
void CTextBubbleDrawable::SetText(const std::wstring &str){
	mTextBubble.SetText(str);
}

/**
 * \brief Get the mirror value in the text bubble
 * \param mirror if the the text bubble is mirrored 
 *  or not
 */
void CTextBubbleDrawable::SetMirror(const bool &mirror){
	mTextBubble.SetMirrored(mirror);
}

/**
* \brief Set the timeline. The tells the channel the timeline
* \param timeline Timeline to set
*/
void CTextBubbleDrawable::SetTimeline(CTimeline *timeline)
{
	//CDrawable::SetTimeline(timeline);
	timeline->AddChannel(&mPositionChannel);
	timeline->AddChannel(&mTextChannel);
}


/** \brief Set the keyframe based on the current status.
*/
void CTextBubbleDrawable::SetKeyframe()
{
	//CDrawable::SetKeyframe();
	mPositionChannel.SetKeyframe(GetPosition());
	mTextChannel.SetKeyframe(GetText(),GetMirror());
}

/** \brief Get the current channel from the animation system.
*/
void CTextBubbleDrawable::GetKeyframe()
{
	//CDrawable::GetKeyframe();

	if (mPositionChannel.IsValid()){
		SetPosition(mPositionChannel.GetPoint());
	}

	if (mTextChannel.IsValid()){
		SetText(mTextChannel.GetText());
		SetMirror(mTextChannel.GetMirror());
	}
}

/**
* \brief Set the actor. This is where we set the channel name
* \param actor Actor to set
*/
void CTextBubbleDrawable::SetActor(CActor *actor)
{
	CDrawable::SetActor(actor);

	// Set the channel name
	mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");
	mTextChannel.SetName(actor->GetName() + L":" + GetName() + L"text");
}