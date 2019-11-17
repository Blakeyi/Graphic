// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Rectangle.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
{

}

CRectangle::CRectangle(UINT drawType , CPoint ptOrigin , CPoint ptEnd , COLORREF colorBorder , COLORREF colorFilled , int borderWidth ) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled , borderWidth ) 
{
	CPoint center( getCenter() ) ;
	m_left.x = m_ptOrigin.x ;
	m_left.y = 2 * center.y -m_ptOrigin.y ;

	m_right.x = m_ptEnd.x ;
	m_right.y = 2 * center.y -m_ptEnd.y ;
	m_rotateNum = 0 ;
}

void CRectangle::draw( CDC* pDC )
{
/*ÉèÖÃ»­Ë¢*/
	CBrush *pBrush ;
	if ( m_colorFilled == -1 )
		pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//´´½¨Í¸Ã÷µÄ»­Ë¢
	else
	{
		pBrush = new CBrush ;
		pBrush->CreateSolidBrush( m_colorFilled ) ;
	}
	CBrush *pOldBrush = pDC->SelectObject( pBrush ) ;	//½«»­Ë¢Ñ¡Ôñµ½Éè±¸ÃèÊö±íµ±ÖÐ
/*ÉèÖÃ»­Ë¢*/
/*ÉèÖÃ»­±Ê*/ 
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*ÉèÖÃ»­±Ê*/

	if ( m_rotateNum == 6 )
		m_rotateNum = 0 ;
	if ( m_rotateNum == 0 )
		pDC->Rectangle( CRect( m_ptOrigin , m_ptEnd ) ) ;
	else
	{
		CPoint pts[4] ;
		pts[ 0 ] = m_ptOrigin ;
		pts[ 1 ] = m_left ;
		pts[ 2 ] = m_ptEnd ;
		pts[ 3 ] = m_right ;
		pDC->MoveTo( pts[0] ) ;
		pDC->LineTo( pts[1] ) ;
		pDC->LineTo( pts[2] ) ;
		pDC->LineTo( pts[3] ) ;
		pDC->LineTo( pts[0] ) ;
		pDC-> Polygon( pts , 4 ) ;	//Ìî³äÑÕÉ«
	}

	pDC->SelectObject( pOldBrush ) ;//ÊÍ·Å»­Ë¢±ÜÃâÄÚ´æÐ¹Â¶
	if( m_colorFilled != -1 )
		delete pBrush ;
	pDC->SelectObject( pOldPen ) ;
}

CPoint CRectangle::getCenter( )
{
	return CPoint( (m_ptOrigin.x + m_ptEnd.x) / 2 , (m_ptOrigin.y + m_ptEnd.y) / 2 ) ;
}

void CRectangle::rotateClockW()
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
	x = static_cast<int>(( m_left.x - center.x ) * cos(pi/12) - ( m_left.y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( m_left.x - center.x ) * sin(pi/12) + ( m_left.y - center.y ) * cos(pi/12)) + center.y ;
	m_left.x = x ;
	m_left.y = y ;
	x = static_cast<int>(( m_right.x - center.x ) * cos(pi/12) - ( m_right.y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( m_right.x - center.x ) * sin(pi/12) + ( m_right.y - center.y ) * cos(pi/12)) + center.y ;
	m_right.x = x ;
	m_right.y = y ;
	++ m_rotateNum ;
}

void CRectangle::rotateCounterClockW()
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
	x = static_cast<int>(( m_left.x - center.x ) * cos(11*pi/12) - ( m_left.y - center.y ) * sin(11*pi/12)) + center.x ;
	y = static_cast<int>(( m_left.x - center.x ) * sin(11*pi/12) + ( m_left.y - center.y ) * cos(11*pi/12)) + center.y ;
	m_left.x = x ;
	m_left.y = y ;
	x = static_cast<int>(( m_right.x - center.x ) * cos(11*pi/12) - ( m_right.y - center.y ) * sin(11*pi/12)) + center.x ;
	y = static_cast<int>(( m_right.x - center.x ) * sin(11*pi/12) + ( m_right.y - center.y ) * cos(11*pi/12)) + center.y ;
	m_right.x = x ;
	m_right.y = y ;
	-- m_rotateNum ;
}

void CRectangle::larger()
{
	CPoint pttemp ( m_ptOrigin - getCenter() ) ;
	m_ptOrigin.x = m_ptOrigin.x + pttemp.x/5 ;
	m_ptOrigin.y = m_ptOrigin.y + pttemp.y/5 ;
	m_ptEnd.x = m_ptEnd.x - pttemp.x/5 ;
	m_ptEnd.y = m_ptEnd.y - pttemp.y/5 ;

	pttemp = m_left - getCenter();
	m_left.x = m_left.x + pttemp.x/5 ;
	m_left.y = m_left.y + pttemp.y/5 ;
	m_right.x = m_right.x - pttemp.x/5 ;
	m_right.y = m_right.y - pttemp.y/5 ;

}

void CRectangle::smaller()
{
	CPoint pttemp ( m_ptOrigin - getCenter() ) ;
	m_ptOrigin.x = m_ptOrigin.x - pttemp.x/10 ;
	m_ptOrigin.y = m_ptOrigin.y - pttemp.y/10 ;
	m_ptEnd.x = m_ptEnd.x + pttemp.x/10 ;
	m_ptEnd.y = m_ptEnd.y + pttemp.y/10 ;

	pttemp = m_left - getCenter();
	m_left.x = m_left.x - pttemp.x/10 ;
	m_left.y = m_left.y - pttemp.y/10 ;
	m_right.x = m_right.x + pttemp.x/10 ;
	m_right.y = m_right.y + pttemp.y/10 ;
}

CRectangle::~CRectangle()
{

}
