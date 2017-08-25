// DlgWillShow.cpp : 实现文件
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgWillShow.h"
#include "afxdialogex.h"


// CDlgWillShow 对话框

IMPLEMENT_DYNAMIC(CDlgWillShow, CDialogEx)

CDlgWillShow::CDlgWillShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWillShow::IDD, pParent)
{

}

CDlgWillShow::~CDlgWillShow()
{
}
CString CDlgWillShow::VariantToCString(CDBVariant*var)
{
	CString str_conv;  //存放转换后的内容
	if (!var)
	{
		str_conv = "NULL Var Parameter";
		return str_conv;
	}
	switch (var->m_dwType)
	{
	case DBVT_SHORT:
		str_conv.Format(L"%d", (int)var->m_iVal);
		break;
	case DBVT_LONG:
		str_conv.Format(L"%d", var->m_lVal);
		break;
	case DBVT_SINGLE:
		str_conv.Format(L"%10.6f", (double)var->m_fltVal);
		break;
	case DBVT_DOUBLE:
		str_conv.Format(L"%10.6f", var->m_dblVal);
		break;
	case DBVT_BOOL:
		str_conv = (var->m_boolVal == 0) ? L"FALSE" : L"TURE";
		break;
	case DBVT_STRING:
		str_conv = var->m_pstring->GetBuffer();
		break;
	case DBVT_ASTRING:
		str_conv = var->m_pstringA->GetBuffer();
		break;
	case DBVT_WSTRING:
		str_conv = var->m_pstringW->GetBuffer();
		break;
	case DBVT_DATE:
		str_conv.Format(L"%d-%d-%d", (var->m_pdate)->year, (var->m_pdate)->month, (var->m_pdate)->day);
		break;
	default:
		str_conv.Format(L"UnKnown type %d\n", var->m_dwType);
		TRACE(L"UnKnown type %d\n", var->m_dwType);

	}
	return str_conv;
}
void CDlgWillShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WillShow, m_ListWillShow);
	CRect rc;
	m_ListWillShow.GetWindowRect(&rc);

	m_ListWillShow.InsertColumn(0, _T("电影名"), LVCFMT_CENTER, rc.Size().cx / 4, 0);
	m_ListWillShow.InsertColumn(1, _T("国家"), LVCFMT_CENTER, rc.Size().cx / 8, 1);
	m_ListWillShow.InsertColumn(2, _T("导演"), LVCFMT_CENTER, rc.Size().cx / 8, 2);
	m_ListWillShow.InsertColumn(3, _T("主演"), LVCFMT_CENTER, rc.Size().cx / 4, 3);
	m_ListWillShow.InsertColumn(4, _T("类型"), LVCFMT_CENTER, rc.Size().cx / 8, 4);
	m_ListWillShow.InsertColumn(5, _T("上映日期"), LVCFMT_CENTER, rc.Size().cx / 8, 5);

	m_ListWillShow.SetExtendedStyle(m_ListWillShow.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP | LVS_EX_TWOCLICKACTIVATE | LVS_EX_FLATSB);


	//将数据库film表的内容部分导入到listcontrol中
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_set(&m_db);
	m_set.Open(CRecordset::forwardOnly, _T("select fname,nation,director,protagonist,type,releasetime from Film where releasetime > getdate()"), CRecordset::readOnly);
	CDBVariant var;
	m_ListWillShow.DeleteAllItems();
	short nFields = m_set.GetODBCFieldCount();
	for (int i = 0; !m_set.IsEOF(); i++, m_set.MoveNext())
	{
		for (short index = 0; index < nFields; index++)
		{
			m_set.GetFieldValue(index, var);
			if (index == 0)
				m_ListWillShow.InsertItem(i, VariantToCString(&var));
			else
				m_ListWillShow.SetItemText(i, index, VariantToCString(&var));
		}
	}
	m_set.Close();
	m_db.Close();
}


BEGIN_MESSAGE_MAP(CDlgWillShow, CDialogEx)
	ON_BN_CLICKED(IDC_MovieDetail, &CDlgWillShow::OnBnClickedMoviedetail)
END_MESSAGE_MAP()


// CDlgWillShow 消息处理程序


void CDlgWillShow::OnBnClickedMoviedetail()
{
	// TODO:  在此添加控件通知处理程序代码

	POSITION pos = m_ListWillShow.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请选择一个电影！");
	}
	else
	{
		while (pos)
		{
			int index_item = m_ListWillShow.GetNextSelectedItem(pos);
			TRACE(_T("item %d was selected!\n"), index_item);
			Fname = m_ListWillShow.GetItemText(index_item, 0);
			//取消选中行
			m_ListWillShow.SetItemState(index_item, 0, LVIS_SELECTED | LVIS_FOCUSED);
			CDlgMovieDetail m_DlgMovieDetail;
			m_DlgMovieDetail.fname = Fname;
			m_DlgMovieDetail.DoModal();
		}
	}
}
