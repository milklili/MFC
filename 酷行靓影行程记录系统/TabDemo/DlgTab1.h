#pragma once
#include "explorer2.h"
#include "afxcmn.h"
static CString ss;
#include"exif.h"
// CDlgTab1 对话框

class CDlgTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTab1();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HTREEITEM m_itemCur;
	EXIFINFO m_exifinfo;
	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_list;
	CImageList a;
	//int InitListCtrlStyle(void);
	//int RefreshListCtrlData(void);
	//afx_msg void OnOpenpic();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonOpenmap2();
	CExplorer2 m_mymap;
	
	CTreeCtrl m_treeJourney;
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMClickTreeJourney(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonNewOne();
	afx_msg void OnNMRClickTreeJourney(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuDelete();
	afx_msg void OnBnClickedButtonOpenmap3();
	afx_msg void OnBnClickedButtonWritepic();
	afx_msg void OnBnClickedButtonPicin();
	bool PromptForFileName(CString& fileName, UINT nIDSTitle, DWORD dwFlags, bool bOpenFileDialog, int* pType);
	void ShowInfoo(void);
	afx_msg void OnBnClickedButtonTrack();
};
