// DlgTab1.cpp : 实现文件
//

#include "stdafx.h"
#include "cinemaODBC.h"
#include "DlgTab1.h"
#include "afxdialogex.h"


// CDlgTab1 对话框

IMPLEMENT_DYNAMIC(CDlgTab1, CDialogEx)

CDlgTab1::CDlgTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab1::IDD, pParent)
{

	m_EditFid = _T("");
	m_EditFname = _T("");
	m_EditDirector = _T("");
	m_EditProtagonist = _T("");
	m_EditType = _T("");
	m_EditReleasetime = _T("");
	m_EditDuration = _T("");
	m_EditNation = _T("");
	m_EditIntro = _T("");
	m_EditLanguage = _T("");
}

CDlgTab1::~CDlgTab1()
{
}

void CDlgTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILM, m_ListFilm);



	DDX_Text(pDX, IDC_EDIT_FID, m_EditFid);
	DDV_MaxChars(pDX, m_EditFid, 50);
	DDX_Text(pDX, IDC_EDIT_FNAME, m_EditFname);
	DDV_MaxChars(pDX, m_EditFname, 50);
	DDX_Text(pDX, IDC_EDIT_DIRECTOR, m_EditDirector);
	DDV_MaxChars(pDX, m_EditDirector, 50);
	DDX_Text(pDX, IDC_EDIT_PROTAGONIST, m_EditProtagonist);
	DDV_MaxChars(pDX, m_EditProtagonist, 50);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_EditType);
	DDV_MaxChars(pDX, m_EditType, 50);
	DDX_Text(pDX, IDC_EDIT_RELEASETIME, m_EditReleasetime);
	DDV_MaxChars(pDX, m_EditReleasetime, 50);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_EditDuration);
	DDV_MaxChars(pDX, m_EditDuration, 50);
	DDX_Text(pDX, IDC_EDIT_NATION, m_EditNation);
	DDV_MaxChars(pDX, m_EditNation, 50);
	DDX_Text(pDX, IDC_EDIT_INTRO, m_EditIntro);
	DDV_MaxChars(pDX, m_EditIntro, 200);
	DDX_Text(pDX, IDC_EDIT_LANGUAGE, m_EditLanguage);
	DDV_MaxChars(pDX, m_EditLanguage, 50);
}

BEGIN_MESSAGE_MAP(CDlgTab1, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILM, &CDlgTab1::OnBnClickedButtonSavefilm)
	ON_BN_CLICKED(IDC_BUTTON_DELEFILM, &CDlgTab1::OnBnClickedButtonDelefilm)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILM, &CDlgTab1::OnNMDblclkListFilm)
	ON_BN_CLICKED(IDC_BUTTON_ALTERFILM, &CDlgTab1::OnBnClickedButtonAlterfilm)
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CDlgTab1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	m_ListFilm.GetWindowRect(&rc);

	m_ListFilm.InsertColumn(0,_T("电影编号"),LVCFMT_CENTER,rc.Size().cx/4,0);
	m_ListFilm.InsertColumn(1,_T("电影名"),LVCFMT_CENTER,rc.Size().cx/4,1);
	m_ListFilm.InsertColumn(2,_T("上映时间"),LVCFMT_CENTER,rc.Size().cx/4,2);
	m_ListFilm.InsertColumn(3,_T("国家"),LVCFMT_CENTER,rc.Size().cx/4,3);
	m_ListFilm.InsertColumn(4,_T("导演"),LVCFMT_CENTER,rc.Size().cx/4,4);
	m_ListFilm.InsertColumn(5,_T("主演"),LVCFMT_CENTER,rc.Size().cx/4,5);
	m_ListFilm.InsertColumn(6,_T("类型"),LVCFMT_CENTER,rc.Size().cx/4,6);
	m_ListFilm.InsertColumn(7,_T("时长"),LVCFMT_CENTER,rc.Size().cx/4,7);
	m_ListFilm.InsertColumn(8,_T("简介"),LVCFMT_CENTER,rc.Size().cx/4,8);
	m_ListFilm.InsertColumn(9,_T("语言"),LVCFMT_CENTER,rc.Size().cx/4,9);


	m_ListFilm.SetExtendedStyle(m_ListFilm.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP|LVS_EX_TWOCLICKACTIVATE|LVS_EX_FLATSB);

	
	//将数据库film表的内容部分导入到listcontrol中
	UpdateData(TRUE);
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"链接错误！");
		return TRUE;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CString CDlgTab1::VariantToCString(CDBVariant*var)
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



// CDlgTab1 消息处理程序


void CDlgTab1::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	
	
}

//向数据库添加新的信息
void CDlgTab1::OnBnClickedButtonSavefilm()
{
	UpdateData(TRUE);
	//判断editcontrol获得的信息填写是否完整
	if( m_EditFid.IsEmpty()||m_EditFname.IsEmpty()||m_EditDirector.IsEmpty()||m_EditProtagonist.IsEmpty()||m_EditType.IsEmpty()
		||m_EditReleasetime.IsEmpty()||m_EditDuration.IsEmpty()||m_EditNation.IsEmpty()||m_EditIntro.IsEmpty()||m_EditLanguage.IsEmpty())
	{
       MessageBox(_T("请输入完整信息"),_T("注意"),MB_OK);
	}
	else
	{
		//连接数据库，打开数据源。IsOpen判断当前是否有一个连接；
		//CDatabase::openReadOnly 表示以只读方式打开数据源；
		//CDatabase::noOdbcDialog 表示不显示ODBC连接对话框
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"连接错误！");
			return;
		}
		try
		{
			
			CString sql;
			sql.Format(_T("insert into Film(fid,fname,releasetime,nation,director,protagonist,type,duration,intro,language) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"),
				       m_EditFid, m_EditFname, m_EditReleasetime, m_EditNation,m_EditDirector,m_EditProtagonist,m_EditType,m_EditDuration,m_EditIntro,m_EditLanguage);//执行插入一行的TSQL
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("该电影已存在或电影号没有按指定格式输入，请更改"),_T("注意"),MB_OK);
			pe->Delete();
		}
		m_db.Close();

		//将数据库film表的内容重新导入到listcontrol中
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"链接错误！");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}

