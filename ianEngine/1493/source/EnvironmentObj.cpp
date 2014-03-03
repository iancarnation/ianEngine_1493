///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:			EnvironmentObj.cpp
// Author:			Ian Rich
// Date Created:	October 2013
// Brief:			EnvironmentObj Class, inherits from Sprite Class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "EnvironmentObj.h"

// default constructor
EnvironmentObj::EnvironmentObj()
{

}

// constructor with parameters
EnvironmentObj::EnvironmentObj(char *a_cNewType, float a_fWidth, float a_fHeight, Vector2D a_Position, 
			   Vector2D a_Velocity, Vector2D a_Force, float a_fMass, float a_fMovementForce, bool a_bAlive, const char* a_cpTextureName, float a_fSheetSlices)
			 : Sprite (a_cNewType, a_fWidth, a_fHeight, a_Position, a_Velocity, a_Force, a_fMass, a_fMovementForce, 
					   a_bAlive, a_cpTextureName, a_fSheetSlices)
{

}

// destructor
EnvironmentObj::~EnvironmentObj()
{

}

void EnvironmentObj::Update()
{
	m_oPosition += m_oVelocity;

	m_fTop = m_oPosition.m_fY - (m_fHeight / 2);
	m_fBottom = m_oPosition.m_fY + (m_fHeight / 2);
	m_fLeft = m_oPosition.m_fX - (m_fWidth / 2);
	m_fRight = m_oPosition.m_fX + (m_fWidth / 2);

	Sprite::Update();
}

void EnvironmentObj::Draw()
{
	Sprite::Draw();
}