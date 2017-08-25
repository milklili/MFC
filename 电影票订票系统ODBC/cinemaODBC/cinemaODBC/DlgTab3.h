#pragma once
#include "afxcmn.h"
#include "afxdb.h"//new
// CDlgTab3 对话框

class CDlgTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab3)

public:
	CDlgTab3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab3();

// 对话框数据
	enum { IDD = IDD_DLGTAB_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CDatabase m_db;//new
public:
	CListCtrl m_ListSchedule;
//	CString m_ComFid;
//	CString m_ComTid;
//	CString m_ComPrice;
//	CString m_ComNum;
	CString m_EditStart;
	CString m_EditEnd;
	CString m_EditSid;
	CString VariantToCString(CDBVariant*var);//new
	afx_msg void OnBnClickedButtonDeleschedule();
	afx_msg void OnBnClickedButtonAddschedule();
//	CComboBox m_ComFid;
	CComboBox m_ComTid;
	CComboBox m_ComFid;
//	CComboBox m_ComNum;
//	CComboBox m_ComPrice;
	CString m_EditPrice;
	CString m_EditNum;
	afx_msg void OnBnClickedButtonAlterschedule();
	afx_msg void OnNMDblclkListSchedule(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditEndtime();
};
