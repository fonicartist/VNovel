#ifndef  GAME_H
#define  GAME_H

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Game {
private:
	// Enumeration controls the different states the game goes into.
	enum GameState {logos, titleStart, titleScreen, intro, inGame, gameOver, pause} gameState_;
	enum MenuChoice {contChoice, newChoice, loadChoice, exitChoice} menuChoice_;

	// Game objects
	int counter = 0,
		bgCounter = 0;

	// SFML Objects
	sf::RenderWindow window;

	sf::Clock clock;
	sf::Time deltaTime;

	sf::View camera;

	// In game text
	sf::Font chancery;
	sf::Text gameTitle,
			 contGame,
			 newGame,
			 loadGame,
			 exitGame;

	// Game Music
	sf::Music titleMusic,
			  introMusic,
			  ingameMusic,
			  gameOverMusic;

	// Game sounds but using music implementation
	sf::Music pressEnter;

	// Background Pictures
	sf::Sprite title;
	sf::Texture titleTexture;
	sf::Sprite introSprite;
	sf::Texture introTexture;
	sf::Sprite GOimage;
	sf::Texture GOTexture;

	// Game sprites
	sf::Sprite cursor;
	sf::Texture cursorTexture;

	// Game mechanic functions
	void handleEvent(sf::Event &event);

	void playIntro();
	void titleUpdate();
	void gameoverUpdate();
	void loadAssets();
	void checkMusic();
	void update();
	void render();

public:
	Game();
	~Game();
	void mainLoop();

};

#endif 