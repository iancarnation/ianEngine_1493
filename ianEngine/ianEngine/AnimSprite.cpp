#include "AnimSprite.h"

AnimSprite::AnimSprite()
{}

AnimSprite::~AnimSprite()
{}

AnimSprite::AnimSprite(const char* a_cpTexture, int a_iWidth, int a_iHeight, Vector4 a_v4Color, GLFWwindow* window)
{
	GameWindow = window;

	LoadVertShader("./resources/VertexShader.glsl");
	LoadFragShader("./resources/FragmentShader.glsl");



}