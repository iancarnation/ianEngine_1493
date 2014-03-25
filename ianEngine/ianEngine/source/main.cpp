#include <gl\glew.h>

#define GLFW_DLL
#include <GLFW\glfw3.h>

#include <assert.h>
#include <stdio.h>
#include "Utilities.h"
#include "Quad.h"
#include "Sprite.h"
#include "AnimSprite.h"
#include "FontManager.h"

// a call-back function
void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
	g_gl_width = width;
	g_gl_height = height;

	/* update any perspective matrices used here */
}

//call back before initalization of GLFW
void glfw_error_callback (int error, const char* description) {
	fputs (description, stderr);
	gl_log (description, __FILE__, __LINE__);
}

int main()
{
	resetDeltaTime();
	//setup to log some GLFW stuff

	char message[256];
	sprintf (message, "starting GLFW %s", glfwGetVersionString ());
	assert (gl_log (message, __FILE__, __LINE__));
	glfwSetErrorCallback (glfw_error_callback);

	//open an OS window using GLFW
	if(!glfwInit())
	{
		fprintf (stderr,"ERROR: could not start GLFW3\n");
		return 1;
	}

	// uncomment these lines if on Apple OS X
	/*	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/	
	//Anti-Aliasing
	glfwWindowHint (GLFW_SAMPLES, 4);

	//get the primary monitor
	GLFWmonitor* mon = glfwGetPrimaryMonitor ();
	//this lets us the the video mode for the monitor we pass
	const GLFWvidmode* vmode = glfwGetVideoMode (mon);
	GLFWwindow* window = glfwCreateWindow (
		vmode->width, vmode->height, "Extended GL Init",NULL/* mon*/, NULL
		);
	glfwSetWindowSize(window, g_gl_width, g_gl_height);

	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	//not sure if this works
	//log_gl_params ();

	glfwMakeContextCurrent(window);

	//start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	float speed = 1.0f; // move at 1 unit per second
	float last_position = 0.0f;

	//Quad * tester = new Quad();
	
	//Sprite * richard = new Sprite("./resources/simmons.png", 384, 324, Vector4(1,1,1,1), window); 
	AnimSprite* tester = new AnimSprite("./resources/sheet.xml", window);

	FontManager Font;
	Font.LoadFont("./resources/FontSheet.xml");

	Ortho = new Matrix4();
	Orthographic(0, g_gl_width, g_gl_height, 0, 0, -1, Ortho);

	while (!glfwWindowShouldClose (window)) {

		glEnable (GL_CULL_FACE); // cull face
		glCullFace (GL_BACK); // cull back face
		glFrontFace (GL_CW); // GL_CCW for counter clock-wise

		glEnable (GL_ALPHA_TEST);
		glAlphaFunc (GL_GREATER, 0.5);
		glEnable (GL_ALPHA);

		glClearColor(0.4, 0.75, 0.9, 1.0);

		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//resize window3
		glViewport (0, 0, g_gl_width, g_gl_height);

		tester->Update();
		
		Font.DrawString("1493 - The Bay of Arrows", Vec2(20,40), 1);

		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (window);

		resetDeltaTime();

		//When do i exit?
		if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (window, 1);
		}
	}

	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;

}