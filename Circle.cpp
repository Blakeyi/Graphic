// Circle.cpp: implementation of the CCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Circle.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircle::CCircle()
{

}

CCircle::CCircle(UINT drawType , CPoint ptOrigin , CPoint ptEnd , COLORREF colorBorder , COLORREF colorFilled , int borderWidth) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled , borderWidth ) 
{

}

void CCircle::draw( CDC* pDC )
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

	pDC->Ellipse( CRect( m_ptOrigin , m_ptEnd ) ) ;	//»­Í¼

	pDC->SelectObject( pOldBrush ) ;//ÊÍ·Å»­Ë¢±ÜÃâÄÚ´æÐ¹Â¶
	if( m_colorFilled != -1 )
		delete pBrush ;
	pDC->SelectObject( pOldPen ) ;
}

CPoint CCircle::getCenter( )
{
	return CPoint( (m_ptOrigin.x + m_ptEnd.x) / 2 , (m_ptOrigin.y + m_ptEnd.y) / 2 ) ;
}

CCircle::~CCircle()
{

}

void CCircle::rotateClockW()
{
	if ( m_drawType == 4 )
	{
		CPoint center( getCenter() ) ;
		int x , y ;
		x = static_cast<int>(( m_ptOrigin.x - center.x ) * cos(pi/2) - ( m_ptOrigin.y - center.y ) * sin(pi/2)) + center.x ;
		y = static_cast<int>(( m_ptOrigin.x - center.x ) * sin(pi/2) + ( m_ptOrigin.y - center.y ) * cos(pi/2)) + center.y ;
		m_ptOrigin.x = x ;
		m_ptOrigin.y = y ;
		x = static_cast<int>(( m_ptEnd.x - center.x ) * cos(pi/2) - ( m_ptEnd.y - center.y ) * sin(pi/2)) + center.x ;
		y = static_cast<int>(( m_ptEnd.x - center.x ) * sin(pi/2) + ( m_ptEnd.y - center.y ) * cos(pi/2)) + center.y ;
		m_ptEnd.x = x ;
		m_ptEnd.y = y ;
	}
}

void CCircle::rotateCounterClockW()
{
	if ( m_drawType == 4 )
	{
		CPoint center( getCenter() ) ;
		int x , y ;
		x = static_cast<int>(( m_ptOrigin.x - center.x ) * cos(pi/2) - ( m_ptOrigin.y - center.y ) * sin(pi/2)) + center.x ;
		y = static_cast<int>(( m_ptOrigin.x - center.x ) * sin(pi/2) + ( m_ptOrigin.y - center.y ) * cos(pi/2)) + center.y ;
		m_ptOrigin.x = x ;
		m_ptOrigin.y = y ;
		x = static_cast<int>(( m_ptEnd.x - center.x ) * cos(pi/2) - ( m_ptEnd.y - center.y ) * sin(pi/2)) + center.x ;
		y = static_cast<int>(( m_ptEnd.x - center.x ) * sin(pi/2) + ( m_ptEnd.y - center.y ) * cos(pi/2)) + center.y ;
		m_ptEnd.x = x ;
		m_ptEnd.y = y ;
	}
}
