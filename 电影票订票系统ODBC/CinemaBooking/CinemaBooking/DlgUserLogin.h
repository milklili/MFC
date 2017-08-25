#pragma once


// CDlgUserLogin 对话框
#include "DlgZhuCe.h"
#include "afxdb.h"  //连接数据库

class CDlgUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUserLogin)

public:
	CDlgUserLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserLogin();

// 对话框数据
	enum { IDD = IDD_UserLogin };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDenglu();
	afx_msg void OnBnClickedZhuce();
	CString m_ID;
	CString m_PassWord;
	//新添加，数据库
private:
	CDatabase m_db;
	BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedOut();
};
