
// LoveCalendarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoveCalendar.h"
#include "LoveCalendarDlg.h"
#include "FlashDlg.h"
#include "FindMusic.h"
#include "afxdialogex.h"
#include "Mmsystem.h"
#include "Digitalv.h"
#include "GifDlg.h"
#include "afxwin.h"
#pragma comment( lib, "winmm.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����ģʽ
#define HM_NONE	0//������
#define HM_TOP	1//��������
#define HM_BOTTOM	2//��������
#define HM_LEFT	3//��������
#define HM_RIGHT	4//��������
#define HM_ALL 6 //ȫ������������
#define CM_ELAPSE	200 //�������Ƿ��뿪���ڵ�ʱ����
#define HS_ELAPSE	5//��������ÿ����ʱ����
#define HS_STEPS	10//�������̷ֳɶ��ٲ����
#define INTERVAL	20//����ճ��ʱ�������Ļ�߽����С���,��λΪ����
#define INFALTE	10//��������ʱ����봰�ڱ߽����С���,��λΪ����
#define MINCY 540

#define STARTX 30
#define STARTY 180   

CString g_CurrentMusic;
bool g_IsPlay;
bool g_ChangeMusic;

static DWORD WINAPI Loop(void* app0)
{ 
	CString music;
	int mark = 0;
	//use   mciSendCommand   
	MCI_OPEN_PARMS   mciOpen;   
	MCIERROR   mciError;   
	UINT   DeviceID;
	while(true)
	{
		if(g_ChangeMusic)
		{
			g_ChangeMusic = false;
			mciSendCommand (DeviceID, MCI_CLOSE, NULL, NULL); 
			g_IsPlay = true;
			mark = 0;
		}

		if(g_IsPlay)
		{
			if(mark == 0)
			{
				mark = 1;
				music = CString(g_CurrentMusic);
				music.Delete(music.GetLength()-1);
				mciOpen.lpstrElementName   =   music; 
				mciOpen.lpstrDeviceType   =   _T("mpegvideo");   
				mciError   =   mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE   |   MCI_OPEN_ELEMENT,(DWORD)&mciOpen);   
				DeviceID =   mciOpen.wDeviceID   ;
			
			    
				MCI_PLAY_PARMS   mciPlay;   

				mciError   =   mciSendCommand(DeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, 
					(DWORD)   (LPMCI_PLAY_PARMS)&mciPlay);  //MCI_DGV_PLAY_REPEAT, Ҫ #include "Digitalv.h"
			
			}
			else if(mark == 2)
				mark = 0;
		}
		else if(!g_IsPlay)
		{
			if(mark==1)
			{
				mark = 2;
				mciSendCommand (DeviceID, MCI_CLOSE, NULL, NULL); 
			}
		}
	}
    return 0;
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	bool DeleteButton(void);
	CPictureEx m_gif0;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}
BOOL CAboutDlg::OnInitDialog()
{
	 CDialogEx::OnInitDialog();
	
	 if(m_gif0.Load(MAKEINTRESOURCE(IDR_GIF4),_T("gif")))//IDR_GIF1����ӵ�GIF������ID�š�gif���������ʱ��������ļ�����
        m_gif0.Draw();
	 return true;
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC01, m_gif0);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoveCalendarDlg �Ի���




CLoveCalendarDlg::CLoveCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoveCalendarDlg::IDD, pParent)
{
	m_isSizeChanged = FALSE;
	m_isSetTimer = FALSE;
	m_hsFinished = TRUE;
	m_hiding = FALSE;
	m_oldWndHeight = MINCY;
	m_taskBarHeight = 30;
	m_edgeHeight = 0;
	m_edgeWidth=0;
	m_hideMode = HM_NONE;

	m_IsBiggest = false;
	g_IsPlay = true;
	g_ChangeMusic = false;
	m_DisplayMusic = false;
	m_DisplaySkin = false;

	CTime t = CTime::GetCurrentTime();
	m_FileOp.PreRead(t.GetYear());

	CFlashDlg dlg;
	dlg.DoModal();
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoveCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Date);
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_CHECK3, m_Check3);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
}

