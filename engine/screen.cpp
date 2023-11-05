#include "screen.h"

g::Screen::Screen(unsigned int width, unsigned int height)
{
	widthV = width;
	heightV = height;

	renderTexture.create(widthV, heightV);
}

//only give width and use an aspect ratio (example: 16/9) to calculate height
g::Screen::Screen(unsigned int width, float aspectRatio)
{
	widthV = width;
	if (aspectRatio != 0)
		heightV = (unsigned int)((float)width / aspectRatio);
	else
		heightV = 1;//no division by 0!

	renderTexture.create(widthV, heightV);
}

void g::Screen::draw(sf::RenderWindow& window, bool smooth)
{
    
    float outAspectRatio = (float)window.getSize().x / (float)window.getSize().y;
    float preferredAspectRatio = (float)widthV / (float)heightV;

    unsigned int barWidth = 0;
    unsigned int barHeight = 0;
    int presentWidth = window.getSize().x;
    int presentHeight = window.getSize().y;

    if (outAspectRatio <= preferredAspectRatio)
    {
        presentHeight = (int)((window.getSize().x / preferredAspectRatio) + 0.5f);
        barHeight = (window.getSize().y - presentHeight) / 2;
    }
    else
    {
        presentWidth = (int)((window.getSize().y * preferredAspectRatio) + 0.5f);
        barWidth = ((float)window.getSize().x - presentWidth) / 2;
    }
    
    //update the texture
    renderTexture.display();

    sf::RectangleShape finalScreenShape;
    sf::Texture tex = renderTexture.getTexture();
    tex.setSmooth(smooth);
    finalScreenShape.setTexture(&tex);
    finalScreenShape.setPosition(sf::Vector2f(barWidth, barHeight));
    finalScreenShape.setSize(sf::Vector2f(presentWidth, presentHeight));
    window.draw(finalScreenShape);
}