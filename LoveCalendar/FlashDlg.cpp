// FlashDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LoveCalendar.h"
#include "FlashDlg.h"
#include "afxdialogex.h"


// CFlashDlg 对话框

IMPLEMENT_DYNAMIC(CFlashDlg, CDialogEx)

CFlashDlg::CFlashDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFlashDlg::IDD, pParent)
{

}

CFlashDlg::~CFlashDlg()
{
}

void CFlashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_FlashShow);
}

BOOL CFlashDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	RECT rc;

	this->GetClientRect(&rc);//获得客户区的坐标

	//调整flash的位置
	/*rc.left=rc.right/2-200;
	rc.right=rc.right/2+200;
	rc.top+=40;
	rc.bottom=rc.bottom/2;
	m_FlashShow.MoveWindow( &rc, true );
	*/
	TCHAR strCurDrt[500];
	int nLen = ::GetCurrentDirectory(500,strCurDrt);

	if( strCurDrt[nLen]!='\\' )
	{
		strCurDrt[nLen++] = '\\';
		strCurDrt[nLen] = '\0';
	}

	CString strFileName = strCurDrt;
	strFileName += "love.swf";//clock.swf是flash文件的名字，该flash文件放在工程目录下。

	m_FlashShow.LoadMovie(0, strFileName);
	m_FlashShow.Play();

	return false;
}

BEGIN_MESSAGE_MAP(CFlashDlg, CDialogEx)
END_MESSAGE_MAP()


// CFlashDlg 消息处理程序
