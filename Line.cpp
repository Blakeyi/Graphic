// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Line.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{

}

CLine::CLine(UINT drawType , CPoint ptOrigin , CPoint ptEnd , COLORREF colorBorder , COLORREF colorFilled , int borderWidth ) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled , borderWidth ) 
{
	return ;
}

void CLine::draw( CDC* pDC )
{
/*…Ë÷√ª≠± */
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*…Ë÷√ª≠± */
	pDC->MoveTo( m_ptOrigin ) ;
	pDC->LineTo( m_ptEnd ) ;

	pDC->SelectObject( pOldPen ) ;// Õ∑≈ª≠± 
}

CPoint CLine::getCenter( )
{
	return CPoint( (m_ptOrigin.x + m_ptEnd.x) / 2 , (m_ptOrigin.y + m_ptEnd.y) / 2 ) ;
}

CLine::~CLine()
{

}

void CLine::rotateClockW()
{
	CPoint center( getCenter() ) ;
	int x , y ;
	x = static_cast<int>(( m_ptOrigin.x - center.x ) * cos(pi/12) - ( m_ptOrigin.y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( m_ptOrigin.x - center.x ) * sin(pi/12) + ( m_ptOrigin.y - center.y ) * cos(pi/12)) + center.y ;
	m_ptOrigin.x = x ;
	m_ptOrigin.y = y ;
	x = static_cast<int>(( m_ptEnd.x - center.x ) * cos(pi/12) - ( m_ptEnd.y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( m_ptEnd.x - center.x ) * sin(pi/12) + ( m_ptEnd.y - center.y ) * cos(pi/12)) + center.y ;
	m_ptEnd.x = x ;
	m_ptEnd.y = y ;
}

void CLine::rotateCounterClockW()
{
	CPoint center( getCenter() ) ;
	int x , y ;
	x = static_cast<int>(( m_ptOrigin.x - center.x ) * cos(11*pi/12) - ( m_ptOrigin.y - center.y ) * sin(11*pi/12)) + center.x ;
	y = static_cast<int>(( m_ptOrigin.x - center.x ) * sin(11*pi/12) + ( m_ptOrigin.y - center.y ) * cos(11*pi/12)) + center.y ;
	m_ptOrigin.x = x ;
	m_ptOrigin.y = y ;
	x = static_cast<int>(( m_ptEnd.x - center.x ) * cos(11*pi/12) - ( m_ptEnd.y - center.y ) * sin(11*pi/12)) + center.x ;
	y = static_cast<int>(( m_ptEnd.x - center.x ) * sin(11*pi/12) + ( m_ptEnd.y - center.y ) * cos(11*pi/12)) + center.y ;
	m_ptEnd.x = x ;
	m_ptEnd.y = y ;
}
