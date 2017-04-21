/*
 * CApp.h
 *
 *  Created on: Feb 4, 2017
 *      Author: coder
 */

#ifndef CAPP_H_
#define CAPP_H_

#include "Singleton.h"

class XRenderer;
class CScene;

//#define USE_OPENGL

#define COORD_MIN_100
//#define COORD_MAX_100


class CApp : public Singleton<CApp> {
protected:
	enum EventStates
	{
		NoChange = 0,
		FrameTimeout
	};
public:
	CApp();
	virtual ~CApp();

public:
	void Init();

	void Run();

	void Release();

	CScene* GetScene() const { return m_CurrentScene; }
	XRenderer* GetRenderer() const { return m_Renderer; }

protected:
	virtual void Update(float dt = 0.0);
	virtual void Render();

protected:
	XRenderer* m_Renderer;

	long int m_LastTime;

	unsigned int m_FrameDuration;

	CScene* m_CurrentScene;
};

#endif /* CAPP_H_ */
