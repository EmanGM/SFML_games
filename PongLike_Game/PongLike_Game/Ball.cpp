#include "Ball.h"
#include <iostream>


#define WIDTH 500.0f
#define HEIGHT 860.0f


Ball::Ball(sf::Vector2f direcao) : minVel(5), maxVel(10) {
	diretor.x = direcao.x;
	diretor.y = direcao.y;
	velocity = pow(diretor.x, 2) + pow(diretor.y, 2);
	position.x = WIDTH / 2;
	position.y = HEIGHT / 2;
	raio = 6.0f;
	bola.setRadius(raio);
	bola.setPosition(position);
	bola.setOrigin(sf::Vector2f(raio, raio));
	speed = 0.8f;

	cor = sf::Color::Blue;
	changeColor = 0;
	corAtual = 1;
	bola.setFillColor(cor);
}
void Ball::move() {

	bola.move(sf::Vector2f(diretor.x * speed, diretor.y * speed));
	position = bola.getPosition();
}

void Ball::setColor(sf::Color cor) {
	bola.setFillColor(cor);
}

void Ball:: checkCollision(Player& player) {

	sf::Vector2f otherPosition;
	otherPosition.x = player.paddle.barra.getPosition().x;
	otherPosition.y = player.paddle.barra.getPosition().y;
	sf::Vector2f otherHalfSize;
	otherHalfSize.x = player.paddle.barra.getSize().x / 2;
	otherHalfSize.y = player.paddle.barra.getSize().y / 2;

	float deltaX = otherPosition.x - position.x;
	float deltaY = otherPosition.y - position.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + raio);
	float intersectY = abs(deltaY) - (otherHalfSize.y + raio);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		player.makeSound();
		if (intersectX > intersectY) {
			//std::cout << "Caso 1\n";
			diretor.x = -diretor.x;
		}
		else {

			//std::cout << "velocity: " << velocity << "\n";
			float dist = position.x - player.paddle.position;
			std::cout << "point: " << dist << "   x: " << diretor.x << "\n";
			velocity = ((minVel - maxVel) / otherHalfSize.x) * abs(dist) + maxVel;
			if (velocity < minVel) {
				velocity = minVel;
			}
			//componente x calculada a partir da velocidade. Equação x = mv + b
			diretor.x = (((-0.40 * maxVel) / (maxVel - minVel)) * velocity) + ((0.40 * maxVel) / (maxVel - minVel)) * maxVel;
			if (position.x < player.paddle.position) {
				diretor.x = -diretor.x;
			}
			diretor.y = sqrt(pow(velocity, 2) - pow(diretor.x, 2));

			std::cout << "x " << diretor.x << "     y " << diretor.y << "   velocity:  " << velocity << "\n";
			if (position.y > HEIGHT / 2)
			{
				diretor.y = -diretor.y;
			}
			//std::cout << "     x " << pow(diretor.x, 2) << "\n";
			//std::cout << "x " << diretor.x << "     y " << diretor.y << "\n";
			//std::cout << "velocity: " << velocity << "\n";

			/*diretor.y = diretor.y;

			float point = position.x - paddle.paddle.position;
			std::cout << point << "\n";
			float teta = point * 40 / (paddle.paddle.size.x / 2);
			teta = teta * (M_PI / 180);
			std::cout << teta << "\n";
			float tempx = diretor.x;
			float tempy = diretor.y;
			diretor.x = (float)diretor.x * cos(teta) - diretor.y * sin(teta);
			diretor.y = (float)tempx * sin(teta) + diretor.y * cos(teta);

			std::cout << "x " << diretor.x << "     y " << diretor.y << "\n";
			velocity = sqrt(pow(diretor.x, 2) + pow(diretor.y, 2));*/
		}
	}
}

void Ball::reset() {
	position.x = WIDTH / 2;
	position.y = HEIGHT / 2;
	bola.setPosition(position);
}

void Ball::draw(sf::RenderWindow& janela) {
	janela.draw(bola);
}
