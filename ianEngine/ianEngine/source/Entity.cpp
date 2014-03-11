#include "Entity.h"

Entity::Entity()
{
	srand(time(NULL)); //?
	LoadVertShader("../resources/exampleVert.glsl");
	LoadFragShader("../resources/exampleFrag.glsl");
	LinkShaders();

	m_v4SpriteColor = Vector4(1,1,1,1);


	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;

	m_aoVerts[0].UV = Vector3(1.0f, 0.0f, 1.0f);
	m_aoVerts[1].UV = Vector3(0.0f, 1.0f, 1.0f);
	m_aoVerts[2].UV = Vector3(1.0f, 0.0f, 1.0f);
	m_aoVerts[3].UV = Vector3(1.0f, 1.0f, 1.0f);

	m_v3Scale = Vector3(1,1,1);
	m_v3Position = Vector3(g_gl_width/2, g_gl_height/2, 0);
}

Entity::~Entity()
{}

Entity::Entity(/*const char* a_cpType,*/ const char* a_cpTexture, /*float a_fSheetSlices(won't need with XML sheet info?),*/ int a_iWidth, int a_iHeight, Vector4 a_v4Color, 
			   /*Vector3 a_v3Velocity,*/ /*Vector3 a_v3Force(gone with new physics?),*/ /*float a_fMass,*/ /*float a_fMovementPower(move to Entity child),*/ /*bool a_bAlive,*/ GLFWwindow* window)
{
	GameWindow = window;

	LoadVertShader("./resources/VertexShader.glsl");
	LoadFragShader("./resources/FragmentShader.glsl");
	LinkShaders();
	
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram, "texcoord");
	glEnableVertexAttribArray(uvAttrib);
	matrix_location = glGetUniformLocation(m_ShaderProgram, "matrix");
	LoadTexture(a_cpTexture);

	m_v4SpriteColor = a_v4Color;

	m_aoVerts[0].Color = m_v4SpriteColor;
	m_aoVerts[1].Color = m_v4SpriteColor;
	m_aoVerts[2].Color = m_v4SpriteColor;
	m_aoVerts[3].Color = m_v4SpriteColor;

	m_v3Scale = Vector3(a_iWidth, a_iHeight, 1);
	m_v3Position = Vector3(g_gl_width/2, g_gl_height/2, 0);		
}



void Entity::Draw()
{
	modelMatrix->m11 = m_v3Scale.m_fX * m_fZoom;
	modelMatrix->m22 = m_v3Scale.m_fY * m_fZoom;
	modelMatrix->m14 = m_v3Position.m_fX;
	modelMatrix->m24 = m_v3Position.m_fY;
	modelMatrix->m34 = m_v3Position.m_fZ;

	*MVP = (*Ortho * *modelMatrix);

	Quad::Draw();
}

void Entity::Input()
{
	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
		m_v3Position += Vector3(0.0f, 1.0f, 0.0f);

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
		m_v3Position += Vector3(-1.0f, 0.0f, 0.0f);

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
		m_v3Position += Vector3(0.0f, -1.0f, 0.0f);

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
		m_v3Position += Vector3(1.0f, 0.0f, 0.0f);

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_O))
		m_v3Scale *= 1.01f;

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_K))
		m_v3Scale *= 0.99f;
}

void Entity::SetPosition(Vector3 a_v3Pos)
{
	Vector3 m_v3Position = a_v3Pos;
}