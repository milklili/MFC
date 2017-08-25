// DlgBookTicket.cpp : 实现文件
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "DlgBookTicket.h"
#include "afxdialogex.h"

const COLORREF BLACK = RGB(1, 1, 1);
const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF DKGRAY = RGB(128, 128, 128);
const COLORREF LLTGRAY = RGB(220, 220, 220);
const COLORREF LTGRAY = RGB(192, 192, 192);
const COLORREF YELLOW = RGB(255, 255, 0);
const COLORREF DKYELLOW = RGB(128, 128, 0);
const COLORREF RED = RGB(255, 0, 0);
const COLORREF DKRED = RGB(128, 0, 0);
const COLORREF BLUE = RGB(3, 122, 169);
const COLORREF LBLUE = RGB(192, 192, 255);
const COLORREF DKBLUE = RGB(0, 0, 128);
const COLORREF CYAN = RGB(0, 255, 255);
const COLORREF DKCYAN = RGB(0, 128, 128);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF DKGREEN = RGB(0, 128, 0);
const COLORREF MAGENTA = RGB(255, 0, 255);
const COLORREF DKMAGENTA = RGB(128, 0, 128);
bool a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
// CDlgBookTicket 对话框

IMPLEMENT_DYNAMIC(CDlgBookTicket, CDialogEx)

CDlgBookTicket::CDlgBookTicket(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBookTicket::IDD, pParent)
{

}

CDlgBookTicket::~CDlgBookTicket()
{
}

void CDlgBookTicket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTOND4, m_d4);
	DDX_Control(pDX, IDC_BUTTOND3, m_d3);
	DDX_Control(pDX, IDC_BUTTOND2, m_d2);
	DDX_Control(pDX, IDC_BUTTOND1, m_d1);
	DDX_Control(pDX, IDC_BUTTONC4, m_c4);
	DDX_Control(pDX, IDC_BUTTONC3, m_c3);
	DDX_Control(pDX, IDC_BUTTONC2, m_c2);
	DDX_Control(pDX, IDC_BUTTONC1, m_c1);
	DDX_Control(pDX, IDC_BUTTONB4, m_b4);
	DDX_Control(pDX, IDC_BUTTONB3, m_b3);
	DDX_Control(pDX, IDC_BUTTONB2, m_b2);
	DDX_Control(pDX, IDC_BUTTONB1, m_b1);
	DDX_Control(pDX, IDC_BUTTONA4, m_a4);
	DDX_Control(pDX, IDC_BUTTONA3, m_a3);
	DDX_Control(pDX, IDC_BUTTONA2, m_a2);
	DDX_Control(pDX, IDC_BUTTONA1, m_a1);
	DDX_Control(pDX, IDC_COMBO_Theatre, m_Theatre);
	DDX_Control(pDX, IDC_COMBO_StartTime, m_starttime);

	//显示影片名
	GetDlgItem(IDC_fname)->SetWindowText(fname);
	//刷新座位号，全部为空
	UpdateSeatnum();
	//设置影院名和开始时间的下拉条
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_set(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	CString sql;
	sql.Format(_T("select distinct tname from Schedule,Film,Theatre where fname = '%s' and Schedule.fid=Film.fid and Theatre.tid=Schedule.tid"), fname);
	m_set.Open(CRecordset::forwardOnly, sql, CRecordset::readOnly);
	for (int i = 0; !m_set.IsEOF(); i++, m_set.MoveNext())
	{

		short index = 0;
		m_set.GetFieldValue(index, tname);//取出第一个字段的值 	
		m_Theatre.AddString(tname);
			
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_Theatre))->GetWindowText(tname);
	m_set.Close();
	m_db.Close();	

}
void CDlgBookTicket::UpdateSeatnum()
{
	m_a1.SetColor(BLACK, WHITE);
	m_a2.SetColor(BLACK, WHITE);
	m_a3.SetColor(BLACK, WHITE);
	m_a4.SetColor(BLACK, WHITE);
	m_b1.SetColor(BLACK, WHITE);
	m_b2.SetColor(BLACK, WHITE);
	m_b3.SetColor(BLACK, WHITE);
	m_b4.SetColor(BLACK, WHITE);
	m_c1.SetColor(BLACK, WHITE);
	m_c2.SetColor(BLACK, WHITE);
	m_c3.SetColor(BLACK, WHITE);
	m_c4.SetColor(BLACK, WHITE);
	m_d1.SetColor(BLACK, WHITE);
	m_d2.SetColor(BLACK, WHITE);
	m_d3.SetColor(BLACK, WHITE);
	m_d4.SetColor(BLACK, WHITE);
	
}

