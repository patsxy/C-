
// mdhscollection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmdhscollectionApp:
// �йش����ʵ�֣������ mdhscollection.cpp
//

class CmdhscollectionApp : public CWinApp
{
public:
	CmdhscollectionApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmdhscollectionApp theApp;