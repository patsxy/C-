/*
* �����cpu ��Ϣ�ռ�
* @author: ����
*/
// mdhscollectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mdhscollection.h"
#include "mdhscollectionDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <string>
#include <iostream>
#include <sstream>
#include  <stdio.h>
#include  <io.h>
#include <cctype>
#include <algorithm>
#include "windows.h"

#include "des.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

//--------------------------------------------------------------
//						�������к� -- ��ȡ����ʱΪ None
//--------------------------------------------------------------
BOOL GetBaseBoardByCmd(char *lpszBaseBoard, int len/*=128*/)
{
	const long MAX_COMMAND_SIZE = 10000; // ��������������С	
	char szFetCmd[] = "wmic BaseBoard get SerialNumber"; // ��ȡ�������к�������	
	const string strEnSearch = "SerialNumber"; // �������кŵ�ǰ����Ϣ

	BOOL   bret = FALSE;
	HANDLE hReadPipe = NULL; //��ȡ�ܵ�
	HANDLE hWritePipe = NULL; //д��ܵ�	
	PROCESS_INFORMATION pi;   //������Ϣ	
	STARTUPINFO			si;	  //���������д�����Ϣ
	SECURITY_ATTRIBUTES sa;   //��ȫ����

	char			szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // ���������н�������������
	string			strBuffer;
	unsigned long	count = 0;
	long			ipos = 0;

	memset(&pi, 0, sizeof(pi));
	memset(&si, 0, sizeof(si));
	memset(&sa, 0, sizeof(sa));

	pi.hProcess = NULL;
	pi.hThread = NULL;
	si.cb = sizeof(STARTUPINFO);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//1.0 �����ܵ�
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		goto END;
	}

	//2.0 ���������д��ڵ���ϢΪָ���Ķ�д�ܵ�
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //���������д���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//3.0 ������ȡ�����еĽ���
	bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (!bret)
	{
		goto END;
	}

	//4.0 ��ȡ���ص�����
	WaitForSingleObject(pi.hProcess, 500/*INFINITE*/);
	bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
	if (!bret)
	{
		goto END;
	}

	//5.0 �����������к�
	bret = FALSE;
	strBuffer = szBuffer;
	ipos = strBuffer.find(strEnSearch);

	if (ipos < 0) // û���ҵ�
	{
		goto END;
	}
	else
	{
		strBuffer = strBuffer.substr(ipos + strEnSearch.length());
	}

	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());

	//ȥ���м�Ŀո� \r \n
	int j = 0;
	for (int i = 0; i < (int)strlen(szBuffer); i++)
	{
		if (szBuffer[i] != ' ' && szBuffer[i] != '\n' && szBuffer[i] != '\r' && szBuffer[i] != '/')
		{
			lpszBaseBoard[j] = szBuffer[i];
			j++;
		}
	}

	bret = TRUE;

END:
	//�ر����еľ��
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return(bret);
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

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmdhscollectionDlg �Ի���




IMPLEMENT_DYNAMIC(CmdhscollectionDlg, CDialogEx);

CmdhscollectionDlg::CmdhscollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmdhscollectionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CmdhscollectionDlg::~CmdhscollectionDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CmdhscollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmdhscollectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmdhscollectionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CmdhscollectionDlg ��Ϣ�������

BOOL CmdhscollectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmdhscollectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �⽫�ɿ���Զ���ɡ�

void CmdhscollectionDlg::OnPaint()
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
HCURSOR CmdhscollectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CmdhscollectionDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CmdhscollectionDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CmdhscollectionDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CmdhscollectionDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

int charlen(const char *p)
{
	int i = 0;
	while (*p++)i++;
	return i;
}



void CmdhscollectionDlg::OnBnClickedOk()
{
	Des* my3Des;

	try {
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		string VernderID;
		unsigned char vendor_id[] = "------------";
		__asm {
			xor eax, eax      //eax=0:ȡVendor��Ϣ
				cpuid    //ȡcpu idָ�����Ring3��ʹ��
				mov dword ptr vendor_id, ebx
				mov dword ptr vendor_id[+4], edx
				mov dword ptr vendor_id[+8], ecx
		}

		VernderID = (char*)vendor_id;


		string strCPUID;
		char  charS1[20], charS2[20];
		unsigned long s1, s2;
		__asm {
			mov eax, 01h
				xor edx, edx
				cpuid
				mov s1, edx
				mov s2, eax
		}

		_itoa(s1, charS1, 16);
		_itoa(s2, charS2, 16);
		strCPUID = charS1;
		strCPUID += charS2;




		string strCPU = strCPUID;


		transform(strCPU.begin(), strCPU.end(), strCPU.begin(), toupper);

		char mBrod[128];
		memset(mBrod, 0x00, sizeof(mBrod));
		GetBaseBoardByCmd(mBrod, 128);
		string n_Brod = mBrod;




		char* STRING_DES_KEY = "V878rkXvmLglkGgNJz9LPq7PdgynNQWi7VDX6KJ2vCdF9cVm";


		 
		my3Des = new Des(STRING_DES_KEY);



		//����
		string cpuEn = my3Des->desEncrypt(my3Des->desEncrypt(strCPU));

		string brodEn = my3Des->desEncrypt(my3Des->desEncrypt(n_Brod));

		string  myCpuBrod=cpuEn+","+brodEn;

		string  cpuBordEn=my3Des->desEncrypt(myCpuBrod);


		char szFilePath[MAX_PATH + 1] = { 0 };


		GetModuleFileName(NULL, szFilePath, MAX_PATH);


		(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //ɾ���ļ�����ֻ���·��

		if (_access(szFilePath,0) == -1)
			return;


		strcat(szFilePath, "\\lc.c"); 

	    stringstream newsFilePath;

		newsFilePath<<szFilePath;

		const  char*	newCharTimes = cpuBordEn.c_str();
		//д��ղŶ�ȡ���ļ�
		FILE *pFileOut = fopen(szFilePath, "wb");
		int	len = charlen(newCharTimes);
		fwrite(newCharTimes, 1, len, pFileOut);
		fclose(pFileOut);


		newCharTimes = nullptr;

		if (my3Des)
		{

			my3Des->clear_key();
			FreeResource(&my3Des);
			free(my3Des);
			my3Des = nullptr;
			delete my3Des;
		}

		string   lscn= "�����ļ���"+newsFilePath.str()+" �ɹ�";
		MessageBox(lscn.c_str());
	}catch (...) {
		if (my3Des)
		{
			//TRIPLE_DES_KEY=nullptr;
			my3Des->clear_key();
			FreeResource(&my3Des);
			free(my3Des);
			my3Des = nullptr;
			delete my3Des;
			//free(TRIPLE_DES_KEY);
			//delete my3Des;
			// DeleteObject(&my3Des);
		}

		cout << "�ɼ����ݴ��󣡣�" << endl;
		return;
	}

}
