// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__12A6C426_3B24_4BF3_B0F4_9F23C8B384E3__INCLUDED_)
#define AFX_LINE_H__12A6C426_3B24_4BF3_B0F4_9F23C8B384E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CLine : public CGraph  
{
public:
	CLine();
	void rotateClockW();
	void rotateCounterClockW();
	CLine(UINT , CPoint , CPoint , COLORREF , COLORREF , int ) ;
	void draw( CDC* pDC ) ;
	CPoint getCenter( ) ;
	virtual ~CLine();

};

#endif // !defined(AFX_LINE_H__12A6C426_3B24_4BF3_B0F4_9F23C8B384E3__INCLUDED_)
