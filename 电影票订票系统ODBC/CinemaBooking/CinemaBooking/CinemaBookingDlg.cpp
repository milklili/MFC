
// CinemaBookingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "CinemaBookingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCinemaBookingDlg 对话框



CCinemaBookingDlg::CCinemaBookingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCinemaBookingDlg::IDD, pParent)
	, m_StaticID(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DlgShowing = NULL;
	m_DlgWillShow = NULL;
}

void CCinemaBookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Showing, m_btn1);
	DDX_Control(pDX, IDC_WillShow, m_btn2);
	DDX_Control(pDX, IDC_MyOrder, m_btn3);
	DDX_Control(pDX, IDC_OutLogin, m_btn4);

	DDX_Text(pDX, IDC_STATIC_ID, m_StaticID);
}

BEGIN_MESSAGE_MAP(CCinemaBookingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Showing, &CCinemaBookingDlg::OnBnClickedShowing)
	ON_BN_CLICKED(IDC_WillShow, &CCinemaBookingDlg::OnBnClickedWillshow)
	ON_BN_CLICKED(IDC_MyOrder, &CCinemaBookingDlg::OnBnClickedMyorder)
	ON_BN_CLICKED(IDC_OutLogin, &CCinemaBookingDlg::OnBnClickedOutlogin)
END_MESSAGE_MAP()


// CCinemaBookingDlg 消息处理程序

BOOL CCinemaBookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//先进入用户登录注册界面
	CDlgUserLogin m_DlgUserLogin;
	m_DlgUserLogin.DoModal();
	
	// TODO:  在此添加额外的初始化代码

	//传值给当前用户
	//CDlgUserLogin m_DlgUserLogin;
	ID=m_DlgUserLogin.m_ID;
	GetDlgItem(IDC_STATIC_ID)->SetWindowText(ID);

	//创建子窗体
	CStatic *pFrame = (CStatic *)GetDlgItem(IDC_MAIN_FRAME);
	RECT rect;
	pFrame->GetClientRect(&rect);
	rect.left += 2;
	rect.top += 2;
	rect.right -= 2;
	rect.bottom -= 2;

	m_DlgShowing = new CDlgShowing;
	//传递账户名
	m_DlgShowing->Id = ID;

	m_DlgShowing->Create(IDD_Showing, pFrame);
	m_DlgShowing->MoveWindow(&rect);
	m_DlgShowing->ShowWindow(SW_SHOW);

	m_DlgWillShow = new CDlgWillShow;
	m_DlgWillShow->Create(IDD_WillShow, pFrame);
	m_DlgWillShow->MoveWindow(&rect);
	m_DlgWillShow->ShowWindow(SW_HIDE);
	//创建子窗体结束

	//透明按钮
	m_btn1.Load(IDB_PNG1, 244);
	m_btn2.Load(IDB_PNG1, 244);
	m_btn3.Load(IDB_PNG1, 244);
	m_btn4.Load(IDB_PNG1, 244);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCinemaBookingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCinemaBookingDlg::OnPaint()
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
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCinemaBookingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCinemaBookingDlg::OnBnClickedShowing()
{
	// TODO:  在此添加控件通知处理程序代码
	m_DlgShowing->ShowWindow(SW_SHOW);
	m_DlgWillShow->ShowWindow(SW_HIDE);
}


void CCinemaBookingDlg::OnBnClickedWillshow()
{
	// TODO:  在此添加控件通知处理程序代码
	m_DlgWillShow->ShowWindow(SW_SHOW);
	m_DlgShowing->ShowWindow(SW_HIDE);
}


void CCinemaBookingDlg::OnBnClickedMyorder()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgMyOrder m_DlgMyOrder;
	//传递账户名
	m_DlgMyOrder.orderID = ID;
	m_DlgMyOrder.DoModal();
	
}

void CCinemaBookingDlg::OnBnClickedOutlogin()
{
	// TODO:  在此添加控件通知处理程序代码

	//重启此程序

	//得到当前程序的路径
	TCHAR strPath[MAX_PATH];
	GetModuleFileName(NULL, strPath, 100);

	//创建守护进程，在启用新进程成功后发送WM_QUIT消息结束原来的进程；
	STARTUPINFO startInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(STARTUPINFO);
	if (CreateProcess(NULL, (LPTSTR)(LPCTSTR)strPath, NULL, NULL, FALSE, 0, NULL, NULL, &startInfo, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		PostQuitMessage(WM_CLOSE);
	}

}
