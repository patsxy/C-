
// mdhscollectionDlg.h : ͷ�ļ�
//

#pragma once

class CmdhscollectionDlgAutoProxy;


// CmdhscollectionDlg �Ի���
class CmdhscollectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CmdhscollectionDlg);
	friend class CmdhscollectionDlgAutoProxy;

// ����
public:
	CmdhscollectionDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CmdhscollectionDlg();

// �Ի�������
	enum { IDD = IDD_MDHSCOLLECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CmdhscollectionDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
