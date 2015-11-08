
// LoveCalendarDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
#include "FileOperation.h"
#include "afxcmn.h"

// CLoveCalendarDlg 对话框
class CLoveCalendarDlg : public CDialogEx
{
// 构造
public:
	CLoveCalendarDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOVECALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HBRUSH m_hBrush;
//	CComboBox m_hYear;

	// 生成的消息映射函数
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
	// 添加新按钮
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
	// 外来引进的函数
	int Xingqi();
	int Year_();
	int Month_();
	// 标注特殊日子标志
	void DisplayMark(CButton* pButton, int choice);
	void DisplayLoveMark();
	void DisplayMemoMark();
	void RefreshMark();
	// 显示对应信息
	void DisplayInfo();
	void DisplayLoveMemo();
	void DisplayMemorandum(int opsition);


	// 自动换肤
	void AutoChangeSkin(void);


	/*自动伸缩模块*/
protected:
	//修正移动时窗口的大小
	void FixMoving(UINT fwSide, LPRECT pRect);
	//从收缩状态显示窗口
	void DoShow();
	//从显示状态收缩窗口
	void DoHide();
	//重载函数,只是为了方便调用，实际调用CWnd的SetWindowPos(…)
	BOOL SetWindowPos(const CWnd* pWndInsertAfter,LPCRECT pCRect, UINT nFlags = SWP_SHOWWINDOW);

private:
	BOOL m_isSizeChanged;//窗口大小是否改变了
	BOOL m_isSetTimer;//是否设置了检测鼠标的Timer
	int m_oldWndHeight;//旧的窗口宽度
	int m_taskBarHeight;//任务栏高度
	int m_edgeHeight;//边缘高度
	int m_edgeWidth;//边缘宽度
	int m_hideMode;//隐藏模式
	BOOL m_hsFinished;//隐藏或显示过程是否完成
	BOOL m_hiding;//该参数只有在!m_hsFinished才有效
	//真:正在隐藏,假:正在显示
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
