#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new

// CDlgTab5 对话框

class CDlgTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab5)

public:
	CDlgTab5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab5();

// 对话框数据
	enum { IDD = IDD_DLGTAB_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;//new
public:
	virtual BOOL OnInitDialog();
	CString VariantToCString(CDBVariant*var);//new
	CListCtrl m_ListAccount;
};
