#include "main.h"
#include "SDL.h"
#include "GL\glew.h"
#include "frame.h"
#include "api.h"

SDL_Window *mainWindow;
SDL_GLContext mainContext;
GLsizei G_width;
GLsizei G_height;

void reshape(GLsizei width, GLsizei height);

void createWindow(const char *name, int w, int h, bool fullscreen)
{
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
	G_width = w;
	G_height = h;
										   // Create an application window with the following settings:
	mainWindow = SDL_CreateWindow(
		name,                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		w,                               // width, in pixels
		h,                               // height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)           // flags - see below
	);
	api->console.dev("Created window " + string(name) + " " + to_string(w) + "x" + to_string(h) + "\n");
	// Check that the window was successfully created
	if (mainWindow == NULL) {
		api->host.criticalError("Could not create window: " + string(SDL_GetError()) + "\n");
	}


	// Create our opengl context and attach it to our window
	api->console.dev("Create opengl context");
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	api->console.dev("...\nSetting");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glEnable(GL_TEXTURE_2D); //Enable texture mapping.
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	reshape(w, h);

	int x, y;
	SDL_GetWindowPosition(mainWindow, &x, &y);
	//api.Render_SetRect(x, y, height, width);

	api->console.dev("...\n");
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
											   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
								  // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(90, aspect, 0.1f, 512.0f);
}

void preFrame()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(1);
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				G_width = event.window.data1;
				G_height = event.window.data2;
				reshape(G_width, G_height);
			}
		}
		break;
	}

	frames::prepare();
}

void postFrame()
{
	SDL_GL_SwapWindow(mainWindow);
}