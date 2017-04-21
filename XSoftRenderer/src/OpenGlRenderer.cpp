#include <stdio.h>
#include <stdlib.h>
#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <chrono>
#include <cmath>

#include "CApp.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "OpenGlRenderer.h"

char WINDOW_NAME[] = "Graphics Window";
char ICON_NAME[] = "Icon";
Display *display;
int screen;
Window main_window;
unsigned long foreground, background;
GLfloat Angle = 10.0;
static int snglBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, None};
#ifdef USE_OPENGL
static int dblBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12,GLX_DOUBLEBUFFER, None};
#else
static int dblBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12,/*GLX_DOUBLEBUFFER,*/ None};
#endif

Bool doubleBuffer = True;
XVisualInfo *vi;
GLXContext cx;
Colormap cmap;
XSetWindowAttributes swa;
Bool recalcModelView = True;
int dummy;
Bool needRedraw = True;

void connectX()
{
   display = XOpenDisplay(NULL);
   if (display == NULL) {fprintf(stderr, "Cannot connect to X\n");
                         exit(1);}
   screen = DefaultScreen(display);
   if (!glXQueryExtension(display, &dummy, &dummy)){
         fprintf(stderr, "X server has no OpenGL GLX Extension\n");
         exit(1);}
   vi = glXChooseVisual(display, screen, dblBuf);
   if (vi == NULL){
      fprintf(stderr, "Double Buffering not available\n");
      vi = glXChooseVisual(display, screen, snglBuf);
      if (vi == NULL) fprintf(stderr, "No RGB Visual with depth buffer\n");
      doubleBuffer = False;
   }
  if (doubleBuffer == True) fprintf(stderr, "We have double buffering\n");
  if (vi->c_class != TrueColor){
            fprintf(stderr, "Need a TrueColor visual\n");
            exit(1);
          }
  cx = glXCreateContext(display, vi , None, True);
  if (cx == NULL){
       fprintf(stderr, "No rendering context\n");
       exit(1);
      }
  cmap = XCreateColormap(display, RootWindow(display, vi->screen),
                         vi->visual, AllocNone);
  if (cmap == NULL){
      fprintf(stderr, "Color map is not available\n");
      exit(1);
     }
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.event_mask = ExposureMask | ButtonPressMask | StructureNotifyMask |
                   KeyPressMask;
}

Window openWindow(int x, int y, int width, int height,
                  int border_width, int argc, char** argv)
{
    XSizeHints size_hints;
    Window new_window;
    new_window = XCreateWindow(display, RootWindow(display, vi->screen),
                 x,y, width, height, border_width, vi->depth, InputOutput,
                 vi->visual, CWBorderPixel | CWColormap | CWEventMask,
                 &swa);
   size_hints.x = x;
   size_hints.y = y;
   size_hints.width = width;
   size_hints.height = height;
   size_hints.flags = PPosition | PSize;
   XSetStandardProperties(display, new_window, WINDOW_NAME, ICON_NAME,
                          None, argv, argc, &size_hints);
   XSelectInput(display, new_window, (ButtonPressMask | KeyPressMask |
                                       StructureNotifyMask | ExposureMask));
   return (new_window);
}


void disconnectX()
{
   XCloseDisplay(display);
   exit(0);
}

