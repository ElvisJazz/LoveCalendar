#pragma once
#include "afxwin.h"
#include "PictureEx.h"

// GifDlg 对话框

class GifDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GifDlg)

public:
	GifDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GifDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CPictureEx  m_gif;
	CString m_tip;
};
