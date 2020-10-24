#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>


#include "bullet.h"
using namespace sf;

bullet::bullet() : direction(0, 0) {
	proiettile.setSize(sf::Vector2f(2, 2));
	proiettile.setFillColor(sf::Color::White);
}

bullet::bullet(sf::Vector2f dir) : bullet() {
	direction = dir;
}

bullet::~bullet()
{
}

void bullet::setPosition(sf::Vector2f newPos) {
	proiettile.setPosition(newPos);
}

sf::Vector2f bullet::getPosition() {
	return(sf::Vector2f(proiettile.getPosition() + sf::Vector2f(1,1)));
}


void bullet::fire() {
	proiettile.move(direction);
}

void  bullet::fireDir(float x, float y) {         //imposta la direzione del proiettile quando viene sparato (in maniera dinamica)
	proiettile.move(x, y);
}

void bullet::fireSpeed(int speed) {             //se l'oggetto che spara è in movimento, i proiettili si muovono ad una velocità relativa 
	proiettile.move(direction.x * (4 + speed), direction.y * (4 + speed));        //alla velocità del'oggetto
}

void bullet::setDirection(sf::Vector2f dir) {
	direction = dir;
}

sf::Vector2f bullet::getDirection() {
	return this->direction;
}


void bullet::draw(sf::RenderWindow & window) {
	window.draw(proiettile);
}
