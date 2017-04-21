/*
 * XSoftwareRenderer.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#include "XSoftwareRenderer.h"

#include <cstdlib>
#include <iostream>
#include <X11/Xutil.h>
#include <X11/Xlib.h>

XSoftwareRenderer::XSoftwareRenderer()
{
	// TODO Auto-generated constructor stub

}

XSoftwareRenderer::~XSoftwareRenderer() {
	// TODO Auto-generated destructor stub
}

void XSoftwareRenderer::Init()
{
	ConnectX();
	m_MainWindow = OpenWindow(10,20,500,400,5);
	m_GC = GetGC();
	XMapWindow(m_Display, m_MainWindow);
}

void XSoftwareRenderer::Release()
{
	DisconnectX();
}

void XSoftwareRenderer::ConnectX()
{
	m_Display = XOpenDisplay(NULL);
   if (m_Display == NULL)
   {
	   std::cerr << "Cannot connect to X" << std::endl;
	   std::exit(1);
   }
   int screen = DefaultScreen(m_Display);
   m_ForegroundColor.dword = BlackPixel(m_Display, screen);
   m_BackgroundColor.dword = WhitePixel(m_Display, screen);
   //screen_colormap = DefaultColormap(m_Display, screen);
}

Window XSoftwareRenderer::OpenWindow(int x, int y, unsigned int width, unsigned int height,
		unsigned int border_width)
{
    Window new_window;
    XSizeHints size_hints;
    new_window = XCreateSimpleWindow(m_Display, DefaultRootWindow(m_Display),
                 x, y, width, height, border_width, m_ForegroundColor.dword,
				 m_BackgroundColor.dword);
   size_hints.x = x;
   size_hints.y = y;
   size_hints.width = width;
   size_hints.height = height;
   size_hints.flags = PPosition | PSize;
   char WINDOW_NAME[] = "Graphics Window";
   char ICON_NAME[] = "Icon";
   XSetStandardProperties(m_Display, new_window, WINDOW_NAME, ICON_NAME,
                          None, NULL, NULL, &size_hints);
   XSelectInput(m_Display, new_window, (ButtonPressMask | KeyPressMask |
                                      ExposureMask | PointerMotionMask));
   return (new_window);
}

GC XSoftwareRenderer::GetGC()
{
    GC gc;
    XGCValues gcValues;
    gc = XCreateGC(m_Display, m_MainWindow, (unsigned long)0, &gcValues);
    XSetBackground(m_Display, gc, m_BackgroundColor.dword);
    XSetForeground(m_Display, gc, m_ForegroundColor.dword);
    return (gc);
}

void XSoftwareRenderer::DisconnectX()
{
	if(m_Display)
	{
		XCloseDisplay(m_Display);
	}
	//exit(0);
}

void XSoftwareRenderer::DrowPoint(PointF &poin, RGBA &color)
{
	XSetForeground(m_Display, m_GC, color.dword);
	XDrawPoint(m_Display, m_MainWindow, m_GC, int(poin.x), int(poin.y));
}

void XSoftwareRenderer::DrowLine(PointF &p1, PointF &p2, RGBA &color)
{
	int x1 = p1.x,  y1 = p1.y,  x2 = p2.x,  y2 = p2.y;

		int	id, dx, dy, adx, ady, dxsign, dysign, lowx, lowy;

		// compute relative displacements
		dx = x2 - x1;
		if (dx >= 0)
		{
			dxsign =  1;
			adx =  dx;
			lowx = x1;
		}
		else
		{
			dxsign = -1;
			adx = -dx;
			lowx = x2;
		}
		dy = y2 - y1;
		if (dy >= 0)
		{
			dysign =  1;
			ady =  dy;
			lowy = y1;
		}
		else
		{
			dysign = -1;
			ady = -dy;
			lowy = y2;
		}

		XSetForeground(m_Display, m_GC, color.dword);
		//Optimization: check for horizontal or vertical lines
		if (ady == 0)		/* horizontal */
		{
			for (int x = 0; x <= adx; x++)
			{
				XDrawPoint(m_Display, m_MainWindow, m_GC, int(lowx + x), int(y1));
			}
		}
		else if (adx == 0)	/* vertical */
		{
			for(int y = 0; y <= ady; y++)
			{
				XDrawPoint(m_Display, m_MainWindow, m_GC, int(x1), int(lowy + y));
			}
		}
		else if (adx >= ady)		/* always increment horizontal */
		{
			int es = 2*ady - adx;
			for(int x = 0, y = 0; x < adx; x++)
			{
				XDrawPoint(m_Display, m_MainWindow, m_GC, int(x1 + dxsign*x), int(y1 + dysign*y));
				if (es >= 0)
				{
					y++;
					es = es - 2*adx;
				}
				es = es + 2*ady;
			}
		}
		else if (ady > adx)		/* interchange x and y */
		{
			int es = es = 2*adx - ady;
			for(int x = 0, y = 0; y < ady; y++)
			{
				XDrawPoint(m_Display, m_MainWindow, m_GC, int(x1 + dxsign*x), int(y1 + dysign*y));
				if (es >= 0)
				{
					x++;
					es = es - 2*ady;
				}
				es = es + 2*adx;
			}
		}
}


