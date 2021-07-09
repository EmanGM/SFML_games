#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Player.h"

#define WIDTH 500.0f
#define HEIGHT 860.0f


Player::Player(float Posição_inicial, float text_position, sf::SoundBuffer& som)
{
	paddle.setStartingPosition(Posição_inicial);
	font.loadFromFile("Fonts/RegularFont/tecnico_regular.ttf");
	pontos.setFont(font);
	pontos.setFillColor(sf::Color::Blue);
	pontos.setCharacterSize(30);
	pontos.setPosition(sf::Vector2f(WIDTH - 80, text_position));
	score = 0;

	buffer = som;
	this->som.setBuffer(buffer);
	this->som.setVolume(10.0f);
}

void Player::reset() {
	tempoRestart = relogio.restart();
}

float Player::getTime() {

	tempoRestart = relogio.getElapsedTime();
	return tempoRestart.asMilliseconds();
}

void Player::makeSound() {
	som.play();
}

void Player::draw(sf::RenderWindow& janela) {
	paddle.draw(janela);
	//std::string texto = std::to_string(score);
	pontos.setString(std::to_string(score));
	janela.draw(pontos);
}

Player::~Player() {

}


Barra::Barra()
{
	size.x = 70.0f;
	size.y = 10.0f;
	barra.setSize(size);
	barra.setOrigin(size.x / 2, size.y / 2);
}

void Barra::setStartingPosition(float startPosition) {
	position = WIDTH / 2;
	barra.setPosition(position, startPosition);
}

void Barra::move(float offset) {

	position += offset;
	if (position < (WIDTH - ((size.x / 2) + 30.0f)) && position >((size.x / 2) + 30.0f)) {
		sf::Vector2f desvio;
		desvio.y = 0;
		desvio.x = offset;
		barra.move(desvio);
	}
}

void Barra::draw(sf::RenderWindow& janela) {
	janela.draw(barra);
}

Barra::~Barra()
{
}

