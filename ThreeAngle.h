// ThreeAngle.h: interface for the CThreeAngle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREEANGLE_H__92F1531C_7420_469C_BB7C_3F5C0F6F486F__INCLUDED_)
#define AFX_THREEANGLE_H__92F1531C_7420_469C_BB7C_3F5C0F6F486F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CThreeAngle : public CGraph  
{
public:
	void smaller();
	void larger();
	CThreeAngle();
	void rotateCounterClockW();
	void rotateClockW();
	CThreeAngle(UINT drawType , CPoint ptOrigin , CPoint ptEnd , CPoint* , COLORREF colorBorder , COLORREF colorFilled , int ) ;
	void draw( CDC *pDC ) ;
	void move ( int ) ;
	CPoint getCenter( ) ;
	virtual ~CThreeAngle();

private:
	CPoint pts[3] ;
};

#endif // !defined(AFX_THREEANGLE_H__92F1531C_7420_469C_BB7C_3F5C0F6F486F__INCLUDED_)
