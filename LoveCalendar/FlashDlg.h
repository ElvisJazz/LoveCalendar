#pragma once
#include "shockwaveflash1.h"


// CFlashDlg �Ի���

class CFlashDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFlashDlg)

public:
	CFlashDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFlashDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 m_FlashShow;
};
