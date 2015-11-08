
// LoveCalendarDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
#include "FileOperation.h"
#include "afxcmn.h"

// CLoveCalendarDlg �Ի���
class CLoveCalendarDlg : public CDialogEx
{
// ����
public:
	CLoveCalendarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOVECALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HBRUSH m_hBrush;
//	CComboBox m_hYear;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT  nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnButtonClicked(UINT  nID);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ����°�ť
	CButton* NewMyButton(int nID, CRect rect, int nStyle);
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT  nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedShape();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();

	CButton m_Date;
	CButton *m_pButton1[31];
	CButton *m_pButton2[12];
	CButton *m_pButton3[35];
	CButton m_Check1;
	CButton m_Check2;
	CButton m_Check3;
	int m_Choice;
	int m_OldYear;
	int m_Year;
	int m_Month;
	int m_Day;
	int m_IndexOfArray;
	bool m_IsCurrentDate;
	bool m_IsBiggest;
	bool m_DisplaySkin;
	bool m_DisplayMusic;
	HANDLE m_pNewThread;
	CFileOperation m_FileOp;

	void DisplayMonth();
	void DeleteButton();
	void DisplayYear();
	void DisplayDay();
	int GetDay();
	void PlayMusic();
	// ���������ĺ���
	int Xingqi();
	int Year_();
	int Month_();
	// ��ע�������ӱ�־
	void DisplayMark(CButton* pButton, int choice);
	void DisplayLoveMark();
	void DisplayMemoMark();
	void RefreshMark();
	// ��ʾ��Ӧ��Ϣ
	void DisplayInfo();
	void DisplayLoveMemo();
	void DisplayMemorandum(int opsition);


	// �Զ�����
	void AutoChangeSkin(void);


	/*�Զ�����ģ��*/
protected:
	//�����ƶ�ʱ���ڵĴ�С
	void FixMoving(UINT fwSide, LPRECT pRect);
	//������״̬��ʾ����
	void DoShow();
	//����ʾ״̬��������
	void DoHide();
	//���غ���,ֻ��Ϊ�˷�����ã�ʵ�ʵ���CWnd��SetWindowPos(��)
	BOOL SetWindowPos(const CWnd* pWndInsertAfter,LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);

private:
	BOOL m_isSizeChanged;//���ڴ�С�Ƿ�ı���
	BOOL m_isSetTimer;//�Ƿ������˼������Timer
	int m_oldWndHeight;//�ɵĴ��ڿ��
	int m_taskBarHeight;//�������߶�
	int m_edgeHeight;//��Ե�߶�
	int m_edgeWidth;//��Ե���
	int m_hideMode;//����ģʽ
	BOOL m_hsFinished;//���ػ���ʾ�����Ƿ����
	BOOL m_hiding;//�ò���ֻ����!m_hsFinished����Ч
	//��:��������,��:������ʾ
public:
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_Slider;
	afx_msg void OnBnClickedCancel();
};