void XSoftwareRenderer::insertEdge(Edge *list,Edge *edge)
{
	Edge *p;
	Edge *q=list;

	p=q->next;

	while(p!=NULL)
	{
		if(edge->xIntersect<p->xIntersect)
			p=NULL;
		else
		{
			q=p;
			p=p->next;
		}
	}

	edge->next=q->next;
	q->next=edge;
}

void XSoftwareRenderer::makeEdgeRec(const PointF lower,const PointF upper,
		const int yComp,Edge *edge,Edge *edges[])
{
	edge->dxPerScan=((upper.x-lower.x)/(upper.y-lower.y));
	edge->xIntersect=lower.x;

	if(upper.y<yComp)
		edge->yUpper=(upper.y-1);
	else
		edge->yUpper=upper.y;

	insertEdge(edges[int(lower.y)],edge);
}

int XSoftwareRenderer::yNext(const int k,const int cnt,const std::vector<PointF*> &pts)
{
	int j;

	if((k+1)>(cnt-1))
		j=0;
	else
		j=(k+1);

	while(pts[k]->y==pts[j]->y)
	{
		if((j+1)>(cnt-1))
			j=0;
		else
			j++;
	}

	return (pts[j]->y);
}

void XSoftwareRenderer::buildEdgeList(const int cnt,const std::vector<PointF*> &pts,Edge *edges[])
{
	Edge *edge;
	PointF v1;
	PointF v2;

	int yPrev=(pts[cnt-2]->y);

	v1.x=pts[cnt-1]->x;
	v1.y=pts[cnt-1]->y;

	for(int count=0;count<cnt;count++)
	{
		v2=(*pts[count]);

		if(v1.y!=v2.y)
		{
			edge=new Edge;

			if(v1.y<v2.y)
				makeEdgeRec(v1,v2,yNext(count,cnt,pts),edge,edges);

			else
				makeEdgeRec(v2,v1,yPrev,edge,edges);
		}

	yPrev=v1.y;
	v1=v2;
	}
}

void XSoftwareRenderer::buildActiveList(const int scan,Edge *active,Edge *edges[])
{
	Edge *p;
	Edge *q;

	p=edges[scan]->next;

	while(p)
	{
		q=p->next;

		insertEdge(active,p);

		p=q;
	}
}

void XSoftwareRenderer::fillScan(const int scan,const Edge *active, RGBA color)
{
	Edge *p1;
	Edge *p2;

	p1=active->next;

	while(p1)
	{
		p2=p1->next;

		for(int count=p1->xIntersect;count<=p2->xIntersect;count++)
		{
			XSetForeground(m_Display, m_GC, color.dword);

			XDrawPoint(m_Display, m_MainWindow, m_GC, int(count), int(scan));
		}

		p1=p2->next;
	}
}

