/**
 * \file MainFrm.cpp
 *
 * Implementation of the CMainFrame class
 * \author  Yiming Li
 */

#include "stdafx.h"
#include "CanadianExperience.h"

#include "MainFrm.h"

#include "ViewTop.h"
#include "Picture.h"
#include "PictureFactory.h"
#include "TimelineDlg.h"
#include "TextBubbleDlg.h"
#include "Actor.h"


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_EDIT_MOVE, &CMainFrame::OnEditMove)
    ON_UPDATE_COMMAND_UI(ID_EDIT_MOVE, &CMainFrame::OnUpdateEditMove)
    ON_COMMAND(ID_EDIT_ROTATE, &CMainFrame::OnEditRotate)
    ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE, &CMainFrame::OnUpdateEditRotate)
    ON_COMMAND(ID_EDIT_TIMELINEPROPERTIES, &CMainFrame::OnEditTimelineproperties)
	ON_COMMAND(ID_EDIT_TEXTBUBBLEFORSPARTY, &CMainFrame::OnEditTextbubbleforsparty)
	ON_COMMAND(ID_EDIT_TEXTBUBBLEFORHAROLD, &CMainFrame::OnEditTextbubbleforharold)
	ON_COMMAND(ID_PLAY_PLAY, &CMainFrame::OnPlayPlay)
	ON_WM_TIMER()
	ON_COMMAND(ID_PLAY_PLAYFROMBEGINNNING, &CMainFrame::OnPlayPlayfrombeginnning)
	ON_COMMAND(ID_PLAY_STOP, &CMainFrame::OnPlayStop)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/** \brief Constructor */
CMainFrame::CMainFrame()
{
}

/** \brief Destructor */
CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockPane(&m_wndToolBar);
    // enable Visual Studio 2005 style docking window behavior
    CDockingManager::SetDockingMode(DT_SMART);
    // enable Visual Studio 2005 style docking window auto-hide behavior
    EnableAutoHidePanes(CBRS_ALIGN_ANY);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the edit window
	//m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
    // Route the command to each of the child windows
    if(mViewEdit->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

    if (mViewActors->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

    if (mViewTimeline->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    {
        return TRUE;
    }

	// otherwise, do default handling
	return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    if (!mWndSplitter.CreateStatic(this, 2, 1))
    {
        TRACE("Failed to create splitter window");
        return FALSE;
    }

    CRect rect;

    GetClientRect(&rect);
    mWndSplitter.CreateView(0, 0, RUNTIME_CLASS(CViewTop), CSize(0, 0), pContext);
    mWndSplitter.CreateView(1, 0, RUNTIME_CLASS(CViewTimeline), CSize(0, 0), pContext);

    mViewTimeline = (CViewTimeline *)mWndSplitter.GetPane(1, 0);
    CViewTop *viewTop = (CViewTop *)mWndSplitter.GetPane(0, 0);

    mViewActors = viewTop->GetViewActors();
    mViewEdit = viewTop->GetViewEdit();

    Initialize();

    return TRUE;
}

/** \brief Handle a Size request from Windows
 * 
 * This function ensures the child windows are the correct size
 * on the screen after the main window is resized 
 * \param nType Type of resizing message
 * \param cx The new width
 * \param cy The new height */
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    // Upcall the base class version
    CFrameWndEx::OnSize(nType, cx, cy);

    // Get the client area without the toolbar and status bar
    CRect rect;
    GetDockingManager()->GetClientAreaBounds(rect);
    mWndSplitter.MoveWindow(rect);

    // Make the children the right size
    int editHeight = rect.Height() - CViewTimeline::Height;
    if (editHeight < 0) 
    {
        editHeight = 0;
    }
    mWndSplitter.SetRowInfo(0, editHeight, 0);
    mWndSplitter.SetRowInfo(1, CViewTimeline::Height, 0);
    mWndSplitter.RecalcLayout();
}

/** \brief Called to erase the background. Disabled so we don't get flicker 
 * \param pDC A device context 
 * \returns FALSE */
BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** \brief Handle the Edit>Mode menu option */
void CMainFrame::OnEditMove()
{
    mMode = Move;
}


/** \brief Update the menu for Edit>Move 
 * \param pCmdUI The pointer to the control user interface */
void CMainFrame::OnUpdateEditMove(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mMode == Move);
}


/** \brief Handle the Edit>Rotate menu option */
void CMainFrame::OnEditRotate()
{
    mMode = Rotate;
}


/** \brief Update the menu for Edit>Rotate
* \param pCmdUI The pointer to the control user interface */
void CMainFrame::OnUpdateEditRotate(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(mMode == Rotate);
}


/** \brief Code to initialize the system */
void CMainFrame::Initialize()
{
    //
    // Create the picture
    //

    // Create our picture
    CPictureFactory factory;
    mPicture = factory.Create();

    //
    // Create the associations with the child windows 
    //

    mViewEdit->SetMainFrame(this);
    mViewActors->SetMainFrame(this);
    mViewTimeline->SetMainFrame(this);

    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewActors->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);

    mPicture->UpdateObservers();
}


/** \brief Handle the Edit/Timeline Properties menu option
*/
void CMainFrame::OnEditTimelineproperties()
{
    CTimelineDlg dlg;
    dlg.SetTimeline(mPicture->GetTimeline());
    if (dlg.DoModal() == IDOK)
    {
        dlg.Take();
        mPicture->UpdateObservers();
    }
}




/**
 * \brief Handle the Text Bubble for Sparty Menu option
 */
void CMainFrame::OnEditTextbubbleforsparty()
{
	// TODO: Add your command handler code here
	CTextBubbleDlg dlg;
	dlg.SetTextBubble(mPicture->GetSparty()->GetTextBubbleDrawable()->GetTextBubble());
	if (dlg.DoModal() == IDOK){
		dlg.Take();
		mPicture->UpdateObservers();
	}
}



/**
 * \brief Handle the Text Bubble for HAROLD Menu option
 */
void CMainFrame::OnEditTextbubbleforharold()
{
	// TODO: Add your command handler code here
	CTextBubbleDlg dlg;
	dlg.SetTextBubble(mPicture->GetHarold()->GetTextBubbleDrawable()->GetTextBubble());
	if (dlg.DoModal() == IDOK){
		dlg.Take();
		mPicture->UpdateObservers();
	}
}


/**
 * \brief Handle the Play Menu Option
 */
void CMainFrame::OnPlayPlay()
{
	/*SetTimer(1, mPicture->GetTimeline()->GetFrameRate(), nullptr);
	mLastTime = (double) mPicture->GetTimeline()->GetCurrentFrame() / mPicture->GetTimeline()->GetFrameRate();
	mPlay = true;*/
	if (!mPlay)
	{
		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

		// Set playing true
		mPlay = true;
		mPicture->SetPlay(true);

		// Start the timer
		SetTimer(1, 30, nullptr);
	}

}



/**
 * \brief The timer to track the time on play.
 * \param nIDEvent 
 */
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	auto timeline = mPicture->GetTimeline();

	/*
	* Compute the elapsed time since the last timer call
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mPicture->SetAnimationTime(mPicture->GetAnimationTime() + elapsed);

	if (mPicture->GetAnimationTime() >= timeline->GetDuration())
	{
		OnPlayStop();
		mPicture->SetAnimationTime(timeline->GetDuration());
	}

	mPicture->GetParticleSystem()->Update(elapsed);

	__super::OnTimer(nIDEvent);
}


/**
 * \brief Handle play from beginning menu option
 */
void CMainFrame::OnPlayPlayfrombeginnning()
{
	/*SetTimer(1, mPicture->GetTimeline()->GetDuration(), nullptr);
	mLastTime = 0;
	mPlay = true;*/
	mPicture->SetAnimationTime(0);

	OnPlayPlay();

}


/**
 * \brief Handle stop the play menu option
 */
void CMainFrame::OnPlayStop()
{
	if (mPlay)
	{
		KillTimer(1);
		mPlay = false;
		mPicture->SetPlay(false);
		mPicture->UpdateObservers();
	}
}
