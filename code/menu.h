#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"



class menu
{
public:
	menu();
	~menu();

	void draw();
	void initialize();
	void gestisciEventi();
	void aggiorna();
	void display();
	void closeGame(sf::RenderWindow& gameWindow);

	const sf::RenderWindow& getWindow();

	void createRank();
	void saveRank();

	void loadTexts();
	void loadRanking();

private:

	struct player {
		string name;
		int points;
	};

	textBox playerName = textBox();
	int i = 0;
	string playerInput;

	player classifica[5];

	sf::RenderWindow gameWindow;
	sf::View gameView;

	std::vector<sf::CircleShape> stelleVect;

	bool play;
	bool showInst;
	bool gameOver;
	bool closeWindow;
	bool nameEntered;
	bool showMenu;
	bool ranking;
	int gameReturn;

	string nomeCorrente;
	int puntiCorrenti;
    int character;
    
	textBox allTB[14];
	textBox utenti[5];

};