//删除选中的信息
void CDlgTab1::OnBnClickedButtonDelefilm()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos=m_ListFilm.GetFirstSelectedItemPosition();//获取当前选中行的位置坐标
	if(pos==NULL)
	{
		MessageBox(_T("请选择一条记录！"),_T("注意"),MB_OK);//判断是否选中了其中一条
	}
	else
	{
		while(pos)
		{
			int index_item=m_ListFilm.GetNextSelectedItem(pos);
			TRACE(_T("item%d was selected!\n"),index_item);
			CString Bno=m_ListFilm.GetItemText(index_item,0);//获取选中行的第一列的数据
			//打开数据库删除数据库中对应的该列
			if(!m_db.IsOpen()&&!m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
			{
				MessageBox(L"链接错误！");
				return;
			}
			try
			{
				CString del;
				del.Format(_T("delete from Film where fid='%s'"),Bno);//执行删除操作的TSQL
				m_db.ExecuteSQL(del);
			}
			catch(CDBException*pe)
			{
				pe->ReportError();
				pe->Delete();
			}
			m_db.Close();
			m_ListFilm.DeleteItem(index_item);
		}
	}

}

//双击列表中的一项将信息导入到editcontrol
void CDlgTab1::OnNMDblclkListFilm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//UpdateData(TRUE);

	CString fid,fname,releasetime,nation,director,protagonist,type,duration,intro,language;
	int i = m_ListFilm.GetSelectionMark();//获取选中的行

	fid=m_ListFilm.GetItemText(i,0);//获取选中行的各列并传给变量
	fname=m_ListFilm.GetItemText(i,1);
	releasetime=m_ListFilm.GetItemText(i,2);
	nation=m_ListFilm.GetItemText(i,3);
	director=m_ListFilm.GetItemText(i,4);
	protagonist=m_ListFilm.GetItemText(i,5);
	type=m_ListFilm.GetItemText(i,6);
	duration=m_ListFilm.GetItemText(i,7);
	intro=m_ListFilm.GetItemText(i,8);
	language=m_ListFilm.GetItemText(i,9);

	m_EditFid=fid;                //将变量值传给各个editcontrol
	m_EditFname=fname;
	m_EditReleasetime=releasetime;
	m_EditNation=nation;
	m_EditDirector=director;
	m_EditProtagonist=protagonist;
	m_EditType=type;
	m_EditDuration=duration;
	m_EditIntro=intro;
	m_EditLanguage=language;

	UpdateData(FALSE);
   
}

//重新更新保存修改过的信息
void CDlgTab1::OnBnClickedButtonAlterfilm()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//先判断传入的参数是否为空
	if( m_EditFid.IsEmpty()||m_EditFname.IsEmpty()||m_EditDirector.IsEmpty()||m_EditProtagonist.IsEmpty()||m_EditType.IsEmpty()
		||m_EditReleasetime.IsEmpty()||m_EditDuration.IsEmpty()||m_EditNation.IsEmpty()||m_EditIntro.IsEmpty()||m_EditLanguage.IsEmpty())
	{
       MessageBox(_T("请输入完整信息"),_T("注意"),MB_OK);
	}
	else
	{
		//连接数据库，打开数据源。IsOpen判断当前是否有一个连接；
		//CDatabase::openReadOnly 表示以只读方式打开数据源；
		//CDatabase::noOdbcDialog 表示不显示ODBC连接对话框
		if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			MessageBox(L"连接错误！");
			return;
		}
		try
		{
			
			CString sql;
			sql.Format(_T("update Film set fname='%s', releasetime='%s', nation='%s',director='%s', protagonist='%s', type='%s', duration='%s',intro='%s',language='%s'where fid='%s'"),
				       m_EditFname, m_EditReleasetime, m_EditNation,m_EditDirector,m_EditProtagonist,m_EditType,m_EditDuration,m_EditIntro,m_EditLanguage, m_EditFid);//执行更新的TSQL语句
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			//pe->ReportError();
			MessageBox(_T("该电影已存在或电影号没有按指定格式，请更改"),_T("注意"),MB_OK);
			pe->Delete();
		}
		m_db.Close();

	//将数据库film表的内容分重新导入到listcontrol中
	if(!m_db.IsOpen()&& !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),CDatabase::openReadOnly|CDatabase::noOdbcDialog))
	{
		MessageBox(L"链接错误！");
		return;
	}
	CRecordset m_set(&m_db);

	m_set.Open(CRecordset::forwardOnly,_T("select * from Film"),CRecordset::readOnly);
	CDBVariant var;
	m_ListFilm.DeleteAllItems();
	short nFields=m_set.GetODBCFieldCount();
	for(int i=0;!m_set.IsEOF();i++,m_set.MoveNext())
	{
		for(short index=0;index< nFields;index++)
		{
			m_set.GetFieldValue(index,var);
			if(index==0)
				m_ListFilm.InsertItem(i,VariantToCString(&var));
			else
				m_ListFilm.SetItemText(i,index,VariantToCString(&var));

		}
	}
	m_set.Close();
	m_db.Close();
	
	}
	
}

