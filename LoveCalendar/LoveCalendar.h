
// LoveCalendar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLoveCalendarApp:
// �йش����ʵ�֣������ LoveCalendar.cpp
//

class CLoveCalendarApp : public CWinApp
{
public:
	CLoveCalendarApp();
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLoveCalendarApp theApp;