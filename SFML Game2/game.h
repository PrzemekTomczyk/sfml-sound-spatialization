#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_headTexture; // texture used for sfml logo
	sf::Sprite m_headSprite; // sprite used for sfml logo
	sf::Texture m_speakerTexture; // texture used for sfml logo
	sf::Sprite m_speakerSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	sf::Listener listener;

	sf::SoundBuffer buffer;

	sf::Sound sound;

	const float ListenerZ = 150.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
};

#endif // !GAME