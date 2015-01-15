/**
 * \file TextBubbleDrawable.h
 *
 * \author Yiming Li
 *
 * \brief The Text Bubble adapater class derived from the Drawable class
 */

#pragma once
#include "Drawable.h"
#include "TextBubble.h"
#include "AnimChannelPoint.h"
#include "AnimChannelText.h"



/**
 * \brief The text bubble class adpater
 */
class CTextBubbleDrawable :
	public CDrawable 
{
public:
	CTextBubbleDrawable(const std::wstring &name);
	virtual ~CTextBubbleDrawable();

	/** \brief Default constructor disabled */
	CTextBubbleDrawable() = delete;
	/** \brief Copy constructor disabled */
	CTextBubbleDrawable(const CTextBubbleDrawable &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTextBubbleDrawable &) = delete;

	/// \brief The Draw function to draw the text bubble
	virtual void Draw(Gdiplus::Graphics *graphics) override;
	/// \brief The Hittest function to check if the click 
	/// is in the text bubble
	virtual bool HitTest(Gdiplus::Point pos) override;

	/// \brief Check if the text bubble can be moved
	virtual bool IsMovable(){ return true; }

	/** \brief Check the drawable is TextBubbleDrawable
	* \returns a bool value*/
	virtual bool IsTextBubbleDrawable() override { return true; }

	/// \brief Get the text value from Text bubble class
	std::wstring GetText(){ return GetTextBubble()->GetText(); }
	/// \brief Get the mirror value from text bubbleclass
	bool GetMirror(){ return GetTextBubble()->GetMirror(); }

	void SetText(const std::wstring &str);

	void SetMirror(const bool &mirror);

	/// \brief Get the Text bubble this class adpated for
	virtual CTextBubble* GetTextBubble() override { return &mTextBubble; }
	
	void SetActor(CActor *actor);

	virtual void SetTimeline(CTimeline *timeline) override;

	virtual void SetKeyframe() override;
	
	virtual void GetKeyframe() override;

	/** \brief The position animation channel
	* \returns Pointer to animation channel */
	CAnimChannelText *GetTextChannel() { return &mTextChannel; }

private:
	/// the text bubble member variable
	CTextBubble mTextBubble;

	/// Channel for the head position
	CAnimChannelPoint mPositionChannel;

	/// Channel for the text and mirror value
	CAnimChannelText mTextChannel;
};

