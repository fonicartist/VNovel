// Implementation file for Game object
#include <iostream>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
#include "Game.h"

using namespace std;

/************************************************
 * Constructor Game() creates a new Game object *
 * containing everything else when the program  *
 * starts up.									*
 ************************************************/
 Game::Game() {
	// Create game render window
	window.create(sf::VideoMode(1280, 720), "V-Novel");// , sf::Style::Fullscreen);
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);

	//window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	camera.setCenter(640, 360);

	gameState_ = logos;
	menuChoice_ = newChoice;

	loadAssets();

}

/************************************************
 * The mainLoop() function handles in game		*
 * occurences while the program window remains	*
 * open.										*
 ************************************************/
void Game::mainLoop() {
	sf::Event event;
	deltaTime = sf::Time::Zero;

	while (window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		deltaTime += elapsedTime;

		while (deltaTime > TimePerFrame) {
			// Reset deltaTime
			deltaTime -= TimePerFrame;

			// Check for events
			while (window.pollEvent(event))
				handleEvent(event);

			// Switch between different gamestates

			checkMusic();
			
		}
		render();
	}
}

/************************************************
 * Event handler								*
 ************************************************/
void Game::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::Closed)
		window.close();

	// Close window by escape or set full screen
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape && (gameState_ == titleStart || gameState_ == titleScreen)) {
			window.close();
		}

	// Switch statement controls what actions are done in each game state
	switch (gameState_) {
	case logos:
		if (keyConfirmed(event) || event.type == event.MouseButtonPressed) {
			gameState_ = titleStart;
		}
		break;
	case titleStart:
		if (keyConfirmed(event) || event.type == event.MouseButtonPressed) {
			gameState_ = titleScreen;
		}
		break;
	case titleScreen:
		// Keyboard confirmation is separate from mouse for the menu confirmations.
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			switch (menuChoice_) {
			//case contChoice: gameState_ = intro; break;
			case newChoice: gameState_ = intro; break;
			case loadChoice: gameState_ = intro; break;
			case exitChoice: window.close(); break;
			}
		}
		// Mouse confirmation has to reflect the position of the mouse.
		else if (event.type == event.MouseButtonPressed) {
			switch (menuChoice_) {
			//case contChoice: gameState_ = intro; break;
			case newChoice: 
				if ((getMouseX() >= 755 && getMouseX() <= 975) && (getMouseY() >= 355 && getMouseY() <= 403))
					gameState_ = intro;
				break;
			case loadChoice: 
				if ((getMouseX() >= 755 && getMouseX() <= 855) && (getMouseY() >= 405 && getMouseY() <= 453))
					gameState_ = intro;
				break;
			case exitChoice: 
				if ((getMouseX() >= 755 && getMouseX() <= 855) && (getMouseY() >= 455 && getMouseY() <= 503))
					window.close();
				break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)) {
			switch (menuChoice_) {
			//case newChoice: menuChoice_ = contChoice; break;
			case loadChoice: menuChoice_ = newChoice; chime.play(); break;
			case exitChoice: menuChoice_ = loadChoice; chime.play(); break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)) {
			switch (menuChoice_) {
			//case contChoice: menuChoice_ = newChoice; break;
			case newChoice: menuChoice_ = loadChoice; chime.play(); break;
			case loadChoice: menuChoice_ = exitChoice; chime.play(); break;
			}
		}
		else if (event.type == sf::Event::MouseMoved) {
			//if (event.mouseMove.x >= 755 && event.mouseMove.x <= 975) {
			//	if (event.mouseMove.y >= 335 && event.mouseMove.y <= 383)
			if (getMouseX() >= 765 && getMouseX() <= 985) {
				if (getMouseY() >= 355 && getMouseY() <= 403) {
					if (menuChoice_ != newChoice)
						chime.play();
					menuChoice_ = newChoice;
				}
			}
			if (getMouseX() >= 765 && getMouseX() <= 865) {
				if (getMouseY() >= 405 && getMouseY() <= 453) {
					if (menuChoice_ != loadChoice)
						chime.play();
					menuChoice_ = loadChoice;
				}
				else if (getMouseY() >= 455 && getMouseY() <= 503) {
					if (menuChoice_ != exitChoice)
						chime.play();
					menuChoice_ = exitChoice;
				}
			}
		}
		break;
	case intro:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = inGame;
		}
		break;
	case inGame:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = gameOver;
		}
		break;
	case gameOver:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = titleStart;
		}
	}
}

