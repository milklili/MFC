#pragma once
#include "explorer1.h"


// CDlgMap 对话框

class CDlgMap : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMap)

public:
	CDlgMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMap();

// 对话框数据
	enum { IDD = IDD_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CExplorer1 m_map;
	afx_msg void OnBnClickedButtonOpenmap();
	afx_msg void OnBnClickedButtonPutin();
};
