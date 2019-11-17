// Dot.h: interface for the CDot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOT_H__5026413F_6418_41E5_BFA9_C1E2DCE1EA7C__INCLUDED_)
#define AFX_DOT_H__5026413F_6418_41E5_BFA9_C1E2DCE1EA7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

//当传入的参数colorFilled为NULL时，表示画点，当colorFilled传入为黑色时，表示标记圆心
class CDot : public CGraph  
{
public:
	CDot();
	void rotateClockW();
	void rotateCounterClockW();
	CDot(UINT , CPoint , CPoint , COLORREF , COLORREF ,int ) ;
	void draw( CDC* pDC ) ;
	CPoint getCenter( ) ;
	virtual ~CDot();

};

#endif // !defined(AFX_DOT_H__5026413F_6418_41E5_BFA9_C1E2DCE1EA7C__INCLUDED_)
