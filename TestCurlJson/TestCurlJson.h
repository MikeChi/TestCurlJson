
// TestCurlJson.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestCurlJsonApp:
// �йش����ʵ�֣������ TestCurlJson.cpp
//

class CTestCurlJsonApp : public CWinApp
{
public:
	CTestCurlJsonApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestCurlJsonApp theApp;