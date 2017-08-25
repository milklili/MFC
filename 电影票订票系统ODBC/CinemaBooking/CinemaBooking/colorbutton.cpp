// colorbutton.cpp : implementation file
//

#include "stdafx.h"
#include "CinemaBooking.h"
#include "colorbutton.h"
#include <afxtempl.h> // 为了使用CArray数组模板

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// colorbutton
const COLORREF CLR_BTN_WHITE  = RGB(255, 255, 255);
const COLORREF CLR_BTN_BLACK  = RGB(0, 0, 0);
const COLORREF CLR_BTN_DGREY  = RGB(128, 128, 128);

colorbutton::colorbutton()
{
	SetColorToDefault();
}

colorbutton::~colorbutton()
{
}


BEGIN_MESSAGE_MAP(colorbutton, CButton)
	//{{AFX_MSG_MAP(colorbutton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// colorbutton message handlers

void colorbutton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC		*pDC;
	CRect	rc;
	UINT	nState;
	
	pDC    = CDC::FromHandle(lpDrawItemStruct->hDC);
	nState = lpDrawItemStruct->itemState;
	rc.CopyRect(&lpDrawItemStruct->rcItem); 

	DrawButton(pDC, rc, nState);
}

void colorbutton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0, BS_OWNERDRAW); //设置按钮属性为自绘式

	CButton::PreSubclassWindow();
}

void colorbutton::DrawButton(CDC *pDC, const CRect &rc, int nState)
{
	CRect	rcFocus, rcButton, rcText, rcOffsetText;
	
	rcFocus = rc; 
	rcButton = rc;
	
	rcOffsetText = rcText = rc;
	rcText.OffsetRect(-1, -1);
	rcOffsetText.OffsetRect(1, 1);
	
	// 设置焦点边框做为拥有焦点按钮的修饰
	rcFocus.InflateRect(-4, -4);
	
	// ODS_FOCUS：有输入焦点状态。   
	// ODS_DISABLED：失效状态   
	// ODS_SELECTED：选中状态	
	if (nState & ODS_DISABLED)
    {
		DrawBkgnd(pDC, rcButton, m_clrDisabledBkgnd);
	}
	else
	{
		DrawBkgnd(pDC, rcButton, m_clrBkgnd);
	}
	
	if (nState & ODS_SELECTED)
	{ 
		DrawRim(pDC, rcButton, BUTTON_CLICK);
	}
	else
	{
		if ((nState & ODS_DEFAULT) || (nState & ODS_FOCUS))
		{
			DrawRim(pDC, rcButton, BUTTON_NORMAL | BUTTON_FOCUS);			
		}
		else
		{
			DrawRim(pDC, rcButton, BUTTON_NORMAL);
		}
	}
	
	// 获得按钮文字
	CString strCaption;
	GetWindowText(strCaption);
	if (nState & ODS_DISABLED)
	{
		DrawText(pDC, rcOffsetText, strCaption, CLR_BTN_WHITE);
		DrawText(pDC, rcText,	strCaption, CLR_BTN_DGREY);
    }
	else
	{
		if (nState & ODS_SELECTED)
		{
			DrawText(pDC, rcOffsetText, strCaption, m_clrText);
		}
		else
		{
			DrawText(pDC, rcText, strCaption, m_clrText);
		}
	}
	
	if (nState & ODS_FOCUS)
	{
		DrawFocusRect(pDC->m_hDC , (LPRECT)&rcFocus);
	}	
}

void colorbutton::DrawLine(CDC *pDC, const CPoint &start, const CPoint &end, COLORREF color)
{
	CPen newPen;
	CPen *oldPen;
	
	newPen.CreatePen(PS_SOLID, 1, color);
	oldPen = pDC->SelectObject(&newPen);

	pDC->MoveTo(start);
	pDC->LineTo(end);
	pDC->SelectObject(oldPen);

    newPen.DeleteObject();	
}

void colorbutton::DrawBkgnd(CDC *pDC, CRect rc, COLORREF color)
{
	CBrush brSolid;
	
	brSolid.CreateSolidBrush(color);
	pDC->FillRect(rc, &brSolid);
}