BEGIN_MESSAGE_MAP(CDlgBookTicket, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONA1, &CDlgBookTicket::OnBnClickedButtona1)
	ON_BN_CLICKED(IDC_BUTTONA2, &CDlgBookTicket::OnBnClickedButtona2)
	ON_BN_CLICKED(IDC_BUTTONA3, &CDlgBookTicket::OnBnClickedButtona3)
	ON_BN_CLICKED(IDC_BUTTONA4, &CDlgBookTicket::OnBnClickedButtona4)
	ON_BN_CLICKED(IDC_BUTTONB1, &CDlgBookTicket::OnBnClickedButtonb1)
	ON_BN_CLICKED(IDC_BUTTONB2, &CDlgBookTicket::OnBnClickedButtonb2)
	ON_BN_CLICKED(IDC_BUTTONB3, &CDlgBookTicket::OnBnClickedButtonb3)
	ON_BN_CLICKED(IDC_BUTTONB4, &CDlgBookTicket::OnBnClickedButtonb4)
	ON_BN_CLICKED(IDC_BUTTONC1, &CDlgBookTicket::OnBnClickedButtonc1)
	ON_BN_CLICKED(IDC_BUTTONC2, &CDlgBookTicket::OnBnClickedButtonc2)
	ON_BN_CLICKED(IDC_BUTTONC3, &CDlgBookTicket::OnBnClickedButtonc3)
	ON_BN_CLICKED(IDC_BUTTONC4, &CDlgBookTicket::OnBnClickedButtonc4)
	ON_BN_CLICKED(IDC_BUTTOND1, &CDlgBookTicket::OnBnClickedButtond1)
	ON_BN_CLICKED(IDC_BUTTOND2, &CDlgBookTicket::OnBnClickedButtond2)
	ON_BN_CLICKED(IDC_BUTTOND3, &CDlgBookTicket::OnBnClickedButtond3)
	ON_BN_CLICKED(IDC_BUTTOND4, &CDlgBookTicket::OnBnClickedButtond4)
	ON_CBN_SELCHANGE(IDC_COMBO_Theatre, &CDlgBookTicket::OnCbnSelchangeComboTheatre)
	ON_CBN_SELCHANGE(IDC_COMBO_StartTime, &CDlgBookTicket::OnCbnSelchangeComboStarttime)
	ON_BN_CLICKED(IDC_OUT, &CDlgBookTicket::OnBnClickedOut)
END_MESSAGE_MAP()


// CDlgBookTicket 消息处理程序

