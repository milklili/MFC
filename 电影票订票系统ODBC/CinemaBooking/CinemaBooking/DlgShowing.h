#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //连接数据库
#include "DlgMovieDetail.h"
#include "DlgBookTicket.h"

// CDlgShowing 对话框

class CDlgShowing : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowing)

public:
	CDlgShowing(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShowing();

// 对话框数据
	enum { IDD = IDD_Showing };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListShowing;
	//新添加，数据库
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	afx_msg void OnBnClickedMoviedetail();
	CString Fname,Id;  //选中的影片名
	afx_msg void OnBnClickedBookticket();
};
