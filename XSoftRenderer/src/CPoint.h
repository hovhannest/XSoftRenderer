/*
 * CPoint.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef CPOINT_H_
#define CPOINT_H_

#include "CDummyObject.h"

class CPoint : public CDummyObject{
public:
	CPoint();
	virtual ~CPoint();

public:
	virtual void Render();

};

#endif /* CPOINT_H_ */
