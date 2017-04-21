/*
 * XSoftwareRenderer.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef XSOFTWARERENDERER_H_
#define XSOFTWARERENDERER_H_

#include "XRenderer.h"
#include "Utils.h"
#include <X11/Xutil.h>
#include <X11/Xlib.h>

class Edge
{
public:
	int yUpper;

	float xIntersect;
	float dxPerScan;

	Edge *next;
};

class XSoftwareRenderer : public XRenderer {
public:
	XSoftwareRenderer();
	virtual ~XSoftwareRenderer();

public:
	virtual void Init();
	virtual void Release();

	virtual void DrowPoint(PointF &poin, RGBA &color);
	virtual void DrowLine(PointF &p1, PointF &end, RGBA &color);
	virtual void FillPolygon(const std::vector<PointF*> &pts, RGBA color);
	virtual void FillTriangleBi(const std::vector<PointF*> &pts,
			RGBA color0, RGBA color1, RGBA color2);
protected:
	void ConnectX();
	Window OpenWindow(int x, int y, unsigned int width, unsigned int height,
			unsigned int border_width);

	void fillScanBi(const int scan,const Edge *active,
			RGBA color0, RGBA color1);
	GC GetGC();
	void DisconnectX();

	// helpers for scanline
	void insertEdge(Edge *list,Edge *edge);
	void makeEdgeRec(const PointF lower,const PointF upper,
			const int yComp,Edge *edge,Edge *edges[]);
	int yNext(const int k,const int cnt,const std::vector<PointF*> &pts);
	void buildEdgeList(const int cnt,const std::vector<PointF*> &pts,Edge *edges[]);
	void buildActiveList(const int scan,Edge *active,Edge *edges[]);
	void fillScan(const int scan,const Edge *active, RGBA color);
	void deleteAfter(Edge * q);
	void updateActiveList(const int scan,Edge *active);
	void resortActiveList(Edge *active);
	void recalcLineColor(RGBA& color0, RGBA& color1);

protected:
	GC m_GC;
	Edge *edges[1024];
	RGBA dBuf[1024][1024];
};

#endif /* XSOFTWARERENDERER_H_ */
