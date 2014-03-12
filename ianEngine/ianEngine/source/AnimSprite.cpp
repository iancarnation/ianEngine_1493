#include "AnimSprite.h"

AnimSprite::AnimSprite()
{}

AnimSprite::~AnimSprite()
{}

AnimSprite::AnimSprite(const char* a_cpTexture, GLFWwindow* window)
{
	GameWindow = window;

	LoadVertShader("./resources/VertexShader.glsl");
	LoadFragShader("./resources/FragmentShader.glsl");
	LinkShaders();
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram, "texcoord");
	glEnableVertexAttribArray(uvAttrib);
	matrix_location = glGetUniformLocation(m_ShaderProgram, "matrix");

	LoadSlices(a_cpTexture);
	/*LoadAnimations();
	LoadTexture();

	currentAnimation = "";
	currentSlice = "";
	iCurrentFrame = 0;
	currentCycle = SINGLE;

	SetSprite();
	SetUVData();*/

}

void AnimSprite::LoadSlices(const char* a_cpTextureAtlas)
{
	/*
	XML Layout
	- Element "TextureAtlas"		the root element
	- - Attribute "imagePath"		attribute of TextureAtlas Element
	- - Attribute "width"			attribute of TextureAtlas Element
	- - Attribute "height"			attribute of TextureAtlas Element

	- - Element "slice"				child of TextureAtlas Element
	- - - Attribute "name"			attribute of slice Element
	- - - Attribute "x"				attribute of slice Element
	- - - Attribute "y"				attribute of slice Element
	- - - Attribute "width"			attribute of slice Element
	- - - Attribute "height"		attribute of slice Element
	*/

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_cpTextureAtlas);
	rootNode = doc.FirstChildElement("TextureAtlas");
	currentNode = rootNode;

	childElement = currentNode->ToElement();
	m_atlas.sSheet = childElement->Attribute("imagePath");
	m_atlas.v2Size.fX = (float)childElement->IntAttribute("width");
	m_atlas.v2Size.fY = (float)childElement->IntAttribute("height");

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		m_mSprites[str].sName = str;
		m_mSprites[str].v2minUV.fX = (float)childElement->IntAttribute("x");
		m_mSprites[str].v2minUV.fY = (float)childElement->IntAttribute("y");
		m_mSprites[str].fWidth = (float)childElement->IntAttribute("width");
		m_mSprites[str].fHeight = (float)childElement->IntAttribute("height");
		m_mSprites[str].v2maxUV.fX = m_mSprites[str].v2minUV.fX + m_mSprites[str].fWidth;
		m_mSprites[str].v2maxUV.fY = m_mSprites[str].v2minUV.fY + m_mSprites[str].fHeight;
	}
	std::printf("done");
}