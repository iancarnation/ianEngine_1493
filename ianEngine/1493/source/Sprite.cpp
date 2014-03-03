///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:			Sprite.cpp
// Author:			Ian Rich
// Date Created:	October 2013
// Brief:			Sprite (Renderable/Movable) Object Class Definition
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sprite.h"

// default constructor
Sprite::Sprite()
{}

// constructor that takes in values
Sprite::Sprite(char *a_cNewType, float a_fWidth, float a_fHeight, Vector2D a_Position, 
			   Vector2D a_Velocity, Vector2D a_Force, float a_fMass, float a_fMovementForce, bool a_bAlive, const char* a_cpTextureName, float a_fSheetSlices)
{
	SetType(a_cNewType);
	m_fWidth = a_fWidth;
	m_fHeight = a_fHeight;
	m_oPosition = a_Position; // check on these **
	m_oVelocity = a_Velocity;
	m_oForce = a_Force;
	m_fMass = a_fMass;
	m_fMovementForce = a_fMovementForce;
	//m_iSpriteId = -1;	//**figure out where to initialize/check for this
	m_iAmmoSlot = 0;
	m_bAlive = a_bAlive;
	m_cpTextureName = a_cpTextureName;
	m_fSheetSlices = a_fSheetSlices;
	//m_dDeltaTime = GetDeltaTime();

	// set UV Coordinates
	UVSetup();

	m_fTop = m_oPosition.m_fY - (m_fHeight / 2);
	m_fBottom = m_oPosition.m_fY + (m_fHeight / 2);
	m_fLeft = m_oPosition.m_fX - (m_fWidth / 2);
	m_fRight = m_oPosition.m_fX + (m_fWidth / 2);

	m_iSpriteId = CreateSprite(m_cpTextureName, m_fWidth, m_fHeight, true); //delete?
	
}

// destructor
Sprite::~Sprite ()
{
	//cout<< "Vector Destroyed, Muhahah!\n";
}

// run functions for changing state of objects
void Sprite::Update()
{
	Move();
}

// calls the MoveSprite function from the AIE Framework
void Sprite::Move()
{
	MoveSprite(m_iSpriteId, m_oPosition.m_fX, m_oPosition.m_fY);
}

// calls the DrawSprite function from the AIE Framework
void Sprite::Draw()
{
	DrawSprite(m_iSpriteId);
}

// calls the DrawSprite function from the AIE Framework
void Sprite::Destroy()
{
	DestroySprite(m_iSpriteId);
}

// returns the 'type' as a char array
char* Sprite::GetType()
{
	return m_cType;
}

// gives the object a 'type' name as a char array
void Sprite::SetType(char *a_cNewType)
{
	// copy NewType into m_cType
	strcpy_s(m_cType,a_cNewType);
}

int& Sprite::GetSpriteId()
{
	return m_iSpriteId;
}

// returns the position vector
Vector2D& Sprite::GetPosition()
{
	return m_oPosition;
}

// returns the velocity vector
Vector2D& Sprite::GetVelocity()
{
	return m_oVelocity;
}

void Sprite::SetPosition(Vector2D a_oPos)
{
	m_oPosition = a_oPos;
}

void Sprite::SetVelocity(Vector2D a_oVel)
{
	m_oVelocity = a_oVel;
}

// calculates velocity for going towards a certain vector
void Sprite::SetVelocityToward(const Vector2D a_rV2)
{
	/*float fAngle = GetPosition().GetAngle(a_rV2);
	Vector2D vect(cos(fAngle), sin(fAngle));
	SetVelocity(vect);*/

	Vector2D direction((m_oPosition.m_fX - a_rV2.m_fX), (m_oPosition.m_fY - a_rV2.m_fY));
	direction.Normalize();
	SetVelocity(direction);
}

// returns the increment by which a sprite will move
float& Sprite::GetMoveFactor()
{
	return m_fMovementForce;
}

// returns whether the sprite is "alive"(visible) or not
bool Sprite::IsAlive()
{
	return m_bAlive;
}

// changes "alive" marker
void Sprite::SetAlive(bool a_bValue)
{
	m_bAlive = a_bValue;
}

float& Sprite::GetEdge(Boundary a_edge)
{
	switch(a_edge)
	{
	case TOP:
		return m_fTop;
		break;
	case BOTTOM:
		return m_fBottom;
		break;
	case LEFT:
		return m_fLeft;
		break;
	case RIGHT:
		return m_fRight;
		break;
	};
}

// updates the values of object boundaries
void Sprite::UpdateEdges()
{
	m_fTop = m_oPosition.m_fY - (m_fHeight / 2);
	m_fBottom = m_oPosition.m_fY + (m_fHeight / 2);
	m_fLeft = m_oPosition.m_fX - (m_fWidth / 2);
	m_fRight = m_oPosition.m_fX + (m_fWidth / 2);
}

// is sprite on screen?
bool Sprite::IsOnScreen()
{
	if (m_fTop > 0 && m_fBottom < SCREEN_Y && m_fLeft > 0 && m_fRight < SCREEN_X)
		return true;
	else
		return false;
}

// sprite collision
bool Sprite::IsCollidingWith(Sprite* a_pSprite2)
{
	if (this->GetEdge(BOTTOM) < a_pSprite2->GetEdge(TOP))
		return 0;
	if (this->GetEdge(TOP) > a_pSprite2->GetEdge(BOTTOM))
		return 0;
	if (this->GetEdge(RIGHT) < a_pSprite2->GetEdge(LEFT))
		return 0;
	if (this->GetEdge(LEFT) > a_pSprite2->GetEdge(RIGHT))
		return 0;

	return 1;
}

// "kills" projectile and returns it to holding area
void Sprite::Die()
{
	SetAlive(false);
	m_oVelocity = ZERO_VELOCITY;
	m_oPosition = HOLDING_AREA;
}

// set UV Coordinates
void Sprite::UVSetup()
{
	float fStepSize = 1/m_fSheetSlices;			// X distance between slices
	float fMin = 0;								// current top-left corner of slice
	float fMax = fStepSize;						// current bottom-right corner of slice
	// for each slice of the sprite sheet
	for (int i=0; i<int(m_fSheetSlices); i++)
	{
		// construct UV coordinate set (Xmin, Ymin, Xmax, Ymax)
		UV Slice(fMin, 0, fMax, 1);
		// add to sprite sheet vector
		m_vSpriteSheet.push_back(Slice);
		// increment min and max cursors
		fMin += fStepSize;
		fMax += fStepSize;
	}
	// set initial slice
}

// sets UV coordinates to a specific slice of the sprite's sheet
void Sprite::SetUV(int a_iSheet)
{
	float tempXmin, tempYmin, tempXmax, tempYmax;
	tempXmin = m_vSpriteSheet[a_iSheet].m_fXmin;
	tempYmin = m_vSpriteSheet[a_iSheet].m_fYmin;
	tempXmax = m_vSpriteSheet[a_iSheet].m_fXmax;
	tempYmax = m_vSpriteSheet[a_iSheet].m_fYmax;

	SetSpriteUVCoordinates(m_iSpriteId, tempXmin, tempYmin, tempXmax, tempYmax);
}