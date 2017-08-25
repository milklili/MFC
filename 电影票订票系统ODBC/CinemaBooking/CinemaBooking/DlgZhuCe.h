#pragma once
#include "afxwin.h"
#include "afxdb.h"  //连接数据库

// CDlgZhuCe 对话框

class CDlgZhuCe : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgZhuCe)

public:
	CDlgZhuCe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgZhuCe();

// 对话框数据
	enum { IDD = IDD_ZhuCe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedZhuceok();
	CString m_id;
	CString m_password;
	CString m_name;
	CString m_tele;
//新添加，数据库
private:
	CDatabase m_db;

};
