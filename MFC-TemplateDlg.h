
// MFC-TemplateDlg.h : header file
//

#pragma once
#include <string>


// CMFCTemplateDlg dialog
class CMFCTemplateDlg : public CDialogEx
{
// Construction
public:
	CMFCTemplateDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEMPLATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	std::string filename;
	void readFromJson();
	void writeToJson();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	bool radioButton1Selected;
	CButton m_radioButton1;
	CButton m_radioButton2;
	CEdit m_textEditBox;
};
