// GraphicView.cpp : implementation of the CGraphicView class
//

#include "stdafx.h"
#include "Graphic.h"

#include "GraphicDoc.h"
#include "GraphicView.h"
#include "Graph.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Dot.h"
#include "Line.h"
#include "Triangle.h"
#include "ThreeAngle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

BEGIN_MESSAGE_MAP(CGraphicView, CView)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_COMMAND(IDM_DRAW_DOT, OnDrawDot)
	ON_COMMAND(IDM_DRAW_RECTANGLE, OnDrawRectangle)
	ON_COMMAND(IDM_DRAW_STRAIGHTLINE, OnDrawStraightline)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(IDM_DRAW_ELLIPSE, OnDrawEllipse)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_WM_PAINT()
	ON_COMMAND(IDM_DRAW_RIGHTANGLED, OnDrawRightangled)
	ON_COMMAND(IDM_DRAW_SAMETRIANGLE, OnDrawSametriangle)
	ON_COMMAND(IDM_COLORFILLED, OnColorfilled)
	ON_COMMAND(IDM_COLORBORDER, OnColorborder)
	ON_COMMAND(IDM_NONEFILLED, OnNonefilled)
	ON_COMMAND(IDM_DRAW_TRIANGLE, OnDrawTriangle)
	ON_COMMAND(IDM_BORDERDOWN, OnBorderdown)
	ON_COMMAND(IDM_BORDERUP, OnBorderup)
	ON_COMMAND(IDM_DRAW_CIRCLEBORDER, OnDrawCircleborder)
	ON_COMMAND(IDM_DRAW_CIRCLEFILLED, OnDrawCirclefilled)
	ON_COMMAND(IDM_DRAW_RECTBORDER, OnDrawRectborder)
	ON_COMMAND(IDM_DRAW_RECTFILLED, OnDrawRectfilled)
	ON_COMMAND(IDM_DRAW_TRIBORDER, OnDrawTriborder)
	ON_COMMAND(IDM_DRAW_TRIFILLED, OnDrawTrifilled)
	ON_COMMAND(IDM_DRAW_CENTER, OnDrawCenter)
	ON_COMMAND(IDM_MOVEDOWN, OnMovedown)
	ON_COMMAND(IDM_MOVELEFT, OnMoveleft)
	ON_COMMAND(IDM_MOVERIGHT, OnMoveright)
	ON_COMMAND(IDM_MOVEUP, OnMoveup)
	ON_COMMAND(IDM_FIGLARGER, OnFiglarger)
	ON_COMMAND(IDM_FIGSMALLER, OnFigsmaller)
	ON_COMMAND(IDM_ROTATESHUN, OnRotateshun)
	ON_COMMAND(IDM_ROTATENI, OnRotateni)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CGraphicView::OnFileOpen)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView construction/destruction

CGraphicView::CGraphicView()
{
	// TODO: add construction code here
	m_beDrawing = false ;
	m_drawType = 0 ;
	m_ptEnd = 0 ;
	m_ptOrigin = 0 ;
	m_colorBorder = RGB ( 0 , 0 , 0 ) ;	//Ĭ�ϱ���ɫΪ��ɫ
	m_colorFilled = -1 ;
	m_ptsNum = 0 ;
	m_borderWidth = 1 ;
	m_moveDirection = 0 ;
	//�Ŵ�����ʼ��
	m_fMultiple = 0.0;
	//ԭͼ����ԭ��
	m_OriginSrcPoint = (0, 0);
	//ԭͼ�Ŀ��
	m_nWidthSrc = 0;
	//ԭͼ�ĸ߶�
	m_nWidthSrc = 0;
	//���ֹ���ʱ�����������
	m_ptRollPointClient = (0, 0);
	//���ֹ���ʱ��Ļ�����
	m_ptRollPointScreen = (0, 0);

}

