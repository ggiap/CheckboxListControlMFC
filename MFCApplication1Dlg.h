
// MFCApplication1Dlg.h : header file
//

#pragma once

#include <afxcmn.h>
#include <vector>
#include "CCheckableListCtrl.h"
#define IDC_MYLISTCONTROL_ID 1001

// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CCheckableListCtrl m_listCtrl;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	void InitializeListControl();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNMCustomdrawYourListControl(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};
