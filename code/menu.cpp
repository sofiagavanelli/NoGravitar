#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

#include "menu.h"

#define NSTELLE 1000

menu::menu()
	: gameWindow({ 1280, 720 }, "NonGravitar")
{
	loadTexts();

	for (int i = 0; i < NSTELLE; i++) {
		int x = -1, y = -1;
		bool isOutside;
		do {
			isOutside = true;
			x = rand() % 1280;
			y = rand() % 720;

		} while (!isOutside);

		sf::CircleShape stella;
		stelleVect.push_back(stella);
		stelleVect[i].setPosition(x, y);
		stelleVect[i].setRadius(0.25);
		stelleVect[i].setFillColor(sf::Color::Black);
		stelleVect[i].setOutlineColor(sf::Color(89, 89, 89));
		stelleVect[i].setOutlineThickness(1);
	}

	loadRanking();

	showMenu = false;
	nameEntered = false;
	play = false;
	gameOver = false;
	closeWindow = false;
	showInst = false;
	ranking = false;
	gameReturn = 0;
	puntiCorrenti = 0;
	character = 0;

	gameWindow.setPosition({ gameWindow.getPosition().x,0 });
	gameWindow.setFramerateLimit(60);

	gameView = gameWindow.getView();
}

menu::~menu()
{
}

const sf::RenderWindow& menu::getWindow() {
	return(gameWindow);
}

void menu::draw() {

	while (gameWindow.isOpen()) {

		gestisciEventi();
		aggiorna();
		display();

	}

}


void menu::aggiorna() {

	if (play) {
		initialize();
	}
	else if (closeWindow)
		closeGame(gameWindow);
	else display();

}

void menu::gestisciEventi() {
    
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		switch (event.type) {

		case sf::Event::TextEntered:
			if (event.text.unicode < 128 && event.text.unicode != 13)
			{
				if (event.text.unicode != 8) {
					playerInput += event.text.unicode;
					character++;
				}
				else {
				    if(character >= 1 ) {
					    playerInput.erase(character - 1, 1);
					    character--;
				    }
				}

				playerName.updateText(playerInput);
			}

			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::I && !gameOver)
				showInst = true;
			else if (event.key.code == sf::Keyboard::Return) {
				if (gameOver && !ranking && nameEntered) {
					ranking = true;
				}
				else if (gameOver && ranking) {
					showMenu = true;
				}
				if (gameOver && !nameEntered) {
					nomeCorrente = playerInput;
					nameEntered = true;
					createRank();
				}
				else if (!gameOver) {
					showMenu = false;
					play = true;
					showInst = false;
				}
                character = 0;
			};
			break;

		case sf::Event::KeyReleased:

			break;

		case sf::Event::Closed:
			saveRank();
			closeGame(gameWindow);

			break;
		}

	}

}

void menu::closeGame(sf::RenderWindow& gameWindow) {

	gameWindow.close();

}

void menu::initialize() {

	game game(gameWindow);
	gameReturn = game.run(gameWindow);
	if (gameReturn == -1) { 
	//se il return è -1 vuol dire che il gioco si è interrotto 
	//perché l'utente ha chiuso la finestra quindi viene chiamata la funzione di chiusura 
	//della finestra modificando il bool che ne gestisce la chiamata -> il gioco va concluso

		play = false;
		closeWindow = true;
	}
	else { 
	//se il return non è -1 allora vuol dire che il return contiene i punti e il
	//gioco si è concluso perché l'utente ha finito le vite o il fuel

		play = false;

		playerName.updateText("");
		playerInput = "";

		puntiCorrenti = gameReturn;

		gameOver = true;
	}

}

