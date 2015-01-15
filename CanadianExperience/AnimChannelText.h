/**
 * \file AnimChannelText.h
 *
 * \author Yiming Li
 *
 * \brief The AnimChannel Class to edit the text in the text 
 * bubble during the animation
 */

#pragma once
#include "AnimChannel.h"

/**
 * \brief The text AnimChannel to implement the the transfer on text
 */
class CAnimChannelText :
	public CAnimChannel
{
public:
	CAnimChannelText();
	~CAnimChannelText();
	/// \brief Get the text in the channel
	std::wstring GetText(){ return mText; }
	/// \brief Get if the text bubble is mirrored
	bool GetMirror(){ return mMirror; }

	/// \brief A ket frame for the text channel
	class KeyframeText : public Keyframe
	{
	public:
		/** \brief Constructor
		* \param channel The channel we are for
		* \param text The text for the keyframe 
		* \param mirror is mirror or not for the keyframe */
		KeyframeText(CAnimChannelText *channel, std::wstring text, bool mirror) :
			Keyframe(channel), mChannel(channel), mText(text), mMirror(mirror){}

		/** \brief Default constructor disabled */
		KeyframeText() = delete;
		/** \brief Copy constructor disabled */
		KeyframeText(const KeyframeText &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframeText &) = delete;

		/** \brief Get the text at this keyframe
		* \returns text in string */
		std::wstring GetText() { return mText; }

		/** \brief Get if the text bubble is mirrored or not at this keyframe
		* \returns true or not */
		bool GetMirror(){ return mMirror; }

		/** \brief Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** \brief Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** \brief Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mText = mText; }

		/** \brief Function to save the text in this keyfram*/
		virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	private:
		/// The keyframe text value
		std::wstring mText;
		/// The keyframe mirror value
		bool mMirror;
		/// The pointer to the text AnimChannel
		CAnimChannelText *mChannel;
	};

	/** \brief Set the keyframe with given text mirror value*/
	void SetKeyframe(std::wstring text, bool mirror);

	/** \The tween  function to set the text and mirror value 
	     Between two frames*/
	virtual void Tween(double t) override;

protected:
	/// \brief The Load function to load the saved setting from the Anim file
	virtual void XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

private:
	/// The text value
	std::wstring mText;
	
	/// The mirror value
	bool mMirror = false;

	/// The first angle keyframe
	KeyframeText *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeText *mKeyframe2 = nullptr;
};

