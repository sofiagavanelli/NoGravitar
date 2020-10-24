#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <cmath>

#include "planet.h"



planet::planet(int nPianeti, int nCorrente) : ground(nCorrente) {

	raggio = (rand() % 16 + 31);
	this->ground.initTerrain(raggio);
	pianeta.setRadius((float)raggio);
	pianeta.setFillColor(sf::Color::Black);
	pianeta.setOutlineColor(sf::Color::White);
	pianeta.setOutlineThickness(2);

	auto posX = nCorrente * (1280 / nPianeti) + rand() % ((1280 / nPianeti - raggio * 2) - 20) + 10;
	auto posY = (rand()*nCorrente) % 510 + 120;

	pianeta.setPosition(posX, posY);

	int x = (raggio - 20);

	for (int i = 0; i < (x / 3); i++) {  //creates bunkers' vector
		bunker* newBunker;
		if (rand() % 3 == 0)  newBunker = new redBunker;
		else if (rand() % 3 == 1) newBunker = new yellowBunker;
		else  newBunker = new blueBunker;
		bunkerVect.push_back(newBunker);
	}

	for (int i = 0; i < (x / 5); i++) {   //creates tanks' vector
		tank newTank;
		tankVect.push_back(newTank);
	}

	this->collocateObjects();  
}

planet::~planet()
{
}


sf::Vector2f planet::getPosition() {
	return(pianeta.getPosition() + sf::Vector2f(raggio,raggio));
}

int planet::getRaggio() {
	return raggio;
}


void planet::recharge() {
	for (int i = 0; i < bunkerVect.size(); i++) {
		bunkerVect[i]->recharge();                           //ricarica il vettore proiettili del bunker
	}
}


void planet::update(spaceship& spaceShip, int& points) {

	for (int i = 0; i < tankVect.size(); i++) {

		if ((fabsf(spaceShip.getFirePoint().x - (tankVect[i].getPosition().x )) < 30) && (spaceShip.isActive())) {
			spaceShip.increaseFuel(tankVect[i].getQuantity());    
			tankVect[i].toEmpty();
		}
	}

	std::vector<bullet> bulletSpaceship = spaceShip.getBullets();


	if (!bulletSpaceship.empty()) {                             //controlla le collisioni dei proiettili, sparati dalla navicella, con il terreno
		for (int i = 0; i < bulletSpaceship.size(); i++) {
			if (ground.collision(bulletSpaceship[i].getPosition()) < 5)  spaceShip.eraseBullet(i);
		}
	}

	//controlla le collisioni della navicella e del raggio traente

	float h = ground.collision(spaceShip.getPosition());
	if (h < 20) {
		spaceShip.decreaseLives();                //se la navicella tocca il terreno, vengono decrementate le vite 
		spaceShip.setPosition(sf::Vector2f(spaceShip.getPosition().x, spaceShip.getPosition().y - 200));    //e la navicella viene riposizionata più in alto
	}

	if (h > 250 || (spaceShip.getRotation() < 10) || (spaceShip.getRotation() > 170)) spaceShip.disactivate();   //sopra a una certa altezza non è possibile attivare il raggio traente
	else {
		float posRl = 40; float posRr = 40;        //setta il raggio traente della lunghezza  opportuna
		posRl = ground.collision(sf::Vector2f(spaceShip.getFirePoint().x - h / 5.6713, spaceShip.getFirePoint().y));
		posRr = ground.collision(sf::Vector2f(spaceShip.getFirePoint().x + h / 5.6713, spaceShip.getFirePoint().y));
		spaceShip.setRaggio(posRl, posRr);
	}
	//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

	for (int i = 0; i < bunkerVect.size(); i++) {

		if (abs(bunkerVect[i]->getPosition().x - spaceShip.getPosition().x) < 250) {
			bunkerVect[i]->activate(true);   //attiva i bunker se la navicella  si trova in loro prossimità
		}
		else bunkerVect[i]->activate(false);

		if (bunkerVect[i]->update(sf::Vector2f(spaceShip.getPosition())))  spaceShip.decreaseLifePoints();

		int x = i;

		for (int i = 0; i < bulletSpaceship.size(); i++) {
			if ((abs(bulletSpaceship[i].getPosition().x - bunkerVect[x]->getPosition().x) < bunkerVect[x]->getSizeX() / 2) && 
				abs(bulletSpaceship[i].getPosition().y - bunkerVect[x]->getPosition().y) < 10) {
				//se i proiettili della navicella colpiscono un bunker, decrementa i punti vita del bunker
				bunkerVect[x]->decreaseLife();
				spaceShip.eraseBullet(i);
			}
		}

		std::vector<bullet> bulletBunker = bunkerVect[i]->getBullets();

		for (int j = 0; j < bulletBunker.size(); j++) {
			if (ground.collision(bulletBunker[j].getPosition()) < 2)  bunkerVect[i]->eraseBullet(j);
		}

		if (!bunkerVect[i]->isAlive()) {                      //per ogni bunker controlla che sia ancora in vita, altrimenti lo elimina
			points = points + bunkerVect[i]->getLifePoints();
			bunkerVect.erase(bunkerVect.begin() + i);
		}
	}
}

bool planet::checkBunker() {
	if (!bunkerVect.empty())  return false;
	else return true;   //ritorna true se tutti i bunker sono stati distrutti
}


void planet::draw(sf::RenderWindow & window) {
	window.draw(pianeta);
}


void planet::collocateObjects() {                      //inserisce bunker e taniche in un unico vettore in maniera casuale
	                                                    //e poi li colloca sul terreno
	std::vector<object*> objects;

	int j = bunkerVect.size() + tankVect.size();
	int b = 0; int t = 0; int i = 0;
	while (i < j && b < bunkerVect.size() && t < tankVect.size()) {
		if (rand() % 2 == 0) {
			objects.push_back(bunkerVect[b]);
			b++;
		}
		else {
			objects.push_back(&tankVect[t]);
			t++;
		}
		i++;
	}
	while (b < bunkerVect.size()) {
		objects.push_back(bunkerVect[b]);
		b++;
	}
	while (t < tankVect.size()) {
		objects.push_back(&tankVect[t]);
		t++;
	}
	ground.setObject(objects);      
}

void planet::drawGround(sf::RenderWindow& window) {

	ground.draw(window);

	if (!bunkerVect.empty()) {

		for (int i = 0; i < bunkerVect.size(); i++) {
			bunkerVect[i]->draw(window);     //disegna i bunker con i relativi proiettili 
		}
	}

	for (int i = 0; i < tankVect.size(); i++) {
		tankVect[i].draw(window);
	}
}



