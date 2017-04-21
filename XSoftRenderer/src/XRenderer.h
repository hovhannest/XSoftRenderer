/*
 * XRenderer.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef XRENDERER_H_
#define XRENDERER_H_

#include "Renderer.h"

#include <X11/Xutil.h>
#include <X11/Xlib.h>

class XRenderer : public Renderer {
public:
	XRenderer();
	virtual ~XRenderer();

	Display* GetDisplay() const { return m_Display; };

	virtual void DrowPoint(PointF &poin, RGBA &color) {};
	virtual void DrowLine(PointF &p1, PointF &p2, RGBA &color) {};
protected:
	Display *m_Display;
	Window m_MainWindow;
};

#endif /* XRENDERER_H_ */
