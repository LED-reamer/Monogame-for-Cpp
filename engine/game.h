#pragma once
#include <SFML/Graphics.hpp>

#include "assets.h"
#include "screen.h"
#include "scene.h"

namespace g
{
	class Game
	{
	public:
		sf::RenderWindow& window;
		AssetManager assetManager;
		Screen& screen;


		//character entered this frame. just += on any string but check if it's 0! If it is don't add it!
		char currentTypedCharacter = 0;
		bool windowFocused = true;

		Game(sf::RenderWindow& refWindow, Screen& refScreen);
		~Game();

		bool running();

		void addScene(g::Scene* scene, std::string name);
		void setCurrentScene(std::string name, bool load = true);
		void setCurrentScene(Scene* newScene, bool load = true);
		Scene* getCurrentScene();

	private:
		std::vector<std::pair<std::string, g::Scene*>> m_scenes;
		Scene* m_currentScene;
		bool m_closed;
	};
}