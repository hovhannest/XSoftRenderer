/*
 * CDummyObject.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef CDUMMYOBJECT_H_
#define CDUMMYOBJECT_H_

#include "IGameObject.h"
#include "Utils.h"
#include "CScene.h"

class CDummyObject : public IGameObject {
public:
	// Constructor could be protected, to force object creation only in CScene
	// by using CreateObject(...) function
	CDummyObject() {};
	virtual ~CDummyObject() {};

public:
	virtual void Init() {
		m_Position.x = 0.0f;
		m_Position.y = 0.0f;
		m_Position.z = 0.0f;
		m_Color.RGBAstruct.r = 0;
		m_Color.RGBAstruct.g = 0;
		m_Color.RGBAstruct.b = 0;
		m_Color.RGBAstruct.a = 255;
	};
	virtual void Update(float dt) {};
	virtual void Render() {};
	virtual void Release() { if(m_Scene) m_Scene->ReleaseObject(this); };

	virtual void SetPosition(float x, float y, float z = 0.0) {
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}

	virtual void SetColor(unsigned short r,unsigned short g, unsigned short b, unsigned short a = 255)
	{
		m_Color.RGBAstruct.r = r;
		m_Color.RGBAstruct.g = g;
		m_Color.RGBAstruct.b = b;
		m_Color.RGBAstruct.a = a;
	}

	float GetAngularVelocity() const { return m_AngularVelosity;}
	void SetAngularVelocity(const float vel) {m_AngularVelosity = vel;}

protected:
	PointF 	m_Position;
	RGBA 	m_Color;

	float m_AngularVelosity;
};

#endif /* CDUMMYOBJECT_H_ */
