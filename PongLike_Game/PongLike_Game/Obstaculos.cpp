#include "Obstaculos.h"
#include <iostream>

Barrier::Barrier(const float animationTime, const float aliveTime) : Obstaculo(animationTime, aliveTime), size(70.0f, 10.0f) {

	rect.setSize(sf::Vector2f(size.x / 10, size.y / 10));
	float posX = rand() % 440 + 28.0f;
	float posY = rand() % 660 + 50.0f;
	rect.setPosition(posX, posY);
	centerPosition = rect.getPosition();
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
}

void Barrier::checkCollision(Ball &ball) {

	//centro do obstáculo pode estar incorreto
	float deltaX = ball.position.x - centerPosition.x;
	float deltaY = ball.position.y - centerPosition.y;

	float intersectX = abs(deltaX) - (ball.raio + size.x / 2);
	float intersectY = abs(deltaY) - (ball.raio + size.y / 2);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		std::cout << "Colidui\n";
		if (intersectX > intersectY) {
			ball.diretor.x = -ball.diretor.x;
		}
		else {
			ball.diretor.y = -ball.diretor.y;
		}
	}
}

static void resize(sf::RectangleShape& rect, int multiplier) {

	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
	float newSizeX = rect.getSize().x + multiplier * 10.0f;
	float newSizeY = rect.getSize().y + multiplier * 1.0f;
	rect.setSize(sf::Vector2f(newSizeX, newSizeY));
}

bool Barrier::animate() {


	timeTotal = clockTime.getElapsedTime();
	timeAnimation = clockAnimation.getElapsedTime();
	//std::cout << "TT: " << tempoTotal.asMilliseconds() << "    TA: " << tempoAnimacao.asMilliseconds() << "\n";
	if (timeTotal.asMilliseconds() < animationTime) {
		if (timeAnimation.asMilliseconds() >= 50) {
			resize(rect, 1);
			animationTimes++;
			timeAnimation = clockAnimation.restart();
		}
	}
	else if (timeTotal.asMilliseconds() >= (aliveTime - animationTime) && timeTotal.asMilliseconds() < aliveTime){
		if (timeAnimation.asMilliseconds() >= 20) {
			if (animationTimes >= 0) {
				resize(rect, -1);
				animationTimes--;
			}
			timeAnimation = clockAnimation.restart();
		}
	} else if (timeTotal.asMilliseconds() >= aliveTime) {
		return false;
	}
	return true;
}
void Barrier::draw(sf::RenderWindow& janela) {
	janela.draw(rect);
}




Oil::Oil(const float animationTime, const float aliveTime) : Obstaculo(animationTime, aliveTime), radius (50.0f) {

	cir.setRadius(radius);
	float posX = rand() % 440 + 28.0f;
	float posY = rand() % 660 + 50.0f;
	cir.setPosition(posX, posY);
	cir.setOrigin(sf::Vector2f(radius, radius));
	centerPosition = cir.getPosition();
	texture.loadFromFile("oil_pool.png");
	cir.setTexture(&texture);
}

void Oil::checkCollision(Ball& bola) {
	sf::Vector2f dist;
	dist.x = abs(bola.position.x - this->centerPosition.x);
	dist.y = abs(bola.position.y - this->centerPosition.y);
	float delta = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

	static bool isColliding = false;

	if (delta <= (bola.raio + this->radius)) {
		//Speed should reduce > 50%
		if (isColliding == false) {
			bola.speed *= 0.5f;
		}
		isColliding = true;
	}
	else {
		bola.speed = 0.8f;
		isColliding = false;
	}
}

bool Oil::animate() {
	timeTotal = clockTime.getElapsedTime();
	timeAnimation = clockAnimation.getElapsedTime();
	//std::cout << "TT: " << tempoTotal.asMilliseconds() << "    TA: " << tempoAnimacao.asMilliseconds() << "\n";
	if (timeTotal.asMilliseconds() < 500) {
		if (timeAnimation.asMilliseconds() >= 20) {
			if (animationTimes < 9) {
				animationTimes++;
			}
			timeAnimation = clockAnimation.restart();
		}
	}
	else if (timeTotal.asMilliseconds() >= 8000 && timeTotal.asMilliseconds() < 8500) {
		if (timeAnimation.asMilliseconds() >= 20) {
			if (animationTimes > 0) {
				animationTimes;
			}
			timeAnimation = clockAnimation.restart();
		}
	}
	else if (timeTotal.asMilliseconds() >= 8000) {
		return false;
	}
	return true;
}
void Oil::draw(sf::RenderWindow& janela) {
	janela.draw(cir);
}




Obstaculo::Obstaculo(const float animation_time, const float alive_time) : animationTime(animation_time), aliveTime(alive_time)
{
	timeTotal = clockTime.restart();
	timeAnimation = clockAnimation.restart();
	animationTimes = 0;
}

bool Obstaculo::animate()
{
	std::cout << "Base Animation!";
	return false;
}

void Obstaculo::checkCollision(Ball& ball)
{
	std::cout << "Base Colision!";
}

void Obstaculo::draw(sf::RenderWindow& janela)
{
}
