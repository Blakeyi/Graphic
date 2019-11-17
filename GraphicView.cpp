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
	m_colorBorder = RGB ( 0 , 0 , 0 ) ;	//默认边线色为黑色
	m_colorFilled = -1 ;
	m_ptsNum = 0 ;
	m_borderWidth = 1 ;
	m_moveDirection = 0 ;
	//放大倍数初始化
	m_fMultiple = 0.0;
	//原图坐标原点
	m_OriginSrcPoint = (0, 0);
	//原图的宽度
	m_nWidthSrc = 0;
	//原图的高度
	m_nWidthSrc = 0;
	//滚轮滚动时工作区坐标点
	m_ptRollPointClient = (0, 0);
	//滚轮滚动时屏幕坐标点
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

//定义代表图形的常量
const int DRAW_DOT = 1 ;
const int DRAW_CIRCLE = 2 ;
const int DRAW_STRAIGHTLINE = 3 ;
const int DRAW_ELLIPSE = 4 ;
const int DRAW_RECTANGLE = 5 ;
const int DRAW_RIGHTANGLED = 6 ;
const int DRAW_CENTER = 7 ;	//表示标记圆心
const int DRAW_SAMETRIANGLE = 8 ;
const int DRAW_TRIANGLE = 9 ;
//const int DRAW_CENTER = 10 ;

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (!image.IsNull())
	{
		//image.Draw(pDC->GetSafeHdc(), 0, 0);
		//矩形对象rectControl：客户区的矩形区域
		CRect rectClient;
		//获取工作区Client的矩形区域
		GetClientRect(rectClient);

		//每次显示前先将原来的界面刷新称白色
		CBrush br(0xffffff);//刷成白色（255,255,255）
		pDC->FillRect(rectClient, &br);

		//获取图片的宽、高
		double dWidthOrigin = image.GetWidth();
		double dHeightOrigin = image.GetHeight();
		//定义拉伸后图片的宽、高
		double dWidthStrectch;
		double dHeightStrectch;

		//显示方法二：使原图最大地显示在客户区当中
		if (dWidthOrigin > dHeightOrigin)
		{
			//原图的宽比高大：处理后的宽度，让它和显示框等宽
			dWidthStrectch = rectClient.Width();
			//处理后的高度
			dHeightStrectch = dWidthStrectch / dWidthOrigin * dHeightOrigin;
		}
		else
		{
			//原图的高比宽大：处理后的高度，让它和显示框等高
			dHeightStrectch = rectClient.Height();
			dWidthStrectch = dHeightStrectch / dHeightOrigin * dWidthOrigin;
		}

		//绘图区域在客户区Client的位置
		m_rectDraw = CRect(CPoint((rectClient.Width() - dWidthStrectch) / 2, (rectClient.Height() - dHeightStrectch) / 2), CSize(dWidthStrectch, dHeightStrectch));

		//绘制图片到控件表示的区域：CImage::StretchBlt
		//句柄+尺寸参数
		//SRCCOPY：将源矩形区直接拷贝到目标矩形区域pDC
		//handle to destination DC：pDC->m_hDC
		/*方法1*/
		//cimgImage.StretchBlt(pDC->m_hDC, rectDraw, SRCCOPY);
		/*方法2*/
		//目标区域Dst
		int xDest = m_rectDraw.TopLeft().x;
		int yDest = m_rectDraw.TopLeft().y;
		int nDestWidth = m_rectDraw.Width();
		int nDestHeight = m_rectDraw.Height();
		//源图片Src
		int xSrc = m_OriginSrcPoint.x;
		int ySrc = m_OriginSrcPoint.y;
		int nSrcWidth = m_nWidthSrc;
		int nSrcHeight = m_nHeightSrc;
		//光栅操作
		DWORD dwROP = SRCCOPY;
		//缩放操作
		pDC->SetStretchBltMode(COLORONCOLOR);
		image.StretchBlt(pDC->GetSafeHdc(), xDest, yDest, nDestWidth, dHeightStrectch, xSrc, ySrc, nSrcWidth, nSrcHeight, dwROP);
		//image.Draw(pDC->GetSafeHdc(), 0, 0);
	}

	

	// TODO: add draw code for native data here
	
	int i ;	//背景重刷
	for ( i = 0 ; i < m_ptrArray.GetSize ( ) ; ++ i )
	{
		((CGraph*)m_ptrArray.GetAt( i ))->draw( pDC ) ;
	}

	//如果当前没在画图，则返回
	if ( !m_beDrawing )	
		return ;
	//否则，绘制当前正在绘画图案
