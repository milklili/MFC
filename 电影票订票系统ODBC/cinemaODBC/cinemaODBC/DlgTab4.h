#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab4 对话框

class CDlgTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab4)

public:
	CDlgTab4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab4();

// 对话框数据
	enum { IDD = IDD_DLGTAB_ORDERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;//new
public:
	CListCtrl m_ListOrders;
	CString VariantToCString(CDBVariant*var);//new
	virtual BOOL OnInitDialog();
};
