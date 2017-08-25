
// cinemaODBCDlg.h : 头文件
//

#pragma once
#include "DlgTab1.h"
#include "DlgTab2.h"
#include "DlgTab3.h"
#include "DlgTab4.h"
#include "DlgTab5.h"
#include "afxdb.h"//new


// CcinemaODBCDlg 对话框
class CcinemaODBCDlg : public CDialogEx
{
// 构造
public:
	CcinemaODBCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CINEMAODBC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;

	CDlgTab1 m_tab1;
	CDlgTab2 m_tab2;
	CDlgTab3 m_tab3;
	CDlgTab4 m_tab4;
	CDlgTab5 m_tab5;

	afx_msg void OnBnClickedButtonAddfilm();
	afx_msg void OnBnClickedButtonAddcinema();
	afx_msg void OnBnClickedButtonAddschedule();
	afx_msg void OnSelchangeTabUser(NMHDR *pNMHDR, LRESULT *pResult);
};
