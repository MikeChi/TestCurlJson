
// TestCurlJsonDlg.h : ͷ�ļ�
//

#pragma once


// CTestCurlJsonDlg �Ի���
class CTestCurlJsonDlg : public CDialogEx
{
// ����
public:
	CTestCurlJsonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTCURLJSON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
