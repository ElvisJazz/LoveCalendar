// GifDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoveCalendar.h"
#include "GifDlg.h"
#include "afxdialogex.h"
#include <stdlib.h>
#include <ctime>

// GifDlg �Ի���

IMPLEMENT_DYNAMIC(GifDlg, CDialogEx)

GifDlg::GifDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GifDlg::IDD, pParent)
	, m_tip(_T(""))
{

}

GifDlg::~GifDlg()
{
}

BOOL GifDlg::OnInitDialog()
{
	 CDialogEx::OnInitDialog();
	 srand(time(0));
	 int i = rand() % 12;
	 switch(i)
	 {
	 case 0: m_tip = _T("����Ҿ�ϲ��С���ڣ�����������ܣ�С�κ�ϲ����ģ�"); break;
	 case 1: m_tip = _T("ѽ�����ᣬ��Ҫ�������ˣ������Һû�ϲ��mua~"); break;
	 case 2: m_tip = _T("��~������������û������˵��è���ϲ�˯����������"); break;
	 case 3: m_tip = _T("���Ҷ����������Сè���˼�������Լ������¼��ϵ���~"); break;
	 case 4: m_tip = _T("��ѽ�����ᣬ�����ˣ�����������������岻�尡����"); break;
	 case 5: m_tip = _T("��Ͳ�������ĺóԣ�ȥȥȥ�������Сè��ȥ��"); break;
     case 7: m_tip = _T("���������������챧�ܣ�Ҳ�౧��С�θ�簡,�˼ҿ��������ϱ���˯�ˣ�"); break;
	 case 8: m_tip = _T("���ڷɻ������Σ��ޱ�˿��ϸ��~���С������������"); break;
	 case 9: m_tip = _T("����è��Ŷ�����ԣ��Ǵ����꣡"); break;
	 case 10: m_tip = _T("�������ң��������ң��ٿ��ң��ҾͰ���Ե���"); break;
	 case 11: m_tip = _T("С���������ţ��ҿ����ղ���������ܶ�����Ŷ��������㱬���⣡"); break;
	 case 6: m_tip = _T("����ĸо�������Ʈ�ڰ�գ���Ʈ��Ʈ��Ʈ~~"); break;
	 default: m_tip = _T("���˸��䣬��Ȼ�����ˣ�"); break;
	 }
	 if(i == 6)
		 i = 12;
	
	 if(m_gif.Load(MAKEINTRESOURCE(IDR_GIF5+i),_T("gif")))//IDR_GIF1����ӵ�GIF������ID�š�gif���������ʱ��������ļ�����
        m_gif.Draw();
	 UpdateData(FALSE);
	 return true;
}

void GifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC00, m_gif);
	DDX_Text(pDX, IDC_STATIC02, m_tip);
}


BEGIN_MESSAGE_MAP(GifDlg, CDialogEx)
END_MESSAGE_MAP()


// GifDlg ��Ϣ�������
