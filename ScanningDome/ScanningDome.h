
// ScanningDome.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CScanningDomeApp: 
// �йش����ʵ�֣������ ScanningDome.cpp
//

class CScanningDomeApp : public CWinApp
{
public:
	CScanningDomeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CScanningDomeApp theApp;