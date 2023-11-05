#pragma once
#include <SFML/Graphics.hpp>
#include "game.h"


namespace g
{
    class Game; //forwarded

    class Scene
    {
    public:
        Game& game;
        Scene(Game& gameRef) : game(gameRef)
        {

        }
        virtual ~Scene() {}
        virtual void load() = 0;
        virtual void unload() = 0;
        virtual void update() = 0;
        virtual void draw(sf::RenderTexture& rt) = 0;
    };
}
