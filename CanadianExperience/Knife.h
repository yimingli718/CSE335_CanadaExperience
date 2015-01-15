/**
 * \file Knife.h
 *
 * \author Yiming Li
 *
 * \brief Implement a knife for sparty
 */

#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPoint.h"



/**
 * \brief Implemnet the knife for sparty
 */
class CKnife :
	public CImageDrawable
{
public:
	CKnife(const std::wstring &name, const std::wstring &filename);    
	/** \brief Default constructor disabled */
	CKnife() = delete;
	/** \brief Copy constructor disabled */
	CKnife(const CKnife &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CKnife &) = delete;
	~CKnife();
	/// \brief Is this drawable moveable?
	/// \returns true
	virtual bool IsMovable() { return true; }
	void Draw(Gdiplus::Graphics *graphics);
	virtual void SetActor(CActor *actor) override;
	virtual void SetTimeline(CTimeline *timeline) override;
	virtual void SetKeyframe() override;
	virtual void GetKeyframe() override;
private:
	/// Channel for the head position
	CAnimChannelPoint mPositionChannel;
	CRotatedBitmap mKnife;        ///< Bitmap for the left eye
};

