#ifndef _QUAD_
#define _QUAD_

#include "Utilities.h"

class Quad
{
public:
	Quad(void);
	~Quad(void);

	GLuint m_VBO; // vertex buffer
	GLuint m_EBO; // element buffer
	GLuint m_VAO; // vertex attributes

	GLuint m_FragmentShader;
	GLuint m_VertexShader;
	GLuint m_ShaderProgram;

	Vertex m_aoVerts[4];

	Vector3 m_minUVCoords;
	Vector3 m_maxUVCoords;
	Vector3 m_UVScale;
	float m_fZoom;

	Matrix4* modelMatrix;
	Matrix4* viewMatrix;
	Matrix4* MVP;

	unsigned int m_uiTexture;
	GLFWwindow* GameWindow;
	// used later
	unsigned int m_uSourceBlendMode;
	unsigned int m_uDestinationBlendMode;
	int tex_location;
	int matrix_location;
	int proj_location;
	int view_location;


	void Draw();
	void LoadVertShader(const char* filePath);	// change to bool for error check?
	void LoadFragShader(const char* filePath);	// **
	void LinkShaders();							// **
	void LoadTexture(const char* a_cpTexture);
	void SetUVData();
	void SetColor();
	void SetColor(Vector4 a_v4Color);
	void SetColor(Vector4 a_v4Color0, Vector4 a_v4Color1, Vector4 a_v4Color2, Vector4 a_v4Color3);
};


#endif