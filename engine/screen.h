#pragma once
#include <SFML/Graphics.hpp>

namespace g
{
	class Screen
	{
	public:
		sf::RenderTexture renderTexture;
		//virtual width of the screen
		unsigned int widthV = 0;
		//virtual height of the screen
		unsigned int heightV = 0;

		Screen(unsigned int width, unsigned int height);
		Screen(unsigned int width, float aspectRatio);
        void draw(sf::RenderWindow& window, bool smooth = true);
	};
}