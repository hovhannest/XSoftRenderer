/*
 * CTriangle.h
 *
 *  Created on: Feb 23, 2017
 *      Author: coder
 */

#ifndef SRC_CTRIANGLE_H_
#define SRC_CTRIANGLE_H_

#include "CPolygon.h"

class CTriangle2D: public CPolygon {
public:
	CTriangle2D();
	CTriangle2D(float x0, float y0,
			float x1, float y1,
			float x2, float y2);
	virtual ~CTriangle2D();

	virtual void Render();

	void IsBilinear(bool bl = true) {m_Bilinear = bl;}
protected:
	bool m_Bilinear;
};

#endif /* SRC_CTRIANGLE_H_ */
