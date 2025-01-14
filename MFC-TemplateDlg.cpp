
// MFC-TemplateDlg.cpp : implementation file
//
// This is the dialog file (^^ Dlg in the name),
// where you want to edit code to change the main dialog.

// Author: Peter Ling

#include "pch.h"
#include "framework.h"
#include "MFC-Template.h"
#include "MFC-TemplateDlg.h"
#include "afxdialogex.h"
#include "atlconv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

//class CAboutDlg : public CDialogEx
//{
//public:
//	CAboutDlg();
//
//// Dialog Data
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_ABOUTBOX };
//#endif
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//// Implementation
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()


// CMFCTemplateDlg dialog



CMFCTemplateDlg::CMFCTemplateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEMPLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// linking the button ids to a control variable
	DDX_Control(pDX, IDC_RADIO1, m_radioButton1);
	DDX_Control(pDX, IDC_RADIO2, m_radioButton2);
	// if you need a large number of buttons with contiguous ids or need to add them to an array
	// you can make a for loop here
	// IDs just map to numbers which are 1000 + n for nth button created (started from n=0)

	DDX_Control(pDX, IDC_EDIT1, m_textEditBox);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
}

BEGIN_MESSAGE_MAP(CMFCTemplateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CMFCTemplateDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCTemplateDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CMFCTemplateDlg message handlers

BOOL CMFCTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	/*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
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
	}*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// HERE IS WHERE YOU PUT YOUR onStart/ onInit/ onCreate CODE

	filename = "data\\settings.json";

	// Reading from file
	readFromJson();

	// setting up initial states
	m_radioButton1.SetCheck(radioButton1Selected);
	m_radioButton2.SetCheck(!radioButton1Selected);

	m_comboBox.SetCurSel(optionSelected);



	return TRUE;  // return TRUE unless you set the focus to a control
}

std::string convertToStringFromCString(CString cstring) {
	CW2A asciiConverter(cstring); // Convert CString (wide) to char*
	std::string str(asciiConverter); // Create std::string from char*
	return str;
}

void CMFCTemplateDlg::readFromJson() {
	radioButton1Selected = true;
	optionSelected = 0;
	// if you list is in the wrong order, check if its sorted 
	m_comboBox.AddString(_T("list element 1"));
	m_comboBox.AddString(_T("list element 2"));
	m_comboBox.AddString(_T("list element 3"));

}
void CMFCTemplateDlg::writeToJson() {
	// CString is the MFC type
	CString editBoxCString;
	m_textEditBox.GetWindowText(editBoxCString);
	// converting to std::string as they are much easier to work with
	std::string editBoxString = convertToStringFromCString(editBoxCString);

	radioButton1Selected;
	optionSelected = m_comboBox.GetCurSel();
}


void CMFCTemplateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	/*if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{*/
	CDialogEx::OnSysCommand(nID, lParam);
	//}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTemplateDlg::OnPaint()
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
HCURSOR CMFCTemplateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Radio Button = only one in the group can be selected at once
// 
// on Click function for radio button 1
// referred to by its ID
// IDC_RADIO1
// double click on the tool on the Dialog and it will generate an onClick function
// The "Group" property determines with what it is a radio button
void CMFCTemplateDlg::OnBnClickedRadio1()
{
	radioButton1Selected = true;
	// do not need to control setting check on this or the other
	// handled automatically as they are Radio Buttons
}


void CMFCTemplateDlg::OnBnClickedRadio2()
{
	// you dont need an onclick for this because you can just check if its checked before you save to json
	// this is an example to show an onClick function
	radioButton1Selected = false;
}
