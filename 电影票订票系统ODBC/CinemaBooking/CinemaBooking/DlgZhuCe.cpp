// DlgZhuCe.cpp : 实现文件
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgZhuCe.h"
#include "afxdialogex.h"


// CDlgZhuCe 对话框

IMPLEMENT_DYNAMIC(CDlgZhuCe, CDialogEx)

CDlgZhuCe::CDlgZhuCe(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgZhuCe::IDD, pParent)
{
	m_id = _T("");
	m_password = _T("");
	m_name = _T("");
	m_tele = _T("");
}

CDlgZhuCe::~CDlgZhuCe()
{
}

void CDlgZhuCe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_id, m_id);
	DDX_Text(pDX, IDC_password, m_password);
	DDX_Text(pDX, IDC_name, m_name);
	DDX_Text(pDX, IDC_tele, m_tele);
}


BEGIN_MESSAGE_MAP(CDlgZhuCe, CDialogEx)
	ON_BN_CLICKED(IDC_ZhuCeOK, &CDlgZhuCe::OnBnClickedZhuceok)
END_MESSAGE_MAP()


// CDlgZhuCe 消息处理程序


void CDlgZhuCe::OnBnClickedZhuceok()
{
	// TODO:  在此添加控件通知处理程序代码
	
	/*CRecordset m_set(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	m_set.Open(CRecordset::forwardOnly, _T("select * from Account"), CRecordset::readOnly);
	CDBVariant var;
	*/
	UpdateData(TRUE);
	if (m_id.IsEmpty() || m_password.IsEmpty() || m_name.IsEmpty() || m_tele.IsEmpty())
	{
		MessageBox(L"注册相关信息不可以为空，注册失败！");
	}
	else
	{
		//连接数据库，打开数据源。IsOpen判断当前是否有一个连接；
		//CDatabase::openReadOnly 表示以只读方式打开数据源；
		//CDatabase::noOdbcDialog 表示不显示ODBC连接对话框
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
			CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"连接错误！");
			return;
		}
		try
		{			
			CString sql;
			sql.Format(_T("insert into Account(id,password,name,tele) values('%s','%s','%s','%s')"), m_id, m_password, m_name, m_tele);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("该账号已被注册！ 请更改账户名！"),_T("注意"),MB_OK);
			pe->Delete();
		}
		m_db.Close();
	}
	CDialogEx::OnOK();
}
