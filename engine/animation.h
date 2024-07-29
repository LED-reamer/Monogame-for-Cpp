#pragma once
#include <SFML/Graphics.hpp>

#include <chrono>

namespace g
{
	class SpriteSheet
	{
	public:
		SpriteSheet(sf::Texture spriteSheetTexture, unsigned int _rows, unsigned int _cols);

		sf::Texture texture;
		unsigned int rows;
		unsigned int cols;
	};

	class Animation; //forward
	class Animation
	{
	public:
		Animation();
		Animation(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, SpriteSheet* spriteSheetPtr = nullptr);
		Animation(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, g::Animation& _followingAnimation, SpriteSheet* spriteSheetPtr = nullptr);
		//static Animation createNewLoop(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, SpriteSheet* spriteSheetPtr = nullptr);
		//static Animation createNewOnce(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, g::Animation _followingAnimation, SpriteSheet* spriteSheetPtr = nullptr);

		//if nulled AnimatedSprite will use texture of the sf::Sprite
		SpriteSheet* spriteSheet;
		
		unsigned int row;
		unsigned int numFrames;
		float secondsPerFrame;
		unsigned int currentFrame = 0;
		std::chrono::steady_clock::time_point timerAnimationStart;
		std::shared_ptr<g::Animation> followingAnimation;
		bool looping = true;
	};

	class AnimatedSprite
	{
	public:
		Animation currentAnimation;
		sf::Sprite sprite;
		bool flipVertically = false;
		bool flipHorizontally = false;

		AnimatedSprite();
		AnimatedSprite(sf::Sprite& sprite, int numRows, int numCols);
		AnimatedSprite(sf::Texture& texture, int numRows, int numCols);
		//set rows and cols if sf::Sprite texture is used
		//static AnimatedSprite createAnimatedSprite(sf::Sprite& sprite, int numRows, int numCols);
		//set rows and cols if sf::Sprite texture is used
		//static AnimatedSprite createAnimatedSprite(sf::Texture& texture, int numRows, int numCols);
		void setAnimation(Animation& animation);
		void updateAnimation();
	private:
		bool m_useSpriteTexture = false;
		unsigned int m_numRows;
		unsigned int m_numCols;
	};

	namespace easing
	{

#define EASE_PI 3.14159265358979323846
#define EASE_PI2 1.57079632679489661923

		// Linear interpolation (no easing)
		float linearInterpolation(float p);

		// Quadratic easing; p^2
		float quadraticIn(float p);
		float quadraticOut(float p);
		float quadraticInOut(float p);

		// Cubic easing; p^3
		float cubicIn(float p);
		float cubicOut(float p);
		float cubicInOut(float p);

		// Quartic easing; p^4
		float quarticIn(float p);
		float quarticOut(float p);
		float quarticInOut(float p);

		// Quintic easing; p^5
		float quinticIn(float p);
		float quinticOut(float p);
		float quinticInOut(float p);

		// Sine wave easing; sin(p * PI/2)
		float sineIn(float p);
		float sineOut(float p);
		float sineInOut(float p);

		// Circular easing; sqrt(1 - p^2)
		float circularIn(float p);
		float circularOut(float p);
		float circularInOut(float p);

		// Exponential easing, base 2
		float exponentialIn(float p);
		float exponentialOut(float p);
		float exponentialInOut(float p);

		// Exponentially-damped sine wave easing
		float elasticIn(float p);
		float elasticOut(float p);
		float elasticInOut(float p);

		// Overshooting cubic easing; 
		float backIn(float p);
		float backOut(float p);
		float backInOut(float p);

		// Exponentially-decaying bounce easing
		float bounceIn(float p);
		float bounceOut(float p);
		float bounceInOut(float p);

	}
}
