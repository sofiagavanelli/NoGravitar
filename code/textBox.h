#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

class textBox {

public:

	textBox(std::string txt);
	textBox();
	~textBox();

	void updateText(std::string txt);    //aggiorna il testo contenuto nel textbox

	void drawRelative(sf::RenderWindow& window, sf::Vector2f pos);    //disegna i textBox che si muovono con la vista, in relazione a quest'ultima
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f(pos));
	void setSize(int size);
	void setColor(sf::Color color);
	void setTitle(int grandezza);
	void setFont();
	void rotate(double rotation);

protected:
	sf::Text text;
	sf::Font font;
};


/************************************************
   sottoclasse per i parametri vitali
   ************************************************/

class textValues : public textBox {

public:
	textValues();
	~textValues();


	void increase(float x);  //incrementa la lunghezza della barra

	bool decrease(float x);  //decrementa la lunghezza della barra

	float getSize();

	void setSize(float x);

	virtual void draw(sf::RenderWindow& window, sf::Vector2f pos);

protected:

	sf::RectangleShape barValue;
	sf::RectangleShape boundary;
};


/************************************************
   sottoclasse che regola la gestione del carburante
   ************************************************/

class fuelValue : public textValues {

public:
	fuelValue();

	void draw(sf::RenderWindow& window, sf::Vector2f pos);

};


/************************************************
   sottoclasse che regola la gestione della vita
   ************************************************/

class lifeValue : public textValues {

public:
	lifeValue();

	int getLives();  //ritorna il numero di vite ancora disponibili
	void setLives(int n);

	void decreaseLives();  //decremta di uno il numero delle vite

	void draw(sf::RenderWindow& window);

private:

	int livesLeft;
	sf::ConvexShape lives;

};