BEGIN_MESSAGE_MAP(CLoveCalendarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLoveCalendarDlg::OnBnClickedOk)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_MYBUTTON1, IDC_MYBUTTON31, OnButtonClicked)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoveCalendarDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoveCalendarDlg::OnBnClickedButton3)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOVING()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_SHAPE, &CLoveCalendarDlg::OnBnClickedShape)
	ON_BN_CLICKED(IDC_CHECK1, &CLoveCalendarDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CLoveCalendarDlg::OnBnClickedCheck2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLoveCalendarDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CLoveCalendarDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_CHECK3, &CLoveCalendarDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_LEFT, &CLoveCalendarDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, &CLoveCalendarDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoveCalendarDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CLoveCalendarDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CLoveCalendarDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CLoveCalendarDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CLoveCalendarDlg::OnBnClickedButton7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CLoveCalendarDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDCANCEL, &CLoveCalendarDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoveCalendarDlg ��Ϣ�������

BOOL CLoveCalendarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//SetLayeredWindowAttributes(RGB(220,238,212),100,LWA_COLORKEY);
	//����͸��
	ModifyStyleEx(0,0x00080000);
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//ȡ��SetLayeredWindowAttributes��������ָ�� 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),RGB(255,235,205),220,2); 
		FreeLibrary(hInst); 
	} 


	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect tRect;
	GetWindowRect(tRect);
	tRect.right = tRect.left + 327;
	tRect.bottom =tRect.top + 680;
	SetWindowPos(&wndTopMost,tRect);
	//�������Ч��ʼ��
	m_hBrush=CreateSolidBrush(RGB(255,235,205));
	m_Choice = 0;
	
	CStatic   *cwm=(CStatic*)GetDlgItem(IDC_STATIC2);   
	CBitmap   bmpload;   
	bmpload.LoadBitmap(IDB_BITMAP2);   
	cwm->ModifyStyle(0,SS_BITMAP);   
	cwm->SetBitmap(HBITMAP(bmpload.Detach()));

	for(int i=0; i<31; i++)
		m_pButton1[i] = NULL;
	for(int i=0; i<12; i++)
		m_pButton2[i] = NULL;


	m_IsCurrentDate = true;
	DisplayDay(); // Ĭ�ϰ�ťѡ��Ϊ��������

	// Music initial	
	(new CFindMusics())->searchAllFile("Music", 0, "temp.txt");
	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	
	CString str;
	int num;
	char s[100];
	FILE* fp;
	fp = fopen("temp.txt", "r");
	ifstream read("temp.txt", ios::in);
	read>>num;
	fgets(s, 100, fp);

	for(int i=0; i<num; i++)
	{
		str.Format(_T("%s"), CString(fgets(s, 100, fp)));
		chooseBox->AddString(str);
	}
	fclose(fp);
	chooseBox->SetCurSel(0);
	chooseBox->GetLBText(chooseBox->GetCurSel(), g_CurrentMusic);
	
	g_ChangeMusic = true;

	m_pNewThread = CreateThread(NULL,0,Loop,this,0,NULL);
	//PlayMusic();
	// Skin initial
	CComboBox* chooseBox1 = (CComboBox*)GetDlgItem(IDC_COMBO3);
	CString s0;
	for(int i=0; i<13; i++)
	{
		CString s("cat");
		s0.Format(_T("%2d"), i);
		s += s0;
		chooseBox1->AddString(s);
	}
	
	m_Slider.SetRange(0, 255);
	m_Slider.SetPos(220);

	CButton *but3 = (CButton*)GetDlgItem(IDC_CHECK3);
	but3->SetCheck(1);
	OnBnClickedCheck3();

	return false;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLoveCalendarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoveCalendarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoveCalendarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ����°�ť
CButton* CLoveCalendarDlg::NewMyButton(int nID, CRect rect, int nStyle)
{
	CString m_Caption;
	m_Caption.LoadString(nID); //ȡ��ť����
	CButton *p_Button = new CButton();
	ASSERT_VALID(p_Button);

	p_Button->Create(m_Caption, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|nStyle, rect, this, nID);
	return p_Button;
}


void CLoveCalendarDlg::OnBnClickedOk() // ��ʾ��ǰ����
{
	m_IsCurrentDate = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	DeleteButton();
	DisplayDay();
	m_Choice = 0;

	if(m_IsBiggest)
	{
		if(m_Check1.GetCheck() == 1)
			DisplayLoveMemo();
		if(m_Check2.GetCheck() == 1)
		{
			if(m_Check1.GetCheck() == 1)
				DisplayMemorandum(2);
			else
				DisplayMemorandum(1);
		}
	}
}


void CLoveCalendarDlg::OnButtonClicked(UINT nID)
{
	CString strText;
	CString stime = _T("");
	int nIndex = nID - IDC_MYBUTTON1+1;
	m_IsCurrentDate = false;

	switch(m_Choice)
	{
	case -2: nIndex += 2008;
			m_Year = nIndex;
			strText.Format(_T("%d"), nIndex);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
			SetDlgItemText(IDC_BUTTON1, strText);
			DeleteButton();
			DisplayMonth();
			m_Choice++;
			break;
	case -1:
			if(m_Year != m_OldYear)
			{
				m_FileOp.PreRead(m_Year);
				m_OldYear = m_Year;
			}
			strText.Format(_T("%d"), nIndex);
			m_Month = nIndex;
			SetDlgItemText(IDC_BUTTON1, strText);
			DeleteButton();
			DisplayDay();
			m_Choice++;
			break;
	case 0: m_Day = nIndex;
			stime.Format(_T("%d/%d/%d"), m_Year, m_Month, m_Day);
			GetDlgItem(IDC_STATIC12)->SetWindowText(stime);
			if(m_IsBiggest)
				DisplayInfo();
			break;
	default: break;
	}

}



HBRUSH CLoveCalendarDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor==CTLCOLOR_DLG || nCtlColor==CTLCOLOR_STATIC) 
	{ 
		pDC-> SetBkMode(TRANSPARENT); 
		//�˴������������ɫ 
		pDC->SetTextColor(RGB(0,0,255));
		return m_hBrush; 
	} 
	else 
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CLoveCalendarDlg::OnBnClickedButton1()
{
	CString year, years;
	year.Format(_T("%d"), m_Year);
	years = "2009-2043";
	m_IsCurrentDate = false;

	if(m_Choice<-1 || m_Choice>0)
	{
		AfxMessageBox(CString("�װ��ģ������ˣ�"));
		exit(1);
	}

	switch(m_Choice)
	{
	case 0: SetDlgItemText(IDC_BUTTON1,year);
			 DeleteButton();
		     DisplayMonth();
			 GetDlgItem(IDC_STATIC1)->ShowWindow(false);
			 GetDlgItem(IDC_RIGHT)->ShowWindow(false);
			 GetDlgItem(IDC_LEFT)->ShowWindow(false);
			 m_Choice--;
			break;
	case -1: SetDlgItemText(IDC_BUTTON1, years);
			 DeleteButton();
		     DisplayYear();
			 GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
			 m_Choice--;
			break;
	default: break;
	}
}


