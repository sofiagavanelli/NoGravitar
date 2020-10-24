#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bunker.h"


bunker::bunker() {
	forte.setSize(sf::Vector2f(40, 20));
	forte.setFillColor(sf::Color(168, 80, 50));
	forte.setOrigin(forte.getPosition() + sf::Vector2f(20, 10));
	puntiVita = 25;
	value = 70;
	firing = false;
}


bunker::~bunker()
{
}

void bunker::setPosition(sf::Vector2f pos) {
	forte.setPosition(sf::Vector2f(pos.x, pos.y - 10));
}

sf::Vector2f bunker::getPosition() {
	return(sf::Vector2f(this->forte.getPosition().x, this->forte.getPosition().y));
}


int bunker::getSizeX() {
	return(forte.getSize().x);
}

void bunker::rotate(float rotation) {
	forte.setRotation(rotation);
}

void bunker::recharge() {
	bullet newBullet;
	newBullet.setPosition(this->getPosition());
	bulletVect.push_back(newBullet);
}

std::vector<bullet> bunker::getBullets() {
	return(bulletVect);
}

void bunker::eraseBullet(int i) {
	if (i < bulletVect.size())
		bulletVect.erase(bulletVect.begin() + i);
}

bool bunker::update(sf::Vector2f(pos)) {

	bool colpito = false;

	for (int i = 0; i < bulletVect.size(); i++) {

		float dist = sqrt(pow(pos.x - bulletVect[i].getPosition().x, 2) + pow(pos.y - bulletVect[i].getPosition().y, 2));

		if (dist < 20) {          //se i proiettili colpiscono la navicella la funzione restituisce true
			bulletVect.erase(bulletVect.begin() + i);      //e i proiettili vengono eliminati
			colpito = true;
		}

		else if (bulletVect[i].getPosition().y < this->getPosition().y - 600)    //ad una certa distanza dal bunker da quale sono stati
			bulletVect.erase(bulletVect.begin() + i);                       //sparati i proiettili vengono eliminati

	}

	return(colpito);
}

void bunker::draw(sf::RenderWindow & window) {
	window.draw(forte);
}


void bunker::activate(bool isActive) {
	this->firing = isActive;
}


void bunker::decreaseLife() {
	if (puntiVita >= 1) {
		puntiVita -= 2;
	}
}

bool bunker::isAlive() {
	return(puntiVita > 0);
}

int bunker::getLifePoints() {
	return(this->value);
}


//SUBCLASS BLUEBUNKER

blueBunker::blueBunker() : bunker()
{
	forte.setFillColor(sf::Color(67, 67, 240));
	direction[0] = rand() % 6 - 6; direction[1] = rand() % 6;
}

void blueBunker::draw(sf::RenderWindow& window) {
	bunker::draw(window);
	if (!bulletVect.empty()) {
		for (int i = 0; i < bulletVect.size(); i++) {
			if (firing) {
				bulletVect[i].draw(window);
				bulletVect[i].fire();
			}
		}
	}
}

void blueBunker::recharge() {
	for (int i = 0; i < 2; i++) {
		bullet newBullet(sf::Vector2f(direction[i], -6));
		newBullet.setPosition(this->getPosition());
		bulletVect.push_back(newBullet);
	}
}
/***************************************/


/**************************/
//SUBCLASS YELLOWBUNKER
/*************************/

yellowBunker::yellowBunker() : bunker()
{
	forte.setFillColor(sf::Color(240, 202, 67));
	direction[0] = rand() % 2 - 4;
	direction[1] = rand() % 3 - 1;
	direction[2] = rand() % 2 + 4;
	value = 80;
}


void yellowBunker::draw(sf::RenderWindow& window) {
	bunker::draw(window);
	if (!bulletVect.empty()) {
		for (int i = 0; i < bulletVect.size(); i++) {
			if (firing) {
				bulletVect[i].draw(window);
				bulletVect[i].fire();
			}
		}
	}
}

void yellowBunker::recharge() {
	for (int i = 0; i < 3; i++) {
		bullet newBullet(sf::Vector2f(direction[i], -4));
		newBullet.setPosition(this->getPosition());
		bulletVect.push_back(newBullet);
	}
}

/****************************************************/



/**********************/
//SUBCLASS REDBUNKER
/**********************/

redBunker::redBunker() : bunker()
{
	forte.setSize(sf::Vector2f(60, 20));
	forte.setFillColor(sf::Color(230, 80, 30));
	forte.setOrigin(forte.getPosition() + sf::Vector2f(30, 10));
	puntiVita = 30;
	value = 100;
	firing = false;
}


void redBunker::draw(sf::RenderWindow& window) {

	bunker::draw(window);

	sf::View view = window.getView();

	if (!bulletVect.empty()) {
		for (int i = 0; i < bulletVect.size(); i++) {
			if (firing) {
				bulletVect[i].draw(window);

				float dirX = -this->getPosition().x + view.getCenter().x;
				float dirY = -this->getPosition().y + view.getCenter().y;
				bulletVect[i].fireDir(dirX / 10, dirY / 10);
			}
		}
	}
}

void redBunker::recharge() {
	bunker::recharge();
}

/*************************************/