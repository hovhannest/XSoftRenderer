/*
22228888 * CApp.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: coder
 */

#include "CApp.h"

#include "XSoftwareRenderer.h"
#include "CScene.h"

#include <stdio.h>
#include <chrono>
#include <unistd.h>
#include <sys/time.h>

#include <iostream>

CApp::CApp():
		m_Renderer(NULL),
		m_CurrentScene(NULL)
{
	// TODO Auto-generated constructor stub
}

CApp::~CApp()
{
	// TODO Auto-generated destructor stub

	if(m_CurrentScene)
	{
		delete m_CurrentScene;
		m_CurrentScene = NULL;
	}

	if(m_Renderer)
	{
		delete m_Renderer;
		m_Renderer = NULL;
	}
}

void CApp::Init()
{
	Release();
	m_Renderer = new XSoftwareRenderer;
	m_Renderer->Init();
	m_LastTime = 0;
	m_FrameDuration = 1000/60; // 60 fps

	m_CurrentScene = new CScene();
	m_CurrentScene->Init();
}

void CApp::Run()
{
	float dt = 0.0f;
	XEvent event;

	int x11_fd;
	fd_set in_fds;

	struct timeval tv;

	x11_fd = ConnectionNumber(m_Renderer->GetDisplay());

	while(1)
	{
		int needToRecalculateState = NoChange;
	    do
	    {
		    struct timeval tp;
		    gettimeofday(&tp, NULL);
		    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

		    unsigned int dtms = ms - m_LastTime;

		    int dtframe = m_FrameDuration - dtms;

		    FD_ZERO(&in_fds);
		    FD_SET(x11_fd, &in_fds);

		    if(dtframe > 0)
		    {	// maping notify xevent
		    	//register event first
				///Xsetpointermapping

		    	usleep(dtframe*100);
		    	tv.tv_usec = 0; // dtframe;
		    	tv.tv_sec = 1;
		    }
		    else
		    {
		    	tv.tv_usec = 0;
		    	tv.tv_sec = 1;
		    }

		    int num_ready_fds = select(x11_fd + 1, &in_fds, NULL, NULL, &tv);
		    if (num_ready_fds > 0)
		    {
		    	std::cout << "Event Received! " << std::endl; //<< in_fds.fds_bits << std::endl;
		    	//event.type = in_fds
		    }
		    else if (num_ready_fds == 0)
		    {
		    	// Handle timer here
		    	//printf("Timer Fired!\n");
		    	needToRecalculateState = FrameTimeout;
		    	break;
		    }
		    else
		    	printf("An error occured!\n");

		    if(m_LastTime > 0)
		    	dt = float(dtms)/1000.0f;
		    m_LastTime = ms;

	    	XNextEvent(m_Renderer->GetDisplay(), &event);
	    	switch (event.type)
	    	{
	    	case ButtonPress:
	    		break;
	    	case KeyPress:
	    		//doKeyPressEvent(&event);
	    		break;
	    	case ConfigureNotify:
	    		/* fprintf(stderr, "In ConfigureNotify\n");*/
	    	case Expose:
	    		/*fprintf(stderr, "In Expose\n");*/
	    		//redraw();
	    		break;
	    	} /*switch*/
	    }
	    while (/*needToRecalculateState == NoChange ||*/ XPending(m_Renderer->GetDisplay()));

	    if(needToRecalculateState > FrameTimeout)
	    {
	    	// Handle events
	    }

	    //std::cout << dt << std::endl;

	    Update(dt);
	    Render();
	}

}

void CApp::Release()
{
	if(m_CurrentScene)
	{
		m_CurrentScene->Release();
	}

	if(m_Renderer)
	{
		m_Renderer->Release();
	}
}

void CApp::Update(float dt /*= 0.0*/)
{
	if(m_CurrentScene)
	{
		m_CurrentScene->Update(dt);
	}
}

void CApp::Render()
{
	if(m_CurrentScene)
	{
		m_CurrentScene->Render();
	}
}
