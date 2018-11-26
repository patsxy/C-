
// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CmdhscollectionDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_Imdhscollection ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {1D56D1A4-23ED-44E7-886A-E79DE4694C3A}
static const IID IID_Imdhscollection =
{ 0x1D56D1A4, 0x23ED, 0x44E7, { 0x88, 0x6A, 0xE7, 0x9D, 0xE4, 0x69, 0x4C, 0x3A } };

BEGIN_INTERFACE_MAP(CmdhscollectionDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CmdhscollectionDlgAutoProxy, IID_Imdhscollection, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {C60DBDED-60A8-4453-808E-D4D6B4DB9C5F}
IMPLEMENT_OLECREATE2(CmdhscollectionDlgAutoProxy, "mdhscollection.Application", 0xc60dbded, 0x60a8, 0x4453, 0x80, 0x8e, 0xd4, 0xd6, 0xb4, 0xdb, 0x9c, 0x5f)


// CmdhscollectionDlgAutoProxy ��Ϣ�������
