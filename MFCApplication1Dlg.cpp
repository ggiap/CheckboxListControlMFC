
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_MYLISTCONTROL_ID, &CMFCApplication1Dlg::OnNMCustomdrawYourListControl)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	int numberOfItems = 4; // Change this as necessary
	m_listCtrl.m_checkboxStates.resize(numberOfItems, std::make_pair(false, false)); // Initialize all to unchecked

	CRect listRect(10, 10, 310, 210);

	m_listCtrl.Create(WS_BORDER | WS_VISIBLE | WS_CHILD | LVS_REPORT, listRect, this, IDC_MYLISTCONTROL_ID);
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_OWNERDRAWFIXED);
	m_listCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

	//m_listCtrl.InsertColumn(0, _T("Label and Checkboxes"), LVCFMT_LEFT, 200);
	//// Add rows with labels. Checkboxes will be added later.
	//m_listCtrl.InsertItem(0, _T("Row 1 Label"));
	//m_listCtrl.InsertItem(1, _T("Row 2 Label"));
	//m_listCtrl.InsertItem(3, _T("Row 3 Label"));
	//m_listCtrl.InsertItem(4, _T("Row 4 Label"));

	m_listCtrl.InsertColumn(1, _T("Item"), LVCFMT_LEFT, 120);

	// Initialize the list control with some items (parents and children)
	InitializeListControl();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::InitializeListControl()
{
	// Insert parent items into the list and mark them as expandable
	int parentIndex1 = m_listCtrl.InsertItem(LVIF_TEXT, 0, _T("Parent Item 1"), 0, 0, 0, 0);
	std::vector<CString> children1 = { _T("Child Item 1.1"), _T("Child Item 1.2") };
	m_listCtrl.AddExpandableItem(parentIndex1, children1);

	/*int parentIndex2 = m_listCtrl.InsertItem(LVIF_TEXT, 5, _T("Parent Item 2"), 0, 0, 0, 0);
	std::vector<CString> children2 = { _T("Child Item 2.1"), _T("Child Item 2.2"), _T("Child Item 2.3") };
	m_listCtrl.AddExpandableItem(parentIndex2, children2);*/
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnNMCustomdrawYourListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		// Request item-specific notifications
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_ITEMPREPAINT:
	{
		CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		CRect rcItem;
		m_listCtrl.GetItemRect(nItem, &rcItem, LVIR_BOUNDS);

		// Draw the checkbox
		CRect rcFirstCheckbox(rcItem);
		rcFirstCheckbox.DeflateRect(5, (rcItem.Height() - m_listCtrl.checkboxSize) / 2);
		rcFirstCheckbox.right = rcFirstCheckbox.left + m_listCtrl.checkboxSize;

		CRect rcSecondCheckbox(rcFirstCheckbox);
		rcSecondCheckbox.OffsetRect(m_listCtrl.checkboxSize + m_listCtrl.checkboxGap, 0);

		UINT firstCheckboxStyle = DFCS_BUTTONCHECK | (m_listCtrl.m_checkboxStates[nItem].first ? DFCS_CHECKED : 0);
		UINT secondCheckboxStyle = DFCS_BUTTONCHECK | (m_listCtrl.m_checkboxStates[nItem].second ? DFCS_CHECKED : 0);

		pDC->DrawFrameControl(rcFirstCheckbox, DFC_BUTTON, firstCheckboxStyle);
		pDC->DrawFrameControl(rcSecondCheckbox, DFC_BUTTON, secondCheckboxStyle);

		// Offset for the text
		int offset = rcFirstCheckbox.Width() + rcSecondCheckbox.Width() + 15;

		CString str;
		str.Format(_T("%d"), nItem);
		// Draw the text
		CString itemText = _T("Item ") + str;
		pDC->TextOutW(rcItem.left + offset, rcItem.top + 5, itemText);

		int nnItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		if (m_listCtrl.IsItemExpandable(nnItem)) // Your method to check if the item is expandable
		{
			// Assuming a 16x16 icon size
			const int iconSize = 16;
			// Margin from the right edge of the control
			const int marginRight = 180;

			// Get the list control's width
			CRect rcList;
			m_listCtrl.GetClientRect(&rcList);
			int listWidth = rcList.Width();

			// Calculate icon's X position (aligned to the right)
			int iconX = listWidth - iconSize - marginRight;
			// Calculate icon's Y position (centered vertically within the item's row)
			RECT itemRect;
			m_listCtrl.GetItemRect(nnItem, &itemRect, LVIR_BOUNDS);
			int iconY = itemRect.top + (itemRect.bottom - itemRect.top - iconSize) / 2;

			// Get the system image list containing the arrow icons
			SHFILEINFO sfi;
			HIMAGELIST hImageList = reinterpret_cast<HIMAGELIST>(SHGetFileInfo(L"C:\\",
				0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON));

			if (hImageList != nullptr)
			{
				// Assuming you want to use a specific arrow icon, adjust the index as needed
				int iconIndex = 10; // Example index, you might need to find the correct index for an arrow
				ImageList_Draw(hImageList, iconIndex, pLVCD->nmcd.hdc, iconX, iconY, ILD_TRANSPARENT);
			}
		}

		*pResult = CDRF_SKIPDEFAULT; // We've drawn everything
		break;
	}

	}
}

