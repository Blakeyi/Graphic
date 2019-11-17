// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__9C388C23_7F86_4179_92A4_463A4D614969__INCLUDED_)
#define AFX_RECTANGLE_H__9C388C23_7F86_4179_92A4_463A4D614969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CRectangle : public CGraph  
{
public:
	void larger();
	void smaller();
	void rotateClockW();
	void rotateCounterClockW();
	CRectangle();
	CRectangle(UINT , CPoint , CPoint , COLORREF , COLORREF , int ) ;
	void draw( CDC* pDC ) ;
	CPoint getCenter( ) ;
	virtual ~CRectangle();
private:
	CPoint m_left ;
	CPoint m_right ;
	int m_rotateNum ;

};

#endif // !defined(AFX_RECTANGLE_H__9C388C23_7F86_4179_92A4_463A4D614969__INCLUDED_)
