#pragma once
#include "shockwaveflash1.h"


// CFlashDlg 对话框

class CFlashDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFlashDlg)

public:
	CFlashDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFlashDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 m_FlashShow;
};
