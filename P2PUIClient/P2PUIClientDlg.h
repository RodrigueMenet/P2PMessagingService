// P2PUIClientDlg.h : header file
//

#pragma once
#include "P2PClient.h"
#include "ZmqFactory.h"


// CP2PUIClientDlg dialog
class CP2PUIClientDlg : public CDialogEx
{
  // Construction
public:
  CP2PUIClientDlg(uint8_t UID, CWnd* pParent = nullptr);

  // Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_P2PUICLIENT_DIALOG };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


  // Implementation
protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnCbnSelchangeCombo1();
  afx_msg void OnBnClickedOk();
  afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
  void UpdateCombobox(const std::vector<int>& ids);
  uint8_t mUID;
  ZmqFactory mFactory;
  std::shared_ptr<IRequester> mServerRequester;
  std::shared_ptr<ISubscriber> mServerSubscriber;
  std::shared_ptr<IReplier> mPeerReplier;
  P2PClient mClient;
};
