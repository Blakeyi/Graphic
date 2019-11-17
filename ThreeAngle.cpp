// ThreeAngle.cpp: implementation of the CThreeAngle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "ThreeAngle.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreeAngle::CThreeAngle()
{

}

CThreeAngle::CThreeAngle(UINT drawType , CPoint ptOrigin , CPoint ptEnd , CPoint *pttemp , COLORREF colorBorder , COLORREF colorFilled , int borderWidth ) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled , borderWidth ) 
{
	pts[0] = pttemp[0] ;
	pts[1] = pttemp[1] ;
	pts[2] = pttemp[2] ;
}

void CThreeAngle::draw( CDC *pDC )
{
/*设置画刷*/
	CBrush *pBrush ;
	if ( m_colorFilled == -1 )
		pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//创建透明的画刷
	else
	{
		pBrush = new CBrush ;
		pBrush->CreateSolidBrush( m_colorFilled ) ;
	}
	CBrush *pOldBrush = pDC->SelectObject( pBrush ) ;	//将画刷选择到设备描述表当中
/*设置画刷*/
/*设置画笔*/
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*设置画笔*/
	pDC->MoveTo( pts[0] ) ;
	pDC->LineTo( pts[1] ) ;
	pDC->LineTo( pts[2] ) ;
	pDC->LineTo( pts[0] ) ;
	pDC-> Polygon( pts , 3 ) ;	//填充颜色

	pDC->SelectObject( pOldBrush ) ;//释放画刷避免内存泄露
	if( m_colorFilled != -1 )
		delete pBrush ;
	pDC->SelectObject( pOldPen ) ;
}

CPoint CThreeAngle::getCenter( )
{
	return CPoint( static_cast<int>((pts[0].x+pts[1].x+pts[2].x)/3) , static_cast<int>((pts[0].y+pts[1].y+pts[2].y)/3) ) ;
}

void CThreeAngle::move( int direction )
{
	//1,2,3,4分别表示上下左右
	switch( direction )
	{
		case 1 :
			pts[0].y -= 4 ;
			pts[1].y -= 4 ;
			pts[2].y -= 4 ;
			break ;
		case 2 :
			pts[0].y += 4 ;
			pts[1].y += 4 ;
			pts[2].y += 4 ;
			break ;
		case 3:
			pts[0].x -= 4 ;
			pts[1].x -= 4 ;
			pts[2].x -= 4 ;
			break ;
		case 4 :
			pts[0].x += 4 ;
			pts[1].x += 4 ;
			pts[2].x += 4 ;
			break ;
	}
}

CThreeAngle::~CThreeAngle()
{

}

void CThreeAngle::larger()
{
	int i = 0 ;
	for ( ; i < 3 ; ++ i )
	{
		CPoint pttemp ( pts[i] - getCenter() ) ;
		if ( pttemp.x > 0 )
			pts[i].x = pts[i].x + pttemp.x/5 ;
		else
			pts[i].x = pts[i].x + pttemp.x/5 ;

		if( pttemp.y > 0 )
			pts[i].y = pts[i].y + pttemp.y/5 ;
		else
			pts[i].y = pts[i].y + pttemp.y/5 ;
	}
}

void CThreeAngle::smaller()
{
	int i = 0 ;
	for ( ; i < 3 ; ++ i )
	{
		CPoint pttemp ( pts[i] - getCenter() ) ;
		if ( pttemp.x > 0 )
			pts[i].x = pts[i].x - pttemp.x/5 ;
		else
			pts[i].x = pts[i].x - pttemp.x/5 ;

		if( pttemp.y > 0 )
			pts[i].y = pts[i].y - pttemp.y/5 ;
		else
			pts[i].y = pts[i].y - pttemp.y/5 ;
	}
}

void CThreeAngle::rotateClockW()
{
	CPoint center( getCenter() ) ;
	int x , y ;
	x = static_cast<int>(( pts[0].x - center.x ) * cos(pi/12) - ( pts[0].y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( pts[0].x - center.x ) * sin(pi/12) + ( pts[0].y - center.y ) * cos(pi/12)) + center.y ;
	pts[0].x = x ;
	pts[0].y = y ;
	x = static_cast<int>(( pts[1].x - center.x ) * cos(pi/12) - ( pts[1].y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( pts[1].x - center.x ) * sin(pi/12) + ( pts[1].y - center.y ) * cos(pi/12)) + center.y ;
	pts[1].x = x ;
	pts[1].y = y ;
	x = static_cast<int>(( pts[2].x - center.x ) * cos(pi/12) - ( pts[2].y - center.y ) * sin(pi/12)) + center.x ;
	y = static_cast<int>(( pts[2].x - center.x ) * sin(pi/12) + ( pts[2].y - center.y ) * cos(pi/12)) + center.y ;
	pts[2].x = x ;
	pts[2].y = y ;
}

void CThreeAngle::rotateCounterClockW()
{
	CPoint center( getCenter() ) ;
	int x , y ;
	x = static_cast<int>(( pts[0].x - center.x ) * cos(23*pi/12) - ( pts[0].y - center.y ) * sin(23*pi/12)) + center.x ;
	y = static_cast<int>(( pts[0].x - center.x ) * sin(23*pi/12) + ( pts[0].y - center.y ) * cos(23*pi/12)) + center.y ;
	pts[0].x = x ;
	pts[0].y = y ;
	x = static_cast<int>(( pts[1].x - center.x ) * cos(23*pi/12) - ( pts[1].y - center.y ) * sin(23*pi/12)) + center.x ;
	y = static_cast<int>(( pts[1].x - center.x ) * sin(23*pi/12) + ( pts[1].y - center.y ) * cos(23*pi/12)) + center.y ;
	pts[1].x = x ;
	pts[1].y = y ;
	x = static_cast<int>(( pts[2].x - center.x ) * cos(23*pi/12) - ( pts[2].y - center.y ) * sin(23*pi/12)) + center.x ;
	y = static_cast<int>(( pts[2].x - center.x ) * sin(23*pi/12) + ( pts[2].y - center.y ) * cos(23*pi/12)) + center.y ;
	pts[2].x = x ;
	pts[2].y = y ;
}

