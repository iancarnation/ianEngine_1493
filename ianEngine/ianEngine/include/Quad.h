#ifndef _QUAD_
#define _QUAD_

#include <Utilities.h>

class Quad
{
public:
	Quad(void);
	~Quad(void);

	void Draw();
	void LoadVertShader(const char* filePath);
	void LoadFragShader(const char* filePath);
	void LinkShaders();
	void LoadTexture(const char* a_cpTexture);
	void SetUVData();

	void SetColor();
	void SetColor(Vector4 a_v4Color);
	void SetColor(Vector4 a_v4Color0,Vector4 a_v4Color1,Vector4 a_v4Color2,Vector4 a_v4Color3);


	GLuint m_VBO; // vertex buffer
	GLuint m_EBO; // element buffer
	GLuint m_VAO; // vertex attributes

	GLuint m_FragmentShader;
	GLuint m_VertexShader;
	GLuint m_ShaderProgram;

	Vertex m_aoVerts[4];


	Vec2 m_minUV;
	Vec2 m_maxUV;

	Matrix4* modelMatrix;
	Matrix4* viewMatrix;
	Matrix4* MVP;
	
	GLFWwindow* GameWindow;

	unsigned int m_uiTexture;
	unsigned int m_uSourceBlendMode;
	unsigned int m_uDestinationBlendMode;
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;
};


#endif