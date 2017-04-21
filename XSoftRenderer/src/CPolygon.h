/*
 * CPolygon.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef CPOLYGON_H_
#define CPOLYGON_H_

#include "CDummyObject.h"
#include "Utils.h"

#include <vector>

class CPolygon  : public CDummyObject{
public:
	CPolygon();
	virtual ~CPolygon();

	virtual void Release();

	virtual void Update(float dt);

	virtual void Render();

	void AddVertex(float x, float y, float z = 0.0)
	{
		PointF* p = new PointF(x, y, z);
		m_Vertexes.push_back(p);
	}

protected:
	std::vector<PointF*> m_Vertexes;
};

#endif /* CPOLYGON_H_ */