void CLoveCalendarDlg::DisplayMonth()
{
	int tmpX = STARTX;
	int tmpY = STARTY;
	for(int i=0; i<12; i++)
	{
		int tmp = i % 4;
		tmpX = STARTX + tmp * 60;

		if(i+1 == m_Month)
			m_pButton2[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+60, tmpY+60), BS_DEFPUSHBUTTON);
		else
			m_pButton2[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+60, tmpY+60), 0);

		if(tmp == 3)
		{
			tmpY += 60;
			tmp = 0;
		}

	}
}


void CLoveCalendarDlg::DisplayYear()
{
	int tmpX = STARTX;
	int tmpY = STARTY;
	CString str;
	for(int i=0; i<35; i++)
	{
		int tmp = i % 7;
		int j = i + 2009;
		tmpX = STARTX + tmp * 35;
		str.Format(_T("%d"), j);

		if(j == m_Year)
			m_pButton3[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+35, tmpY+35), BS_DEFPUSHBUTTON);
		else
			m_pButton3[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+35, tmpY+35), 0);
		SetDlgItemText(IDC_MYBUTTON1+i, str);

		if(tmp == 6)
		{
			tmpY += 35;
			tmp = 0;
		}

	}
}

void CLoveCalendarDlg::DisplayDay(void)
{
	if(m_IsCurrentDate)
	{
		CTime t = CTime::GetCurrentTime();
		m_Day = t.GetDay(); //��ü���
		m_Year = t.GetYear(); //��ȡ���
		m_Month = t.GetMonth(); //��ȡ��ǰ�·�
		m_OldYear = m_Year;
	}

	int tmpX = STARTX;
	int tmpY = STARTY;
	int maxDays;
	int tmpDay = GetDay();

	CString str;
	str.Format(_T("%d.%d"), m_Year, m_Month);
	SetDlgItemText(IDC_BUTTON1, str);
	GetDlgItem(IDC_STATIC1)->ShowWindow(true);
	GetDlgItem(IDC_RIGHT)->ShowWindow(true);
	GetDlgItem(IDC_LEFT)->ShowWindow(true);

	if(m_Month == 2)
	{
		if(m_Year%400==0 || m_Year%100!=0 && m_Year%4==0)
			maxDays=29;
		else
			maxDays=28;
	}
	else
	{
		switch(m_Month)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:maxDays=31;break;
			case 4:
			case 6:
			case 9:
			case 11:maxDays=30;break;
			default:break;
		}
	}
	for(int i=0; i<maxDays; i++)
	{
		int tmp = (i+tmpDay) % 7;
		tmpX = STARTX + tmp * 35;

		if(i+1 == m_Day)
			m_pButton1[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+35, tmpY+35), BS_DEFPUSHBUTTON);
		else
			m_pButton1[i] = NewMyButton(IDC_MYBUTTON1+i, CRect(tmpX, tmpY, tmpX+35, tmpY+35), 0);

		if(tmp == 6)
		{
			tmpY += 35;
			tmp = 0;
		}
	}

	RefreshMark();

	CString stime = _T("");
	stime.Format(_T("%d/%d/%d"), m_Year, m_Month, m_Day);
	GetDlgItem(IDC_STATIC12)->SetWindowText(stime);
}

void CLoveCalendarDlg::DeleteButton()
{
	switch(m_Choice)
	{
	case 0: 
			for(int i=0; i<31; i++)
			{
				if(m_pButton1[i] != NULL)
				{
					GetDlgItem(IDC_MYBUTTON1+i)->ShowWindow(SW_HIDE); 
					delete m_pButton1[i];
					m_pButton1[i] = NULL;
				}
				else
					return;
			}
			break;
	case -1: 
			for(int i=0; i<12; i++)
			{
				if(m_pButton2[i] != NULL)
				{
					GetDlgItem(IDC_MYBUTTON1+i)->ShowWindow(SW_HIDE); 
					delete m_pButton2[i];
					m_pButton2[i] = NULL;
				}
				else
					return;
			}
			break;
	case -2: 
			for(int i=0; i<35; i++)
			{
				if(m_pButton3[i] != NULL)
				{
					GetDlgItem(IDC_MYBUTTON1+i)->ShowWindow(SW_HIDE); 
					delete m_pButton3[i];
					m_pButton3[i] = NULL;
				}
				else
					return;
			}
			break;
	default: break;
	}
	
}


// �������
int CLoveCalendarDlg::GetDay(void)
{
	int tmp = Xingqi();
	if(tmp==0 || tmp==7)
		tmp = 6;
	else
		tmp--;

	return tmp;
}

