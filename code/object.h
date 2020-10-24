#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

//classe astratta per la gestione degli oggetti sul terreno

class object {

public:

	virtual sf::Vector2f getPosition() { return (sf::Vector2f(1, 1)); };

	virtual void setPosition(sf::Vector2f pos) {};

	virtual void rotate(float rotation) {};

};