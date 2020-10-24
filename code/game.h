#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "spaceship.h"
#include "planet.h"

using namespace std;

class game
{
public:
	game(sf::RenderWindow& gameWindow);
	~game();
	int run(sf::RenderWindow& gameWindow);

private:
	bool processEvents(sf::RenderWindow& gameWindow);  //gestisce i comandi impartiti dal giocatore sulla navicella
	bool update(sf::RenderWindow& gameWindow);
	void render(sf::RenderWindow& gameWindow);

	void newSolarSystem();

private:
	sf::View view;

	spaceship spaceShip;

	int points;
	textBox score;

	int nPianeti;
	std::vector<planet> pianetiVect;

	std::vector<sf::CircleShape> stelleVect;

	int isInside;    //variabile che indica in quale pianeta si trova la navicella, all'inizio � fuori da tutti i pianeti (inizializzata a -1)


	sf::Clock clock;
	sf::Time time;

	bool alive;
	bool close;
	bool pausa;
	int planetsLeft; //tiene conto dei pianeti ancora "in vita"

	textBox Tpausa = textBox(std::string("~ PAUSE ~"));
	textBox Treplay = textBox(std::string("PRESS P TO CONTINUE"));

	textBox Tcomplimenti = textBox(std::string("WELL DONE! YOU DESTROYED THE FIRST SOLAR SYSTEM\n\t\t\t\tPRESS ENTER TO CONTINUE"));
};

