#include "FontManager.h"

FontManager::FontManager()
{

}

FontManager::~FontManager()
{}

void FontManager::LoadFont(const char* a_cpFontSheet)
{
	// load from XML
	// atlas information
	// character information
	//// watch for special characters

		/*
	XML Layout
	- Element "TextureAtlas"		the root element
	- - Attribute "imagePath"		attribute of TextureAtlas Element
	- - Attribute "width"			attribute of TextureAtlas Element
	- - Attribute "height"			attribute of TextureAtlas Element
	- - Attrubute "kerning"			attribute of TextureAtlas Element

	- - Element "char"				child of TextureAtlas Element
	- - - Attribute "name"			attribute of char Element
	- - - Attribute "x"				attribute of char Element
	- - - Attribute "y"				attribute of char Element
	- - - Attribute "width"			attribute of char Element
	- - - Attribute "height"		attribute of char Element
	- - - Attribute "offset"		attribute of char Element
	*/

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	char chr;
	doc.LoadFile(a_cpFontSheet);
	rootNode = doc.FirstChildElement("TextureAtlas");
	currentNode = rootNode;

	childElement = currentNode->ToElement();
	m_FontAtlas.sSheet = childElement->Attribute("imagePath");
	m_FontAtlas.v2Size.fX = (float)childElement->IntAttribute("width");
	m_FontAtlas.v2Size.fY = (float)childElement->IntAttribute("height");
	m_FontAtlas.fKerning = (float)childElement->IntAttribute("kerning");

	m_iSprite.LoadTexture(m_FontAtlas.sSheet.c_str());
	m_iSprite.m_texSize = m_FontAtlas.v2Size;
	GLint uvAttrib = glGetAttribLocation(m_iSprite.m_ShaderProgram,"texcoord");
	glEnableVertexAttribArray(uvAttrib);
	m_iSprite.matrix_location = glGetUniformLocation (m_iSprite.m_ShaderProgram, "matrix");

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		if (str.length() > 1)
		{
			if(str == "&apos")
			chr = '\'';

			else if(str =="&aster")
				chr = '*';

			else if(str =="&backSlash")
				chr = '\\';

			else if(str =="&fwdSlash")
				chr = '/';

			else if(str =="&bar2")
				chr = '|';

			else if(str =="&doubQuot")
				chr = '\"';

			else if(str =="&less")
				chr = '<';

			else if(str =="&great")
				chr = '>';

			else if(str =="&quest")
				chr = '?';

		}
		else
		{
			chr = str.at(0);
		}
		m_mChars[chr].sName = str;
		m_mChars[chr].v2minUV.fX = (float)childElement->IntAttribute("x");
		m_mChars[chr].v2minUV.fY = (float)childElement->IntAttribute("y");
		m_mChars[chr].fWidth = (float)childElement->IntAttribute("width");
		m_mChars[chr].fHeight = (float)childElement->IntAttribute("height");
		m_mChars[chr].v2maxUV.fX = m_mChars[chr].v2minUV.fX + m_mChars[chr].fWidth;
		m_mChars[chr].v2maxUV.fY = m_mChars[chr].v2minUV.fY + m_mChars[chr].fHeight;
		m_mChars[chr].fOffset = (float)childElement->IntAttribute("offset");
		
	}
	std::printf("done");

}

void FontManager::LoadString(std::string a_string)
{
	//clear then fill draw list
	m_vDrawList.clear();
	char c;
	for (int count = 0; count < a_string.length(); count ++)
	{
		c = a_string.at(count);
		m_vDrawList.push_back(m_mChars[c]);
	}
}

void FontManager::DrawString(std::string a_string, Vec2 a_v2Pos, float a_fScale)
{
	LoadString(a_string);
	glBlendFunc (m_iSprite.m_uSourceBlendMode, m_iSprite.m_uDestinationBlendMode);
	glUseProgram(m_iSprite.m_ShaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i (m_iSprite.tex_loc, 0); 

	m_iSprite.SetScale(a_fScale, a_fScale);

	// new position var
	float newPos;
	Char c;
	// for each char in draw list
	for (int i=0; i < m_vDrawList.size(); i++)
	{
		c = m_vDrawList[i];
	//// if it is not the first character: set new position based off previous char's
		if (i != 0)
		{
			// check for 'return'
			// new position = iSprite's pos + half this char's width + half previous char's width + kerning
			newPos = m_iSprite.GetPosition().m_fX + c.fWidth/2.0 + m_vDrawList[i-1].fWidth/2.0 + m_FontAtlas.fKerning;
			// move iSprite position to new char's position
			m_iSprite.SetPosition(newPos, a_v2Pos.fY);
		}
	//// if it is the first character: set position, minmax UV, scale, UVsetup, modelMatrix

			// set initial position
		else
			m_iSprite.SetPosition(Vector3(a_v2Pos.fX + c.fWidth/2.0, a_v2Pos.fY, 0));

		// UVs and scale
		m_iSprite.m_minUVCoords = c.v2minUV;
		m_iSprite.m_maxUVCoords = c.v2maxUV;
		m_iSprite.SetScale(c.fWidth*a_fScale, c.fHeight*a_fScale);

		// set vertex UV data
		m_iSprite.UVSetup();

		// set model matrix data
		m_iSprite.modelMatrix->m11 = m_iSprite.GetScale().m_fX;
		m_iSprite.modelMatrix->m22 = m_iSprite.GetScale().m_fY;
		m_iSprite.modelMatrix->m14 = m_iSprite.GetPosition().m_fX;
		m_iSprite.modelMatrix->m24 = m_iSprite.GetPosition().m_fY - c.fOffset;
		m_iSprite.modelMatrix->m34 = m_iSprite.GetPosition().m_fZ;

	////   set MVP
		m_iSprite.MVP = &(*Ortho * *m_iSprite.modelMatrix);
	////   Draw
		glUniformMatrix4fv(m_iSprite.matrix_location, 1, GL_TRUE, &m_iSprite.MVP->m11);
		m_iSprite.Draw();
	}
}