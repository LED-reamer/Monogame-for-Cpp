#include "animation.h"

#include <math.h>
#include <iostream>

g::SpriteSheet::SpriteSheet(sf::Texture spriteSheetTexture, unsigned int _rows, unsigned int _cols)
{
	texture = spriteSheetTexture;
	rows = _rows;
	cols = _cols;
}


g::Animation::Animation()
{
	spriteSheet = nullptr;

	row = 0;
	numFrames = 0;
	secondsPerFrame = 0;
	looping = true;
}

g::Animation::Animation(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, SpriteSheet* spriteSheetPtr)
{
	spriteSheet = spriteSheetPtr;

	row = _row;
	numFrames = _numFrames;
	secondsPerFrame = _secondsPerFrame;
	looping = true;
}

g::Animation::Animation(unsigned int _row, unsigned int _numFrames, float _secondsPerFrame, g::Animation& _followingAnimation, SpriteSheet* spriteSheetPtr)
{
	spriteSheet = spriteSheetPtr;

	row = _row;
	numFrames = _numFrames;
	secondsPerFrame = _secondsPerFrame;
	looping = false;
	followingAnimation = std::make_shared<g::Animation>(_followingAnimation);
}

g::AnimatedSprite::AnimatedSprite()
{

}

g::AnimatedSprite::AnimatedSprite(sf::Sprite& sprite, int numRows, int numCols)
{
	sprite = sprite;
	m_numRows = numRows;
	m_numCols = numCols;
}

g::AnimatedSprite::AnimatedSprite(sf::Texture& texture, int numRows, int numCols)
{
	sprite = sf::Sprite(texture);
	m_numRows = numRows;
	m_numCols = numCols;
}

void g::AnimatedSprite::setAnimation(Animation& animation)
{
	if (animation.spriteSheet == nullptr)
	{
		m_useSpriteTexture = true;
	}
	else
	{
		m_useSpriteTexture = false;
	}

	currentAnimation = animation;
	currentAnimation.timerAnimationStart = std::chrono::system_clock::now();
	
}

void g::AnimatedSprite::updateAnimation()
{
	unsigned int frameWidth, frameHeight;
	if (m_useSpriteTexture)
	{
		frameWidth = sprite.getTexture()->getSize().x / m_numCols;
		frameHeight = sprite.getTexture()->getSize().y / m_numRows;
	}
	else if (currentAnimation.spriteSheet != nullptr)
	{
		frameWidth = currentAnimation.spriteSheet->texture.getSize().x / currentAnimation.spriteSheet->cols;
		frameHeight = currentAnimation.spriteSheet->texture.getSize().y / currentAnimation.spriteSheet->rows;
	}
	else return;

	//get time since last animation reset
	std::chrono::system_clock::time_point timerNow = std::chrono::system_clock::now();
	float duration = std::chrono::duration_cast<std::chrono::milliseconds>(timerNow - currentAnimation.timerAnimationStart).count() / 1000.0f; //convert to seconds float

	//if animation is done reset timer
	const float fullAnimationTime = currentAnimation.numFrames * currentAnimation.secondsPerFrame;
	if (duration > fullAnimationTime)//animation went through
	{
		if (currentAnimation.looping == false)
			currentAnimation = *currentAnimation.followingAnimation.get();

		duration = 0.0f;
		currentAnimation.timerAnimationStart = std::chrono::system_clock::now();
	}

	//set current frame
	float percentage = 0.0f;
	if(fullAnimationTime != 0)
		percentage = duration / fullAnimationTime;

	if (duration != 0.0f)
		currentAnimation.currentFrame = (unsigned int)(percentage * currentAnimation.numFrames);
	else
		currentAnimation.currentFrame = 0;

	//handling edge case when duration happens to be exactly fullAnimationTime or other edge cases
	if (currentAnimation.currentFrame >= currentAnimation.numFrames)// >= since currentFrame is an index starting from 0 and numFrames is not
		currentAnimation.currentFrame = 0;

	//set animation
	sprite.setTextureRect(
		sf::IntRect(
			currentAnimation.currentFrame * frameWidth + (flipVertically ? frameWidth : 0), 
			currentAnimation.row * frameHeight + (flipHorizontally ? frameHeight : 0), 
			flipVertically ? -(int)frameWidth : frameWidth, 
			flipHorizontally ? -(int)frameHeight : frameHeight)
	);
}

float g::easing::linearInterpolation(float p)
{
	return p;
}

