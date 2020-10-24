#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "bullet.h"
#include "textBox.h"



class spaceship
{

public:

	spaceship();            //constructor - design spaceShip
	~spaceship();

	void handleEvents(sf::Keyboard::Key key, bool isPressed);   //controls player's inputs

	bool move(sf::View view);     //moving spaceShip - return a boolean tha specifies if spaceship is actually moving

	void setPosition(sf::Vector2f newPos);           //change spaceShip position

	sf::Vector2f getPosition();   //ritorna il punto centrale della navicella

	float getRotation();     //ritorna la rotazione della navicella rispetto all'asse x

	void recharge();

	void update();

	void draw(sf::RenderWindow& window);


	int getLives();
	void setLives(int n);

	void decreaseLives();          //decrementa le vite della navicella
	void decreaseLifePoints();     //decrementa la barra della vita 

	bool decreaseFuel();            //diminuisce la quantit� di carburante in relazione al tempo trascorso
	void increaseFuel(float x);    //aumenta il carburante di un valore x uguale alla quantit� contenuta nel serbatoio raccolto


	bool isActive();   //ritorna true se � attivo il raggio traente

	void disactivate();     //disattiva il raggio traente

	void setRaggio(float y1, float y2);      //setta il raggio traente della lunghezza corretta, a seconda della distanza tra navicella e terreno

	sf::Vector2f getFirePoint();             //setta il firing point in basso e al centro

	std::vector<bullet> getBullets();

	void eraseBullet(int i);         //delete bullets when they touch the ground

private:
	sf::ConvexShape   Navicella;

	std::vector<bullet> bulletVect;
	
	sf::Vector2f direction;

	bool IsMoving;
	bool IsAccelerating;
	bool IsRotatingL;
	bool IsRotatingR;

	bool IsFiring;
	sf::Vector2f firePoint;


	lifeValue puntiVita;        
	fuelValue carburante;

	bool raggioT;      //raggio traente
	sf::RectangleShape line1, line2;  //linee che delimitano il raggio traente

};
