#include <stdio.h>
#include <random>
#include <cmath>
#include "terrain.h"

#define PI 3.14159265

terrain::terrain(int nPianeta){
	size = 50;
	
	for (int i = 0; i < 2; i++) {
		textBox planet =  textBox("PLANET " + std::to_string(nPianeta));
		pianeta.push_back(planet);
	}
}

terrain::~terrain()
{
}


void terrain::initTerrain(int size) {
	this->size = size;
	ground.setPrimitiveType(sf::PrimitiveType::LineStrip);
	ground.resize(size);

	for (int i = 10; i < ground.getVertexCount() - 1; i++) {              //crea il terreno di lunghezza proporzionale al raggio del pianeta
		ground[i].position = sf::Vector2f(i * 128, rand() % 128 + 550);
		ground[i].color = sf::Color::Green;
	}
	ground[size - 1].position = sf::Vector2f(ground[10].position.x + (size - 10) * 128, ground[10].position.y);
	ground[size - 1].color = sf::Color::Green;

	for (int i = 0; i < 10; i++) {
		ground[i].position = sf::Vector2f((i - 1) * 128, ground[size - 11 + i].position.y);
		ground[i].color = sf::Color::Green;
	}

	this->setFlag();
}


int terrain::getSize() {
	return size;
}


void terrain::draw(sf::RenderWindow & window) {

	window.draw(ground);

	//disegna i riquadri che contraddistinguono il pianeta
	for (int i = 0; i < 2; i++) {
		window.draw(convexShape[i]);
		window.draw(rectVect[i]);
		pianeta[i].draw(window);
	}
	//
}


void terrain::setObject(std::vector<object*> objVect) {
	int j = 1;
	for (int i = 0; i < objVect.size(); i++) {
		float x1 = ground[9 + j].position.x;
		float y1 = ground[9 + j].position.y;
		float x2 = ground[9 + (j + 1)].position.x;
		float y2 = ground[9 + (j + 1)].position.y;

		  sf::Vertex line[] =
		   {
			  sf::Vertex(sf::Vector2f(x1, y1)),
			  sf::Vertex(sf::Vector2f(x2, y2))
		   };

		 float deltaX = (x2 - x1) / 2;
		 float deltaY = (y2 - y1) / 2;
		 float alpha = atan((y2 - y1) / (x2 - x1));
		 alpha = (alpha * 180) / PI;
		 objVect[i]->setPosition(sf::Vector2f(line->position.x + deltaX, line->position.y + deltaY));
		 objVect[i]->rotate(alpha);
		 j = j + 2;
	}
}

float terrain::collision(sf::Vector2f pos) {

	float posX = pos.x;
	float posY = pos.y;

	for (int i = 0; i < ground.getVertexCount() - 1; i++) {   //controlla le collisioni per tutta la lunghezza del terreno
		float x1 = ground[i].position.x;
		float y1 = ground[i].position.y;
		float x2 = ground[i + 1].position.x;
		float y2 = ground[i + 1].position.y;


		if ((posX >= x1) && (posX <= x2)) {           //colloca la posizione dell'oggetto tra due punti che definiscono il terreno

			float minY = y1;  float minX = x1;

			if (y2 > y1) {
				minY = y2;
				minX = x2;
			}

			float deltaX = fabsf(posX - minX);
			float deltaY = deltaX * (fabsf((y2 - y1) / (x2 - x1)));

			float cY = fabsf(minY - deltaY);              //altezza del terreno nel punto nel punto in cui si trova la navicella


			return(cY - posY);
		}
	}

	return(10);
}


void terrain::setFlag() {

	for (int i = 0; i < 2; i++) {
		sf::RectangleShape newRect(sf::Vector2f(100, 45));
		rectVect.push_back(newRect);
		rectVect[i].setFillColor(sf::Color::Black);
		rectVect[i].setOutlineThickness(5.f);
		rectVect[i].setOutlineColor(sf::Color(148, 86, 6));
	}

	rectVect[0].setPosition(ground[size - 5].position.x, ground[size - 5].position.y - 150);
	rectVect[1].setPosition(ground[6].position.x, ground[6].position.y - 150);

	double y1 = ground[6].position.y; double y2 = ground[7].position.y;
	double tan = (-(y2 - y1) / 128);

	double minY = y1; 	double deltaX1 = 42; double deltaX2 = 57;

	if (y2 > y1) {
		minY = y2;
		deltaX1 = 42.0 - 128;
		deltaX2 = 57.0 - 128;
	}

	double deltaY1 = (deltaX1 * tan); 	double deltaY2 = (deltaX2 * tan);
	double p1 = minY - deltaY1;
	double p2 = minY - deltaY2;

	for (int i = 0; i < 2; i++) {
		sf::ConvexShape newCS;
		convexShape.push_back(newCS);

		float x = rectVect[i].getPosition().x + 42;
		float y = rectVect[i].getPosition().y - 10;

		double
			X[4] = { x, x + 15, x + 15, x},
			Y[4] = { y, y, p2, p1};

		convexShape[i].setPointCount(4);

		for (int j = 0; j < 4; j++) {
			convexShape[i].setPoint(j, sf::Vector2f(X[j], Y[j]));
		}

		convexShape[i].setFillColor(sf::Color(120, 70, 5));
	}

	for (int i = 0; i < 2; i++) {
		pianeta[i].setColor(sf::Color(130, 92, 62));
		pianeta[i].setSize(15);
		pianeta[i].setPosition(sf::Vector2f(rectVect[i].getPosition().x + 10, rectVect[i].getPosition().y + 15));

	}

}


	