void doKeyPressEvent(XKeyEvent *pEvent)
{
 int key_buffer_size = 10;
 char key_buffer[9];
 XComposeStatus compose_status;
 KeySym key_sym;
 XLookupString(pEvent, key_buffer, key_buffer_size,
               &key_sym, &compose_status);
 if (key_buffer[0] == 'q') disconnectX();
 else fprintf(stderr, "You pressed %c\n", key_buffer[0]);
}

 void draw()
{
}
 GC gc;
 void redraw()
{
	 long            ms; // Milliseconds
	     time_t          s;  // Seconds
	     struct timespec spec;
	 clock_gettime(CLOCK_REALTIME, &spec);
	 s  = spec.tv_sec;
	    ms = round(spec.tv_nsec / 1.0e6);

     XWindowAttributes wndAttr;
     XGetWindowAttributes(display,main_window,&wndAttr);
     int dim = MIN(wndAttr.width, wndAttr.height);
     float dx = float(dim)/float(wndAttr.width);
     float dy = float(dim)/float(wndAttr.height);
     //int dim = MAX(wndAttr.width, wndAttr.height);
     //glViewport(0.5*(wndAttr.width-(4.0/3.0)*dim),0.5*(wndAttr.height - dim),(4.0/3.0)*dim,dim);
     glViewport(0.0, 0.0, wndAttr.width, wndAttr.height);
/* draw a Gouraud triangle
  fprintf(stderr, "Calling redraw()\n");*/
  glClear(GL_COLOR_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_POLYGON);
  sleep(100)
  {
	  /*
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-0.9/dx,-0.9/dy);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.9/dx,-0.9/dy);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.0/dx,0.9/dy);
    */

    glColor3f(1.0,0.0,0.0);
    glVertex2f(-cos(0.5*Angle/M_PI)*0.5*dx + sin(0.5*Angle/M_PI)*0.5*dx,
    		-cos(0.5*Angle/M_PI)*0.5*dy - sin(0.5*Angle/M_PI)*0.5*dy);
  /*  glColor3f(0.0,1.0,0.0);
    glVertex2f(cos(0.5*Angle/M_PI)*150.0/dim*dx + sin(0.5*Angle/M_PI)*150.0/dim*dy,
    		-cos(0.5*Angle/M_PI)*150.0/dim*dy + sin(0.5*Angle/M_PI)*150.0/dim*dx);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.0/dx - sin(0.5*Angle/M_PI)*150.0/dim*dy , cos(0.5*Angle/M_PI)*150.0/dim*dy);
*/
    glColor3f(0.0,1.0,0.0);
    glVertex2f(cos(0.5*Angle/M_PI)*0.5*dx  + sin(0.5*Angle/M_PI)*0.5*dx,
    		-cos(0.5*Angle/M_PI)*0.5*dy + sin(0.5*Angle/M_PI)*0.5*dy);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.0 - sin(0.5*Angle/M_PI)*0.5*dx,cos(0.5*Angle/M_PI)*0.5*dy);
  }
  glEnd();
#ifdef USE_OPENGL
  if (!USE_OPENGL && doubleBuffer) glXSwapBuffers(display,main_window); else glFlush();
#else
  if (doubleBuffer) glXSwapBuffers(display,main_window); else glFinish();
#endif
	 long            ms2; // Milliseconds
	     time_t          s2;  // Seconds
	     struct timespec spec2;
	 clock_gettime(CLOCK_REALTIME, &spec2);
	 s2  = spec2.tv_sec;
	    ms2 = round(spec2.tv_nsec / 1.0e6);
	printf("Timer %d\n", (s2-s)*1000+ ms2 - ms);
}

void doButtonPressEvent(XButtonEvent pEvent)
{
   disconnectX();
}

int main1 (int argc, char** argv){
  XEvent event;
  GLboolean needRedraw = GL_FALSE, recalcModelView = GL_TRUE;
  const unsigned char *version;
  GLint *params;
  connectX();
  main_window = openWindow(10,20,640,480,5, argc, argv);
  glXMakeCurrent(display, main_window, cx);
  XMapWindow(display, main_window);
  version = glGetString(GL_VERSION);
  if (version == NULL) {fprintf(stderr, "Version not supported\n");
                        exit(1);}
  fprintf(stderr, "The Version is: %s\n", version);
  /* Try it another way*/
 /* glGetIntegerv(GL_MAJOR_VERSION,params);
   Doesn't work need 3.0 or later */
 /*glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glFrustum(-1.0,1.0, -1.0, 1.0,1.0,10.0);*/
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
/*glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-1,-1,0,1,0,1);
glMatrixMode(GL_MODELVIEW);*/

	int x11_fd;
	fd_set in_fds;
	float m_LastTime = 0.0;
	float m_FrameDuration = 1.0/60.0;
	float dt = 0.0;
	float ang = 0.0f;

	struct timeval tv;
while(1){

    do {
	    {
	    	recalcModelView = GL_TRUE;
	    	dt = 0.01;
	    	break;
	    }
    XNextEvent(display, &event);
    switch (event.type){
      case ButtonPress:
        recalcModelView = GL_TRUE;
        Angle += 10; break;
      case KeyPress:
        //doKeyPressEvent(&event);
        break;
      case ConfigureNotify:
        /* fprintf(stderr, "In ConfigureNotify\n");*/
      case Expose:
        /*fprintf(stderr, "In Expose\n");*/
        redraw();
        break;
  } /*switch*/
 } while (XPending(display));
   if (recalcModelView){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Angle += dt*10.1;
    glRotatef(0.0, 0.0,0.0,1.0);
    recalcModelView =  GL_FALSE;
    needRedraw = GL_TRUE;
    } /*if*/
    if (needRedraw){
      redraw();
      needRedraw = GL_FALSE;
    }
}
}
