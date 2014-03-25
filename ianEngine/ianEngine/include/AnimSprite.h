#ifndef _ANIMSPRITE_H_
#define _ANIMSPRITE_H_

#include "Utilities.h"
#include "Sprite.h"
#include <tinyxml2.h>

// represents a single image on the sprite sheet
struct AniSlice
{
	std::string sName;
	float fWidth, fHeight;
	Vec2 v2minUV, v2maxUV;
};

typedef std::vector<std::string> sequence;  // single animation sequence (group of frames/slices)

struct Atlas
{
	Vec2 v2Size;
	std::string sSheet;
	std::string sAnimations;
};


class AnimSprite: public Sprite
{
public:
	AnimSprite();
	~AnimSprite();
	AnimSprite(/*const char* a_cpType,*/ const char* a_cpTexture,
			   /*Vector3 a_v3Velocity,*/ /*Vector3 a_v3Force(gone with new physics?),*/ /*float a_fMass,*/ /*float a_fMovementPower(move to Entity child),*/ /*bool a_bAlive,*/ GLFWwindow* window);

	void Input();
	void Draw(); // ** Justin made virtual..figure out why **
	void Update();
	void SetSlice();
	void SetAnimation(std::string animation, AnimCycle cycle, int frame);
	void PlayAnimation();
	void LoadSlices(const char* a_cpTextureAtlas);
	void LoadAnimations(const char* a_cpAnimationData);

	std::map<std::string, AniSlice> m_mSprites;
	std::map<std::string, sequence> m_mAnimations;
	Atlas m_atlas;

	std::string m_sCurrentAnimation, m_sCurrentSlice;
	int iCurrentFrame, iLoopMarker, iPlayDirection;
	AnimCycle currentCycle;
	double m_dElapsedTime, m_dFrameDuration;
};

#endif