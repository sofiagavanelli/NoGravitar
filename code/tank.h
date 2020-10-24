#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "textBox.h"
#include "object.h"


class tank : public object {

public:
	tank();
	~tank();

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void rotate(float rotation);

	float getQuantity();

	void toEmpty();    //svuota il serbatoio quando la navicella lo prende

	void draw(sf::RenderWindow& window);


private:
	sf::RectangleShape serbatoio;
	float quantity;
	textBox testo;
	sf::Font font;
	int type;
};

