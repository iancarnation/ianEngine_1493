#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Quad.h"
#include "MathLibrary.h"
#include "Utilities.h"
#include <SOIL.h>
#include <vector>

class Sprite: public Quad
{
public:
	Sprite(void);
	~Sprite(void);
	Sprite(const char* a_cpTexture, int a_iWidth, int a_iHeight, Vector4 color, GLFWwindow*
    /*optional params , Vector3 a_v3Velocity = Vector3(0,0,0), Vector3 a_v3Force = Vector3(0,0,0)*/); // temp starter..add variables below once needed, **move to AnimatedSprite later? **
	//Sprite(const char*, const char*, Vector3, Vector3, Vector4, Vector3, float, bool, GLFWwindow*);

	// -- Functions from AIE Framework..work through and implement functions that will be useful in new engine -- 
	//unsigned int	CreateSprite( const char* a_pTextureName, int a_iWidth, int a_iHeight, bool a_bDrawFromCenter = true, SColour a_sColour = SColour(0xFF,0xFF,0xFF,0xFF) );
	//unsigned int	DuplicateSprite( unsigned int a_uiSpriteID );
	//void			SetSpriteColour( unsigned int a_uiSpriteID, SColour& a_sColour );
	//void			GetSpriteColour( unsigned int a_uiSpriteID, SColour& a_sColour );
	//void			MoveSprite( unsigned int a_uiSpriteID, float a_fXPos, float a_fYPos );
	//void			RotateSprite( unsigned int a_uiSpriteID, float a_fRotation );
	//void			DestroySprite( unsigned int a_uiSpriteID );
	//void			DrawSprite( unsigned int a_uiSpriteID );
	//void			SetSpriteUVCoordinates( unsigned int a_uiSpriteID, float a_minUCoord, float a_minVCoord, float a_maxUCoord, float a_maxVCoord );
	//void			GetSpriteUVCoordinates( unsigned int a_uiSpriteID, float& a_minUCoord, float& a_minVCoord, float& a_maxUCoord, float& a_maxVCoord );
	//void			SetSpriteScale( unsigned int a_uiSpriteID, float& a_fSpriteWidth, float& a_fSpriteHeight );
	//void			GetSpriteScale( unsigned int a_uiSpriteID, float& a_fSpriteWidth, float& a_fSpriteHeight );

	// New Functions -------------------------------------******
	unsigned int CreateSprite(const char* a_cpType, const char* a_cpTexture, /*float a_fSheetSlices(won't need with XML sheet info?),*/ Vector3 a_v3Dimensions, Vector3 a_v3Position, 
							  Vector3 a_v3Velocity, /*Vector3 a_v3Force(gone with new physics?),*/ float a_fMass, /*float a_fMovementPower(move to Entity child),*/ bool a_bAlive, Vector4 a_v4Color);

	// ---------------------------------------------------******

	void Draw();
	void Input();
	void LoadTexture(const char* a_cpTexture);

	void UVSetup();

	void SetPosition(Vector3 a_v3Pos);
	void SetPosition(float a_fX, float a_fY);
	Vector3 GetPosition();
	void SetScale(Vec2 a_v2Scale);
	void SetScale(float a_fX, float a_fY);
	Vector3 GetScale();

	GLFWwindow * GameWindow;

// private:
	Vertex m_aoVerts[4];
	Matrix4 * modelMatrix;
	Matrix4 * viewMatrix;
	Matrix4 * MVP;

	Vector3 m_v3Scale;
	Vector3 m_v3Position;
	Vector4 m_v4SpriteColor;

	unsigned int m_uiTexture;
	
	// used later
	Vec2 m_minUVCoords, m_maxUVCoords;
	Vec2 m_texSize;//, m_uvOffset;

	unsigned int m_uSourceBlendMode;
	unsigned int m_uDestinationBlendMode;
	int tex_loc, matrix_location, proj_location;

	bool flipped;

	//vector<UV> m_vSpriteSheet;
};

#endif