void CDlgBookTicket::AddOrders(CString seat)
{
	//CDatabase::openReadOnly 表示以只读方式打开数据源；
	//CDatabase::noOdbcDialog 表示不显示ODBC连接对话框
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}

	CRecordset m_set(&m_db);
	m_set.Open(CRecordset::forwardOnly, _T("select * from Orders"), CRecordset::readOnly);
	//获取行数目
	int nordersnum = 0;
	while (!m_set.IsEOF())
	{
		nordersnum++;
		m_set.MoveNext(); //直接用MoveLast不管用
	}
	nordersnum++;
	m_set.Close();
	if (nordersnum < 10)
	{
		try
		{
			CString sql;
			sql.Format(_T("insert into Orders(oid,sid,seatnum,id) values('o0%d','%s','%s','%s')"), nordersnum, sid, seat,id);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			pe->ReportError();
			pe->Delete();
		}
	}
	else if (nordersnum >= 10)
	{
		try
		{
			CString sql;
			sql.Format(_T("insert into Orders(oid,sid,seatnum,id) values('o%d','%s','%s','%s')"), nordersnum, sid,seat, id);
			m_db.ExecuteSQL(LPCTSTR(sql));
		}
		catch (CDBException *pe)
		{
			pe->ReportError();
			pe->Delete();
		}
	}
	m_db.Close();
	MessageBox(L"恭喜您，订购成功！");
}
void CDlgBookTicket::SeatTrue()
{
	a1 = false; a2 = false; a3 = false; a4 = false; b1 = false; b2 = false; b3 = false; b4 = false; c1 = false; c2 = false; c3 = false; c4 = false; d1 = false; d2 = false; d3 = false; d4 = false;



	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_SET(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	CString SQL;

	//a排
	SQL.Format(_T("select oid from Orders where seatnum = 'a1' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_a1.SetColor(WHITE, BLUE); a1 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'a2' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_a2.SetColor(WHITE, BLUE); a2 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'a3' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_a3.SetColor(WHITE, BLUE); a3 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'a4' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_a4.SetColor(WHITE, BLUE); a4 = true; }
	m_SET.Close();



	//b排
	SQL.Format(_T("select oid from Orders where seatnum = 'b1' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_b1.SetColor(WHITE, BLUE); b1 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'b2' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_b2.SetColor(WHITE, BLUE); b2 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'b3' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_b3.SetColor(WHITE, BLUE); b3 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'b4' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_b4.SetColor(WHITE, BLUE); b4 = true; }
	m_SET.Close();

	//c排
	SQL.Format(_T("select oid from Orders where seatnum = 'c1' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_c1.SetColor(WHITE, BLUE); c1 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'c2' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_c2.SetColor(WHITE, BLUE); c2 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'c3' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_c3.SetColor(WHITE, BLUE); c3 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'c4' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_c4.SetColor(WHITE, BLUE); c4 = true; }
	m_SET.Close();

	//d排
	SQL.Format(_T("select oid from Orders where seatnum = 'd1' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_d1.SetColor(WHITE, BLUE); d1 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'd2' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_d2.SetColor(WHITE, BLUE); d2 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'd3' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_d3.SetColor(WHITE, BLUE); d3 = true; }
	m_SET.Close();

	SQL.Format(_T("select oid from Orders where seatnum = 'd4' and sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	if (!m_SET.IsEOF()) { m_d4.SetColor(WHITE, BLUE); d4 = true; }
	m_SET.Close();

	m_db.Close();
}

void CDlgBookTicket::OnBnClickedButtona1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (a1)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!a1)
	{
		CString Seat;
		Seat = "a1";
		AddOrders(Seat);
		m_a1.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtona2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (a2)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!a2)
	{
		CString Seat;
		Seat="a2";
		AddOrders(Seat);
		m_a2.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtona3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (a3)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!a3)
	{
		CString Seat;
		Seat="a3";
		AddOrders(Seat);
		m_a3.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtona4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (a4)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!a4)
	{
		CString Seat;
		Seat="a4";
		AddOrders(Seat);
		m_a4.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonb1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (b1)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!b1)
	{
		CString Seat;
		Seat="b1";
		AddOrders(Seat);
		m_b1.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonb2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (b2)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!b2)
	{
		CString Seat;
		Seat="b2";
		AddOrders(Seat);
		m_b2.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonb3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (b3)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!b3)
	{
		CString Seat;
		Seat="b3";
		AddOrders(Seat);
		m_b3.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonb4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else  if (b4)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!b4)
	{
		CString Seat;
		Seat="b4";
		AddOrders(Seat);
		m_b4.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonc1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (c1)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!c2)
	{
		CString Seat;
		Seat="c1";
		AddOrders(Seat);
		m_c1.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonc2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (c2)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!c2)
	{
		CString Seat;
		Seat="c2";
		AddOrders(Seat);
		m_c2.SetColor(WHITE, BLUE);
		SeatTrue();

	}
}


void CDlgBookTicket::OnBnClickedButtonc3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (c3)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!c3)
	{
		CString Seat;
		Seat="c3";
		AddOrders(Seat);
		m_c3.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtonc4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (c4)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!c4)
	{
		CString Seat;
		Seat="c4";
		AddOrders(Seat);
		m_c4.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtond1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (d1)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!d1)
	{
		CString Seat;
		Seat="d1";
		AddOrders(Seat);
		m_d1.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtond2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (d2)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!d2)
	{
		CString Seat;
		Seat="d2";
		AddOrders(Seat);
		m_d2.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtond3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (d3)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!d3)
	{
		CString Seat;
		Seat="d3";
		AddOrders(Seat);
		m_d3.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnBnClickedButtond4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (sid.IsEmpty())
	{
		MessageBox(L"请选择影院和开始时间！");
	}
	else if (d4)
	{
		MessageBox(L"该位置已被订！");
		return;
	}
	else if (!d4)
	{
		CString Seat;
		Seat="d4";
		AddOrders(Seat);
		m_d4.SetColor(WHITE, BLUE);
		SeatTrue();
	}
}


void CDlgBookTicket::OnCbnSelchangeComboTheatre()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateSeatnum();
	GetDlgItem(IDC_price)->SetWindowText(NULL);

	((CComboBox*)GetDlgItem(IDC_COMBO_Theatre))->GetWindowText(tname);
	((CComboBox*)GetDlgItem(IDC_COMBO_StartTime))->ResetContent();//消除现有所有内容
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_set1(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	CString sql1;
	sql1.Format(_T("select starttime from Schedule,Film,Theatre where fname = '%s' and Schedule.fid=Film.fid and Theatre.tid=Schedule.tid and tname ='%s'"), fname, tname);
	m_set1.Open(CRecordset::forwardOnly, sql1, CRecordset::readOnly);
	for (int i = 0; !m_set1.IsEOF(); i++, m_set1.MoveNext())
	{
		short index = 0;
		m_set1.GetFieldValue(index, starttime);//取出第一个字段的值 
		m_starttime.AddString(starttime);	
	}
	m_set1.Close();
	m_db.Close();

}


void CDlgBookTicket::OnCbnSelchangeComboStarttime()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateSeatnum();

	((CComboBox*)GetDlgItem(IDC_COMBO_StartTime))->GetWindowText(starttime);
	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_set1(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	CString sql1;
	sql1.Format(_T("select sid from Schedule,Film,Theatre where fname = '%s' and Schedule.fid=Film.fid and Theatre.tid=Schedule.tid and tname ='%s'and starttime='%s'"), fname, tname,starttime);
	m_set1.Open(CRecordset::forwardOnly, sql1, CRecordset::readOnly);
	for (int i = 0; !m_set1.IsEOF(); i++, m_set1.MoveNext())
	{
		short index = 0;
		m_set1.GetFieldValue(index, sid);//取出第一个字段的值 
	}
	m_set1.Close();
	m_db.Close();


	SeatTrue();

	if (!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=bookingdns;UID=aa;PWD=123"),
		CDatabase::openReadOnly | CDatabase::noOdbcDialog))
	{
		MessageBox(L"连接错误！");
		return;
	}
	CRecordset m_SET(&m_db);
	//Open打开记录集，执行T-SQL语句，获取的数据为只读类型
	CString SQL;
	//显示价格
	CString price;
	SQL.Format(_T("select price from schedule where sid='%s'"), sid);
	m_SET.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
	short index = 0;
	m_SET.GetFieldValue(index, price);//取出第一个字段的值 

	m_SET.Close();

	GetDlgItem(IDC_price)->SetWindowText(price);

	m_db.Close();
	
}


void CDlgBookTicket::OnBnClickedOut()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
