// Triangle.h: interface for the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLE_H__6F46C333_71C8_4E41_9C63_013FE162F7EB__INCLUDED_)
#define AFX_TRIANGLE_H__6F46C333_71C8_4E41_9C63_013FE162F7EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CTriangle : public CGraph  
{
public:
	CTriangle();
	void rotateClockW();
	void rotateCounterClockW();
	CTriangle(UINT , CPoint , CPoint , COLORREF , COLORREF , int ) ;
	void draw( CDC* pDC ) ;
	CPoint getCenter( ) ;
	virtual ~CTriangle();

};

#endif // !defined(AFX_TRIANGLE_H__6F46C333_71C8_4E41_9C63_013FE162F7EB__INCLUDED_)
