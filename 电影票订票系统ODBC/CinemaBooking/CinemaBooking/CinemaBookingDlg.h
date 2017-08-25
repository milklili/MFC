
// CinemaBookingDlg.h : 头文件
//
#include "DlgShowing.h"   
#include "DlgWillShow.h"
#include "DlgMyOrder.h"
#include "DlgMovieDetail.h"
#include "DlgBookTicket.h"
#include "DlgUserLogin.h"

#include "TraButton.h"  //透明按钮

#pragma once


// CCinemaBookingDlg 对话框
class CCinemaBookingDlg : public CDialogEx
{
// 构造
public:
	CCinemaBookingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CINEMABOOKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//新建两个标签页
	CDlgShowing *m_DlgShowing;
	CDlgWillShow *m_DlgWillShow;
	afx_msg void OnBnClickedShowing();
	afx_msg void OnBnClickedWillshow();
	//弹出一个页面，显示我的订单
	afx_msg void OnBnClickedMyorder();
public:
	//透明按钮
	CTraButton m_btn1;
	CTraButton m_btn2;
	CTraButton m_btn3;
	CTraButton m_btn4;

	
	afx_msg void OnBnClickedOutlogin();
	
	CString m_StaticID;
public:
	CString ID; //设置一个全局变量，为账户名
};
