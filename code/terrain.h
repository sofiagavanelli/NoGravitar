#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "bunker.h"
#include "tank.h"
#include "textBox.h"
#include "object.h"


class terrain {

public:
	terrain(int nPianeta);
	~terrain();

	void initTerrain(int size);           //inizializza il terreno impostandone i punti in maniera randomica

	int getSize();                      //ritorna la lunghezza (eq. raggio) del pianeta

	void setObject(std::vector<object*> objVect);   //posiziona i vari oggetti sulla linea del terreno

	void draw(sf::RenderWindow& window);

	float collision(sf::Vector2f pos);           //restituisce la distanza tra l'ordinata in input e il terreno sottostante

	void setFlag();             //posiziona i "cartelli" che identificano un pianeta

private:
	sf::VertexArray ground;
	int size;

	std::vector<sf::RectangleShape> rectVect;
	std::vector<sf::ConvexShape> convexShape;
	std::vector<textBox> pianeta;

};
