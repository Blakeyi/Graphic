// GraphicView.h : interface of the CGraphicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICVIEW_H__D40B17E6_3B8A_4F9C_A1D1_969B5B2F58FD__INCLUDED_)
#define AFX_GRAPHICVIEW_H__D40B17E6_3B8A_4F9C_A1D1_969B5B2F58FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlimage.h>
class CGraphicView : public CView
{
protected: // create from serialization only
	CGraphicView();
	DECLARE_DYNCREATE(CGraphicView)

// Attributes
public:
	CGraphicDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg void OnDrawDot();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawStraightline();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnEditUndo();
	afx_msg void OnPaint();
	afx_msg void OnDrawRightangled();
	afx_msg void OnDrawSametriangle();
	afx_msg void OnColorfilled();
	afx_msg void OnColorborder();
	afx_msg void OnNonefilled();
	afx_msg void OnDrawTriangle();
	afx_msg void OnBorderdown();
	afx_msg void OnBorderup();
	afx_msg void OnDrawCircleborder();
	afx_msg void OnDrawCirclefilled();
	afx_msg void OnDrawRectborder();
	afx_msg void OnDrawRectfilled();
	afx_msg void OnDrawTriborder();
	afx_msg void OnDrawTrifilled();
	afx_msg void OnDrawCenter();
	afx_msg void OnMovedown();
	afx_msg void OnMoveleft();
	afx_msg void OnMoveright();
	afx_msg void OnMoveup();
	afx_msg void OnFiglarger();
	afx_msg void OnFigsmaller();
	afx_msg void OnRotateshun();
	afx_msg void OnRotateni();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_moveDirection;
	int m_borderWidth;
	int m_ptsNum ;
	CPoint m_pts[3] ;
	CPtrArray m_ptrArray ;
	COLORREF m_colorBorder ;
	COLORREF m_colorFilled ;
	BOOL m_beDrawing ;
	CPoint m_ptEnd ;
	CPoint m_ptOrigin ;
	UINT m_drawType ;
	CImage image;
	//缩放功能
    //放大的倍数
	float m_fMultiple;
	//原图坐标原点
	CPoint m_OriginSrcPoint;
	//原图的宽度
	int m_nWidthSrc;
	//原图的高度
	int	m_nHeightSrc;
	//滚轮滚动时工作区坐标点
	CPoint m_ptRollPointClient;
	//滚轮滚动时屏幕坐标点
	CPoint m_ptRollPointScreen;
	//绘图区的矩形区域
	CRect m_rectDraw;
	CString cstrLoadPathName;
	CString cstrLoadName;
	CString cstrLoadPath;


public:
	afx_msg void OnFileOpen();
	//afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in GraphicView.cpp
inline CGraphicDoc* CGraphicView::GetDocument()
   { return (CGraphicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__D40B17E6_3B8A_4F9C_A1D1_969B5B2F58FD__INCLUDED_)