int CLoveCalendarDlg::Xingqi()//function xingqi definition 
{
	int x;
	if(m_Year>=2000)
	    x=(Year_()+Month_())%7;
	else
		x=7-(Year_()-Month_())%7;
	return x;
}


//calculate how many days there are from Jan 1,2000 to the day you want to know
int CLoveCalendarDlg::Year_()//function year1 definition
{
	int n = m_Year;
	int x=0,y=2000;
	if(n==2000)
		x=0;
	else
	{
		if(n>2000)
			while(y<n)
			{
				if(y%400==0 || y%100!=0 && y%4==0)
					x=x+366;
				else
					x=x+365;
				y++;
			}
		else
            while(y>n)
			{
				int m=y-1;
				if(m%400==0 || m%100!=0 && m%4==0)
					x=x+366;
				else
					x=x+365;
				y--;
			}
	}
	return x;
}
int CLoveCalendarDlg::Month_()//function month1 definition
{
	int n = m_Year;
	int m = m_Month;
	int l = 1;
	int x;
	switch(m)
	{
	case(1):x=l-1;break;
	case(2):x=l+30;break;
	case(3):x=l+58;break;
	case(4):x=l+89;break;
	case(5):x=l+119;break;
	case(6):x=l+150;break;
	case(7):x=l+180;break;
	case(8):x=l+211;break;
	case(9):x=l+242;break;
	case(10):x=l+272;break;
	case(11):x=l+303;break;
	case(12):x=l+333;break;
	default:break;
	}
	
    if(n%400==0 || n%100!=0 && n%4==0)
	 if(m>2)
		x++;
	return x;
}

void CLoveCalendarDlg::OnBnClickedButton3()
{
	PlayMusic();
}

void CLoveCalendarDlg::PlayMusic()
{
	if(!g_IsPlay)
	{
		g_IsPlay = true;
	}
	else
	{
		g_IsPlay = false;
	}
}


/*��Чģ��*/
int CLoveCalendarDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//����������߶�
	CWnd* p;
	p = this->FindWindow(CString("Shell_TrayWnd"), NULL);
	if(p != NULL)
	{
		CRect tRect;
		p->GetWindowRect(tRect);
		m_taskBarHeight = tRect.Height();
	}
	//�޸ķ��ʹ����������������ʾ
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	//ȥ���رհ���(����뻭3�������Ļ�)
	//ModifyStyle(WS_SYSMENU,NULL);
	//��ñ�Ե�߶ȺͿ��
	m_edgeHeight = GetSystemMetrics(SM_CYEDGE)/2;
	m_edgeWidth = GetSystemMetrics(SM_CXFRAME)/2;
	return 0;
}

LRESULT CLoveCalendarDlg::OnNcHitTest(CPoint point)
{
	CString str;
	str.Format(_T("Mouse (%d,%d)"),point.x,point.y);
	//GetDlgItem(IDC_CURSOR)->SetWindowText(str);
	if(m_hideMode != HM_ALL &&m_hideMode != HM_NONE && !m_isSetTimer &&
	//��ֹ��곬����Ļ�ұ�ʱ���ұ����������˸
	point.x < GetSystemMetrics(SM_CXSCREEN) + INFALTE)
	{ //������ʱ,����Ǵ�����״̬����ʾ״̬����Timer
		SetTimer(1,CM_ELAPSE,NULL);
		m_isSetTimer = TRUE;
		m_hsFinished = FALSE;
		m_hiding = FALSE;
		SetTimer(2,HS_ELAPSE,NULL); //������ʾ����
	}
	CRect tRect;
	GetWindowRect(tRect);
	UINT   nHitTest   =   CDialog::OnNcHitTest(point);   
	if((nHitTest== HTCLIENT)  && (::GetAsyncKeyState(MK_LBUTTON)<0) && point.x>tRect.left && point.x<tRect.right
		&& point.y>tRect.top && point.y<tRect.top+100)   
		 nHitTest   =   HTCAPTION;   
	return   nHitTest;  
}

void CLoveCalendarDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 1 )
	{
		POINT curPos;
		GetCursorPos(&curPos);
		CString str;
		str.Format(_T("Timer On(%d,%d)"),curPos.x,curPos.y);
		//GetDlgItem(IDC_TIMER)->SetWindowText(str);
		CRect tRect;
		//��ȡ��ʱ���ڴ�С
		GetWindowRect(tRect);
		//����tRect,�Դﵽ����뿪���ڱ���һ������Ŵ����¼�
		tRect.InflateRect(INFALTE,INFALTE);

		if(!tRect.PtInRect(curPos)) //�������뿪���������
		{
			KillTimer(1); //�رռ�����Timer
			m_isSetTimer = FALSE;
			//GetDlgItem(IDC_TIMER)->SetWindowText(CString("Timer Off"));
			m_hsFinished = FALSE;
			m_hiding = TRUE;
			SetTimer(2,HS_ELAPSE,NULL); //������������
		}
	}

	if(nIDEvent == 2)
	{
		if(m_hsFinished) //�����������ʾ���������ر�Timer
		{
			m_hiding = false;
			KillTimer(2);
			if(m_hideMode == HM_ALL)
				CDialogEx::OnCancel();
		}
		else
			m_hiding ? DoHide() : DoShow();
	}

	if(nIDEvent == 3)
		AutoChangeSkin();

}