void menu::display() {
	gameWindow.clear();

	//ISTRUZIONI:
	if (!play && showInst && !gameOver && !closeWindow && !ranking) {

		gameWindow.clear();

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		allTB[6].setTitle(50);
		allTB[6].setPosition(sf::Vector2f(380, 120));
		allTB[6].draw(gameWindow);

		for (int i = 7; i < 13; i++) {
			allTB[i].setSize(35);
			if (i == 12)  allTB[i].setPosition(sf::Vector2f(380, 550));
			else allTB[i].setPosition(sf::Vector2f(380, i * 35));
			allTB[i].draw(gameWindow);
		}

		gameWindow.display();
	}

	//MENU PRINCIPALE:
	else if ((!play && !showInst && !gameOver && !closeWindow && !ranking) || showMenu) { 
	//non sta giocando e non ha perso: viene mostrato il menù principale

		gameWindow.clear();

		gameWindow.setView(gameView);

		if (gameOver) {
			nameEntered = false;
			gameOver = false;
			ranking = false;
		}

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		allTB[0].setTitle(125);
		allTB[0].setPosition(sf::Vector2f(270, 200));
		allTB[0].draw(gameWindow);
		allTB[1].setSize(30);
		allTB[1].setPosition(sf::Vector2f(370, 360));
		allTB[1].draw(gameWindow);

		allTB[12].setSize(30);
		allTB[12].setPosition(sf::Vector2f(490, 390));
		allTB[12].draw(gameWindow);

		gameWindow.display();
	}

	//MESSAGGIO DI GAME OVER:
	else if (!play && gameOver && !ranking) { 
	//non sta giocando perché ha perso: viene mostrato "game over" e il
	//punteggio ottenuto nella partita -> dà la possibilità di iniziare una nuova partita

		gameWindow.setView(gameView);

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		allTB[3].setTitle(95);
		allTB[3].setPosition(sf::Vector2f(220, 140));
		allTB[3].draw(gameWindow);

		allTB[2].setSize(30);
		allTB[2].setPosition(sf::Vector2f(320, 350));
		allTB[2].draw(gameWindow);

		if (nameEntered) {
			allTB[12].setSize(30);
			allTB[12].setPosition(sf::Vector2f(520, 480));
			allTB[12].draw(gameWindow);
		}

		allTB[5].setTitle(40);
		allTB[5].updateText(std::string("SCORE " + std::to_string(gameReturn)));
		allTB[5].setPosition(sf::Vector2f(390, 250));
		allTB[5].draw(gameWindow);

		playerName.setSize(35);
		playerName.setPosition(sf::Vector2f(390, 390));
		playerName.draw(gameWindow);

		gameWindow.display();

	}

	//CLASSIFICA:
	else if (ranking) {

		gameWindow.clear();

		gameWindow.setView(gameView);

		for (int i = 0; i < stelleVect.size(); i++) {
			gameWindow.draw(stelleVect[i]);
		}

		allTB[13].setTitle(70);
		allTB[13].setPosition(sf::Vector2f(400, 120));
		allTB[13].draw(gameWindow);

		for (int i = 0; i < 5; i++) {
			utenti[i].setSize(30);
			utenti[i].setPosition(sf::Vector2f(460, 250 + i * 60));
			utenti[i].draw(gameWindow);
		}

		allTB[12].setPosition(sf::Vector2f(400, 570));
		allTB[12].draw(gameWindow);

		gameWindow.display();
	}
}


//ogni volta che finisce una partita riordina i cinque punteggi migliori
void menu::createRank() {

	bool created = false;

	int j = 4, n = 0;

	while (!created && n < 5) {
		if (puntiCorrenti > classifica[n].points && !created) {
			while (j > n) {
				classifica[j].name = classifica[j - 1].name;
				classifica[j].points = classifica[j - 1].points;
				j--;
			}
			classifica[n].points = puntiCorrenti;
			classifica[n].name = nomeCorrente;

			created = true;
		}
		else
			n++;
	}

	for (int k = 0; k < 5; k++) {
		utenti[k] = textBox(classifica[k].name + ": " + to_string(classifica[k].points));
    }

}

//salva la classifica su file - sovrascrive quella precedente
void menu::saveRank() {

	ofstream testo; //ofstream: per scrivere
	int i = 0;

	testo.open("../src/classifica.txt", ios::out);

	for (i = 0; i < 5; i++) {
		testo << classifica[i].name << "\n";
		testo << classifica[i].points << "\n";
	}

	testo.close();

}

//carica la classifica dal file
void menu::loadRanking() {

	ifstream testo; //ifstream: per leggere
	string x;
	int i = 0;

	testo.open("../src/classifica.txt", ios::in);

	for (i = 0; i < 5; i++) {

		getline(testo, x);
		classifica[i].name = x;
		getline(testo, x);
		//stoi(): da tipo string a tipo int
		classifica[i].points = stoi(x);

	}

	testo.close();
}


//carica il testo dei textBox dal file 
void menu::loadTexts() {

	ifstream testo;
	std::string x;
	int i = 0;

	testo.open("../src/texts.txt", ios::in);

	while (getline(testo, x)) {
	    x.resize(x.size()-1) ;
		allTB[i] = textBox(x);
		i++;
	}

	testo.close();
}
