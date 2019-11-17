// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__21ACD1E7_5459_42BD_943C_0C1D75C61AAB__INCLUDED_)
#define AFX_GRAPH_H__21ACD1E7_5459_42BD_943C_0C1D75C61AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const double pi = 3.141592654 ;

//����
class CGraph  
{
public:
	CPoint m_ptOrigin ;//���
	CPoint m_ptEnd ;//�յ�
	UINT m_drawType ;
	COLORREF m_colorBorder ;	//�߽���ɫ
	COLORREF m_colorFilled ;	//���ɫ
	int m_borderWidth;//�������

public:
	virtual void rotateClockW() = 0 ;
	virtual void rotateCounterClockW() = 0 ;
	virtual void smaller( );
	virtual void larger( );
	virtual void move( int ) ;
	CGraph();
	CGraph(UINT m_drawType , CPoint m_ptOrigin , CPoint m_ptEnd , COLORREF m_colorBorder , COLORREF m_colorFilled , int ) ;
	virtual void draw( CDC* pDC ) = 0 ;
	virtual CPoint getCenter( ) = 0 ;
	virtual ~CGraph();
	
};

#endif // !defined(AFX_GRAPH_H__21ACD1E7_5459_42BD_943C_0C1D75C61AAB__INCLUDED_)
