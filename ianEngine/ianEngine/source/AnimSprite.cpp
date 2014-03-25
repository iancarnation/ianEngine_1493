#include "AnimSprite.h"

AnimSprite::AnimSprite()
{}

AnimSprite::~AnimSprite()
{}

AnimSprite::AnimSprite(const char* a_cpTexture, GLFWwindow* window)
{
	GameWindow = window;
	m_dElapsedTime = 0;
	
	m_v3Position = Vector3(g_gl_width/2, g_gl_height/2, 0);

	LoadVertShader("./resources/VertexShader.glsl");
	LoadFragShader("./resources/FragmentShader.glsl");
	LinkShaders();
	GLint uvAttrib = glGetAttribLocation(m_ShaderProgram, "texcoord");
	glEnableVertexAttribArray(uvAttrib);
	matrix_location = glGetUniformLocation(m_ShaderProgram, "matrix");

	LoadSlices(a_cpTexture);
	LoadAnimations(m_atlas.sAnimations.c_str());
	LoadTexture(m_atlas.sSheet.c_str());

	m_dFrameDuration = (1.0/5.0);
	m_sCurrentAnimation = "move N";
	m_sCurrentSlice = "move N 0";
	iCurrentFrame = 0;
	iLoopMarker = 0;
	currentCycle = LOOP;
	m_texSize = m_atlas.v2Size;

	SetSlice();
	UVSetup();

}

void AnimSprite::Draw()
{
	Sprite::Draw();
}

void AnimSprite::Update()
{
	Input();
	Draw();
	PlayAnimation();
}

void AnimSprite::SetSlice()
{
	m_minUVCoords = m_mSprites[m_sCurrentSlice].v2minUV;
	m_maxUVCoords = m_mSprites[m_sCurrentSlice].v2maxUV;
	m_v3Scale = Vector3(m_mSprites[m_sCurrentSlice].fWidth, 
						m_mSprites[m_sCurrentSlice].fHeight, 1);
}

void AnimSprite::LoadSlices(const char* a_cpTextureAtlas)
{
	/*
	XML Layout
	- Element "TextureAtlas"		the root element
	- - Attribute "imagePath"		attribute of TextureAtlas Element
	- - Attribute "width"			attribute of TextureAtlas Element
	- - Attribute "height"			attribute of TextureAtlas Element
	- - Attrubute "animationData"	attribute of TextureAtlas Element

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
	m_atlas.sAnimations = childElement->Attribute("animationData");

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
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

void AnimSprite::LoadAnimations(const char* a_cpAnimationData)
{
	/*
	XML Layout
	- Element "animation"		the root Element
	- - Attribute "name"		Attribute of "animation" Element
	- - Attribute "fps"			Attribute of "animation" Element

	- - Element "frame"			Child Element of "animation" Element
	- - - Attribute "name"		Attribute of "frame" Element
	*/

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str, aniName;
	doc.LoadFile(a_cpAnimationData);
	rootNode = doc.FirstChildElement("animation");
	currentNode = rootNode;

	// iterate through each animation
	for (childElement = currentNode->ToElement(); childElement != NULL;	
		childElement = childElement->NextSiblingElement())
	{
		// animation attributes
		aniName = childElement->Attribute("name");

		// iterate through frames of animation
		for (child = childElement->FirstChildElement(); child != NULL;
			child = child->NextSiblingElement())
		{
			// get frame name attribute
			str = child->Attribute("name");
			// add name to "sequence" vector
			m_mAnimations[aniName].push_back(str);
		}
	}
}

void AnimSprite::SetAnimation(std::string a_sAnimation, AnimCycle cycle, int frame = 0)
{
	m_sCurrentAnimation = a_sAnimation;
	iCurrentFrame = 0;
	iLoopMarker = frame;
	iPlayDirection = 1;
	currentCycle = cycle;

	switch (cycle)
	{
	case ONCE:
		break;
	case LOOP:
		iLoopMarker = 0;
		break;
	case PINGPONG:
		break;
	case REVERSE:
		iCurrentFrame = m_mAnimations[m_sCurrentAnimation].size();
		iLoopMarker = iCurrentFrame;
		break;
	case RANDOM:
		break;
	case SINGLE:
		break;
	default:
		SetAnimation(a_sAnimation, cycle);
		break;
	}

	m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
	SetSlice();
	UVSetup();
}

void AnimSprite::PlayAnimation()
{
	m_dElapsedTime += getDeltaTime();

	// if the elapsed time is greater than desired frame duration:
	if (m_dElapsedTime > m_dFrameDuration)
	{
		m_dElapsedTime = 0;

		switch(currentCycle)
		{
			//case ONCE, if not at the end of the animation, advance one frame
		case ONCE:
			if (m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame] != m_mAnimations.at(m_sCurrentAnimation).back())
			{	
				iCurrentFrame++;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			break;
			//case LOOP, if the animation is at last frame, change frame to "loop marker" frame
		case LOOP:
			if (m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame] == m_mAnimations.at(m_sCurrentAnimation).back())
			{
				iCurrentFrame = iLoopMarker;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			else
			{
				iCurrentFrame++;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			break;
		case PINGPONG:
			// if at the end of animation, change direction
			if (m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame] == m_mAnimations.at(m_sCurrentAnimation).back())
			{
				iPlayDirection = -1;
				iCurrentFrame += iPlayDirection;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			// if at the beginning, change direction
			else if (m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame] == m_mAnimations.at(m_sCurrentAnimation).front())
			{
				iPlayDirection = 1;
				iCurrentFrame += iPlayDirection;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			else 
			{
				iCurrentFrame += iPlayDirection;
				m_sCurrentSlice = m_mAnimations.at(m_sCurrentAnimation)[iCurrentFrame];
			}
			break;
		}
		SetSlice();
		UVSetup();
	}
}

void AnimSprite::Input()
{
	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W))
	{
		m_v3Position += Vector3(0.0f, 1.0f, 0.0f);
		if (m_sCurrentAnimation != "move N")
			SetAnimation("move N", PINGPONG);
	}	

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		m_v3Position += Vector3(-1.0f, 0.0f, 0.0f);
		flipped = true;
		if (m_sCurrentAnimation != "move E")
			SetAnimation("move E", PINGPONG);
	}	

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S))
	{
		m_v3Position += Vector3(0.0f, -1.0f, 0.0f);
		if (m_sCurrentAnimation != "move S")
			SetAnimation("move S", PINGPONG);
	}	

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		m_v3Position += Vector3(1.0f, 0.0f, 0.0f);
		flipped = false;
		if (m_sCurrentAnimation != "move E")
			SetAnimation("move E", PINGPONG);
	}	

	// diagonals
	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W) && GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		flipped = false;
		if (m_sCurrentAnimation != "move NE")
			SetAnimation("move NE", PINGPONG);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S) && GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_D))
	{
		flipped = false;
		if (m_sCurrentAnimation != "move SE")
			SetAnimation("move SE", PINGPONG);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_W) && GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		flipped = true;
		if (m_sCurrentAnimation != "move NE")
			SetAnimation("move NE", PINGPONG);
	}

	if (GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_S) && GLFW_PRESS == glfwGetKey(GameWindow, GLFW_KEY_A))
	{
		flipped = true;
		if (m_sCurrentAnimation != "move SE")
			SetAnimation("move SE", PINGPONG);
	}
}