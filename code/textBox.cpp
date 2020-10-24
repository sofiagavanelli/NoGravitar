#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include  "textBox.h"


textBox::textBox() {
	font.loadFromFile("../src/LucidaSansRegular.ttf");

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(10, 10));
	text.setStyle(sf::Text::Style::Bold);
}


textBox::textBox(std::string txt) : textBox() {
	text.setString(txt);
}

textBox::~textBox()
{
}


void textBox::updateText(std::string txt) {   
	text.setString(txt);
}


void textBox::drawRelative(sf::RenderWindow& window, sf::Vector2f pos) {  

	text.setFont(font);

	sf::Vector2f viewSize = window.getView().getCenter();

	text.setPosition(viewSize.x - pos.x, viewSize.y - pos.y);

	window.draw(text);
}

void textBox::draw(sf::RenderWindow & window) {
	text.setFont(font);
	window.draw(text);
}

void textBox::setTitle(int grandezza) {
	text.setCharacterSize(grandezza);
	text.setFillColor(sf::Color::Red);
}

void textBox::setPosition(sf::Vector2f(pos)) {
	text.setPosition(pos);
}

void textBox::setSize(int size) {
	text.setCharacterSize(size);
}

void textBox::setColor(sf::Color color) {
	text.setFillColor(color);
}

void textBox::setFont() {
	font.loadFromFile("LucidaSansRegular.ttf");
	text.setFont(font);
}

void textBox::rotate(double rotation) {
	text.rotate(rotation);
}




textValues::textValues() : textBox(std::string(" ")) {
	boundary.setSize(sf::Vector2f(85, 20));
	boundary.setFillColor(sf::Color::Black);
	boundary.setOutlineColor(sf::Color::White);
	boundary.setOutlineThickness(2);

	barValue.setSize(sf::Vector2f(80, 15));
	barValue.setFillColor(sf::Color::White);

}



textValues::~textValues()
{
}


void textValues::draw(sf::RenderWindow& window, sf::Vector2f pos) {

	sf::Vector2f viewSize = window.getView().getCenter();

	boundary.setPosition(viewSize - pos);
	window.draw(boundary);

	barValue.setPosition(boundary.getPosition() + sf::Vector2f(2.5,2.5));
	window.draw(barValue);
}


float textValues::getSize() {
	return barValue.getSize().x;
}

void textValues::setSize(float x) {
	barValue.setSize(sf::Vector2f(x, barValue.getSize().y));
}

void textValues::increase(float x) {
	if (barValue.getSize().x + x > 80) barValue.setSize(sf::Vector2f(80, 15));
	else barValue.setSize(sf::Vector2f(barValue.getSize().x + x, 15));
}

bool textValues::decrease(float x) {
	if (this->getSize() >= 0) {
		barValue.setSize(sf::Vector2f(this->getSize() - x, 15));   
		return(true);
	}
	else return(false);	    //ritorna false quando il carburante è finito e il gioco finisce
}



//FUELVALUE

fuelValue::fuelValue() : textValues() {
	this->updateText("FUEL");
}

void fuelValue::draw(sf::RenderWindow& window, sf::Vector2f pos) {
	textValues::draw(window, pos);
	this->drawRelative(window, sf::Vector2f(630, 280));
}


//LIFEVALUE 

lifeValue::lifeValue() : textValues() {

	livesLeft = 3;
	lives.setPointCount(8);
	double
		X[8] = { 0,10,20,17,13,10,7,3 },
		Y[8] = { 5,15,5,0,0,5,0,0 };

	for (int i = 0; i < 8; i++) {
		lives.setPoint(i, sf::Vector2f(X[i], Y[i]));
	}

	lives.setFillColor(sf::Color::Red);

	this->updateText("LIFE");
}


int lifeValue::getLives() {
	return livesLeft;
}

void lifeValue::setLives(int n) {
	livesLeft = n;
}


void lifeValue::decreaseLives() {
	livesLeft = livesLeft - 1;
}


void lifeValue::draw(sf::RenderWindow& window) {

	textValues::draw(window, sf::Vector2f(570, 315));

	sf::View view = window.getView();

	for (int i = 0; i < livesLeft; i++) {
		lives.setPosition(view.getCenter().x + 600 - i * 30, view.getCenter().y - 340);
		window.draw(lives);
	}

	this->drawRelative(window, sf::Vector2f(630, 315));

}
