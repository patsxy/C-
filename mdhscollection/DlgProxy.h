
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CmdhscollectionDlg;


// CmdhscollectionDlgAutoProxy ����Ŀ��

class CmdhscollectionDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CmdhscollectionDlgAutoProxy)

	CmdhscollectionDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CmdhscollectionDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CmdhscollectionDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CmdhscollectionDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

