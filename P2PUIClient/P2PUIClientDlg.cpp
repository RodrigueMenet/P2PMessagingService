// P2PUIClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "P2PUIClient.h"
#include "P2PUIClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CP2PUIClientDlg::CP2PUIClientDlg(uint8_t uid, CWnd* pParent /*=nullptr*/)
  : CDialogEx(IDD_P2PUICLIENT_DIALOG, pParent)
    , mUID(uid)
    , mServerRequester(mFactory.BuildRequester(BuildServerCompleteUrl(false)))
    , mServerSubscriber(mFactory.BuildSubscriber(BuildServerCompleteUrl(false)))
    , mPeerReplier(mFactory.BuildReplier(BuildPeerCompleteUrl(uid)))
    , mClient(*mServerRequester, *mServerSubscriber, *mPeerReplier, uid)
{
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CP2PUIClientDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CP2PUIClientDlg, CDialogEx)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_CBN_SELCHANGE(IDC_COMBO1, &CP2PUIClientDlg::OnCbnSelchangeCombo1)
  ON_BN_CLICKED(IDOK, &CP2PUIClientDlg::OnBnClickedOk)
  ON_WM_TIMER()
END_MESSAGE_MAP()


// CP2PUIClientDlg message handlers

BOOL CP2PUIClientDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon

  // TODO: Add extra initialization here
  mClient.Start();
  return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CP2PUIClientDlg::OnPaint()
{
  if(IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialogEx::OnPaint();
  }
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CP2PUIClientDlg::OnQueryDragIcon()
{
  return static_cast<HCURSOR>(m_hIcon);
}


void CP2PUIClientDlg::OnCbnSelchangeCombo1()
{
  // TODO: Add your control notification handler code here
}


void CP2PUIClientDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CDialogEx::OnOK();
}


void CP2PUIClientDlg::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: Add your message handler code here and/or call default


  CDialogEx::OnTimer(nIDEvent);
}
