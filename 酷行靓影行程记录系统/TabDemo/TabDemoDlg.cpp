
// TabDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TabDemo.h"
#include "TabDemoDlg.h"
#include "afxdialogex.h"

#include "DlgBefore.h"

#include "DlgMap.h"
#include "DlgBuild.h"
#include "shellapi.h"
#include "windows.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTabDemoDlg 对话框




CTabDemoDlg::CTabDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_csID = _T("");
}

void CTabDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_USER, m_tab);
	DDX_Text(pDX, IDC_EDIT_ID, m_csID);
	DDV_MaxChars(pDX, m_csID, 8);
}

BEGIN_MESSAGE_MAP(CTabDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_USER, &CTabDemoDlg::OnSelchangeTabUser)
	
	ON_BN_CLICKED(IDCANCEL, &CTabDemoDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_STYLE1, &CTabDemoDlg::OnMenuStyle1)
	ON_COMMAND(ID_MENU_STYLE2, &CTabDemoDlg::OnMenuStyle2)
	ON_COMMAND(ID_MENU_STYLE3, &CTabDemoDlg::OnMenuStyle3)
	ON_COMMAND(ID_OUTMAP, &CTabDemoDlg::OnOutmap)
	
	
	//ON_BN_CLICKED(IDC_BUTTON3, &CTabDemoDlg::OnBnClickedButton3)
	//ON_COMMAND(ID_INPIC, &CTabDemoDlg::OnInpic)
	ON_COMMAND(ID_WRITE, &CTabDemoDlg::OnWrite)
	//ON_COMMAND(ID_NEW, &CTabDemoDlg::OnNew)
END_MESSAGE_MAP()


// CTabDemoDlg 消息处理程序

BOOL CTabDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	this->MoveWindow(0,0,1300,750,true);

	LoadDlgBk(IDB_BITMAP1);


	// TODO: 在此添加额外的初始化代码

    /*CDlgBefore m_CDlgBefore;

	m_CDlgBefore.DoModal();

	*/

	CRect tabRect;

	m_tab.InsertItem(0, _T("我的作品"));//插入第一个标签
	m_tab.InsertItem(1, _T("我的照片"));//插入第二个标签
	m_tab.InsertItem(2, _T(""));//插入第二个标签

	m_tab1.Create(IDD_DIALOG_TAB1, &m_tab);//创建第一个标签页
	m_tab2.Create(IDD_DIALOG_TAB2, &m_tab);//创建第一个标签页
	m_tab3.Create(IDD_DIALOG_TAB3, &m_tab);//创建第一个标签页

	m_tab.GetClientRect(&tabRect);//获取标签控件的属性

	//调整tabRect的值，让它的覆盖范围适合这个标签页
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	//根据调整好的tabRect，放置m_tab1和m_tab2这2个标签页，并把第一个标签页设置为显示，吧第二个设置为隐藏
	m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTabDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{//获取客户区域的大小
		CRect rect;
		GetClientRect(rect);
		CPaintDC dc(this);
		dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcMain,0,0,SRCCOPY);



		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTabDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTabDemoDlg::LoadDlgBk(int iBmpID)
{
	
	//释放资源
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();
	//获取客户区域大小
	CRect   rect;
	GetClientRect(rect);

	//绘制背景
	CClientDC  dc(this);
	m_dcMain.CreateCompatibleDC(&dc);
	m_bmpMain.CreateCompatibleBitmap(&dc,rect.right,rect.bottom);
	m_dcMain.SelectObject(&m_bmpMain);

	m_dcBk.CreateCompatibleDC(&m_dcMain);
	m_bmpBk.LoadBitmap(iBmpID);
	m_dcBk.SelectObject(m_bmpBk);


	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);

	m_dcMain.StretchBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,708,623,SRCCOPY);

	Invalidate(FALSE);

}


void CTabDemoDlg::OnSelchangeTabUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;

	m_tab.GetClientRect(&tabRect);//获取标签控件的属性

	//调整tabRect的值，让它的覆盖范围适合这个标签页
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch(m_tab.GetCurSel())
	{
		//显示第一页，隐藏第二页
	case 0:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;

	case 1:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;

    case 2:
		m_tab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		//ShellExecute(NULL,_T("open"),_T("d:\\1.txt "),NULL,NULL,SW_SHOWNORMAL);

		break;

	default :
		break;
	}

}


/*void CTabDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	/*m_csID = m_pParent->m_csID;

    UpdateData(TRUE);
	

	CDlgAfter m_DlgAfter;

	m_DlgAfter.DoModal();



	CDialogEx::OnOK();
}
*/

void CTabDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CTabDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//释放资源
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();
}


void CTabDemoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CTabDemoDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CTabDemoDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CTabDemoDlg::OnMenuStyle1()
{
LoadDlgBk(IDB_BITMAP1);
}

void CTabDemoDlg::OnMenuStyle2()
{
LoadDlgBk(IDB_BITMAP4);
}

void CTabDemoDlg::OnMenuStyle3()
{
LoadDlgBk(IDB_BITMAP3);
}



void CTabDemoDlg::OnOutmap()
{
	// TODO: 在此添加命令处理程序代码
	CDlgMap m_DlgMap ;

	m_DlgMap.DoModal();
     
}





void CTabDemoDlg::OnWrite()
{
	// TODO: 在此添加命令处理程序代码
	//ShellExecute(0,(LPCWSTR)L"open",(LPCWSTR)L"NOTEPAD.EXE",(LPCWSTR)L"",(LPCWSTR)L"",SW_SHOWNORMAL);
	ShellExecute(0,"open","NOTEPAD.EXE","","",SW_SHOWNORMAL);
}


