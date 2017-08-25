// DlgBefore.cpp : 实现文件
//

#include "stdafx.h"
#include "TabDemo.h"
#include "DlgBefore.h"
#include "afxdialogex.h"

#include "TabDemoDlg.h"

// CDlgBefore 对话框

IMPLEMENT_DYNAMIC(CDlgBefore, CDialogEx)

CDlgBefore::CDlgBefore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBefore::IDD, pParent)
{

	m_csID = _T("");
}

CDlgBefore::~CDlgBefore()
{
}

void CDlgBefore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_csID);
	DDV_MaxChars(pDX, m_csID, 8);
}


BEGIN_MESSAGE_MAP(CDlgBefore, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgBefore::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgBefore::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_ID, &CDlgBefore::OnEnChangeEditId)
END_MESSAGE_MAP()


// CDlgBefore 消息处理程序


void CDlgBefore::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CTabDemoDlg m_TabDemoDlg;

	m_TabDemoDlg.m_pParent = this;
	
	m_TabDemoDlg.DoModal();

	

	CDialogEx::OnOK();
}

void CDlgBefore::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}




void CDlgBefore::OnEnChangeEditId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