/* 这里设置画刷…………*/
	CBrush *pBrush ;
	if ( m_colorFilled == -1 )
		pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//创建透明的画刷
	else
	{
		pBrush = new CBrush ;
		pBrush->CreateSolidBrush( m_colorFilled ) ;
	}
	CBrush *pOldBrush = pDC->SelectObject( pBrush ) ;	//将画刷选择到设备描述表当中
/* 这里设置画刷…………*/
/*设置画笔*/
	CPen pen( PS_SOLID , m_borderWidth , m_colorBorder ) ;
	CPen *pOldPen = pDC->SelectObject( &pen ) ;		
/*设置画笔*/
	CRect rectangle( m_ptOrigin , m_ptEnd ) ;
	CPoint point( m_ptEnd ) ;
	CPoint pt_temp ( point - m_ptOrigin ) ;//用于绘制三角形
	CPoint pts[3] ;	//用于填充三角形
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
			//在switch外定义CRect rectangle( m_ptOrigin , point ) ;
			if( rectangle.Height() >= rectangle.Width() )
			{	//高度比较大，水平方向point扩大
				point += CPoint( abs(rectangle.Height() - rectangle.Width()) , 0 ) ;
			}
			else
			{	//宽度比较大，竖直方向point扩大
				point += CPoint( 0 , abs(rectangle.Height() - rectangle.Width()) ) ;
			}
			pDC->Ellipse( CRect( m_ptOrigin , point ) ) ;
			break ;
		case DRAW_ELLIPSE:
			pDC->Ellipse( rectangle ) ;
			break ;
		case DRAW_RIGHTANGLED :
			//定义在switch之外CPoint pt_temp ( point - m_ptOrigin ) ;
			pts[ 0 ] = m_ptOrigin ;
			pts[ 1 ] = CPoint( point.x + pt_temp.y , point.y - pt_temp.x ) ;
			pts[ 2 ] = CPoint( point.x - pt_temp.y , point.y + pt_temp.x ) ;
			pDC->MoveTo( pts[0] ) ;
			pDC->LineTo( pts[1] ) ;
			pDC->LineTo( pts[2] ) ;
			pDC->LineTo( pts[0] ) ;
			pDC-> Polygon( pts , 3 ) ;	//填充颜色
			break ;
		case DRAW_SAMETRIANGLE :
			pts[ 0 ] = m_ptOrigin ;
			pts[ 1 ] = CPoint( point.x + static_cast<int>(pt_temp.y * 0.57735) , point.y - static_cast<int>(pt_temp.x * 0.57735) ) ;
			pts[ 2 ] = CPoint( point.x - static_cast<int>(pt_temp.y * 0.57735) , point.y + static_cast<int>(pt_temp.x * 0.57735) ) ;
			pDC->MoveTo( pts[0] ) ;
			pDC->LineTo( pts[1] ) ;
			pDC->LineTo( pts[2] ) ;
			pDC->LineTo( pts[0] ) ;
			pDC-> Polygon( pts , 3 ) ;	//填充颜色
		default:
			break ;
	}
/* 这里释放画刷…………*/
	pDC->SelectObject( pOldBrush ) ;//释放画刷避免内存泄露
	if( m_colorFilled != -1 )
		delete pBrush ;
/* 这里释放画刷…………*/
/* 这里释放画笔…………*/
	pDC->SelectObject( pOldPen ) ;
