/**
 * \file AnimChannelText.cpp
 *
 * \author Yiming Li
 */

#include "stdafx.h"
#include "AnimChannelText.h"
#include "Timeline.h"

using namespace std;
using namespace Gdiplus;

CAnimChannelText::CAnimChannelText()
{
}


CAnimChannelText::~CAnimChannelText()
{
}

/**
* \brief Set a keyframe
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param text point The text of ketframe
* \param mirror if the text bubble mirrored or not
*/
void CAnimChannelText::SetKeyframe(std::wstring text, bool mirror)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the text
	shared_ptr<KeyframeText> keyframe = make_shared<KeyframeText>(this, text, mirror);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/** \brief Save this keyframe to an XML node
* \param node The node we are going to be a child of
* \returns Allocated XML node.
*/
std::shared_ptr<xmlnode::CXmlNode> CAnimChannelText::KeyframeText::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CAnimChannel::Keyframe::XmlSave(node);
	itemNode->SetAttribute(L"text", mText);
	itemNode->SetAttribute(L"mirror", mMirror);
	return itemNode;
}

/**
* \brief Handle loading this channel's keyframe type
* \param node keyframe tag node
*/
void CAnimChannelText::XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	wstring text = node->GetAttributeValue(L"text", L"");
	bool mirror = node->GetAttributeIntValue(L"mirror", 0);
	// Set a keyframe there
	SetKeyframe(text, mirror);
}



/**
 * \brief set the text mirro value between two keyfreams
 * \param t time
 */
void CAnimChannelText::Tween(double t) {
	mText = mKeyframe1->GetText();
	mMirror = mKeyframe1->GetMirror();
}