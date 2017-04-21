/*
 * Renderer.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "Utils.h"
#include <vector>

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

public:

	virtual void Init() {};
	virtual void Release() {};

	virtual void DrowPoint(PointF &poin, RGBA &color) {};
	virtual void DrowLine(PointF &p1, PointF &p2, RGBA &color) {};
	virtual void FillPolygon(const std::vector<PointF*> &pts, RGBA color) {};

protected:
	RGBA m_BackgroundColor;
	RGBA m_ForegroundColor;
};

#endif /* RENDERER_H_ */
