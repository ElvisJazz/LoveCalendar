#pragma once
#include "afxwin.h"
#include "PictureEx.h"

// GifDlg �Ի���

class GifDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GifDlg)

public:
	GifDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GifDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CPictureEx  m_gif;
	CString m_tip;
};
