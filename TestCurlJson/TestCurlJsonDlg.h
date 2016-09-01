
// TestCurlJsonDlg.h : 头文件
//
#include "CvvImage.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

#pragma once


// CTestCurlJsonDlg 对话框
class CTestCurlJsonDlg : public CDialogEx
{
// 构造
public:
	CTestCurlJsonDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTCURLJSON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	char m_showDate;
	char m_show2;
	CString m_show;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