/* 这里释放画笔…………*/
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
	m_beDrawing = true ;	//表示正要画图
	m_ptOrigin = point ;	//起始坐标
	
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_beDrawing = false ;
	
	CClientDC dc ( this ) ;	//创建DC
	CGraph *pGraph = NULL ;
	CRect rectangle( m_ptOrigin , point ) ;	//绘制圆形用

	//绘制普通三角形用
	static int m_i = 0 ;
	switch ( m_drawType )	//根据用户选择绘制图形
	{
		case DRAW_DOT :	//绘制像素点
			pGraph = new CDot( m_drawType , m_ptOrigin , point , m_colorBorder , m_colorFilled , m_borderWidth ) ;
			Invalidate();	//更新视图
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
			{	//高度比较大，水平方向point扩大
				point += CPoint( abs(rectangle.Height() - rectangle.Width()) , 0 ) ;
			}
			else
			{	//宽度比较大，竖直方向point扩大
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

	if ( m_beDrawing )	//如果正在画图，即L-BUTTON-DOWN
	{
		m_ptEnd = point ;
		Invalidate();			// 更新视图，也就是调用OnDraw函数
	}
}

void CGraphicView::OnEditUndo() 
{	//选择了撤销，则去掉m_ptrArray数组的最后一个元素
	//即重绘时，不再绘最后一个数组
	int i = m_ptrArray.GetSize() - 1 ;
	CGraph *temp ;
	if ( (temp = (CGraph*)m_ptrArray.GetAt(i)) != NULL )
	{
		m_ptrArray.RemoveAt(i) ;
		delete temp ;
	}

	Invalidate();	//更新视图
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
	//如果选择显示重心，就直接画出重心
	CClientDC dc(this) ;
	COLORREF color = m_colorFilled ;
	if ( color == RGB(255,0,0) )
		color = RGB(0,0,0) ;
	else
		color = RGB(255,0,0) ;
	CPoint center( ((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->getCenter( ) ) ;

/*设置画刷*/
	CBrush *pBrush = CBrush::FromHandle ( (HBRUSH)GetStockObject( NULL_BRUSH ) ) ;//创建透明的画刷
	CBrush *pOldBrush = dc.SelectObject( pBrush ) ;	//将画刷选择到设备描述表当中
/*设置画刷*/
/*设置画笔*/
	CPen pen( PS_SOLID , 1 , color ) ;
	CPen *pOldPen = dc.SelectObject( &pen ) ;		
/*设置画笔*/

	dc.Rectangle( CRect(((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->m_ptOrigin,
				((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->m_ptEnd) ) ;

	dc.SelectObject( pOldBrush ) ;//释放画刷避免内存泄露
	dc.SelectObject( pOldPen ) ;

/*设置画刷*/
	pBrush = new CBrush ;
	pBrush->CreateSolidBrush( color ) ;
	pOldBrush = dc.SelectObject( pBrush ) ;	//将画刷选择到设备描述表当中
/*设置画刷*/
/*设置画笔*/
	CPen pen1( PS_SOLID , 4 , color ) ;
	pOldPen = dc.SelectObject( &pen1 ) ;	
/*设置画笔*/

	dc.Ellipse( CRect( CPoint(center.x-1,center.y-1) , CPoint(center.x+1,center.y+1) ) ) ;	//画图

	dc.SelectObject( pOldBrush ) ;//释放画刷避免内存泄露
	dc.SelectObject( pOldPen ) ;
}

void CGraphicView::OnMoveup() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 1 ) ;
	Invalidate();	//更新视图
}

void CGraphicView::OnMovedown() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 2 ) ;
	Invalidate();	//更新视图
}

void CGraphicView::OnMoveleft() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 3 ) ;
	Invalidate();	//更新视图
}

void CGraphicView::OnMoveright() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->move( 4 ) ;
	Invalidate();	//更新视图
}

void CGraphicView::OnFiglarger() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->larger() ;
	Invalidate();	//更新视图
}

void CGraphicView::OnFigsmaller() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->smaller() ;
	Invalidate();	//更新视图
}

void CGraphicView::OnRotateshun() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->rotateClockW() ;
	Invalidate();	//更新视图
}

void CGraphicView::OnRotateni() 
{
	if (m_ptrArray.GetSize()==0)
		return ;
	((CGraph*)m_ptrArray[m_ptrArray.GetSize() - 1])->rotateCounterClockW() ;
	Invalidate();	//更新视图
}


