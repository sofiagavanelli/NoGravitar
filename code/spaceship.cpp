#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>

#include "spaceship.h"
#include "game.h"

#define PI 3.14159265

spaceship::spaceship() : carburante() {      //design spaceShip

	double
		X[30] = { 0, 3, 7, 11, 5, 18, 25, 11, 5, 18, 25, 30, 34, 37, 39, 41, 39, 37, 34, 30, 25, 18, 5, 11, 25, 18, 5, 11, 7, 3 },
		Y[30] = { 18, 23, 23, 28, 33, 35, 28, 28, 33, 35, 28, 25, 23, 21, 20, 18, 16, 15, 13, 11, 8, 1, 3, 8, 8, 1, 3, 8, 13, 13 };


	Navicella.setPointCount(30);

	for (int i = 0; i < 30; i++) {
		Navicella.setPoint(i, sf::Vector2f(X[i], Y[i]));
	}

	Navicella.setFillColor(sf::Color::Black);
	Navicella.setOutlineThickness(2);
	Navicella.setOutlineColor(sf::Color(0, 184, 194));
	Navicella.setPosition(sf::Vector2f(640, 50));

	Navicella.scale(sf::Vector2f(1.1, 1.1));

	float originX = (Navicella.getPoint(15).x - Navicella.getPoint(0).x)/2;
	float originY = Navicella.getPoint(15).y ;
	Navicella.setOrigin(sf::Vector2f(originX, originY));

	firePoint = Navicella.getPoint(15);
	
	direction = sf::Vector2f(0, 0);

	IsMoving = false;
	IsAccelerating = false;
	IsFiring = false;
	IsRotatingL = false;
	IsRotatingR = false;
	raggioT = false;

	line1.setSize(sf::Vector2f(2, 80)); line2.setSize(sf::Vector2f(2, 80));
	line1.setFillColor(sf::Color(255, 153, 102)); line2.setFillColor(sf::Color(255, 153, 102));
	line1.setRotation(10); line2.setRotation(-10);

}

spaceship::~spaceship()
{
}


void spaceship::handleEvents(sf::Keyboard::Key key, bool isPressed) {

	if (key == sf::Keyboard::Down)
		IsMoving = isPressed;
	else if (key == sf::Keyboard::Up)
		IsAccelerating = isPressed;
	else if (key == sf::Keyboard::Right)
		IsRotatingR = isPressed;
	else if (key == sf::Keyboard::Left)
		IsRotatingL = isPressed;
	else if (key == sf::Keyboard::Space)
		IsFiring = isPressed;
	else if (key == sf::Keyboard::Tab)
		raggioT = isPressed;

}

bool spaceship::move(sf::View view) {

	sf::Vector2f dir(0.f, 0.f);

	if (IsMoving) {
		dir.x = direction.x * 4;
		dir.y = direction.y * 4;
	}

	if (IsAccelerating) {
		dir.x = direction.x * 6;
		dir.y = direction.y * 6;
	}

	if ((IsRotatingL)) {
		Navicella.rotate(-2);
	}

	if ((IsRotatingR)) {
		Navicella.rotate(2);
	}

	Navicella.move(dir);   //muove la navicella nella direzione impostata

	return(IsMoving || IsAccelerating);  
}

void spaceship::setPosition(sf::Vector2f newPos) {
	Navicella.setPosition(newPos);
}

sf::Vector2f spaceship::getPosition() {
	return(Navicella.getPosition());
}

float spaceship::getRotation() {
	return(Navicella.getRotation());
}


void spaceship::recharge() {
	if (IsFiring) {
		bullet newBullet(direction);
		newBullet.setPosition(this->getFirePoint());
		bulletVect.push_back(newBullet);
	}
}

void spaceship::update() {

	direction = sf::Vector2f(cos(Navicella.getRotation()*PI / 180), sin(Navicella.getRotation()*PI / 180));
	firePoint = sf::Vector2f(Navicella.getPosition().x + 22 * direction.x, Navicella.getPosition().y + 22 * direction.y);

	for (int i = 0; i < bulletVect.size(); i++) {                           //ad una certa distanza dalla navicella i proiettili vengono eliminati
		if (sqrt(pow(bulletVect[i].getPosition().x - Navicella.getPosition().x, 2) + pow(bulletVect[i].getPosition().y - Navicella.getPosition().y, 2)) > 800) 
			bulletVect.erase(bulletVect.begin() + i);
	}

	if (raggioT) {                                     //se attivo, setta appropriatamente il raggio traente
		line1.setPosition(this->getFirePoint());
	    line2.setPosition(this->getFirePoint());    
	}

}


void spaceship::draw(sf::RenderWindow & window) {

	window.draw(Navicella);

	puntiVita.draw(window);
	carburante.draw(window, sf::Vector2f(570, 280));

	if (raggioT) {                 //se il raggio traente è attivo lo disegna
		window.draw(line1);
		window.draw(line2);
	}

	for (int i = 0; i < bulletVect.size(); i++) {
		bulletVect[i].draw(window);
		int speed = 0;
		if (IsMoving) speed = 4;
		if (IsAccelerating) speed = 6;
		bulletVect[i].fireSpeed(speed);
	}

}


int spaceship::getLives() {
	return puntiVita.getLives();
}

void spaceship::setLives(int n) {
	puntiVita.setLives(n);
}

void spaceship::decreaseLives() {
	puntiVita.decreaseLives();
	puntiVita.setSize(80);
}


void spaceship::decreaseLifePoints() {

	if (puntiVita.getLives() >= 0) {
		if (puntiVita.getSize() > 0) {
			this->puntiVita.decrease(0.5);
		}
		else {
			this->decreaseLives();
			puntiVita.setSize(80);
		}
	}
}

bool spaceship::decreaseFuel() {
	return(carburante.decrease(0.04));  //ritorna false se il carburante è finito
}

void spaceship::increaseFuel(float x) {
	carburante.increase(x);
}


bool spaceship::isActive() {
	return(raggioT);
}

void spaceship::disactivate() {
	raggioT = false;
}

void spaceship::setRaggio(float y1, float y2) {
	line1.setSize(sf::Vector2f(2, y1));
	line2.setSize(sf::Vector2f(2, y2));
}

sf::Vector2f spaceship::getFirePoint() {
	return(firePoint);
}

std::vector<bullet> spaceship::getBullets() {
	return(bulletVect);
}

void spaceship::eraseBullet(int i) {
	if (i < bulletVect.size())
		bulletVect.erase(bulletVect.begin() + i);
}

