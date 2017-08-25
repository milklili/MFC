// DlgBuild.cpp : 实现文件
//

#include "stdafx.h"
#include "TabDemo.h"
#include "DlgBuild.h"
#include "afxdialogex.h"
#include "DlgTab1.h"


// CDlgBuild 对话框

IMPLEMENT_DYNAMIC(CDlgBuild, CDialogEx)

CDlgBuild::CDlgBuild(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBuild::IDD, pParent)
{

}

CDlgBuild::~CDlgBuild()
{
}

void CDlgBuild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBuild, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgBuild::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgBuild::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgBuild 消息处理程序


void CDlgBuild::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//m_treeJourney.InsertItem(_T("关于"),TVI_ROOT,TVI_LAST);//添加一个根节点
	 //获得EDIT 
	CEdit* pBoxOne; 
	pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT_NAME); 
	//取值
	CString str;
	pBoxOne-> GetWindowText(str); 

    HWND hWnd=::FindWindow(NULL,_T(""));      //得到对话框的句柄
    CDlgTab1* pWnd= (CDlgTab1*)FromHandle(hWnd); //由句柄得到对话框的对象指针
    pWnd->m_treeJourney.InsertItem(_T("str"),TVI_ROOT,TVI_LAST);//添加一个根节点                       
	MessageBox(str,_T("创建成功"),MB_OK);
	str.ReleaseBuffer();

	CDialogEx::OnOK();
}


void CDlgBuild::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
