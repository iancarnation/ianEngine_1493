#ifndef _ANIMSPRITE_H_
#define _ANIMSPRITE_H_

#include "Utilities.h"
#include "Sprite.h"

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
	AnimSprite(/*const char* a_cpType,*/ const char* a_cpTexture, int a_iWidth, int a_iHeight, Vector4 a_v4Color, 
			   /*Vector3 a_v3Velocity,*/ /*Vector3 a_v3Force(gone with new physics?),*/ /*float a_fMass,*/ /*float a_fMovementPower(move to Entity child),*/ /*bool a_bAlive,*/ GLFWwindow* window);

	/*virtual*/ void Draw(); // ** Justin made virtual..figure out why **
	void Update();
	void SetSlice();
	void SetAnimation(std::string animation, AnimCycle cycle, int frame);
	void PlayAnimation();
	void LoadSlices(const char* a_cpTextureAtlas);
	void LoadAnimations(const char* a_cpAnimationInfo);
	void Input();

	std::map<std::string, AniSlice> m_mSprites;
	std::map<std::string, sequence> m_mAnimations;

	std::string currentAnimation, currentSlice;
	int iCurrentFrame, iPlayHead;
	AnimCycle currentCycle;
};

#endif