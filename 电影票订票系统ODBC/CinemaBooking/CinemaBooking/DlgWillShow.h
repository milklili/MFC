#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //连接数据库
#include "DlgMovieDetail.h"
// CDlgWillShow 对话框

class CDlgWillShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWillShow)

public:
	CDlgWillShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWillShow();

// 对话框数据
	enum { IDD = IDD_WillShow };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListWillShow;
	//新添加，数据库
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	afx_msg void OnBnClickedMoviedetail();
	CString Fname;  //选中的影片名
};
