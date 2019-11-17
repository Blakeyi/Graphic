// Triangle.cpp: implementation of the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Triangle.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTriangle::CTriangle()
{

}

CTriangle::CTriangle(UINT drawType , CPoint ptOrigin , CPoint ptEnd , COLORREF colorBorder , COLORREF colorFilled , int borderWidth ) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled , borderWidth ) 
{
	return ;
}

void CTriangle::draw( CDC* pDC )
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

	CPoint pt_temp ( m_ptEnd - m_ptOrigin ) ;//用于绘制三角形
	CPoint pts[3] ;
	if( m_drawType == 6)
	{	//如果画的是等腰直角三角形
		pts[ 0 ] = m_ptOrigin ;
		pts[ 1 ] = CPoint( m_ptEnd.x + pt_temp.y , m_ptEnd.y - pt_temp.x ) ;
		pts[ 2 ] = CPoint( m_ptEnd.x - pt_temp.y , m_ptEnd.y + pt_temp.x ) ;
		pDC->MoveTo( pts[0] ) ;
		pDC->LineTo( pts[1] ) ;
		pDC->LineTo( pts[2] ) ;
		pDC->LineTo( pts[0] ) ;
	}
	else	//画的是等边三角形
	{
		pts[ 0 ] = m_ptOrigin ;
		pts[ 1 ] = CPoint( m_ptEnd.x + static_cast<int>(pt_temp.y * 0.57735) , m_ptEnd.y - static_cast<int>(pt_temp.x * 0.57735) ) ;
		pts[ 2 ] = CPoint( m_ptEnd.x - static_cast<int>(pt_temp.y * 0.57735) , m_ptEnd.y + static_cast<int>(pt_temp.x * 0.57735) ) ;
		pDC->MoveTo( pts[0] ) ;
		pDC->LineTo( pts[1] ) ;
		pDC->LineTo( pts[2] ) ;
		pDC->LineTo( pts[0] ) ;
	}
	pDC-> Polygon( pts , 3 ) ;	//填充颜色
	pDC->SelectObject( pOldBrush ) ;//释放画刷避免内存泄露
	if( m_colorFilled != -1 )
		delete pBrush ;
	pDC->SelectObject( pOldPen ) ;
}

CPoint CTriangle::getCenter( )
{
	if( m_drawType == 6)
	{	//如果画的是等腰直角三角形
		return m_ptEnd ;
	}
	else
	{
		CPoint pt_temp ( m_ptEnd - m_ptOrigin ) ;//用于计算重心
		return CPoint( static_cast<int>((m_ptOrigin.x+2*m_ptEnd.x)/3) , static_cast<int>((m_ptOrigin.y+2*m_ptEnd.y)/3) ) ;
	}
}

CTriangle::~CTriangle()
{

}

void CTriangle::rotateClockW()
{
	CPoint center ;
	if ( m_drawType == 6 )
		center = CPoint( (m_ptOrigin.x+m_ptEnd.x)/2 , (m_ptOrigin.y+m_ptEnd.y)/2 ) ;
	else
		center = getCenter() ;
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

void CTriangle ::rotateCounterClockW()
{
	CPoint center ;
	if ( m_drawType == 6 )
		center = CPoint( (m_ptOrigin.x+m_ptEnd.x)/2 , (m_ptOrigin.y+m_ptEnd.y)/2 ) ;
	else
		center = getCenter() ;
	int x , y ;
	x = static_cast<int>(( m_ptOrigin.x - center.x ) * cos(23*pi/12) - ( m_ptOrigin.y - center.y ) * sin(23*pi/12)) + center.x ;
	y = static_cast<int>(( m_ptOrigin.x - center.x ) * sin(23*pi/12) + ( m_ptOrigin.y - center.y ) * cos(23*pi/12)) + center.y ;
	m_ptOrigin.x = x ;
	m_ptOrigin.y = y ;
	x = static_cast<int>(( m_ptEnd.x - center.x ) * cos(23*pi/12) - ( m_ptEnd.y - center.y ) * sin(23*pi/12)) + center.x ;
	y = static_cast<int>(( m_ptEnd.x - center.x ) * sin(23*pi/12) + ( m_ptEnd.y - center.y ) * cos(23*pi/12)) + center.y ;
	m_ptEnd.x = x ;
	m_ptEnd.y = y ;
}
