
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "mdhscollection.h"
#include "DlgProxy.h"
#include "mdhscollectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmdhscollectionDlgAutoProxy

IMPLEMENT_DYNCREATE(CmdhscollectionDlgAutoProxy, CCmdTarget)

CmdhscollectionDlgAutoProxy::CmdhscollectionDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CmdhscollectionDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CmdhscollectionDlg)))
		{
			m_pDialog = reinterpret_cast<CmdhscollectionDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CmdhscollectionDlgAutoProxy::~CmdhscollectionDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CmdhscollectionDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_Imdhscollection 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {1D56D1A4-23ED-44E7-886A-E79DE4694C3A}
static const IID IID_Imdhscollection =
{ 0x1D56D1A4, 0x23ED, 0x44E7, { 0x88, 0x6A, 0xE7, 0x9D, 0xE4, 0x69, 0x4C, 0x3A } };

BEGIN_INTERFACE_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CmdhscollectionDlgAutoProxy, IID_Imdhscollection, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {C60DBDED-60A8-4453-808E-D4D6B4DB9C5F}
IMPLEMENT_OLECREATE2(CmdhscollectionDlgAutoProxy, "mdhscollection.Application", 0xc60dbded, 0x60a8, 0x4453, 0x80, 0x8e, 0xd4, 0xd6, 0xb4, 0xdb, 0x9c, 0x5f)


// CmdhscollectionDlgAutoProxy 消息处理程序