float g::easing::quadraticIn(float p)
{
	return p * p;
}

float g::easing::quadraticOut(float p)
{
	return -(p * (p - 2));
}

float g::easing::quadraticInOut(float p)
{
	if (p < 0.5)
	{
		return 2 * p * p;
	}
	else
	{
		return (-2 * p * p) + (4 * p) - 1;
	}
}

float g::easing::cubicIn(float p)
{
	return p * p * p;
}

float g::easing::cubicOut(float p)
{
	float f = (p - 1);
	return f * f * f + 1;
}

float g::easing::cubicInOut(float p)
{
	if (p < 0.5)
	{
		return 4 * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

float g::easing::quarticIn(float p)
{
	return p * p * p * p;
}

float g::easing::quarticOut(float p)
{
	float f = (p - 1);
	return f * f * f * (1 - p) + 1;
}

float g::easing::quarticInOut(float p)
{
	if (p < 0.5)
	{
		return 8 * p * p * p * p;
	}
	else
	{
		float f = (p - 1);
		return -8 * f * f * f * f + 1;
	}
}

float g::easing::quinticIn(float p)
{
	return p * p * p * p * p;
}

float g::easing::quinticOut(float p)
{
	float f = (p - 1);
	return f * f * f * f * f + 1;
}

float g::easing::quinticInOut(float p)
{
	if (p < 0.5)
	{
		return 16 * p * p * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return  0.5 * f * f * f * f * f + 1;
	}
}

float g::easing::sineIn(float p)
{
	return sin((p - 1) * EASE_PI2) + 1;
}

float g::easing::sineOut(float p)
{
	return sin(p * EASE_PI2);
}

float g::easing::sineInOut(float p)
{
	return 0.5 * (1 - cos(p * EASE_PI));
}

float g::easing::circularIn(float p)
{
	return 1 - sqrt(1 - (p * p));
}

float g::easing::circularOut(float p)
{
	return sqrt((2 - p) * p);
}

float g::easing::circularInOut(float p)
{
	if (p < 0.5)
	{
		return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
	}
	else
	{
		return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
	}
}

float g::easing::exponentialIn(float p)
{
	return (p == 0.0) ? p : pow(2, 10 * (p - 1));
}

float g::easing::exponentialOut(float p)
{
	return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

float g::easing::exponentialInOut(float p)
{
	if (p == 0.0 || p == 1.0) return p;

	if (p < 0.5)
	{
		return 0.5 * pow(2, (20 * p) - 10);
	}
	else
	{
		return -0.5 * pow(2, (-20 * p) + 10) + 1;
	}
}

float g::easing::elasticIn(float p)
{
	return sin(13 * EASE_PI2 * p) * pow(2, 10 * (p - 1));
}

float g::easing::elasticOut(float p)
{
	return sin(-13 * EASE_PI2 * (p + 1)) * pow(2, -10 * p) + 1;
}

float g::easing::elasticInOut(float p)
{
	if (p < 0.5)
	{
		return 0.5 * sin(13 * EASE_PI2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
	}
	else
	{
		return 0.5 * (sin(-13 * EASE_PI2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
	}
}

float g::easing::backIn(float p)
{
	return p * p * p - p * sin(p * EASE_PI);
}

float g::easing::backOut(float p)
{
	float f = (1 - p);
	return 1 - (f * f * f - f * sin(f * EASE_PI));
}

float g::easing::backInOut(float p)
{
	if (p < 0.5)
	{
		float f = 2 * p;
		return 0.5 * (f * f * f - f * sin(f * EASE_PI));
	}
	else
	{
		float f = (1 - (2 * p - 1));
		return 0.5 * (1 - (f * f * f - f * sin(f * EASE_PI))) + 0.5;
	}
}

float g::easing::bounceIn(float p)
{
	return 1 - g::easing::bounceOut(1 - p);
}

float g::easing::bounceOut(float p)
{
	if (p < 4 / 11.0)
	{
		return (121 * p * p) / 16.0;
	}
	else if (p < 8 / 11.0)
	{
		return (363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0;
	}
	else if (p < 9 / 10.0)
	{
		return (4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0;
	}
	else
	{
		return (54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0;
	}
}

float g::easing::bounceInOut(float p)
{
	if (p < 0.5)
	{
		return 0.5 * bounceIn(p * 2);
	}
	else
	{
		return 0.5 * bounceOut(p * 2 - 1) + 0.5;
	}
}