/************************************************
 * The loadAssets() function loads all the		*
 * resources needed by the Game object for		*
 * title screen, main menu, etc.				*
 ************************************************/
void Game::loadAssets() {
	// Load game images
	titleTexture.loadFromFile("..\\assets\\bg\\titlebg.png");
	introTexture.loadFromFile("..\\assets\\bg\\WIP.png");
	GOTexture.loadFromFile("..\\..\\assets\\bg\\gameover.png");
	cursorTexture.loadFromFile("..\\assets\\sprites\\cursor.png");
	// Load game music
	titleMusic.openFromFile("..\\assets\\music\\Together.ogg");
	introMusic.openFromFile("..\\assets\\music\\NowOrNever.ogg");
	gameOverMusic.openFromFile("..\\..\\assets\\music\\gameover.ogg");
	// Load game sounds
	chime.openFromFile("..\\assets\\sounds\\chime.ogg");
	// Load fonts
	chancery.loadFromFile("..\\assets\\chancery.ttf");


	// Set game images
	title.setTexture(titleTexture);
	title.setTextureRect(sf::IntRect(0, 0, 1280, 720));
	title.setOrigin(0, 0);
	title.setPosition(0, 0);
	title.setColor(sf::Color(255,255,255,0));

	introSprite.setTexture(introTexture);
	introSprite.setOrigin(0, 0);
	introSprite.setPosition(0, 0);

	GOimage.setTexture(GOTexture);
	GOimage.setOrigin(0, 0);
	GOimage.setPosition(0, 0);

	cursor.setTexture(cursorTexture);
	cursor.setOrigin(0, 0);
	cursor.setPosition(720, 340);
	cursor.setScale(sf::Vector2f(1.0 / 2.75, 1.0 / 2.75));

	gameTitle.setFont(chancery);
	gameTitle.setCharacterSize(80);
	gameTitle.setColor(sf::Color::White);
	gameTitle.setString("V-Novel");

	contGame.setFont(chancery);
	contGame.setCharacterSize(46);
	contGame.setColor(sf::Color(150, 150, 150, 255));
	contGame.setString("Continue");
	contGame.setPosition(760, 280);
	
	newGame.setFont(chancery);
	newGame.setCharacterSize(46);
	newGame.setColor(sf::Color::White);
	newGame.setString("New Game");
	newGame.setPosition(760, 330);
	
	loadGame.setFont(chancery);
	loadGame.setCharacterSize(46);
	loadGame.setColor(sf::Color::White);
	loadGame.setString("Load");
	loadGame.setPosition(760, 380);
	
	exitGame.setFont(chancery);
	exitGame.setCharacterSize(46);
	exitGame.setColor(sf::Color::White);
	exitGame.setString("Exit");
	exitGame.setPosition(760, 430);

}

void Game::checkMusic() {
	// Play title theme music
	if (titleMusic.getStatus() != sf::Music::Playing && (gameState_ == titleStart || gameState_ == titleScreen))
		titleMusic.play();
	else if (titleMusic.getStatus() == sf::Music::Playing && (gameState_ != titleStart && gameState_ != titleScreen))
		titleMusic.stop();
	// Play intro music
	if (introMusic.getStatus() != sf::Music::Playing && gameState_ == intro) {
		cout << introPlayed << endl;
		if (introPlayed == false)
			introMusic.play();
		introMusic.setLoop(false);
		introPlayed = true;
	}
	else if (introMusic.getStatus() == sf::Music::Playing && gameState_ != intro) {
		introPlayed = false;
		introMusic.stop();
	}
	// Play gameover music
	if (gameOverMusic.getStatus() != sf::Music::Playing && gameState_ == gameOver)
		gameOverMusic.play();
	else if (gameOverMusic.getStatus() == sf::Music::Playing && gameState_ != gameOver)
		gameOverMusic.stop();
}

