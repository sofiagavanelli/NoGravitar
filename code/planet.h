#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <vector>
#include <ctime>

#include "terrain.h"
#include "object.h"
#include "spaceship.h"



class planet {

public:

	planet(int nPianeti, int i);
	~planet();


	sf::Vector2f getPosition();   //ritorna il punto centrale del pianeta

	int getRaggio();

	void recharge();  //ricarica i proiettili dei bunker

	void update(spaceship& spaceShip, int& x);   //aggiorna i bunker e i tank del pianeta e controlla tutto quanto avviene all'interno del pianeta

	bool checkBunker();

	void draw(sf::RenderWindow& window);

	void collocateObjects();   //colloca gli oggetti (bunker e taniche) sul terreno

	void drawGround(sf::RenderWindow& window);   //disegna il terreno una volta che si è entrati in un pianeta




private:
	sf::CircleShape  pianeta;
	terrain ground;

	int raggio;

	std::vector<bunker*> bunkerVect;
	std::vector<tank> tankVect;
};
