// Circle.h: interface for the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLE_H__080CF4F8_E0C0_433B_86B5_F810DFCE28D7__INCLUDED_)
#define AFX_CIRCLE_H__080CF4F8_E0C0_433B_86B5_F810DFCE28D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CCircle : public CGraph  
{
public:
	CCircle();
	void rotateClockW();
	void rotateCounterClockW();
	CCircle(UINT , CPoint , CPoint , COLORREF , COLORREF , int ) ;
	void draw( CDC* pDC ) ;
	CPoint getCenter( ) ;
	virtual ~CCircle();

};

#endif // !defined(AFX_CIRCLE_H__080CF4F8_E0C0_433B_86B5_F810DFCE28D7__INCLUDED_)
