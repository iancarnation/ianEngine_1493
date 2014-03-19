#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <Utilities.h>
#include <tinyxml2.h>
#include <Sprite.h>

struct Char
{
	std::string sName;
	float fWidth, fHeight;
	Vec2 v2minUV, v2maxUV;
	float fOffset;
};

struct Font
{
	Vec2 v2Size;
	std::string sSheet;
	float fKerning;
};

class FontManager
{
public:
	FontManager();
	~FontManager();
	void LoadFont(const char* a_cpFontSheet);
	void LoadString(std::string string);
	void DrawString(std::string a_string, Vec2 a_v2Position, float fScale);

	Sprite m_iSprite;				// instanced Sprite
	Font m_FontAtlas;					// font texture atlas
	std::map<char,Char> m_mChars;	// map of characters
	std::vector<Char> m_vDrawList;	// draw list
};


#endif