#include "Tetromio.h"
#include <SFML\Graphics.hpp>
#include <iostream>


void drawQ(sf::RenderWindow &window, int height, int width, int cor) {

	sf::RectangleShape req;
	req.setSize(sf::Vector2f(LadoQuadrados, LadoQuadrados));
	req.setPosition(sf::Vector2f(width * LadoQuadrados, height * LadoQuadrados));
	req.setOutlineColor(sf::Color::White);
	req.setOutlineThickness(-0.5f);

	sf::Color color;

	switch (cor)
	{
		case 1:
			color = sf::Color::Yellow;
			break;
		case 2:
			color = sf::Color::Blue;
			break;
		case 3:
			color = sf::Color(179, 0, 179);
			break;
		case 4: 
			color = sf::Color::Red;
			break;
		case 5:
			color = sf::Color::Green;
			break;
		case 6:
			color = sf::Color(255, 100, 0);
			break;
		case 7:
			color = sf::Color(50, 160, 255);
			break;
	default:
		break;
	}
	req.setFillColor(color);
	window.draw(req);
}


Tetromio::Tetromio(bool arr[][2], int Id, sf::Color cor) : size (4)
{
	srand(time(NULL));

	this->ID = Id;
	this->cor = cor;
	quadrados = new sf::RectangleShape[this->size];

	int i = 0;
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 2; n++) {
			if (arr[m][n] == 1) {
				quadrados[i].setSize(sf::Vector2f(LadoQuadrados, LadoQuadrados));
				quadrados[i].setPosition(sf::Vector2f(m * LadoQuadrados, n * LadoQuadrados));
				quadrados[i].setFillColor(this->cor);
				quadrados[i].setOutlineColor(sf::Color::White);
				quadrados[i].setOutlineThickness(-0.5f);
				i++;
			}
		} 
	}
}

Tetromio::Tetromio(const Tetromio &exemplo) : size (4)
{

	//std::cout << "Nova peca\n";
	this->ID = exemplo.ID;
	//this->size = exemplo.size;
	this->cor = exemplo.cor;
	quadrados = new sf::RectangleShape[this->size];

	for (int i = 0; i < size; i++) {
		this->quadrados[i] = exemplo.quadrados[i];
	}
	//int afastamento = (rand() % WIDTH) + 2;
	//for (int i = 0; i < afastamento; i++) {
	//	move(0);
	//}
}

void Tetromio::setPlace(sf::Vector2f new_pos) {

	//translação dos pontos a partir do ponto do 1º quadrado
	sf::Vector2f currrentPos = quadrados[0].getPosition();
	sf::Vector2f moveDir(new_pos.x - currrentPos.x, new_pos.y - currrentPos.y);
	for (int i = 0; i < size; i++) {
		quadrados[i].move(moveDir);
		quadrados[i].setScale(sf::Vector2f(0.6f, 0.6f));
	}
}


void Tetromio::getDown() {

	for (int i = 0; i < size; i++) {
		quadrados[i].setPosition(sf::Vector2f(quadrados[i].getPosition().x,
											    quadrados[i].getPosition().y + LadoQuadrados));
	}
}

void Tetromio::move(bool go_to_right) {

	float amount = go_to_right ? LadoQuadrados : -LadoQuadrados;
	for (int i = 0; i < size; i++)
	{
		quadrados[i].move(sf::Vector2f(amount, 0.0f));
	}
	CheckInsideGrid();
}

void Tetromio::rotate(int graus) {

	sf::Vector2f p = quadrados[1].getPosition();
	for (int i = 0; i < size; i++) {
		float x_dist = p.x - quadrados[i].getPosition().x;
		float y_dist = p.y - quadrados[i].getPosition().y;
		quadrados[i].setPosition(p.x - y_dist, p.y + x_dist);
	}
	CheckInsideGrid();
}

void Tetromio::CheckInsideGrid() {
	for (int i = 0; i < size; i++)
	{
		while (quadrados[i].getPosition().x < 0.0f || quadrados[i].getPosition().x >(WIDTH * LadoQuadrados) - LadoQuadrados) {
			if (quadrados[i].getPosition().x < 0.0f ||
				quadrados[i].getPosition().x >(WIDTH * LadoQuadrados) - LadoQuadrados) {
				if (quadrados[i].getPosition().x < 0.0f) {
					move(1);
				}
				if (quadrados[i].getPosition().x >(WIDTH * LadoQuadrados) - LadoQuadrados) {
					move(0);
				}
				break;
			}
		}
	}
}


bool Tetromio::isDown() {
	for (int i = 0; i < size; i++) {
		if (quadrados[i].getPosition().y >= (HEIGHT * LadoQuadrados) - LadoQuadrados) {
			return true;
		}
	}
	return false;
}

int Tetromio::getColor() {

	if (cor == sf::Color::Yellow)
		return 1;
	else if (cor == sf::Color::Blue)
		return 2;
	else if (cor == sf::Color(179, 0, 179))
		return 3;
	else if (cor == sf::Color::Red)
		return 4;
	else if (cor == sf::Color::Green)
		return 5;
	else if (cor == sf::Color(255, 100, 0))
		return 6;
	else if (cor == sf::Color(50, 160, 255))
		return 7;
	else
	{
		return 0;
	}
}

sf::Vector2f Tetromio::getPosition(int square) {
	return quadrados[square].getPosition();
}

int Tetromio::getID() {
	return ID;
}


bool Tetromio::Collision(int t[][WIDTH]) {

	for (int i = 0; i < size; i++) {
		int x = quadrados[i].getPosition().x / LadoQuadrados;
		int y = (quadrados[i].getPosition().y + LadoQuadrados) / LadoQuadrados;
		if (t[y][x] != 0) {
			return true;
		}
	}
	return false;
}


void Tetromio::draw(sf::RenderWindow &janela) {
	for (int i = 0; i < size; i++) {
		janela.draw(quadrados[i]);
	}
}


Tetromio::~Tetromio()
{
}
