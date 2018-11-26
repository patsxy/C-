
// mdhscollectionDlg.h : 头文件
//

#pragma once

class CmdhscollectionDlgAutoProxy;


// CmdhscollectionDlg 对话框
class CmdhscollectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CmdhscollectionDlg);
	friend class CmdhscollectionDlgAutoProxy;

// 构造
public:
	CmdhscollectionDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CmdhscollectionDlg();

// 对话框数据
	enum { IDD = IDD_MDHSCOLLECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CmdhscollectionDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
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