void colorbutton::DrawRim(CDC *pDC, CRect rc, int nState)
{
	COLORREF color;
	
	if (nState & BUTTON_FOCUS)
	{
		color = CLR_BTN_BLACK;
		
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.right, rc.top),    color); // Across top
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.left,  rc.bottom), color); // Down left
		
		DrawLine(pDC, CPoint(rc.left, rc.bottom - 1), CPoint(rc.right, rc.bottom - 1), color); // Across bottom
		DrawLine(pDC, CPoint(rc.right - 1, rc.top), CPoint(rc.right - 1, rc.bottom), color); // Down right
		
		rc.InflateRect(-1, -1);
	}
	
	if (nState & BUTTON_NORMAL)
	{
		color = m_clrHighlight;
		
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.right, rc.top),    color); // Across top
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.left,  rc.bottom), color); // Down left
		
		color = m_clrDarkShadow;
		
		DrawLine(pDC, CPoint(rc.left, rc.bottom - 1), CPoint(rc.right, rc.bottom - 1), color); // Across bottom
		DrawLine(pDC, CPoint(rc.right - 1, rc.top), CPoint(rc.right - 1, rc.bottom),  color); // Down right
		
		rc.InflateRect(-1, -1);
		
		color = m_clrLight;
		
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.right, rc.top),    color); // Across top
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.left,  rc.bottom), color); // Down left
		
		color = m_clrShadow;
		
		DrawLine(pDC, CPoint(rc.left, rc.bottom - 1), CPoint(rc.right, rc.bottom - 1), color); // Across bottom
		DrawLine(pDC, CPoint(rc.right - 1, rc.top), CPoint(rc.right - 1, rc.bottom),   color); // Down right
	}
	
	if (nState & BUTTON_CLICK)
	{
		color = m_clrDarkShadow;
		
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.right, rc.top),    color); // Across top
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.left,  rc.bottom), color); // Down left
		DrawLine(pDC, CPoint(rc.left, rc.bottom - 1), CPoint(rc.right, rc.bottom - 1), color); // Across bottom
		DrawLine(pDC, CPoint(rc.right - 1, rc.top), CPoint(rc.right - 1, rc.bottom),  color); // Down right
		
		rc.InflateRect(-1, -1);
		
		color = m_clrShadow;
		
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.right, rc.top),    color); // Across top
		DrawLine(pDC, CPoint(rc.left, rc.top), CPoint(rc.left,  rc.bottom), color); // Down left
		DrawLine(pDC, CPoint(rc.left, rc.bottom - 1), CPoint(rc.right, rc.bottom - 1), color); // Across bottom
		DrawLine(pDC, CPoint(rc.right - 1, rc.top), CPoint(rc.right - 1, rc.bottom),  color); // Down right
	}

}

void colorbutton::DrawText(CDC *pDC, CRect rc, CString strCaption, COLORREF clrText)
{
	DWORD uStyle = GetWindowLong(this->m_hWnd,GWL_STYLE);

	CArray<CString, CString> arLines;

	if((uStyle & BS_MULTILINE) == BS_MULTILINE) // 多行文字的处理
	{
		int nIndex = 0;
		while(nIndex != -1)
		{
			nIndex = strCaption.Find('\n');
			if(nIndex>-1)
			{
				CString line = strCaption.Left(nIndex);
				arLines.Add(line);
				strCaption.Delete(0,nIndex+1);
			}
			else
				arLines.Add(strCaption);
		}
	}
	else
	{
		arLines.Add(strCaption);
	}

	CSize sizeText = pDC->GetOutputTextExtent( strCaption );
	
    COLORREF oldColour;
	oldColour = pDC->SetTextColor(clrText);
	pDC->SetBkMode(TRANSPARENT);
	
	int nStartPos = (rc.Height() - arLines.GetSize()*sizeText.cy)/2-1;
	if((uStyle & BS_TOP) == BS_TOP)
		nStartPos = rc.top+2;
	if((uStyle & BS_BOTTOM) == BS_BOTTOM)
		nStartPos = rc.bottom- arLines.GetSize()*sizeText.cy-2;
	if((uStyle & BS_VCENTER) == BS_VCENTER)
		nStartPos = (rc.Height() - arLines.GetSize()*sizeText.cy)/2-1;
	
	UINT uDrawStyles = 0;
	if((uStyle & BS_CENTER) == BS_CENTER)
		uDrawStyles |= DT_CENTER;
	else
	{
		if((uStyle & BS_LEFT) == BS_LEFT)
			uDrawStyles |= DT_LEFT;
		else
		if((uStyle & BS_RIGHT) == BS_RIGHT)
			uDrawStyles |= DT_RIGHT;
		else
		if(uDrawStyles == 0)
			uDrawStyles = DT_CENTER|DT_VCENTER | DT_SINGLELINE;
	}
	
	for(int i=0; i<arLines.GetSize(); i++)
	{
		CRect textrc = rc;
		textrc.DeflateRect(3,0,3,0);
		textrc.top = nStartPos + sizeText.cy*i;
		textrc.bottom = nStartPos + sizeText.cy*(i+1);
		CString line = arLines.GetAt(i);
		pDC->DrawText(line, line.GetLength(), textrc, uDrawStyles);
	}

	pDC->SetTextColor(oldColour);

}

void colorbutton::SetColor(COLORREF text, COLORREF bkgnd, COLORREF disabled, COLORREF light, COLORREF highlight, COLORREF shadow, COLORREF darkShadow)
{
	m_clrText			= text;
	m_clrBkgnd			= bkgnd; 
	m_clrDisabledBkgnd	= disabled;
	m_clrLight			= light;
	m_clrHighlight		= highlight;
	m_clrShadow			= shadow;
	m_clrDarkShadow		= darkShadow;

	if(m_hWnd != NULL)
		Invalidate();
}

void colorbutton::SetColorToDefault()
{
	m_clrText			= GetSysColor(COLOR_BTNTEXT);
	m_clrBkgnd			= GetSysColor(COLOR_BTNFACE); 
	m_clrDisabledBkgnd	= GetSysColor(COLOR_BTNFACE);
	m_clrLight			= GetSysColor(COLOR_3DLIGHT);
	m_clrHighlight		= GetSysColor(COLOR_BTNHIGHLIGHT);
	m_clrShadow			= GetSysColor(COLOR_BTNSHADOW);
	m_clrDarkShadow		= GetSysColor(COLOR_3DDKSHADOW);	
}