void CLoveCalendarDlg::FixMoving(UINT fwSide, LPRECT pRect)
{
	POINT curPos;
	GetCursorPos(&curPos);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int height = pRect->bottom - pRect->top;
	int width = pRect->right - pRect->left;

	if (curPos.y <= INTERVAL)
	{ //ճ�����ϱ�
		pRect->bottom = height - m_edgeHeight;
		pRect->top = -m_edgeHeight;
		m_hideMode = HM_TOP;
	}
	else if(curPos.y >= (screenHeight - INTERVAL - m_taskBarHeight))
	{ //ճ�����±�
		pRect->top = screenHeight - m_taskBarHeight - height;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_hideMode = HM_BOTTOM;
	}
	else if (curPos.x < INTERVAL)
	{ //ճ�������
		if(!m_isSizeChanged)
		{
		CRect tRect;
		GetWindowRect(tRect);
		m_oldWndHeight = tRect.Height();
		}
		pRect->right = width;
		pRect->left = 0;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_LEFT;
	}
	else if(curPos.x >= (screenWidth - INTERVAL))
	{ //ճ�����ұ�
		if(!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			m_oldWndHeight = tRect.Height();
		}
		pRect->left = screenWidth - width;
		pRect->right = screenWidth;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_RIGHT;
	}
	else
	{ //��ճ��
		if(m_isSizeChanged)
		{	//�������������,���ϳ��������ԭ����С
			//��"�϶�����ʾ����������"ֻ�й�դ���ԭ����С
			pRect->bottom = pRect->top + m_oldWndHeight;
			m_isSizeChanged = FALSE;
		}
		if(m_isSetTimer)
		{ //���Timer������,��ر�֮
			if(KillTimer(1) == 1)
				m_isSetTimer = FALSE;
		}
		m_hideMode = HM_NONE;
	//	GetDlgItem(IDC_TIMER)->SetWindowText(CString("Timer off"));
	}
}

void CLoveCalendarDlg::DoHide()
{
	if(m_hideMode == HM_NONE)
		return;
	
	if(m_IsBiggest)
		OnBnClickedShape();

	CRect tRect;
	GetWindowRect(tRect);
	int height = tRect.Height();
	int width = tRect.Width();
	int steps = 0;
	
	switch(m_hideMode)
	{
	case HM_TOP:
				steps = height/HS_STEPS;
				tRect.bottom -= steps;
				if(tRect.bottom <= m_edgeWidth)
				{ //����԰�����һ���滻����� ...+=|-=steps �ﵽȡ������Ч��
				//���õİ취����Ӹ�BOOLֵ������,����caseͬ��.
					tRect.bottom = m_edgeWidth;
					m_hsFinished = TRUE; //������ع���
				}
				tRect.top = tRect.bottom - height;
				break;
	case HM_BOTTOM:
				steps = height/HS_STEPS;
				tRect.top += steps;
				if(tRect.top >= (GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth))
				{
					tRect.top = GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth;
					m_hsFinished = TRUE;
				}
				tRect.bottom = tRect.top + height;
				break;
	case HM_LEFT:
				steps = width/HS_STEPS;
				tRect.right -= steps;
				if(tRect.right <= m_edgeWidth)
				{
					tRect.right = m_edgeWidth;
					m_hsFinished = TRUE;
				}
				tRect.left = tRect.right - width;
				tRect.top = -m_edgeHeight;
				tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
				break;
	case HM_RIGHT:
				steps = width/HS_STEPS;
				tRect.left += steps;
				if(tRect.left >= (GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth))
				{
					tRect.left = GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth;
					m_hsFinished = TRUE;
				}
				tRect.right = tRect.left + width;
				tRect.top = -m_edgeHeight;
				tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
				break;
	case HM_ALL:steps = height/HS_STEPS;
			    tRect.bottom -= steps;
				tRect.top += steps;
				if(tRect.bottom - tRect.top < 10)
				{
					m_hsFinished = TRUE;
				}
				break;
	default:
				break;	
	}																																
	SetWindowPos(&wndTopMost,tRect);
}

void CLoveCalendarDlg::DoShow()
{
	if(m_hideMode == HM_NONE)
		return;
	CRect tRect;
	GetWindowRect(tRect);
	int height = tRect.Height();
	int width = tRect.Width();
	int steps = 0;
	
	switch(m_hideMode)
	{
	case HM_TOP:
				steps = height/HS_STEPS;
				tRect.top += steps;
				if(tRect.top >= -m_edgeHeight)
				{ //����԰�����һ���滻����� ...+=|-=steps �ﵽȡ������Ч��
					//���õİ취����Ӹ�BOOLֵ������,����caseͬ��.
					tRect.top = -m_edgeHeight;
					m_hsFinished = TRUE; //�����ʾ����
				}
				tRect.bottom = tRect.top + height;
				break;
	case HM_BOTTOM:
				steps = height/HS_STEPS;
				tRect.top -= steps;
				if(tRect.top <= (GetSystemMetrics(SM_CYSCREEN) - height))
				{
					tRect.top = GetSystemMetrics(SM_CYSCREEN) - height;
					m_hsFinished = TRUE;
				}
				tRect.bottom = tRect.top + height;
				break;
	case HM_LEFT:
				steps = width/HS_STEPS;
				tRect.right += steps;
				if(tRect.right >= width)
				{
					tRect.right = width;
					m_hsFinished = TRUE;
				}
				tRect.left = tRect.right - width;
				tRect.top = -m_edgeHeight;
				tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
				break;
	case HM_RIGHT:
				steps = width/HS_STEPS;
				tRect.left -= steps;
				if(tRect.left <= (GetSystemMetrics(SM_CXSCREEN) - width))
				{
					tRect.left = GetSystemMetrics(SM_CXSCREEN) - width;
					m_hsFinished = TRUE;
				}
				tRect.right = tRect.left + width;
				tRect.top = -m_edgeHeight;
				tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
				break;
	default:
				break;
	}
	SetWindowPos(&wndTopMost,tRect);
}

