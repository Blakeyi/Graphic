// Dot.cpp: implementation of the CDot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Dot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDot::CDot()
{

}

CDot::CDot(UINT drawType , CPoint ptOrigin , CPoint ptEnd , COLORREF colorBorder , COLORREF colorFilled , int borderWidth ) :
	CGraph(drawType , ptOrigin , ptEnd , colorBorder , colorFilled ,borderWidth ) 
{
	
}

void CDot::draw( CDC* pDC )
{
/*���û�ˢ*/
	CBrush *pBrush = new CBrush ;
	pBrush->CreateSolidBrush( m_colorBorder ) ;
	CBrush *pOldBrush = pDC->SelectObject( pBrush ) ;	//����ˢѡ���豸��������
/*���û�ˢ*/
/*���û���*/
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*���û���*/

	pDC->Ellipse( CRect( CPoint(m_ptEnd.x-2,m_ptEnd.y-2) , CPoint(m_ptEnd.x+2,m_ptEnd.y+2) ) ) ;

	pDC->SelectObject( pOldBrush ) ;//�ͷŻ�ˢ�����ڴ�й¶
	delete pBrush ;
	pDC->SelectObject( pOldPen ) ;
}

CPoint CDot::getCenter( )
{
	return m_ptOrigin ;
}

CDot::~CDot()
{

}

void CDot::rotateClockW()
{

}

void CDot::rotateCounterClockW()
{

}
