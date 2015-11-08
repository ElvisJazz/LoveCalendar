// FileOperation.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoveCalendar.h"
#include "FileOperation.h"
#include <iostream>
using namespace std;
// CFileOperation

IMPLEMENT_DYNAMIC(CFileOperation, CWnd)

CFileOperation::CFileOperation()
{
	m_RecordName = _T("");

}

CFileOperation::~CFileOperation()
{
	delete [m_NumOfArray]m_Month;
	delete [m_NumOfArray]m_Day;
	delete [m_NumOfArray]m_Memory1;
	delete [m_NumOfArray]m_Memory2;
	delete [m_NumOfArray]m_SweetMessage;
	delete [m_NumOfArray]m_MarkInfo;
	delete [m_NumOfArray]m_ExtralSM;
}


BEGIN_MESSAGE_MAP(CFileOperation, CWnd)
END_MESSAGE_MAP()



// �������Ԥ�ȶ�ȡ���ű��




void CFileOperation::PreRead(int year, bool create)
{
	CString s = _T("");
	s.Format(_T("%d"), year);
	s += ".xls";
	m_RecordName = s;
	CSpreadSheet SS(s, _T("Sheet1"));

	if(SS.OpenSuccess())
	{
		m_EnableAdd = true;
		CStringArray Rows, Column;
		m_NumOfArray = SS.GetTotalRows();
		m_Month = new int[m_NumOfArray];
		m_Day = new int[m_NumOfArray];
		m_Memory1 = new CString[m_NumOfArray];
		m_Memory2 = new CString[m_NumOfArray];
		m_SweetMessage = new CString[m_NumOfArray];
		m_MarkInfo = new int[m_NumOfArray];
		m_ExtralSM = new CString[m_NumOfArray];

		for (int i = 2; i <= m_NumOfArray; i++)
		{
			 // ��ȡһ��
			 SS.ReadRow(Rows, i);
			 CString strContents = _T("");
			 m_MarkInfo[i-2] = 0;
			 for (int j = 0; j < Rows.GetSize(); j++)
			 {
				 switch(j)
				 {
				 case 0: m_Month[i-2] = _ttoi(Rows.GetAt(j));
						break;
				 case 1: m_Day[i-2] = _ttoi(Rows.GetAt(j));
						break;
				 case 2: m_Memory1[i-2] = Rows.GetAt(j);
						if(m_Memory1[i-2] != "")
						{
							if(m_Memory1[i-2][0] == '@')
								m_MarkInfo[i-2] += 1000;
							else
								m_MarkInfo[i-2] += 1;
						}
						break;
				 case 3: m_Memory2[i-2] = Rows.GetAt(j);
						if(m_Memory2[i-2] != "")
							m_MarkInfo[i-2] += 10;
						break;
				 case 4: m_SweetMessage[i-2] = Rows.GetAt(j);
						if(m_SweetMessage[i-2] != "")
							m_MarkInfo[i-2] += 100;
						break;
				 default: break;
				 }
			 }
		 
		}
		return;
	}
	else if(create)
	{
		Create();
	}
	m_EnableAdd = false;
	m_Month = new int[1];
	m_Day = new int[1];
	m_Memory1 = new CString[1];
	m_Memory2 = new CString[1];
	m_SweetMessage = new CString[1];
	m_MarkInfo = new int[1];
	
}

void CFileOperation::Create()
{
	// �½�Excel�ļ�����·����TestSheetΪ�ڲ�����
	CSpreadSheet SS(m_RecordName, _T("Sheet1"));

	CStringArray sampleArray, testRow;
	
	SS.BeginTransaction();
	
	// �������
	sampleArray.RemoveAll();
	sampleArray.Add(_T("Month"));
	sampleArray.Add(_T("Day"));
	sampleArray.Add(_T("Love_Memory"));
	sampleArray.Add(_T("Memorandum"));
	sampleArray.Add(_T("Sweet_Message"));
	sampleArray.Add(_T("Extral_Sweet_Message"));
	SS.AddHeaders(sampleArray);

	SS.Commit();	
}

// ��ȡ���ۼ���
CString CFileOperation::GetLoveMemory(int index)
{
	return m_Memory1[index];
}


// ��ȡ����¼
CString CFileOperation::GetMemorandum(int index)
{
	return m_Memory2[index];
}

// ��ȡ����
CString CFileOperation::GetSweetMessage(int index)
{
	return m_SweetMessage[index]+m_ExtralSM[index];
}


// ��Ӻ���ģ��

void CFileOperation::AddMessage(int month, int day, bool check1, bool check2, CString s1, CString s2, CString s3)
{
	if(!m_EnableAdd)
	{
		m_EnableAdd = true;
		Create();
	}
	// �½�Excel�ļ�����·����TestSheetΪ�ڲ�����
	CSpreadSheet SS(m_RecordName, _T("Sheet1"));
	SS.BeginTransaction();
	
	// ��������
	int i;
	bool insertMark=true; // ��־�ǲ����µ�һ�У������滻ֵ

	for(i=0; i<m_NumOfArray; i++)
	{
		if(m_Month[i] == month)
		{
			if(m_Day[i] == day)
			{
				insertMark = false; // �滻
				break;
			}
			else if(m_Day[i] > day)
			{
				insertMark = true; // ����
				break;
			}
			else
				continue;
		}
		else if(m_Month[i] > month)
		{
			insertMark = true; // ����
			break;
		}
	}

	if(insertMark)
	{
		CString month1, day1;
		CStringArray array1;
		month1.Format(_T("%d"), month);
		day1.Format(_T("%d"), day);
		array1.RemoveAll();
		array1.Add(month1);
		array1.Add(day1);
		array1.Add(s1);
		array1.Add(s3);

		if(s2.GetLength() > 250)
		{
			CString s20 = s2.Mid(0, 250);
			CString s21 = s2.Mid(250);
			array1.Add(s20);
			array1.Add(s21);
		}
		else
		{
			array1.Add(s2);
		}

		if(i == m_NumOfArray)
			i--;
		SS.AddRow(array1, i+2);
	}
	else
	{
		if(check1)
		{
			SS.AddCell(s1, 3, i+2);    // ���(������)���滻(����)��i+2�У���3�е�Ԫ������
			if(s2.GetLength() > 250)
			{
				CString s20 = s2.Mid(0, 250);
				CString s21 = s2.Mid(250);
				SS.AddCell(s20, 5, i+2);
				SS.AddCell(s21, 6, i+2);
			}
			else
			{
				SS.AddCell(s2, 5, i+2); 
				SS.AddCell(_T(""), 6, i+2); 
			}
			cout<<s1<<endl;
			cout<<s2<<endl;
		}
		if(check2)
			SS.AddCell(s3, 4, i+2); 
	}
	SS.Commit();	
}
