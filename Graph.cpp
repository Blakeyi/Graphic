// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Graph.h"
#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraph::CGraph()
{

}


CGraph::CGraph(UINT m_drawType , CPoint m_ptOrigin , CPoint m_ptEnd , COLORREF m_colorBorder , COLORREF m_colorFilled , int m_borderWidth )
{
	this->m_drawType = m_drawType ;
	this->m_ptEnd = m_ptEnd ;
	this->m_ptOrigin = m_ptOrigin ;
	this->m_colorBorder = m_colorBorder ;
	this->m_colorFilled = m_colorFilled ;
	this->m_borderWidth = m_borderWidth ;
}


CGraph::~CGraph()
{

}

void CGraph::move( int direction )
{
	//1,2,3,4分别表示上下左右
	switch( direction )
	{
		case 1 :
			m_ptOrigin.y -= 4 ;
			m_ptEnd.y -= 4 ;
			break ;
		case 2 :
			m_ptOrigin.y += 4 ;
			m_ptEnd.y += 4 ;
			break ;
		case 3:
			m_ptOrigin.x -= 4 ;
			m_ptEnd.x -= 4 ;
			break ;
		case 4 :
			m_ptOrigin.x += 4 ;
			m_ptEnd.x += 4 ;
			break ;
	}
}

void CGraph::larger()
{
	CPoint pttemp ( m_ptOrigin - getCenter() ) ;
	m_ptOrigin.x = m_ptOrigin.x + pttemp.x/5 ;
	m_ptOrigin.y = m_ptOrigin.y + pttemp.y/5 ;
	m_ptEnd.x = m_ptEnd.x - pttemp.x/5 ;
	m_ptEnd.y = m_ptEnd.y - pttemp.y/5 ;

}

void CGraph::smaller()
{
	CPoint pttemp ( m_ptOrigin - getCenter() ) ;
	m_ptOrigin.x = m_ptOrigin.x - pttemp.x/10 ;
	m_ptOrigin.y = m_ptOrigin.y - pttemp.y/10 ;
	m_ptEnd.x = m_ptEnd.x + pttemp.x/10 ;
	m_ptEnd.y = m_ptEnd.y + pttemp.y/10 ;
}