/** \file TextBubble.h
*
* \brief This class implements a basic text bubble control.
*
* \author Charles B. Owen
* \version 1.00 10-28-2010 Original development in wxWidgets
* \version 2.00 10-28-2014 MFC version
* \version 2.01 11-14-2014 Removed inline functions from headers
*/

#pragma once

#include <string>
#include <vector>
#include <memory>

/// \cond
#ifdef TEXTBUBBLE_DLL
#define TBEXPORT __declspec( dllexport )
#else
#define TBEXPORT __declspec( dllimport )
#endif
/// \endcond

/*! \brief Basic text bubble support class
*/
class TBEXPORT CTextBubble
{
public:
    CTextBubble();
    virtual ~CTextBubble();

    /** \brief Copy constructor disabled */
    CTextBubble(const CTextBubble &) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CTextBubble &) = delete;

    void DrawMe(Gdiplus::Graphics *graphics);
    bool IsPointInside(int x, int y);

    std::wstring GetText() const;

    void SetText(const std::wstring &str);
    bool GetMirror() const;
    void SetMirrored(bool m);
    bool IsMirrored();
    void SetBubblePosition(int x, int y);
    int GetX() const;
    int GetY() const;

private:
    void NewString(Gdiplus::Graphics *graphics);

    bool     mMirror = false;       ///< Should we mirror the text box?
    std::wstring mText;             ///< The unadulterated text
    Gdiplus::Point  mPosition= Gdiplus::Point(200, 200);    ///< Position for the tip of the text bubble

    bool     mNewString = true;     ///< Set true when the string changes

    std::unique_ptr<Gdiplus::Bitmap> mBubble; ///< Text bubble image
    int      mBubbleWid = 0;        ///< Width to draw the bubble
    int      mBubbleHit = 0;        ///< Height to draw the bubble

    //! The array of string objects that holds the split text
    std::vector<std::wstring> mSplitText;

    std::unique_ptr<Gdiplus::Font> mFont;   ///< The font we will use
};
