#pragma once
#include "afxdb.h"  //连接数据库
#include "afxwin.h"

// CDlgMovieDetail 对话框

class CDlgMovieDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMovieDetail)

public:
	CDlgMovieDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMovieDetail();

// 对话框数据
	enum { IDD = IDD_MovieDetail };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	//新添加，数据库
private:
	CDatabase m_db;
public:
	CString fname;
	afx_msg void OnBnClickedOut();
	CStatic m_MovieDetail;
	CStatic m_BoxFname;
};