BOOL CLoveCalendarDlg::SetWindowPos(const CWnd* pWndInsertAfter, LPCRECT pCRect, UINT nFlags)
{
	return CDialog::SetWindowPos(pWndInsertAfter,pCRect->left, pCRect->top,
		pCRect->right - pCRect->left, pCRect->bottom - pCRect->top, nFlags);
}

void CLoveCalendarDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	FixMoving(fwSide, pRect);
	CDialog::OnMoving(fwSide, pRect);
}


void CLoveCalendarDlg::OnBnClickedShape()
{
	if(!m_IsBiggest)
	{
		CRect tRect;
		GetWindowRect(tRect);
		tRect.right =tRect.left + 797;
		SetWindowPos(&wndTopMost,tRect);
		m_IsBiggest = true;
		GetDlgItem(IDC_SHAPE)->SetWindowText(_T("<<"));
		DisplayInfo();
	}
	else
	{
		CRect tRect;
		GetWindowRect(tRect);
		tRect.right = tRect.left + 327;
		SetWindowPos(&wndTopMost,tRect);
		m_IsBiggest = false;
		GetDlgItem(IDC_SHAPE)->SetWindowText(_T(">>"));
	}
}

// ��ע�������ӱ�־
void CLoveCalendarDlg::DisplayMark(CButton* pButton, int choice)
{
	HICON ico;
	if(choice == 1)
		ico = AfxGetApp()->LoadIcon(IDI_ICON1);
	else if(choice == 2)
		ico = AfxGetApp()->LoadIcon(IDI_ICON2);
	else
		ico = AfxGetApp()->LoadIcon(IDI_ICON3);
	pButton-> ModifyStyle(0, BS_ICON); 	 
	pButton-> SetIcon(ico);
}


void CLoveCalendarDlg::OnBnClickedCheck1()
{
	GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
	GetDlgItem(IDC_EDIT3)->EnableWindow(false);
	if(m_Choice == 0)
	{
		if(m_Check1.GetCheck() == 1)
		{
			DisplayLoveMark();
			if(m_IsBiggest)
				DisplayInfo();
		}
		else
		{
			DeleteButton();
			DisplayDay();
			GetDlgItem(IDC_STATIC9)->ShowWindow(false);
			GetDlgItem(IDC_STATIC10)->ShowWindow(false);
			GetDlgItem(IDC_STATIC11)->ShowWindow(false);
			GetDlgItem(IDC_EDIT5)->ShowWindow(false);
			GetDlgItem(IDC_EDIT4)->ShowWindow(false);
			GetDlgItem(IDC_EDIT3)->ShowWindow(false);
			
			if(m_Check2.GetCheck() == 1)
				DisplayMemorandum(1);
		}
	}
}


void CLoveCalendarDlg::OnBnClickedCheck2()
{
	GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
	GetDlgItem(IDC_EDIT3)->EnableWindow(false);
	if(m_Choice == 0)
	{
		if(m_Check2.GetCheck() == 1)
		{
			DisplayMemoMark();
			DisplayInfo();
		}
		else
		{
			DeleteButton();
			DisplayDay();
			if(m_Check1.GetCheck() == 1)
			{
				GetDlgItem(IDC_EDIT3)->ShowWindow(false);
				GetDlgItem(IDC_STATIC11)->ShowWindow(false);
			}
			else
			{
				GetDlgItem(IDC_EDIT3)->ShowWindow(false);
				GetDlgItem(IDC_EDIT5)->ShowWindow(false);
				GetDlgItem(IDC_STATIC9)->ShowWindow(false);
				GetDlgItem(IDC_STATIC11)->ShowWindow(false);
			}
		}
	}
}


void CLoveCalendarDlg::OnCbnSelchangeCombo1()
{
	CString tmp;
	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	chooseBox->GetLBText(chooseBox->GetCurSel(), tmp);

	if(tmp == g_CurrentMusic)
		return;
	else
	{
		g_CurrentMusic = tmp;
		g_ChangeMusic = true;
	}
}

void CLoveCalendarDlg::OnCbnSelchangeCombo3()
{
	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	CString s0;
	int index = chooseBox->GetCurSel();
	if(index == 12)
		index++;
	CStatic   *cwm=(CStatic*)GetDlgItem(IDC_STATIC4);   
	CBitmap   bmpload; 
	bmpload.LoadBitmap(IDB_BITMAP3+index);   
	cwm->ModifyStyle(0,SS_BITMAP);   
	cwm->SetBitmap(HBITMAP(bmpload.Detach()));
}


void CLoveCalendarDlg::OnBnClickedCheck3()
{
	if(m_Check3.GetCheck() == 1)
		SetTimer(3, 30000, NULL);
	else
		KillTimer(3);
}


