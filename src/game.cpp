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
	window.create(sf::VideoMode(1280, 720), "V-Novel");
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);

	//window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	camera.setCenter(640, 360);

	gameState_ = titleStart;
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

	// Pressing escape closes the window
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape) {
			window.close();
		}

	// Switch statement controls what actions are done in each game state
	switch (gameState_) {
	case titleStart:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = titleScreen;
		}
		break;
	case titleScreen:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			switch (menuChoice_) {
			//case contChoice: gameState_ = intro; break;
			case newChoice: gameState_ = intro; break;
			case loadChoice: gameState_ = intro; break;
			case exitChoice: window.close(); break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)) {
			switch (menuChoice_) {
			//case newChoice: menuChoice_ = contChoice; break;
			case loadChoice: menuChoice_ = newChoice; break;
			case exitChoice: menuChoice_ = loadChoice; break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)) {
			switch (menuChoice_) {
			//case contChoice: menuChoice_ = newChoice; break;
			case newChoice: menuChoice_ = loadChoice; break;
			case loadChoice: menuChoice_ = exitChoice; break;
			}
		}
		/*else if (event.type == sf::Event::MouseMoved) {
			if (event.mouseMove.x >= 755 && event.mouseMove.x <= 975) {
				if (event.mouseMove.y >= 335 && event.mouseMove.y <= 383)
					menuChoice_ = newChoice;
			}
			if (event.mouseMove.x >= 755 && event.mouseMove.x <= 855) {
				if (event.mouseMove.y >= 385 && event.mouseMove.y <= 433)
					menuChoice_ = loadChoice;
				else if (event.mouseMove.y >= 435 && event.mouseMove.y <= 483)
					menuChoice_ = exitChoice;
			}
		}*/
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
	GOTexture.loadFromFile("..\\..\\assets\\bg\\gameover.png");
	cursorTexture.loadFromFile("..\\assets\\sprites\\cursor.png");
	// Load game music
	titleMusic.openFromFile("..\\assets\\music\\Together.ogg");
	introMusic.openFromFile("..\\assets\\music\\NowOrNever.ogg");
	gameOverMusic.openFromFile("..\\..\\assets\\music\\gameover.ogg");
	// Load fonts
	chancery.loadFromFile("..\\assets\\chancery.ttf");


	// Set game images
	title.setTexture(titleTexture);
	title.setOrigin(0, 0);
	title.setPosition(0, 0);
	title.setColor(sf::Color(255,255,255,0));

	GOimage.setTexture(GOTexture);
	GOimage.setOrigin(0, 0);
	GOimage.setPosition(0, 0);

	cursor.setTexture(cursorTexture);
	cursor.setOrigin(0, 0);
	cursor.setPosition(720, 345);

	gameTitle.setFont(chancery);
	gameTitle.setCharacterSize(80);
	gameTitle.setColor(sf::Color::White);
	gameTitle.setString("V-Novel");

	contGame.setFont(chancery);
	contGame.setCharacterSize(46);
	contGame.setColor(sf::Color(150, 150, 150, 255));
	contGame.setString("Continue");

	newGame.setFont(chancery);
	newGame.setCharacterSize(46);
	newGame.setColor(sf::Color::White);
	newGame.setString("New Game");

	loadGame.setFont(chancery);
	loadGame.setCharacterSize(46);
	loadGame.setColor(sf::Color::White);
	loadGame.setString("Load");

	exitGame.setFont(chancery);
	exitGame.setCharacterSize(46);
	exitGame.setColor(sf::Color::White);
	exitGame.setString("Exit");

}

void Game::checkMusic() {
	// Play title theme music
	if (titleMusic.getStatus() != sf::Music::Playing && (gameState_ == titleStart || gameState_ == titleScreen))
		titleMusic.play();
	else if (titleMusic.getStatus() == sf::Music::Playing && (gameState_ != titleStart && gameState_ != titleScreen))
		titleMusic.stop();
	// Play intro music
	if (introMusic.getStatus() != sf::Music::Playing && gameState_ == intro)
		introMusic.play();
	else if (introMusic.getStatus() == sf::Music::Playing && gameState_ != intro)
		introMusic.stop();
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
		if (counter == 242)
			counter = 0;
		title.setColor(sf::Color(255, 255, 255, 246));
		gameTitle.setPosition(700, 150);
		contGame.setPosition(760, 280);
		newGame.setPosition(760, 330);
		loadGame.setPosition(760, 380);
		exitGame.setPosition(760, 430);
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
			cursor.setPosition(720, 345);
			break;
		case loadChoice: 
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::White);
			loadGame.setColor(sf::Color::Yellow);
			exitGame.setColor(sf::Color::White);
			cursor.setPosition(720, 395);
			break;
		case exitChoice: 
			contGame.setColor(sf::Color(150, 150, 150, 255));
			newGame.setColor(sf::Color::White);
			loadGame.setColor(sf::Color::White);
			exitGame.setColor(sf::Color::Yellow);
			cursor.setPosition(720, 445);
			break;
		}

	}
	if (gameState_ == intro) {
		counter++;
		if (counter == 5880)
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
	else if (gameState_ == inGame) {

	}
	else if (gameState_ == gameOver) {
		window.draw(GOimage);
	}
	
	window.display();

}

/************************************************
 * Destructor ~Game() deletes any objects and	*
 * instances before the program shuts down.		*
 ************************************************/
Game::~Game() {

}