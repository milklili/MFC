#pragma once
#include "afxcmn.h"
#include "afxdb.h"  //连接数据库

// CDlgMyOrder 对话框

class CDlgMyOrder : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMyOrder)

public:
	CDlgMyOrder(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMyOrder();

// 对话框数据
	enum { IDD = IDD_MyOrder };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListOrderInfo;
	//新添加，数据库
private:
	CDatabase m_db;
public:
	CString VariantToCString(CDBVariant* var);
	CString orderID;
	afx_msg void OnBnClickedOut();
};
