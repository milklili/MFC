#if !defined(AFX_COLORBUTTON_H__EFF23031_09FE_4EBB_A13B_892E41556F53__INCLUDED_)
#define AFX_COLORBUTTON_H__EFF23031_09FE_4EBB_A13B_892E41556F53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// colorbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// colorbutton window

class colorbutton : public CButton
{
// Construction
public:
	colorbutton();

// Attributes
public:

// Operations
public:
	void SetColor(COLORREF text, COLORREF bkgnd, 
					COLORREF disabled = GetSysColor(COLOR_BTNFACE), 
					COLORREF light = GetSysColor(COLOR_3DLIGHT), 
					COLORREF highlight = GetSysColor(COLOR_BTNHIGHLIGHT), 
					COLORREF shadow = GetSysColor(COLOR_BTNSHADOW), 
					COLORREF darkShadow = GetSysColor(COLOR_3DDKSHADOW));
	void SetColorToDefault();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(colorbutton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~colorbutton();

	// Generated message map functions
protected:
	//{{AFX_MSG(colorbutton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void DrawText(CDC *pDC, CRect rc, CString strCaption, COLORREF clrText);
	void DrawRim(CDC *pDC, CRect rc, int nState);
	void DrawBkgnd(CDC *pDC, CRect rc, COLORREF color);
	void DrawButton(CDC *pDC, const CRect& rc, int nState);
	void DrawLine(CDC *pDC, const CPoint& start, const CPoint& end,  COLORREF color);
	
	enum 
	{
		BUTTON_CLICK		= 0x01,  // 按钮点击状态
		BUTTON_NORMAL		= 0x02,  // 按钮正常状态
		BUTTON_FOCUS		= 0x04,  // 按钮焦点状态 
	};
	
	COLORREF m_clrText;  //文字的颜色
	COLORREF m_clrBkgnd; //背景颜色
	COLORREF m_clrDisabledBkgnd; //无效时背景颜色
	COLORREF m_clrLight;  // 边框亮处的颜色
	COLORREF m_clrHighlight; // 边框亮处的颜色
	COLORREF m_clrShadow; // 边框暗处的颜色
	COLORREF m_clrDarkShadow; // 边框暗处的颜色
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__EFF23031_09FE_4EBB_A13B_892E41556F53__INCLUDED_)