// �Զ�����
void CLoveCalendarDlg::AutoChangeSkin(void)
{
	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	CString s0;
	int index = chooseBox->GetCurSel();
	index = (index+1) % 13;
	chooseBox->SetCurSel(index);
	if(index == 12)
		index++;

	CStatic   *cwm=(CStatic*)GetDlgItem(IDC_STATIC4);   
	CBitmap   bmpload; 
	bmpload.LoadBitmap(IDB_BITMAP3+index);   
	cwm->ModifyStyle(0,SS_BITMAP);   
	cwm->SetBitmap(HBITMAP(bmpload.Detach()));
}


void CLoveCalendarDlg::DisplayLoveMark()
{
	m_IndexOfArray = -1;
	for(int i=0; i<m_FileOp.m_NumOfArray; i++)
	{
		if(m_IndexOfArray==-1 && m_FileOp.m_Month[i]==m_Month)
			m_IndexOfArray = i;

		if(m_FileOp.m_Month[i]==m_Month)
		{
			if(m_FileOp.m_MarkInfo[i]%10==1)
				DisplayMark((CButton*)GetDlgItem(IDC_MYBUTTON1+m_FileOp.m_Day[i]-1), 1);
			else if(m_FileOp.m_MarkInfo[i]/1000==1)
				DisplayMark((CButton*)GetDlgItem(IDC_MYBUTTON1+m_FileOp.m_Day[i]-1), 3);
		}
		else if(m_FileOp.m_Month[i] > m_Month)
			break;
	}
}

void CLoveCalendarDlg::DisplayMemoMark()
{
	m_IndexOfArray = -1;
	for(int i=0; i<m_FileOp.m_NumOfArray; i++)
	{
		if(m_IndexOfArray==-1 && m_FileOp.m_Month[i]==m_Month)
			m_IndexOfArray = i;

		if(m_FileOp.m_Month[i]==m_Month && m_FileOp.m_MarkInfo[i]%100/10==1)
			DisplayMark((CButton*)GetDlgItem(IDC_MYBUTTON1+m_FileOp.m_Day[i]-1), 2);
		else if(m_FileOp.m_Month[i] > m_Month)
			break;
	}
}

void CLoveCalendarDlg::RefreshMark()
{
	if(m_Check1.GetCheck() == 1)
		DisplayLoveMark();

	if(m_Check2.GetCheck() == 1)
		DisplayMemoMark();
}

void CLoveCalendarDlg::OnBnClickedLeft()
{
	m_IsCurrentDate = false;
	if(m_Month == 1)
	{
		m_Year--;
		m_FileOp.PreRead(m_Year, false);
		m_Month = 12;
	}
	else
		m_Month--;

	DeleteButton();
	DisplayDay();
	DisplayInfo();
}


void CLoveCalendarDlg::OnBnClickedRight()
{
	m_IsCurrentDate = false;
	if(m_Month == 12)
	{
		m_Year++;
		m_FileOp.PreRead(m_Year, false);
		m_Month = 1;
	}
	else
		m_Month++;

	DeleteButton();
	DisplayDay();
	DisplayInfo();
}

void CLoveCalendarDlg::DisplayInfo()
{
	if(m_Check1.GetCheck() == 1)
		DisplayLoveMemo();
	if(m_Check2.GetCheck() == 1)
	{
		if(m_Check1.GetCheck() == 1)
			DisplayMemorandum(2);
		else
			DisplayMemorandum(1);
	}
}

void CLoveCalendarDlg::DisplayLoveMemo()
{
	GetDlgItem(IDC_EDIT5)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC9)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC9)->SetWindowText(_T("Sweet Together"));
	GetDlgItem(IDC_STATIC10)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC10)->SetWindowText(_T("Sweet Message"));

	for(int i=m_IndexOfArray; i<m_FileOp.m_NumOfArray; i++)
	{
		if(m_FileOp.m_Month[i]==m_Month && m_FileOp.m_Day[i]==m_Day)
		{
			GetDlgItem(IDC_EDIT5)->SetWindowText(m_FileOp.GetLoveMemory(i));
			GetDlgItem(IDC_EDIT4)->SetWindowText(m_FileOp.GetSweetMessage(i));
			break;
		}
		else if(m_FileOp.m_Day[i]>m_Day || m_FileOp.m_Month[i]>m_Month)
			break;
	}
}
	
void CLoveCalendarDlg::DisplayMemorandum(int opsition)
{
	if(opsition == 1)
	{
		GetDlgItem(IDC_EDIT5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC9)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC9)->SetWindowText(_T("Memorandum"));
	}
	else
	{
		GetDlgItem(IDC_EDIT3)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT3)->SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC11)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC11)->SetWindowText(_T("Memorandum"));
	}

	for(int i=m_IndexOfArray; i<m_FileOp.m_NumOfArray; i++)
	{
		if(m_FileOp.m_Month[i]==m_Month && m_FileOp.m_Day[i]==m_Day)
		{
			if(opsition == 1)
			{
				GetDlgItem(IDC_EDIT5)->SetWindowText(m_FileOp.GetMemorandum(i));
			}
			else
			{
				GetDlgItem(IDC_EDIT3)->SetWindowText(m_FileOp.GetMemorandum(i));
			}
			break;
		}
		else if(m_FileOp.m_Day[i]>m_Day || m_FileOp.m_Month[i]>m_Month)
			break;
	}

}

