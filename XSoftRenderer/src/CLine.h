/*
 * CLine.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef CLINE_H_
#define CLINE_H_

#include "CDummyObject.h"
#include "Utils.h"

class CLine : public CDummyObject{
public:
	CLine();
	virtual ~CLine();
public:
	virtual void Render();

	virtual void SetCoordinates(PointF start, PointF end)
	{
		m_Start = start, m_End = end;
	}

	virtual void SetStart(float x, float y, float z = 0.0f)
	{
		m_Start.x = x;
		m_Start.y = y;
		m_Start.z = z;
	}

	virtual void SetEnd(float x, float y, float z = 0.0f)
	{
		m_End.x = x;
		m_End.y = y;
		m_End.z = z;
	}

protected:
	PointF m_Start;
	PointF m_End;
};

#endif /* CLINE_H_ */
