#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"



Player::Player(sf::Texture& Tex)
{

	//Tamanho da nave:
	sf::Vector2f size;
	size.x = 50.0f;
	size.y = 70.0f;
	nave.setSize(size);
	//Origem:
	nave.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	//Posição:
	NavePosition.x = 0.0f;
	NavePosition.y = 0.0f;
	nave.setPosition(NavePosition);
	//Aspecto:
	nave.setTexture(&Tex);
	//Movimento:
	NaveDirection.x = 0.0f;
	NaveDirection.y = -1.0f;
	angle = 0.0f;
	velocidade = 0.0f;
	aceleracao = 0.0f;


	//Pistola:
	pistol.setFillColor(sf::Color(10, 10, 10));
	pistol.setSize(sf::Vector2f(2.0f, 15.0f));
	pistol.setOrigin(sf::Vector2f(2.0f / 2, 15.0f / 3));
	PistolPosition.x = NavePosition.x;
	PistolPosition.y = NavePosition.y;
	pistol.setPosition(PistolPosition);
	PistolDirection.x = 0.0f;
	PistolDirection.y = -1.0f;

}

void Player::ShootDirection(sf::Vector2f mouse) {

	sf::Vector2f direction;
	//Posição do rato é dada de acordo com a janela,
	//Logo é a posição da nave relativamente à janela, que está sempre no meio.
	direction.x = mouse.x - NavePosition.x;
	direction.y = mouse.y - NavePosition.y;
	//std::cout << direction.x << "  " << direction.y << "\n";
	PistolDirection.x = direction.x / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));
	PistolDirection.y = direction.y / (sqrt(pow(direction.x, 2) + pow(direction.y, 2)));

	//Calcular o angulo da pistola em relação à nave
	//Produto escalar a servir para alguma coisa xD

	//float Np = sqrt(pow(PistolDirection.x, 2) + pow(PistolDirection.y, 2));
	//float Nn = sqrt(pow(NaveDirection.x, 2) + pow(NaveDirection.y, 2));
	float produto = PistolDirection.x * NaveDirection.x + PistolDirection.y * NaveDirection.y;
	//float angulo = acos(produto / (Np * Nn)) * 180 / 3.14159265f;

	//O motivo de não utilizar o P.E. é porque não dá sinal ao angulo, pelo que,
	//É necessário utilizar a fórmula abaixo:
	float angulo = atan2(PistolDirection.x * NaveDirection.y - PistolDirection.y * NaveDirection.x, produto);
	angulo = angulo * 180 / 3.14159265f;
	float theta = 0;
	if (angulo >= 135.0f) {
		theta = 135.0 - angulo;
		angulo = 135;
	} 
	if (angulo <= -135.0f) {
		theta = -angulo - 135.0;
		angulo = -135;
	}
	theta = -theta * 3.14159265f / 180;
	float newPistolDirectionX = PistolDirection.x*cos(theta) - PistolDirection.y*sin(theta);
	float newPistolDirectionY = PistolDirection.x*sin(theta) + PistolDirection.y*cos(theta);
	PistolDirection.x = newPistolDirectionX;
	PistolDirection.y = newPistolDirectionY;
	//std::cout << "N: " << NaveDirection.x << "  " << NaveDirection.y << "   P:" << PistolDirection.x << "  " << PistolDirection.y << " ";
	//std::cout << theta << "\n";
	float tangente = PistolDirection.y / PistolDirection.x;
	float angle = -atan(tangente);
	float degree = angle * 180 / 3.14159265f - 90;
	if (PistolDirection.x < 0) {
		degree += 180;
	}
	pistol.setRotation(180 - degree);
}

void Player::Shoot() {
	Tiro tiro;
	tiro.setDirection(PistolDirection);
	tiro.initPoint(PistolPosition);
	tiros.push_back(tiro);
}

sf::Vector2f Player::getPistolPosition() {
	return PistolPosition;
}

sf::Vector2f Player::getNavePosition() {
	return NavePosition;
}

sf::Vector2f Player::getCenter() {
	return nave.getPosition();
}

void Player::acelerar(posicao lado) {

	if (aceleracao < 4.0f && aceleracao > -4.0f) {

		switch (lado) {
		case frente:
			velocidade += 1.0f;
			break;
		case tras:
			velocidade -= 1.0f;
			break;
		}
	}
	//velocidade += aceleracao;
}

void Player::move() {

	//std::cout << velocidade << "  " << aceleracao << "\n";
	sf::Vector2f NewPos(sf::Vector2f(NavePosition.x + NaveDirection.x * velocidade,
		NavePosition.y + NaveDirection.y * velocidade));
	if (NewPos.x < (NaveLimit / 2) && NewPos.x > -(NaveLimit / 2) &&
		NewPos.y < (NaveLimit / 2) && NewPos.y > -(NaveLimit / 2)) {

		nave.move(sf::Vector2f(NaveDirection.x * velocidade, NaveDirection.y * velocidade));

	}
	NavePosition = nave.getPosition();
	PistolPosition.x = NavePosition.x + NaveDirection.x * 25.0f;
	PistolPosition.y = NavePosition.y + NaveDirection.y * 25.0f;
	pistol.setPosition(PistolPosition);
}

void Player::rotate(float angle) {

	this->angle += angle;
	float radianos = this->angle * 3.14159265f / 180;
	NaveDirection.x = sin(radianos);
	NaveDirection.y = -cos(radianos);
	nave.rotate(angle);
}

void Player::restart() {

	NavePosition.x = 0.0f;
	NavePosition.y = 0.0f;
	nave.setPosition(NavePosition);
	//Movimento:
	NaveDirection.x = 0.0f;
	NaveDirection.y = -1.0f;
	angle = 0.0f;
	velocidade = 0.0f;
	aceleracao = 0.0f;
	nave.setRotation(0);

	//Pistola:
	PistolPosition.x = NavePosition.x;
	PistolPosition.y = NavePosition.y;
	pistol.setPosition(PistolPosition);
	PistolDirection.x = 0.0f;
	PistolDirection.y = -1.0f;
}

void Player::draw(sf::RenderWindow& janela) {

	janela.draw(pistol);
	janela.draw(nave);
	for (int i = 0; i < tiros.size(); i++)
	{
		janela.draw(tiros[i].tiro);
	}
}




//Classe tiros porque o player tem tiros.


Tiro::Tiro() {
	tiro.setSize(sf::Vector2f(2.6f, 6.0f));
	tiro.setFillColor(sf::Color::Red);
	//position.x = naveCenter.x;
	//position.y = naveCenter.y;
	//tiro.setPosition(position);
	tiro.setOrigin(sf::Vector2f(2.6f / 2, 6.0f / 2));
}
void Tiro::initPoint(sf::Vector2f pistolCenter) {
	position.x = pistolCenter.x;
	position.y = pistolCenter.y;
	tiro.setPosition(position);
}

void Tiro::setDirection(sf::Vector2f& direcao) {
	diretor.x = direcao.x / sqrt(pow(direcao.x, 2) + pow(direcao.y, 2));
	diretor.y = direcao.y / sqrt(pow(direcao.x, 2) + pow(direcao.y, 2));
}

void Tiro::move() {
	tiro.move(sf::Vector2f(diretor.x * 15, diretor.y * 15));
	position = tiro.getPosition();
}

