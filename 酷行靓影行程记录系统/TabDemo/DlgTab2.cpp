// DlgTab2.cpp : 实现文件
//

#include "stdafx.h"
#include "TabDemo.h"
#include "DlgTab2.h"
#include "afxdialogex.h"
CString path[100];


// CDlgTab2 对话框

IMPLEMENT_DYNAMIC(CDlgTab2, CDialogEx)

CDlgTab2::CDlgTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTab2::IDD, pParent)
{

}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST22, m_list);
	//InitListCtrlStyle(); //调用方法初始化ListCtrl的样式
	//RefreshListCtrlData(); //刷新ListCtrl的数据
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}


BEGIN_MESSAGE_MAP(CDlgTab2, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST22, &CDlgTab2::OnLvnItemchangedList22)
	ON_BN_CLICKED(IDC_BUTTON_LOADPIC, &CDlgTab2::OnBnClickedButtonLoadpic)
	ON_BN_CLICKED(IDC_BIGPIC, &CDlgTab2::OnBnClickedBigpic)
	ON_BN_CLICKED(IDC_BUTTON_READNOTE, &CDlgTab2::OnBnClickedButtonReadnote)
	ON_BN_CLICKED(IDC_BUTTON_SAVENOTE, &CDlgTab2::OnBnClickedButtonSavenote)
	ON_NOTIFY(NM_CLICK, IDC_LIST22, &CDlgTab2::OnNMClickList22)
END_MESSAGE_MAP()


// CDlgTab2 消息处理程序


void CDlgTab2::OnLvnItemchangedList22(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void CDlgTab2::OnBnClickedButtonLoadpic()
{
	// TODO: 在此添加控件通知处理程序代码

 m_list.DeleteAllItems();//释放上一次运行的缓存
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
			path[i]= cstrfilepath ;
			i++;
         }	
		
	    nPIC=i;

		}
     }


CImageList a;
	a.Create(100,100, ILC_COLOR32 |ILC_MASK , 8, 1);//控制显示图片的大小
		for(int j=0;j<nPIC;j++)
		{
		HBITMAP hBmp  = (HBITMAP)::LoadImage
			(
			::AfxGetInstanceHandle(), 
			path[j],
			IMAGE_BITMAP,
			100,
			100,
			LR_LOADFROMFILE
			);
		CBitmap* pBmp = CBitmap::FromHandle(hBmp); 		 
		a.Add(pBmp,RGB(0 ,0, 0));	
		m_list.SetImageList(&a,LVSIL_NORMAL);
		CString strTemp;
		strTemp.Format(_T("pic:%d"),j);
	    m_list.InsertItem(j,strTemp, j);
		

		}
	a.Detach();

}



void CDlgTab2::OnBnClickedBigpic()
{
/*CString str; 
 int nId; 
 //首先得到点击的位置 
POSITION pos=m_list.GetFirstSelectedItemPosition(); 
 if(pos==NULL) 
 { 
 MessageBox(TEXT("请至少选择一项"),NULL,MB_ICONEXCLAMATION); 
 return; 
 } 
 //得到行号，通过POSITION转化 
nId=(int)m_list.GetNextSelectedItem(pos); 

CString filename;
filename=path[nId];
CDC *pDC =m_picture.GetWindowDC(); 
		CImage m_image;
		m_image.Load(filename);//文件路径

		CRect rect;
		m_picture.GetClientRect(&rect);

		int Width = rect.right - rect.left;
		int Height = rect.bottom - rect.top;

		pDC->SetStretchBltMode(STRETCH_HALFTONE); //避免失真
		m_image.Draw(pDC->m_hDC,0,0,Width,Height);
 //得到列中的内容（0表示第一列，同理1,2,3...表示第二，三，四...列） 


/*HBITMAP hBitmap;
  hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1));
     m_Bmp.SetBitmap(hBitmap); 


	 HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(),
  m_strfile,
 IMAGE_BITMAP,
 r.Width()/2,
 r.Height()/2,
 LR_LOADFROMFILE);  
 m_Bmp.SetBitmap(hbitmap);
*/
}


void CDlgTab2::OnBnClickedButtonReadnote()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NOTE); 
        pedit->LineScroll(pedit->GetLineCount());
	CString filename;                             // 打开的文件名字符串
    CFile file;                                         // 文件对象
    DWORD len;                                    // 用于保存文件长度
    CFileDialog    dlg(TRUE,_T(""),_T("*.*"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("*.*|*.*|"));

    DWORD local_1 = dlg.DoModal ();

    if(IDOK== local_1){
		filename = dlg.GetPathName();
	}
  else if( IDCANCEL == local_1){
      return ;
  }

  // 读取数据
   file.Open(filename,CFile::modeReadWrite);
   len = file.GetLength();
   char *pReadData = new char[len+1]; // 分配内存
  
    file.Read(pReadData,len);                                       //  这里保存的读取文件的数据
	pReadData[len] = 0;

	file.Close();
  
   CEdit* pBoxOne;
   pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT_NOTE);
   ::SetWindowTextA(pBoxOne->m_hWnd, pReadData);
}


void CDlgTab2::OnBnClickedButtonSavenote()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filename;
	CFile file;
	DWORD len;

	CFileDialog *dlg = new CFileDialog(FALSE, _T("*.*"), _T("*.*"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("*.txt||"));
	DWORD local_2 = dlg->DoModal();

	if (IDOK==local_2) {
		filename = dlg->GetPathName();
	}
	else if (IDCANCEL == local_2) {
		return;
	}

	len = ::GetWindowTextLengthA(GetDlgItem(IDC_EDIT_NOTE)->m_hWnd);
	char *pReadData = new char[len+1]; // 分配内存
	::GetWindowTextA(GetDlgItem(IDC_EDIT_NOTE)->m_hWnd, pReadData, len);

	file.Open(filename, CFile::modeCreate|CFile::modeWrite);
	file.Write(pReadData, len);
	file.Close();
	delete pReadData;
	delete dlg;
}


void CDlgTab2::OnNMClickList22(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString str; 
 int nId; 
 //首先得到点击的位置 
POSITION pos=m_list.GetFirstSelectedItemPosition(); 
 if(pos==NULL) 
 { 
 MessageBox(TEXT("请至少选择一项"),NULL,MB_ICONEXCLAMATION); 
 return; 
 } 
 //得到行号，通过POSITION转化 
nId=(int)m_list.GetNextSelectedItem(pos); 

CString filename;
filename=path[nId];
CDC *pDC =m_picture.GetWindowDC(); 
		CImage m_image;
		m_image.Load(filename);//文件路径

		CRect rect;
		m_picture.GetClientRect(&rect);

		int Width = rect.right - rect.left;
		int Height = rect.bottom - rect.top;

		pDC->SetStretchBltMode(STRETCH_HALFTONE); //避免失真
		m_image.Draw(pDC->m_hDC,0,0,Width,Height);

		CString strt; 
        int n = filename.ReverseFind('.') ;
        strt = filename.Left(n);
	    CString cc;
	    cc=strt+".txt";
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NOTE); 
        pedit->LineScroll(pedit->GetLineCount());
		CFile file;                                         // 文件对象
        DWORD len;   // 用于保存文件长度
		file.Open( cc,CFile::modeReadWrite);
        len = file.GetLength();
        char *pReadData = new char[len+1]; // 分配内存
  
        file.Read(pReadData,len);                                       //  这里保存的读取文件的数据
	    pReadData[len] = 0;

	    file.Close();
  
       CEdit* pBoxOne;
       pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT_NOTE);
       ::SetWindowTextA(pBoxOne->m_hWnd, pReadData);
}
