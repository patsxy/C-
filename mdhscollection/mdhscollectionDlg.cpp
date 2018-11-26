/*
* 主板和cpu 信息收集
* @author: 宋勇
*/
// mdhscollectionDlg.cpp : 实现文件
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
//						主板序列号 -- 获取不到时为 None
//--------------------------------------------------------------
BOOL GetBaseBoardByCmd(char *lpszBaseBoard, int len/*=128*/)
{
	const long MAX_COMMAND_SIZE = 10000; // 命令行输出缓冲大小	
	char szFetCmd[] = "wmic BaseBoard get SerialNumber"; // 获取主板序列号命令行	
	const string strEnSearch = "SerialNumber"; // 主板序列号的前导信息

	BOOL   bret = FALSE;
	HANDLE hReadPipe = NULL; //读取管道
	HANDLE hWritePipe = NULL; //写入管道	
	PROCESS_INFORMATION pi;   //进程信息	
	STARTUPINFO			si;	  //控制命令行窗口信息
	SECURITY_ATTRIBUTES sa;   //安全属性

	char			szBuffer[MAX_COMMAND_SIZE + 1] = { 0 }; // 放置命令行结果的输出缓冲区
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

	//1.0 创建管道
	bret = CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);
	if (!bret)
	{
		goto END;
	}

	//2.0 设置命令行窗口的信息为指定的读写管道
	GetStartupInfo(&si);
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	si.wShowWindow = SW_HIDE; //隐藏命令行窗口
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//3.0 创建获取命令行的进程
	bret = CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (!bret)
	{
		goto END;
	}

	//4.0 读取返回的数据
	WaitForSingleObject(pi.hProcess, 500/*INFINITE*/);
	bret = ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0);
	if (!bret)
	{
		goto END;
	}

	//5.0 查找主板序列号
	bret = FALSE;
	strBuffer = szBuffer;
	ipos = strBuffer.find(strEnSearch);

	if (ipos < 0) // 没有找到
	{
		goto END;
	}
	else
	{
		strBuffer = strBuffer.substr(ipos + strEnSearch.length());
	}

	memset(szBuffer, 0x00, sizeof(szBuffer));
	strcpy_s(szBuffer, strBuffer.c_str());

	//去掉中间的空格 \r \n
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
	//关闭所有的句柄
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return(bret);
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CmdhscollectionDlg 对话框




IMPLEMENT_DYNAMIC(CmdhscollectionDlg, CDialogEx);

CmdhscollectionDlg::CmdhscollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmdhscollectionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CmdhscollectionDlg::~CmdhscollectionDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
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


// CmdhscollectionDlg 消息处理程序

BOOL CmdhscollectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
// 如果向对话框添加最小化按钮，则需要下面的代码
//  这将由框架自动完成。

void CmdhscollectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmdhscollectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

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
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
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
		// TODO: 在此添加控件通知处理程序代码
		string VernderID;
		unsigned char vendor_id[] = "------------";
		__asm {
			xor eax, eax      //eax=0:取Vendor信息
				cpuid    //取cpu id指令，可在Ring3级使用
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



		//加密
		string cpuEn = my3Des->desEncrypt(my3Des->desEncrypt(strCPU));

		string brodEn = my3Des->desEncrypt(my3Des->desEncrypt(n_Brod));

		string  myCpuBrod=cpuEn+","+brodEn;

		string  cpuBordEn=my3Des->desEncrypt(myCpuBrod);


		char szFilePath[MAX_PATH + 1] = { 0 };


		GetModuleFileName(NULL, szFilePath, MAX_PATH);


		(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径

		if (_access(szFilePath,0) == -1)
			return;


		strcat(szFilePath, "\\lc.c"); 

	    stringstream newsFilePath;

		newsFilePath<<szFilePath;

		const  char*	newCharTimes = cpuBordEn.c_str();
		//写入刚才读取的文件
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

		string   lscn= "生成文件："+newsFilePath.str()+" 成功";
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

		cout << "采集数据错误！！" << endl;
		return;
	}

}
