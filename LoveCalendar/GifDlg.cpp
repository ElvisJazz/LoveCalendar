// GifDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LoveCalendar.h"
#include "GifDlg.h"
#include "afxdialogex.h"
#include <stdlib.h>
#include <ctime>

// GifDlg 对话框

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
	 case 0: m_tip = _T("姐姐我就喜欢小自在，告诉你个秘密，小治很喜欢你的！"); break;
	 case 1: m_tip = _T("呀，讨厌，又要折腾我了，不过我好欢喜！mua~"); break;
	 case 2: m_tip = _T("哈~啊，做阿狸真没劲，听说做猫晚上不睡觉，好玩吗？"); break;
	 case 3: m_tip = _T("看我耳朵像不像你家小猫，人家特意把自己晾在衣架上的诶~"); break;
	 case 4: m_tip = _T("哎呀，讨厌，羞死了，你俩又在秀恩爱，腻不腻啊？！"); break;
	 case 5: m_tip = _T("甜筒真喵喵的好吃，去去去，叫你家小猫买去！"); break;
     case 7: m_tip = _T("猪宝宝，抱抱。天天抱熊，也多抱抱小治哥哥啊,人家可想你晚上抱着睡了！"); break;
	 case 8: m_tip = _T("自在飞花轻似梦，无边丝雨细如愁啊~你家小治有我文艺吗？"); break;
	 case 9: m_tip = _T("大变活猫，哦，不对，是大变活狸！"); break;
	 case 10: m_tip = _T("看不见我，看不见我，再看我，我就把你吃掉！"); break;
	 case 11: m_tip = _T("小样，别嚣张，我可是收藏了猪宝宝你很多萌照哦，哪天给你爆个光！"); break;
	 case 6: m_tip = _T("爱你的感觉，就像飘在半空，我飘啊飘啊飘~~"); break;
	 default: m_tip = _T("喵了个咪，居然出错了！"); break;
	 }
	 if(i == 6)
		 i = 12;
	
	 if(m_gif.Load(MAKEINTRESOURCE(IDR_GIF5+i),_T("gif")))//IDR_GIF1是添加的GIF动画的ID号。gif即是在添加时所键入的文件类型
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


// GifDlg 消息处理程序
