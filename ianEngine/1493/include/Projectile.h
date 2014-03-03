///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:			Projectile.h
// Author:			Ian Rich
// Date Created:	October 2013
// Brief:			Projectile Class Definition, inherits from Sprite Class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Sprite.h"

class Projectile: public Sprite
{
	public:
		Projectile();	// default constructor
		Projectile(char *a_cNewType, float a_fWidth, float a_fHeight, Vector2D a_Position, 
				   Vector2D a_Velocity, Vector2D a_Force, float a_fMass, float a_fMovementForce, bool a_bAlive, const char* a_cpTextureName, float a_fSheetSlices);		// constructor with parameters 
		~Projectile();	// destructor

		void Update(double dt);
		void Draw();	
		//void Die();		// "kills" projectile and returns it to holding area
};

#endif