void Game::update() {

	// Camera
	camera.setSize(sf::Vector2f(1280, 720));
	//camera.setCenter(640, 360);
	camera.zoom(1.0);
	window.setView(camera);

	// Updates for game logos
	if (gameState_ == logos) {
		counter++;
		if (counter > 240) {
			counter = 0;
			gameState_ = titleStart;
		}
	}

	// Update title screen animation
	if (gameState_ == titleStart || gameState_ == titleScreen) {
		if (bgCounter >= 80)
			bgCounter = 0;
		if (bgCounter < 19)
			title.setTextureRect(sf::IntRect(0, 0, 1280, 720));
		else if (bgCounter < 29)
			title.setTextureRect(sf::IntRect(0, 720 * 1, 1280, 720));
		else if (bgCounter < 39)
			title.setTextureRect(sf::IntRect(0, 720 * 2, 1280, 720));
		else if (bgCounter < 59)
			title.setTextureRect(sf::IntRect(0, 720 * 3, 1280, 720));
		else if (bgCounter < 69)
			title.setTextureRect(sf::IntRect(0, 720 * 2, 1280, 720));
		else if (bgCounter < 79)
			title.setTextureRect(sf::IntRect(0, 720 * 1, 1280, 720));
		bgCounter++;
	}

	if (gameState_ == titleStart) {
		if (counter > 242)
			counter = 0;
		gameTitle.setPosition(700, counter - 92);
		title.setColor(sf::Color(255, 255, 255, counter));
		counter++;
		if (counter == 242)
			gameState_ = titleScreen;
	}
	if (gameState_ == titleScreen) {
		if (counter != 0)
			counter = 0;
		title.setColor(sf::Color(255, 255, 255, 250));
		gameTitle.setPosition(700, 150);
		switch (menuChoice_) {
		case contChoice:
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::White);
			loadGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::White);
			break;
		case newChoice: 
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::Yellow);
			loadGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::White);
			cursor.setPosition(720, 340);
			break;
		case loadChoice: 
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::White);
			loadGame.setColor(sf::Color::Yellow);
			exitGame.setColor(sf::Color::White);
			cursor.setPosition(720, 390);
			break;
		case exitChoice: 
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::White);
			loadGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::Yellow);
			cursor.setPosition(720, 440);
			break;
		}

	}
	if (gameState_ == intro) {
		if (introMusic.getStatus() == sf::Music::Stopped)
			gameState_ = inGame;
	}
	if (gameState_ == gameOver) {

	}

}

void Game::render() {
	// Clear window of every image
	window.clear();
	// Update game before drawing
	update();

	// Render functions for other objects
	if (gameState_ == titleStart) {
		window.draw(title);
		window.draw(gameTitle);
	}
	else if (gameState_ == titleScreen) {
		window.draw(title);
		window.draw(gameTitle);
		window.draw(contGame);
		window.draw(newGame);
		window.draw(loadGame);
		window.draw(exitGame);
		window.draw(cursor);
	}
	else if (gameState_ == intro) {
		window.draw(introSprite);
	}
	else if (gameState_ == inGame) {

	}
	else if (gameState_ == gameOver) {
		window.draw(GOimage);
	}
	
	window.display();

}

bool Game::keyConfirmed(sf::Event &event) {
	return (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space));
}

int Game::getMouseX() {
	return window.mapPixelToCoords(getMousePos()).x;
}

int Game::getMouseY() {
	return window.mapPixelToCoords(getMousePos()).y;
}

sf::Vector2i Game::getMousePos() {
	return sf::Vector2i(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y);
}

/************************************************
 * Destructor ~Game() deletes any objects and	*
 * instances before the program shuts down.		*
 ************************************************/
Game::~Game() {

}