void XSoftwareRenderer::deleteAfter(Edge * q)
{
    Edge *p=q->next;

    q->next=p->next;

    delete p;
}

void XSoftwareRenderer::updateActiveList(const int scan,Edge *active)
{
	Edge *q=active;
	Edge *p=active->next;

	while(p)
	{
		if(scan>=p->yUpper)
		{
			p=p->next;

			deleteAfter(q);
		}
		else
		{
			p->xIntersect=(p->xIntersect+p->dxPerScan);
			q=p;
			p=p->next;
		}
	}
}

void XSoftwareRenderer::resortActiveList(Edge *active)
{
	Edge *q;
	Edge *p=active->next;

	active->next=NULL;

	while(p)
	{
		q=p->next;

		insertEdge(active,p);

		p=q;
	}
}

void XSoftwareRenderer::FillPolygon(const std::vector<PointF*> &pts, RGBA color)
{
	const int n = pts.size();
	Edge *active;

	for(int count_2=0;count_2<1024;count_2++)
	{
		edges[count_2]=new Edge;
		edges[count_2]->next=NULL;
	}

	buildEdgeList(n,pts,edges);

	active=new Edge;
	active->next=NULL;

	for(int count_3=0;count_3<480;count_3++)
	{
		buildActiveList(count_3,active,edges);

		if(active->next)
		{
			fillScan(count_3,active,color);
			updateActiveList(count_3,active);
			resortActiveList(active);
		}
	}
}


void XSoftwareRenderer::FillTriangleBi(const std::vector<PointF*> &pts, RGBA color0, RGBA color1, RGBA color2)
{
	const int n = pts.size();
	Edge *active;

	for(int count_2=0;count_2<1024;count_2++)
	{
		edges[count_2]=new Edge;
		edges[count_2]->next=NULL;
	}

	buildEdgeList(n,pts,edges);

	active=new Edge;
	active->next=NULL;

	for(int count_3=0;count_3<1024;count_3++)
	{
		buildActiveList(count_3,active,edges);

		if(active->next)
		{
			recalcLineColor(color0, color1 );
			fillScanBi(count_3,active,color0, color1);
			updateActiveList(count_3,active);
			resortActiveList(active);
		}
	}
}



void XSoftwareRenderer::fillScanBi(const int scan,const Edge *active, RGBA color0, RGBA color1)
{
	Edge *p1;
	Edge *p2;

	p1=active->next;

	while(p1)
	{
		p2=p1->next;

		float dx = p2->xIntersect - p1->xIntersect;
		float dr = color0.RGBAstruct.r - color1.RGBAstruct.r;
		float dg = color0.RGBAstruct.g - color1.RGBAstruct.g;
		float db = color0.RGBAstruct.b - color1.RGBAstruct.b;
		RGBA tColor;
		tColor.RGBAstruct.r = color0.RGBAstruct.r;
		tColor.RGBAstruct.g = color0.RGBAstruct.g;
		tColor.RGBAstruct.b = color0.RGBAstruct.b;
		float tr = dr, tg = dg, tb = db;
		for(int count=p1->xIntersect;count<=p2->xIntersect;count++)
		{
			XSetForeground(m_Display, m_GC, tColor.dword);

			XDrawPoint(m_Display, m_MainWindow, m_GC, int(count), int(scan));

			tr += dr;
			tg += dg;
			tb += db;

			if(tr > 1)
			{
				int t = int(tr);
				tColor.RGBAstruct.r += t;
				tr -= t;
			}
			if(tg > 1)
						{
							int t = int(tg);
							tColor.RGBAstruct.g += t;
							tg -= t;
						}
			if(tb > 1)
						{
							int t = int(tb);
							tColor.RGBAstruct.b += t;
							tb -= t;
						}
		}

		p1=p2->next;
	}
}

void XSoftwareRenderer::recalcLineColor(RGBA& color0, RGBA &color1)
{

}