// �������
void CLoveCalendarDlg::OnBnClickedButton2()
{
	if(m_Check1.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(true);
		GetDlgItem(IDC_EDIT4)->EnableWindow(true);
	}

	if(m_Check2.GetCheck() == 1)
	{
		if(m_Check1.GetCheck() == 1)
		{
			GetDlgItem(IDC_EDIT3)->EnableWindow(true);
		}
		else
			GetDlgItem(IDC_EDIT5)->EnableWindow(true);
	}
	
	if(m_Check1.GetCheck()==1 || m_Check2.GetCheck()==1)
		GetDlgItem(IDC_BUTTON4)->ShowWindow(TRUE);
	else
	{
		AfxMessageBox(_T("����ѡ��Ҫ��ӵ�ģʽ��"));
		return;
	}

	if(!m_IsBiggest)
		OnBnClickedShape();
}

// �ύ������
void CLoveCalendarDlg::OnBnClickedButton4()
{
	CString s1 = _T("");
	CString s2 = _T("");
	CString s3 = _T("");
	bool check1 = false;
	bool check2 = false;

	if(m_Check1.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT5)->GetWindowTextW(s1);
		GetDlgItem(IDC_EDIT4)->GetWindowTextW(s2);
		check1 = true;
		if(m_Check2.GetCheck() == 1)
		{
			check2 = true;
			GetDlgItem(IDC_EDIT3)->GetWindowTextW(s3);
		}
	}
	else if(m_Check2.GetCheck() == 1)
	{
		check2 = true;
		GetDlgItem(IDC_EDIT5)->GetWindowTextW(s3);
	}

	m_FileOp.AddMessage(m_Month, m_Day, check1, check2, s1, s2, s3);
	m_FileOp.PreRead(m_Year);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	RefreshMark();
	//AfxMessageBox(_T("�ύ�ɹ���"));
	GifDlg dlg1;
	dlg1.DoModal();
	
}


void CLoveCalendarDlg::OnBnClickedButton6()
{
	m_DisplaySkin = false;
	CRect tRect;
	GetWindowRect(tRect);

	if(!m_DisplayMusic)
	{
		tRect.bottom =tRect.top + 745;
		SetWindowPos(&wndTopMost,tRect);

		GetDlgItem(IDC_COMBO1)->ShowWindow(true);
		GetDlgItem(IDC_COMBO3)->ShowWindow(false);
		GetDlgItem(IDC_CHECK3)->ShowWindow(false);
		GetDlgItem(IDC_SLIDER1)->ShowWindow(false);
		GetDlgItem(IDC_STATIC6)->ShowWindow(false);
		GetDlgItem(IDC_STATIC5)->ShowWindow(true);
		GetDlgItem(IDC_STATIC5)->SetWindowText(_T("MUSIC"));
		m_DisplayMusic = true;
	}
	else
	{
		tRect.bottom =tRect.top + 680;
		SetWindowPos(&wndTopMost,tRect);

		GetDlgItem(IDC_COMBO1)->ShowWindow(false);
		GetDlgItem(IDC_STATIC5)->ShowWindow(false);
		m_DisplayMusic = false;
	}
}


void CLoveCalendarDlg::OnBnClickedButton5()
{
	m_DisplayMusic = false;
	CRect tRect;
	GetWindowRect(tRect);

	if(!m_DisplaySkin)
	{
		
		tRect.bottom =tRect.top + 745;
		SetWindowPos(&wndTopMost,tRect);

		GetDlgItem(IDC_COMBO1)->ShowWindow(false);
		GetDlgItem(IDC_COMBO3)->ShowWindow(true);
		GetDlgItem(IDC_CHECK3)->ShowWindow(true);
		GetDlgItem(IDC_SLIDER1)->ShowWindow(true);
		GetDlgItem(IDC_STATIC6)->ShowWindow(true);
		GetDlgItem(IDC_STATIC5)->ShowWindow(true);
		GetDlgItem(IDC_STATIC5)->SetWindowText(_T("SKIN"));
		m_DisplaySkin = true;
	}
	else
	{
		tRect.bottom =tRect.top + 680;
		SetWindowPos(&wndTopMost,tRect);

		GetDlgItem(IDC_COMBO3)->ShowWindow(false);
		GetDlgItem(IDC_CHECK3)->ShowWindow(false);
		GetDlgItem(IDC_SLIDER1)->ShowWindow(false);
		GetDlgItem(IDC_STATIC6)->ShowWindow(false);
		GetDlgItem(IDC_STATIC5)->ShowWindow(false);
		m_DisplaySkin = false;
	}
}


void CLoveCalendarDlg::OnBnClickedButton7()
{
	
	CAboutDlg dlg;
	dlg.DoModal();
		
}


void CLoveCalendarDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int index = m_Slider.GetPos();
	ModifyStyleEx(0,0x00080000);
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//ȡ��SetLayeredWindowAttributes��������ָ�� 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(), RGB(255,235,205), index, 2); 
		FreeLibrary(hInst); 
	} 

	*pResult = 0;
}


void CLoveCalendarDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_hsFinished = FALSE;
	m_hideMode = HM_ALL;
	m_hiding = TRUE;
	SetTimer(2, HS_ELAPSE, NULL);
}
