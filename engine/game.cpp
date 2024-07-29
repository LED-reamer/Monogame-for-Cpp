#include "game.h"

g::Game::Game(sf::RenderWindow& refWindow, Screen& refScreen) : window(refWindow), assetManager(), m_closed(false), screen(refScreen), m_currentScene(nullptr)
{

}

g::Game::~Game()
{
	
}

bool g::Game::running()
{
	//resize window
	sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	window.setView(view);


	//end update
	screen.draw(window, false);

	window.display();

	//begin update
	window.clear(sf::Color::Black);
	if(m_currentScene != nullptr)//if working with scenes
		m_currentScene->update();//take care for fixed time steps

	if(m_currentScene != nullptr)//if working with scenes
		m_currentScene->draw(screen.renderTexture);

	//check events for closing, text input, window focus, ...
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_closed = true;
			break;
		}

		currentTypedCharacter = 0;
		if (event.type == sf::Event::TextEntered && std::isprint(event.text.unicode))
		{
			currentTypedCharacter = event.text.unicode;
		}

		if (event.type == sf::Event::GainedFocus)
			windowFocused = true;
		if (event.type == sf::Event::LostFocus)
			windowFocused = false;
	}

	//close window if closing
	if(m_closed)
		window.close();
	return !m_closed;
}

void g::Game::addScene(g::Scene* scene, std::string name)
{
	m_scenes.push_back(std::make_pair(name, scene));
}

void g::Game::setCurrentScene(std::string name, bool load)
{
	for (size_t i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i].first == name)
		{
			if (m_scenes[i].second != nullptr)
				setCurrentScene(m_scenes[i].second, load);
		}
	}

	//error occurred!
}

void g::Game::setCurrentScene(Scene* newScene, bool load)
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->unload();
	}

	m_currentScene = newScene;
	if (load && m_currentScene != nullptr)
		m_currentScene->load();
}

g::Scene* g::Game::getCurrentScene()
{
	return m_currentScene;
}