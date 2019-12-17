#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	listener.setPosition(sf::Mouse::getPosition(m_window).x, -sf::Mouse::getPosition(m_window).y, ListenerZ);


	buffer.loadFromFile("ASSETS\\SOUNDS\\mono.wav");


	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.setMinDistance(MinDistance3D);
	sound.setAttenuation(Attenuation);
	sound.setPosition(sf::Vector3f(640.f, -360.f, 0.f));
	sound.play();
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	listener.setPosition(sf::Mouse::getPosition(m_window).x, -sf::Mouse::getPosition(m_window).y, ListenerZ);

	m_headSprite.setPosition(
		sf::Mouse::getPosition(m_window).x - m_headSprite.getGlobalBounds().width / 2.0f,
		sf::Mouse::getPosition(m_window).y - m_headSprite.getGlobalBounds().height / 2.0f
	);


	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_speakerSprite);
	m_window.draw(m_headSprite);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_headTexture.loadFromFile("ASSETS\\IMAGES\\head.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading head image" << std::endl;
	}
	m_headSprite.setTexture(m_headTexture);
	m_headSprite.setScale(0.25f, 0.25f);
	m_headSprite.setPosition(sf::Mouse::getPosition(m_window).x - m_headSprite.getGlobalBounds().width / 2.0f, sf::Mouse::getPosition(m_window).y - m_headSprite.getGlobalBounds().height / 2.0f);

	if (!m_speakerTexture.loadFromFile("ASSETS\\IMAGES\\speaker.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading speaker image" << std::endl;
	}
	m_speakerSprite.setTexture(m_speakerTexture);
	m_speakerSprite.setScale(0.25f, 0.25f);
	m_speakerSprite.setPosition(640.f - m_speakerSprite.getGlobalBounds().width / 2.0f, 360.f - m_speakerSprite.getGlobalBounds().height / 2.0f);

}
