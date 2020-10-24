#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "bullet.h"
#include "object.h"


class bunker : public object {

public:
	bunker();
	~bunker();

	virtual void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	int getSizeX();

	void rotate(float rotation);

	virtual void recharge();    //ricarica il vettore dei proiettili
	std::vector<bullet> getBullets();

	void eraseBullet(int i);

	bool update(sf::Vector2f(pos));  //aggiorna il vettore dei proiettili e ritorna true se uno di essi colpisce la navicella

	virtual void draw(sf::RenderWindow& window);

	void activate(bool isActive);   //attiva il bunker se la navicella è abbastanza vicina

	void decreaseLife();

	bool isAlive();

    int getLifePoints();

protected:
	sf::RectangleShape forte;
	int value;
	int puntiVita;
	bool firing;
	std::vector<bullet> bulletVect;
};


//sottoclassi della classe bunker

class blueBunker : public bunker
{

public:
	blueBunker();
	void recharge();
	void draw(sf::RenderWindow& window);

private:
	int direction[2];
};


class yellowBunker : public bunker
{
public:
	yellowBunker();
	void recharge();
	void draw(sf::RenderWindow& window);
private:
	int direction[3];
};


class redBunker : public bunker
{

public:
	redBunker();
	void draw(sf::RenderWindow& window);
	void recharge();
};