void CGraphicView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, _T("Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png||"));
	
		// TODO: 在此添加命令处理程序代码
		//设置打开文件类型的滤波器

		//打开对话框
	int result = dlg.DoModal();
	if (IDOK == result)	//.DoModal()显示一个模态对话框,成功返回IDOK
	{
		//成功显示打开加载图片的对话框	
		//获取加载的相关信息：路径名字、名字、路径
		cstrLoadPathName = dlg.GetPathName();
		//获取格式化的图片的名字
		cstrLoadName = dlg.GetFileName();
		//去除路径当中的名字:
		//找到路径名字从左往右是第几个索引值
		int index = cstrLoadPathName.Find(cstrLoadName);
		cstrLoadPath = cstrLoadPathName.Left(index);

		//判断是否加载过图片
		if (!image.IsNull())
		{
			//加载过，销毁
			image.Destroy();
		}
		//加载图片
		image.Load(cstrLoadPathName);
		//放大倍数清零
		m_fMultiple = 0;
		//原图的宽度
		m_nWidthSrc = image.GetWidth();
		//原图的高度
		m_nHeightSrc = image.GetHeight();
		//源的原点清零
		m_OriginSrcPoint = (0, 0);
		//使当前的窗口无效:让Windows知道这个窗口现在该重新绘制一下了
		Invalidate();
	}
	else if (IDCANCEL == result)
	{
		MessageBox(_T("没有选择加载图片"));
		return;
	}
	
}



BOOL CGraphicView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//pt是Screen显示器坐标系的坐标
	//将OnMouseWheel的左边传到当前位置坐标变量当中
	m_ptRollPointScreen = pt;
	//将pt从屏幕坐标系转换工作区坐标系
	//ScreenToClient传入的是坐标点的指针
	m_ptRollPointClient = pt;
	ScreenToClient(&m_ptRollPointClient);


	//如果存在加载的图像，改变原点和宽、高
	if (!image.IsNull())
	{
		//设立一个tmp暂存正常变量
		//保存上一次的结果
		CPoint ptTmp = m_OriginSrcPoint;
		int nTmpWidth = m_nWidthSrc;
		int nTmpHeight = m_nHeightSrc;

		//放大操作
		if (zDelta > 0)
		{
			//判断滚轮坐标是否在绘图区当中：在左侧的右边，在右侧的左边
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//防止缩放过度
			//如果宽、高<50，则缩放过度
			else if (m_nWidthSrc < 50 || m_nHeightSrc < 50)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//设置放大倍数
			m_fMultiple = 0.1;
			//改变原图的宽、高：
			//实现放大的过程其实是获取原图某个【区域】的过程
			//这个【区域】对比【源图区域】是小的
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			/*（计算缩放前在Rect的宽和高的比例）、然后用比例乘以Delta（缩放前后宽、高的差值）*/
			float nDeltaX = m_ptRollPointClient.x - float(m_rectDraw.TopLeft().x);
			float fPosXRatio = nDeltaX / float(m_rectDraw.Width());
			float nDeltaY = m_ptRollPointClient.y - float(m_rectDraw.TopLeft().y);
			float fPosYRatio = nDeltaY / float(m_rectDraw.Height());

			//改变显示区域的原点位置
			//改变原点的位置，往右、下移动
			//1、以鼠标为中心的缩放（放大）
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * fPosXRatio;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * fPosYRatio;

		}
		//缩小操作
		if (zDelta < 0)
		{
			//判断滚轮坐标是否在绘图区当中
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//如果宽、高到为3000，则缩小过度
			else if (m_nWidthSrc > 20000 || m_nHeightSrc > 20000)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//设置缩小倍数
			m_fMultiple = -0.1;

			//改变原图的宽、高：
			//实现放大的过程其实是获取原图某个【区域】的过程
			//这个【区域】对比【源图区域】是小的
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			//改变显示区域的原点位置
			//改变原点的位置，往右、下移动
			//2、以工作区的中心进行缩放（缩小）fPosXRatio = fPosYRatio = 0.5
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * 0.5;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * 0.5;
		}

		//使当前的窗口无效:让Windows知道这个窗口现在该重新绘制一下了
		Invalidate();

	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
