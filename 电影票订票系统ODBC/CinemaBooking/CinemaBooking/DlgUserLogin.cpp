// DlgUserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgUserLogin.h"
#include "afxdialogex.h"


// CDlgUserLogin 对话框

IMPLEMENT_DYNAMIC(CDlgUserLogin, CDialogEx)

CDlgUserLogin::CDlgUserLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUserLogin::IDD, pParent)
	, m_ID(_T(""))
	, m_PassWord(_T(""))
{

}

CDlgUserLogin::~CDlgUserLogin()
{
}

void CDlgUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Name, m_ID);
	DDX_Text(pDX, IDC_EDIT_PassWord, m_PassWord);
}


BEGIN_MESSAGE_MAP(CDlgUserLogin, CDialogEx)
	ON_BN_CLICKED(IDC_DengLu, &CDlgUserLogin::OnBnClickedDenglu)
	ON_BN_CLICKED(IDC_ZhuCe, &CDlgUserLogin::OnBnClickedZhuce)
	ON_BN_CLICKED(IDC_OUT, &CDlgUserLogin::OnBnClickedOut)
END_MESSAGE_MAP()


// CDlgUserLogin 消息处理程序
BOOL CDlgUserLogin::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgUserLogin::OnBnClickedDenglu()
{
	// TODO:  在此添加控件通知处理程序代码
	//连接数据库，打开数据源。IsOpen判断当前是否有一个连接；
	//CDatabase::openReadOnly 表示以只读方式打开数据源；
	//CDatabase::noOdbcDialog 表示不显示ODBC连接对话框
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_set(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	m_set.Open(CRecordset::forwardOnly, _T("select * from Account"), CRecordset::readOnly);
	if (!m_set.IsEOF())
	{
		while (!m_set.IsEOF())
		{
			UpdateData(TRUE);
			CString sID, sPassWord;
			short index = 0;
			m_set.GetFieldValue(index, sID);//取出第一个字段的值，放到sID中 
			m_set.GetFieldValue(1, sPassWord);//取出第二个值放到sPassWord中 
			if ((_tcscmp(sID, m_ID) == 0) && (_tcscmp(sPassWord, m_PassWord) == 0))
			{
				//MessageBox(L"登陆成功");
				CDialogEx::OnOK();
				return;
			}
			m_set.MoveNext();
		}
		MessageBox(L"登录失败，用户名不存在或者密码错误！");
		return;
	}
	m_set.Close();
	m_db.Close();

	
}


void CDlgUserLogin::OnBnClickedZhuce()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgZhuCe m_DlgZhuCe;
	m_DlgZhuCe.DoModal();
}


void CDlgUserLogin::OnBnClickedOut()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(0);
}
