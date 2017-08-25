// DlgMap.cpp : 实现文件
//

#include "stdafx.h"
#include "TabDemo.h"
#include "DlgMap.h"
#include "afxdialogex.h"
#include "explorer1.h"
//#include <Mshtml.h>
//#include "WebPage.h"
CString mpath[100];
// CDlgMap 对话框

IMPLEMENT_DYNAMIC(CDlgMap, CDialogEx)
	
CDlgMap::CDlgMap(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMap::IDD, pParent)
{

}

CDlgMap::~CDlgMap()
{
}

void CDlgMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_map);
}


BEGIN_MESSAGE_MAP(CDlgMap, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDlgMap::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgMap::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPENMAP, &CDlgMap::OnBnClickedButtonOpenmap)
	ON_BN_CLICKED(IDC_BUTTON_OPENMAP, &CDlgMap::OnBnClickedButtonOpenmap)
	ON_BN_CLICKED(IDC_BUTTON_PUTIN, &CDlgMap::OnBnClickedButtonPutin)
END_MESSAGE_MAP()


// CDlgMap 消息处理程序


void CDlgMap::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	//DestroyWindow();
}


void CDlgMap::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}





void CDlgMap::OnBnClickedButtonOpenmap()
{
	// TODO: 在此添加控件通知处理程序代码
	 m_map.Navigate(_T("file:///C:/Users/K550/Desktop/map3.html"),NULL,NULL,NULL,NULL);
    /*
    CString m_JD="106.562627";
	CString m_WD="29.613458";
	 
	CWebPage web;
    web.SetDocument(m_map.get_Document());
	const CString funcName("justmarkfun");
	CComVariant varResult;
	web.CallJScript(funcName,m_JD,m_WD,&varResult);//这里m_JD和m_WD是与编辑框控件的两个CString类型变量,传入经度纬度值这里参数的个数要与javascript函数justmakefun函数的个数相同,而且顺序要保持一致
	 if( varResult. dblVal == 122.211 ) { // double型对应dblVal，整形对应intVal

                   MessageBox(NULL,_T("创建成功"),MB_OK);
	 }
	 else{
	 
		  MessageBox(NULL,_T("创建失败"),MB_OK);
	 }
	*/
}


void CDlgMap::OnBnClickedButtonPutin()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_map.DeleteAllItems();//释放上一次运行的缓存
 size_t index;
 CString cstrsucstring;

 CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT,_T("image files (*.bmp; *.jpg) |*.bmp; *.jpg | All Files (*.*) |*.*||"), NULL);
   
 TCHAR *pBuffer = new TCHAR[MAX_PATH    * 20];//最多允许同时打开20个文件
 filedlg.m_ofn.lpstrFile = pBuffer;
 filedlg.m_ofn.nMaxFile = MAX_PATH * 20;
 filedlg.m_ofn.lpstrFile[0] = '\0';

 int nPIC=20;
 CString cstrfilepath = _T("");

 if (filedlg.DoModal() == IDOK)
     {
        for(static int i=0;i<nPIC;)
		{
         POSITION pos = filedlg.GetStartPosition();
         while (pos != NULL)
         {

            cstrfilepath = filedlg.GetNextPathName(pos);//取得文件路径
			 mpath[i]= cstrfilepath ;
			i++;
         }	
		
	    nPIC=i;

		}
     }

 

	/*
	CWebPage web;
    web.SetDocument(m_map.GetDocument());
	const CString funcName("justmarkfun");
	CComVariant varResult;
	web.CallJScript(funcName,m_JD,m_WD,&varResult);//这里m_JD和m_WD是与编辑框控件的两个CString类型变量,传入经度纬度值这里参数的个数要与javascript函数justmakefun函数的个数相同,而且顺序要保持一致
	*/

}
