#include "Tubo.h"
#include <SFML\Graphics.hpp>



Tubo::Tubo(int sitio, float XStart)
{
	//std::cout << "\nTubo criado!";
	int altura = sitio;
	//std::cout << altura << "  ";
	size[0].x = 40.0f;
	size[0].y = (float)altura;
	size[1].x = 40.0f;
	size[1].y = 550.0f - size[0].y - space;

	//Tubo de cima
	position[0].x = XStart;
	position[0].y = 0.0f;
	tuboCima.setFillColor(sf::Color::Green);
	tuboCima.setSize(size[0]);
	tuboCima.setPosition(position[0]);
	//Tubo de baixo
	position[1].x = XStart;
	position[1].y = 550.0f - size[1].y;
	tuboBaixo.setFillColor(sf::Color::Green);
	tuboBaixo.setSize(size[1]);
	tuboBaixo.setPosition(position[1]);

	//std::cout << "\nTubo criado!";
}

void Tubo::UpDate() {

	position[0].x -= 2.5f;
	position[1].x -= 2.5f;
	tuboCima.setPosition(position[0]);
	tuboBaixo.setPosition(position[1]);
}


Tubo Tubo::operator= (const Tubo& objeto) {
	Tubo res(2, 400.0f);
	//res.tuboBaixo = objeto.tuboBaixo;
	//res.tuboCima = objeto.tuboCima;
	//res.position[0] = objeto.position[0];
	//res.position[1] = objeto.position[1];
	//res.size[0] = objeto.size[0];
	//res.size[1] = objeto.size[1];
	return res;
}


float Tubo::getXPosistion() {
	return position[0].x;
}

sf::Vector2f Tubo::getPosition(bool isCeil) {

	sf::Vector2f Position;
	if (!isCeil) {
		Position.x = tuboCima.getPosition().x + tuboCima.getSize().x / 2;
		Position.y = tuboCima.getPosition().y + tuboCima.getSize().y / 2;
	}
	else {
		Position.x = tuboBaixo.getPosition().x + tuboBaixo.getSize().x / 2;
		Position.y = tuboBaixo.getPosition().y + tuboBaixo.getSize().y / 2;
	}

	return Position;
}


sf::Vector2f Tubo::getHalfSize(bool isCeil) {

	sf::Vector2f HalfSize;
	if (!isCeil) {
		HalfSize.x = tuboCima.getSize().x / 2 - 5;
		HalfSize.y = tuboCima.getSize().y / 2 - 5;
	}
	else {
		HalfSize.x = tuboBaixo.getSize().x / 2 - 5;
		HalfSize.y = tuboBaixo.getSize().y / 2 - 5;
	}

	return HalfSize;
}


void Tubo::draw(sf::RenderWindow& janela) {

	janela.draw(tuboCima);
	janela.draw(tuboBaixo);
}

Tubo::~Tubo()
{
}
