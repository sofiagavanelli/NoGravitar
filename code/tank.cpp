#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "tank.h"



tank::tank() : testo("F ") {
	serbatoio.setSize(sf::Vector2f(40, 15));
	serbatoio.setOutlineColor(sf::Color::Black);
	serbatoio.setFillColor(sf::Color(184, 183, 180));
	serbatoio.setOutlineThickness(1.0);
	testo.setSize(14);
	testo.setColor(sf::Color::Black);

	this->type = rand() % 2;
	if (type == 0) {
		quantity = 10;
		testo.updateText(" F 2L");
	}
	else {
		quantity = 20;
		testo.updateText(" F 4L");
	}
}

tank::~tank()
{
}

void tank::setPosition(sf::Vector2f pos) {
	serbatoio.setPosition(sf::Vector2f(pos.x, pos.y - 15));
	testo.setPosition(serbatoio.getPosition());
}

sf::Vector2f tank::getPosition() {
	return(serbatoio.getPosition() + sf::Vector2f(20,0));   //ritorna il punto centrale dell'oggetto
}

void tank::rotate(float rotation) {
	serbatoio.setRotation(rotation);
	testo.rotate(rotation);
}

float tank::getQuantity() {
	return(quantity);
}

void tank::toEmpty() {
	serbatoio.setFillColor(sf::Color::Black);
	testo.setColor(sf::Color::White);
	serbatoio.setOutlineColor(sf::Color::White);
	quantity = 0;
}

void tank::draw(sf::RenderWindow& window) {
	window.draw(serbatoio);
	testo.draw(window);
}