CGraphicView::~CGraphicView()
{
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing

//�������ͼ�εĳ���
const int DRAW_DOT = 1 ;
const int DRAW_CIRCLE = 2 ;
const int DRAW_STRAIGHTLINE = 3 ;
const int DRAW_ELLIPSE = 4 ;
const int DRAW_RECTANGLE = 5 ;
const int DRAW_RIGHTANGLED = 6 ;
const int DRAW_CENTER = 7 ;	//��ʾ���Բ��
const int DRAW_SAMETRIANGLE = 8 ;
const int DRAW_TRIANGLE = 9 ;
//const int DRAW_CENTER = 10 ;

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (!image.IsNull())
	{
		//image.Draw(pDC->GetSafeHdc(), 0, 0);
		//���ζ���rectControl���ͻ����ľ�������
		CRect rectClient;
		//��ȡ������Client�ľ�������
		GetClientRect(rectClient);

		//ÿ����ʾǰ�Ƚ�ԭ���Ľ���ˢ�³ư�ɫ
		CBrush br(0xffffff);//ˢ�ɰ�ɫ��255,255,255��
		pDC->FillRect(rectClient, &br);

		//��ȡͼƬ�Ŀ���
		double dWidthOrigin = image.GetWidth();
		double dHeightOrigin = image.GetHeight();
		//���������ͼƬ�Ŀ���
		double dWidthStrectch;
		double dHeightStrectch;

		//��ʾ��������ʹԭͼ������ʾ�ڿͻ�������
		if (dWidthOrigin > dHeightOrigin)
		{
			//ԭͼ�Ŀ�ȸߴ󣺴����Ŀ�ȣ���������ʾ��ȿ�
			dWidthStrectch = rectClient.Width();
			//�����ĸ߶�
			dHeightStrectch = dWidthStrectch / dWidthOrigin * dHeightOrigin;
		}
		else
		{
			//ԭͼ�ĸ߱ȿ�󣺴����ĸ߶ȣ���������ʾ��ȸ�
			dHeightStrectch = rectClient.Height();
			dWidthStrectch = dHeightStrectch / dHeightOrigin * dWidthOrigin;
		}

		//��ͼ�����ڿͻ���Client��λ��
		m_rectDraw = CRect(CPoint((rectClient.Width() - dWidthStrectch) / 2, (rectClient.Height() - dHeightStrectch) / 2), CSize(dWidthStrectch, dHeightStrectch));

		//����ͼƬ���ؼ���ʾ������CImage::StretchBlt
		//���+�ߴ����
		//SRCCOPY����Դ������ֱ�ӿ�����Ŀ���������pDC
		//handle to destination DC��pDC->m_hDC
		/*����1*/
		//cimgImage.StretchBlt(pDC->m_hDC, rectDraw, SRCCOPY);
		/*����2*/
		//Ŀ������Dst
		int xDest = m_rectDraw.TopLeft().x;
		int yDest = m_rectDraw.TopLeft().y;
		int nDestWidth = m_rectDraw.Width();
		int nDestHeight = m_rectDraw.Height();
		//ԴͼƬSrc
		int xSrc = m_OriginSrcPoint.x;
		int ySrc = m_OriginSrcPoint.y;
		int nSrcWidth = m_nWidthSrc;
		int nSrcHeight = m_nHeightSrc;
		//��դ����
		DWORD dwROP = SRCCOPY;
		//���Ų���
		pDC->SetStretchBltMode(COLORONCOLOR);
		image.StretchBlt(pDC->GetSafeHdc(), xDest, yDest, nDestWidth, dHeightStrectch, xSrc, ySrc, nSrcWidth, nSrcHeight, dwROP);
		//image.Draw(pDC->GetSafeHdc(), 0, 0);
	}

	

	// TODO: add draw code for native data here
	
	int i ;	//������ˢ
	for ( i = 0 ; i < m_ptrArray.GetSize ( ) ; ++ i )
	{
		((CGraph*)m_ptrArray.GetAt( i ))->draw( pDC ) ;
	}

	//�����ǰû�ڻ�ͼ���򷵻�
	if ( !m_beDrawing )	
		return ;
	//���򣬻��Ƶ�ǰ���ڻ滭ͼ��
/* �������û�ˢ��������*/
	CBrush *pBrush ;
	if ( m_colorFilled == -1 )
		pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//����͸���Ļ�ˢ
	else
	{
		pBrush = new CBrush ;
		pBrush->CreateSolidBrush( m_colorFilled ) ;
	}
	CBrush *pOldBrush = pDC->SelectObject( pBrush ) ;	//����ˢѡ���豸��������
/* �������û�ˢ��������*/
/*���û���*/
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*���û���*/
	CRect rectangle( m_ptOrigin , m_ptEnd ) ;
	CPoint point( m_ptEnd ) ;
	CPoint pt_temp ( point - m_ptOrigin ) ;//���ڻ���������
	CPoint pts[3] ;	//�������������
	switch ( m_drawType )
	{
		case DRAW_RECTANGLE :
			pDC->Rectangle( CRect( m_ptOrigin , m_ptEnd ) ) ;
			break ;
		case DRAW_STRAIGHTLINE :
			pDC->MoveTo( m_ptOrigin ) ;
			pDC->LineTo( m_ptEnd ) ;
			break ;
		case DRAW_CIRCLE :
			//��switch�ⶨ��CRect rectangle( m_ptOrigin , point ) ;
			if( rectangle.Height() >= rectangle.Width() )
			{	//�߶ȱȽϴ�ˮƽ����point����
				point += CPoint( abs(rectangle.Height() - rectangle.Width()) , 0 ) ;
			}
			else
			{	//��ȱȽϴ���ֱ����point����
				point += CPoint( 0 , abs(rectangle.Height() - rectangle.Width()) ) ;
			}
			pDC->Ellipse( CRect( m_ptOrigin , point ) ) ;
			break ;
		case DRAW_ELLIPSE:
			pDC->Ellipse( rectangle ) ;
			break ;
		case DRAW_RIGHTANGLED :
			//������switch֮��CPoint pt_temp ( point - m_ptOrigin ) ;
			pts[ 0 ] = m_ptOrigin ;
			pts[ 1 ] = CPoint( point.x + pt_temp.y , point.y - pt_temp.x ) ;
			pts[ 2 ] = CPoint( point.x - pt_temp.y , point.y + pt_temp.x ) ;
			pDC->MoveTo( pts[0] ) ;
			pDC->LineTo( pts[1] ) ;
			pDC->LineTo( pts[2] ) ;
			pDC->LineTo( pts[0] ) ;
			pDC-> Polygon( pts , 3 ) ;	//�����ɫ
			break ;
		case DRAW_SAMETRIANGLE :
			pts[ 0 ] = m_ptOrigin ;
			pts[ 1 ] = CPoint( point.x + static_cast<int>(pt_temp.y * 0.57735) , point.y - static_cast<int>(pt_temp.x * 0.57735) ) ;
			pts[ 2 ] = CPoint( point.x - static_cast<int>(pt_temp.y * 0.57735) , point.y + static_cast<int>(pt_temp.x * 0.57735) ) ;
			pDC->MoveTo( pts[0] ) ;
			pDC->LineTo( pts[1] ) ;
			pDC->LineTo( pts[2] ) ;
			pDC->LineTo( pts[0] ) ;
			pDC-> Polygon( pts , 3 ) ;	//�����ɫ
		default:
			break ;
	}
/* �����ͷŻ�ˢ��������*/
	pDC->SelectObject( pOldBrush ) ;//�ͷŻ�ˢ�����ڴ�й¶
	if( m_colorFilled != -1 )
		delete pBrush ;
/* �����ͷŻ�ˢ��������*/
/* �����ͷŻ��ʡ�������*/
	pDC->SelectObject( pOldPen ) ;
/* �����ͷŻ��ʡ�������*/
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView printing

BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView diagnostics

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicDoc* CGraphicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicDoc)));
	return (CGraphicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers

void CGraphicView::OnDrawDot() 
{
	m_drawType = DRAW_DOT ;
}

void CGraphicView::OnDrawRectangle() 
{
	m_drawType = DRAW_RECTANGLE ;
}

void CGraphicView::OnDrawStraightline() 
{
	m_drawType = DRAW_STRAIGHTLINE ;
}

void CGraphicView::OnDrawCircle() 
{
	m_drawType = DRAW_CIRCLE ;
}

void CGraphicView::OnDrawEllipse() 
{
	m_drawType = DRAW_ELLIPSE ;	
}

void CGraphicView::OnDrawRightangled() 
{
	m_drawType = DRAW_RIGHTANGLED ;
}

void CGraphicView::OnDrawSametriangle() 
{
	m_drawType = DRAW_SAMETRIANGLE ;	
}

void CGraphicView::OnDrawTriangle() 
{
	m_drawType = DRAW_TRIANGLE ;
}

void CGraphicView::OnDrawCircleborder() 
{
	m_drawType = DRAW_CIRCLE ;
	m_colorFilled = -1 ;
}

void CGraphicView::OnDrawCirclefilled() 
{
	m_drawType = DRAW_CIRCLE ;
	if( m_colorFilled == -1 )
		m_colorFilled = RGB(255,255,255) ;
	m_colorBorder = m_colorFilled ;
}

void CGraphicView::OnDrawRectborder() 
{
	m_drawType = DRAW_RECTANGLE ;
	m_colorFilled = -1 ;
}

void CGraphicView::OnDrawRectfilled() 
{
	m_drawType = DRAW_RECTANGLE ;
	if( m_colorFilled == -1 )
		m_colorFilled = RGB(255,255,255) ;
	m_colorBorder = m_colorFilled ;
}

void CGraphicView::OnDrawTriborder() 
{
	m_drawType = DRAW_TRIANGLE ;
	m_colorFilled = -1 ;
}

void CGraphicView::OnDrawTrifilled() 
{
	m_drawType = DRAW_TRIANGLE ;
	if( m_colorFilled == -1 )
		m_colorFilled = RGB(255,255,255) ;
	m_colorBorder = m_colorFilled ;
}

void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_beDrawing = true ;	//��ʾ��Ҫ��ͼ
	m_ptOrigin = point ;	//��ʼ����
	
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_beDrawing = false ;
	
	CClientDC dc ( this ) ;	//����DC
	CGraph *pGraph = NULL ;
	CRect rectangle( m_ptOrigin , point ) ;	//����Բ����

	//������ͨ��������
	static int m_i = 0 ;
	switch ( m_drawType )	//�����û�ѡ�����ͼ��
	{
		case DRAW_DOT :	//�������ص�
			pGraph = new CDot( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			Invalidate();	//������ͼ
			break ;
		case DRAW_RECTANGLE :
			pGraph = new CRectangle ( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			break ;
		case DRAW_STRAIGHTLINE :
			pGraph = new CLine ( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			break ;
		case DRAW_CIRCLE :
		//	CRect rectangle( m_ptOrigin , point ) ;
			if( rectangle.Height() >= rectangle.Width() )
			{	//�߶ȱȽϴ�ˮƽ����point����
				point += CPoint( abs(rectangle.Height() - rectangle.Width()) , 0 ) ;
			}
			else
			{	//��ȱȽϴ���ֱ����point����
				point += CPoint( 0 , abs(rectangle.Height() - rectangle.Width()) ) ;
			}
		case DRAW_ELLIPSE:
			pGraph = new CCircle( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			break ;
		case DRAW_RIGHTANGLED :
		case DRAW_SAMETRIANGLE :
			pGraph = new CTriangle( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			break ;
		case DRAW_TRIANGLE :
			dc.SetPixel( m_ptOrigin , m_colorBorder ) ;
			m_pts[ m_i ] = m_ptOrigin ;
			++ m_i ;
			if( m_i == 3 )
			{
				pGraph = new CThreeAngle( m_drawType , 0 , 0 , m_pts , m_colorBorder , m_colorFilled , m_borderWidth ) ;
				m_i = 0 ;
				Invalidate();
			}
			break ;
		default:
			break ;
	}

	if( pGraph )
		m_ptrArray.Add( pGraph ) ;

	CView::OnLButtonUp(nFlags, point);
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{	
	CView::OnMouseMove(nFlags, point);	

	if ( m_beDrawing )	//������ڻ�ͼ����L-BUTTON-DOWN
	{
		m_ptEnd = point ;
		Invalidate();			// ������ͼ��Ҳ���ǵ���OnDraw����
	}
}

void CGraphicView::OnEditUndo() 
{	//ѡ���˳�������ȥ��m_ptrArray��������һ��Ԫ��
	//���ػ�ʱ�����ٻ����һ������
	int i = m_ptrArray.GetSize() - 1 ;
	CGraph *temp ;
	if ( (temp = (CGraph*)m_ptrArray.GetAt(i)) != NULL )
	{
		m_ptrArray.RemoveAt(i) ;
		delete temp ;
	}

	Invalidate();	//������ͼ
}

void CGraphicView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);
    OnDraw(&dc); 
	
	// Do not call CView::OnPaint() for painting messages
}

void CGraphicView::OnColorfilled() 
{
	CColorDialog dlg ;
	dlg.m_cc.Flags |= CC_RGBINIT ;
	dlg.m_cc.rgbResult = m_colorFilled ;
	if( IDOK == dlg.DoModal( ) )
	{
		m_colorFilled = dlg.m_cc.rgbResult ;
	}
}

void CGraphicView::OnColorborder() 
{
	CColorDialog dlg ;
	dlg.m_cc.Flags |= CC_RGBINIT ;
	dlg.m_cc.rgbResult = m_colorBorder ;
	if( IDOK == dlg.DoModal( ) )
	{
		m_colorBorder = dlg.m_cc.rgbResult ;
	}
}

void CGraphicView::OnNonefilled() 
{
	m_colorFilled = -1 ;	
}

void CGraphicView::OnBorderdown() 
{
	if( m_borderWidth == 1 )
		return ;
	m_borderWidth -= 1 ;
}

void CGraphicView::OnBorderup() 
{
	if( m_borderWidth >= 10 )
		return ;
	m_borderWidth += 1 ;	
}

void CGraphicView::OnDrawCenter() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	//���ѡ����ʾ���ģ���ֱ�ӻ�������
	CClientDC dc(this) ;
	COLORREF color = m_colorFilled ;
	if ( color == RGB(255,0,0) )
		color = RGB(0,0,0) ;
	else
		color = RGB(255,0,0) ;
	CPoint center( ((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->getCenter( ) ) ;

/*���û�ˢ*/
	CBrush *pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//����͸���Ļ�ˢ
	CBrush *pOldBrush = dc.SelectObject( pBrush ) ;	//����ˢѡ���豸��������
/*���û�ˢ*/
/*���û���*/
	CPen pen( PS_SOLID , 1 , color ) ;
	CPen *pOldPen = dc.SelectObject( &pen ) ;		
/*���û���*/

	dc.Rectangle( CRect(((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->m_ptOrigin,
				((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->m_ptEnd) ) ;

	dc.SelectObject( pOldBrush ) ;//�ͷŻ�ˢ�����ڴ�й¶
	dc.SelectObject( pOldPen ) ;

/*���û�ˢ*/
	pBrush = new CBrush ;
	pBrush->CreateSolidBrush( color ) ;
	pOldBrush = dc.SelectObject( pBrush ) ;	//����ˢѡ���豸��������
/*���û�ˢ*/
/*���û���*/
	CPen pen1( PS_SOLID , 4 , color ) ;
	pOldPen = dc.SelectObject( &pen1 ) ;	
/*���û���*/

	dc.Ellipse( CRect( CPoint(center.x-1,center.y-1) , CPoint(center.x+1,center.y+1) ) ) ;	//��ͼ

	dc.SelectObject( pOldBrush ) ;//�ͷŻ�ˢ�����ڴ�й¶
	dc.SelectObject( pOldPen ) ;
}

void CGraphicView::OnMoveup() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 1 ) ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnMovedown() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 2 ) ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnMoveleft() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 3 ) ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnMoveright() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 4 ) ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnFiglarger() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->larger() ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnFigsmaller() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->smaller() ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnRotateshun() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->rotateClockW() ;
	Invalidate();	//������ͼ
}

void CGraphicView::OnRotateni() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->rotateCounterClockW() ;
	Invalidate();	//������ͼ
}


void CGraphicView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png||"));
	
		// TODO: �ڴ���������������
		//���ô��ļ����͵��˲���

		//�򿪶Ի���
	int result = dlg.DoModal();
	if (IDOK == result)	//.DoModal()��ʾһ��ģ̬�Ի���,�ɹ�����IDOK
	{
		//�ɹ���ʾ�򿪼���ͼƬ�ĶԻ���	
		//��ȡ���ص������Ϣ��·�����֡����֡�·��
		cstrLoadPathName = dlg.GetPathName();
		//��ȡ��ʽ����ͼƬ������
		cstrLoadName = dlg.GetFileName();
		//ȥ��·�����е�����:
		//�ҵ�·�����ִ��������ǵڼ�������ֵ
		int index = cstrLoadPathName.Find(cstrLoadName);
		cstrLoadPath = cstrLoadPathName.Left(index);

		//�ж��Ƿ���ع�ͼƬ
		if (!image.IsNull())
		{
			//���ع�������
			image.Destroy();
		}
		//����ͼƬ
		image.Load(cstrLoadPathName);
		//�Ŵ�������
		m_fMultiple = 0;
		//ԭͼ�Ŀ��
		m_nWidthSrc = image.GetWidth();
		//ԭͼ�ĸ߶�
		m_nHeightSrc = image.GetHeight();
		//Դ��ԭ������
		m_OriginSrcPoint = (0, 0);
		//ʹ��ǰ�Ĵ�����Ч:��Windows֪������������ڸ����»���һ����
		Invalidate();
	}
	else if (IDCANCEL == result)
	{
		MessageBox(_T("û��ѡ�����ͼƬ"));
		return;
	}
	
}



BOOL CGraphicView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//pt��Screen��ʾ������ϵ������
	//��OnMouseWheel����ߴ�����ǰλ�������������
	m_ptRollPointScreen = pt;
	//��pt����Ļ����ϵת������������ϵ
	//ScreenToClient�������������ָ��
	m_ptRollPointClient = pt;
	ScreenToClient(&m_ptRollPointClient);


	//������ڼ��ص�ͼ�񣬸ı�ԭ��Ϳ���
	if (!image.IsNull())
	{
		//����һ��tmp�ݴ���������
		//������һ�εĽ��
		CPoint ptTmp = m_OriginSrcPoint;
		int nTmpWidth = m_nWidthSrc;
		int nTmpHeight = m_nHeightSrc;

		//�Ŵ����
		if (zDelta > 0)
		{
			//�жϹ��������Ƿ��ڻ�ͼ�����У��������ұߣ����Ҳ�����
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//��ֹ���Ź���
			//�������<50�������Ź���
			else if (m_nWidthSrc < 50 || m_nHeightSrc < 50)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//���÷Ŵ���
			m_fMultiple = 0.1;
			//�ı�ԭͼ�Ŀ��ߣ�
			//ʵ�ַŴ�Ĺ�����ʵ�ǻ�ȡԭͼĳ�������򡿵Ĺ���
			//��������򡿶Աȡ�Դͼ������С��
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			/*����������ǰ��Rect�Ŀ�͸ߵı�������Ȼ���ñ�������Delta������ǰ����ߵĲ�ֵ��*/
			float nDeltaX = m_ptRollPointClient.x - float(m_rectDraw.TopLeft().x);
			float fPosXRatio = nDeltaX / float(m_rectDraw.Width());
			float nDeltaY = m_ptRollPointClient.y - float(m_rectDraw.TopLeft().y);
			float fPosYRatio = nDeltaY / float(m_rectDraw.Height());

			//�ı���ʾ�����ԭ��λ��
			//�ı�ԭ���λ�ã����ҡ����ƶ�
			//1�������Ϊ���ĵ����ţ��Ŵ�
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * fPosXRatio;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * fPosYRatio;

		}
		//��С����
		if (zDelta < 0)
		{
			//�жϹ��������Ƿ��ڻ�ͼ������
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//������ߵ�Ϊ3000������С����
			else if (m_nWidthSrc > 20000 || m_nHeightSrc > 20000)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//������С����
			m_fMultiple = -0.1;

			//�ı�ԭͼ�Ŀ��ߣ�
			//ʵ�ַŴ�Ĺ�����ʵ�ǻ�ȡԭͼĳ�������򡿵Ĺ���
			//��������򡿶Աȡ�Դͼ������С��
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			//�ı���ʾ�����ԭ��λ��
			//�ı�ԭ���λ�ã����ҡ����ƶ�
			//2���Թ����������Ľ������ţ���С��fPosXRatio = fPosYRatio = 0.5
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * 0.5;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * 0.5;
		}

		//ʹ��ǰ�Ĵ�����Ч:��Windows֪������������ڸ����»���һ����
		Invalidate();

	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
