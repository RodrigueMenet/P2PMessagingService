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
    , mServerSubscriber(mFactory.BuildSubscriber(BuildServerCompleteUrl(true)))
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

UINT_PTR PEER_TIMER;


BOOL CP2PUIClientDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  SetWindowText((std::wstring(L"P2PUiClient ") + std::to_wstring(mUID)).c_str());

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon

  mClient.Start();

  const auto peers = mClient.ConnectToServer();
  UpdateCombobox(peers);

  SetTimer(PEER_TIMER, 100, nullptr);
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


void CP2PUIClientDlg::UpdateCombobox(const std::vector<int>& peerIds)
{
  if(peerIds.empty() == false)
  {
    auto combo_box = reinterpret_cast<CComboBox*>(GetDlgItem(IDC_COMBO1));
    combo_box->ResetContent();
    for(const auto& peer : peerIds)
    {
      combo_box->AddString(std::to_wstring(peer).c_str());
    }
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
  if(nIDEvent == PEER_TIMER)
  {
    const auto list_peer = mClient.ReceiveMessageFromServer(10);
    UpdateCombobox(list_peer);
  }

  CDialogEx::OnTimer(nIDEvent);
}
