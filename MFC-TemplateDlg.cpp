
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

#include "data/nlohmann.json.3.10.5/build/native/include/nlohmann/json.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <fstream>

// json library
using json = nlohmann::json;


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
	ON_BN_CLICKED(IDOK, &CMFCTemplateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCTemplateDlg message handlers

BOOL CMFCTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	// HERE IS WHERE YOU PUT YOUR onStart/ onInit/ onCreate CODE
	filename = L"data\\settings.json";

	// Reading from file
	readFromJson();

	return TRUE;  // return TRUE unless you set the focus to a control
}

std::string convertCStringToString(CString cstring) {
	CW2A asciiConverter(cstring); // convert CString (wide) to char*
	std::string str(asciiConverter); // create std::string from char*
	return str;
}

CString convertStringToCString(std::string string) {
	std::wstring wstring(string.begin(), string.end());
	CString cstring = wstring.c_str();
	return cstring;
}

json getJsonConfig(std::wstring filename) {
	// path to the JSON file
	std::wstring wstring = filename;
	LPCWSTR pathConfig = wstring.c_str();
	// doing a bunch of type conversions
	std::ifstream ifs_config(pathConfig);
	std::string content_config((std::istreambuf_iterator<char>(ifs_config)), (std::istreambuf_iterator<char>()));
	// parsed version of file
	json myjson_config = json::parse(content_config);
	return myjson_config;
}

void setJsonConfig(std::wstring filename, json myjson_config) {
	std::wstring wstring = filename;
	LPCWSTR pathConfig = wstring.c_str();
	std::ofstream outputModesFile(pathConfig);
	outputModesFile << std::setw(4) << myjson_config << std::endl;
}

void CMFCTemplateDlg::readFromJson() {

	// parsed version of file
	json myjson_config = getJsonConfig(filename);

	// setting up for radio button and option selection
	radioButton1Selected = myjson_config["radioButton1Selected"];
	// setting up initial states
	m_radioButton1.SetCheck(radioButton1Selected);
	m_radioButton2.SetCheck(!radioButton1Selected);

	// adding list for drop down menu
	for (std::string list_element : myjson_config["comboBoxList"]) {
		m_comboBox.AddString(convertStringToCString(list_element));
	}
	// if your list is in the wrong order, check if its sorted (in the dialog editor, not here)

	// setting up initial states
	m_comboBox.SetCurSel(myjson_config["current_selection"]);

	// setting up textEditBox
	m_textEditBox.SetWindowText(convertStringToCString(myjson_config["textEditText"]));

}
void CMFCTemplateDlg::writeToJson() {

	// get the current_config json
	json myjson_config = getJsonConfig(filename);

	// set all the fields

	// radio buttons
	myjson_config["radioButton1Selected"] = m_radioButton1.GetCheck() == 1;

	// current selection
	myjson_config["current_selection"] = m_comboBox.GetCurSel();

	// text edit box
	CString editBoxCString;
	m_textEditBox.GetWindowText(editBoxCString);
	myjson_config["textEditText"] = convertCStringToString(editBoxCString);

	// write to file
	setJsonConfig(filename, myjson_config);
}


void CMFCTemplateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
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
	// do not need to control setting check on this or the other
	// handled automatically as they are Radio Buttons
}


void CMFCTemplateDlg::OnBnClickedRadio2()
{
	// you dont need an onclick for this because you can just check if its checked before you save to json
	// this is an example to show an onClick function
}


void CMFCTemplateDlg::OnBnClickedOk()
{
	writeToJson();

	// closes the window
	CDialogEx::OnOK();
}
