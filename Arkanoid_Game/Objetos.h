#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#ifndef OFFSET_Y
#define OFFSET_Y 30.0f
#endif

class Tijolo
{
public:
	sf::RectangleShape brick;
	int vida;
	Tijolo();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
	void draw(sf::RenderWindow& janela);
	~Tijolo();
};


#define WIDTH  880.0f
#define HEIGTH  560.0f

#define MAX_ANGLE 40


class Racket {

private:
	//sf::RectangleShape racket;

public:

	sf::RectangleShape racket;
	sf::Vector2f size;
	sf::Vector2f position;
	float velocidadeMovimento;

	Racket(float vel) {

		size.x = 80.0f;
		size.y = 10.0f;
		racket.setSize(size);
		racket.setOrigin(size.x / 2, size.y / 2);
		position.x = WIDTH / 2;
		position.y = (HEIGTH + OFFSET_Y) - (size.y + 5);
		racket.setPosition(position);
		velocidadeMovimento = vel;
	}

	void move(bool dir_is_right) {

		sf::Vector2f desvio;
		desvio.y = 0;
		desvio.x = dir_is_right ? velocidadeMovimento : -velocidadeMovimento;
		position += desvio;
		if (position.x > 0 && position.x < WIDTH) {
			racket.move(desvio);
		}
	}

	void setSize(float Xfator) {
		racket.setSize(sf::Vector2f(80.0f * Xfator, 10.0f));
		size.x = racket.getSize().x;
	}

	void setPosition(float nova_posicao) {
		sf::Vector2f newPosition(nova_posicao, (HEIGTH + OFFSET_Y) - (size.y + 5));
		racket.setPosition(newPosition);
		position = newPosition;
	}

	sf::Vector2f GetPosition() {
		return position;
	}

	void draw(sf::RenderWindow& janela) {
		janela.draw(racket);
	}
};


class Bola {
private:
	sf::CircleShape bola;

public:

	sf::Vector2f position;
	sf::Vector2f diretor;
	float velocity;
	float raio;
	bool isOnFire;
	int TempoNovaBatida;


	Bola(float velocidade) {
		isOnFire = false;
		TempoNovaBatida = 0;
		velocity = velocidade;
		diretor.x = 0.0f;
		diretor.y = sqrt(pow(velocity, 2) - pow(diretor.x, 2));
		position.x = WIDTH / 2;
		position.y = HEIGTH / 2 + OFFSET_Y + 20.0f;
		raio = 8.0f;
		bola.setRadius(raio);
		bola.setPosition(position);
		bola.setOrigin(sf::Vector2f(raio, raio));
	}

	Bola(float velocidade, sf::Vector2f position, short DirXsignal) {
		TempoNovaBatida = 0;
		isOnFire = false;
		velocity = velocidade;
		diretor.x = (rand() % int((velocity / 2) * 100)) / 100.0f;
		diretor.x *= DirXsignal;
		diretor.y = sqrt(pow(velocity, 2) - pow(diretor.x, 2));
		std::cout << diretor.x << "  " << diretor.y << "\n";
		this->position.x = position.x;
		this->position.y = position.y;
		raio = 8.0f;
		bola.setRadius(raio);
		bola.setPosition(position);
		bola.setOrigin(sf::Vector2f(raio, raio));
	}

	void move() {

		bola.move(diretor.x, diretor.y);
		position = bola.getPosition();
	}

	void setPosition(sf::Vector2f nova_posicao) {
		bola.setPosition(nova_posicao);
	}

	void setDirection(sf::Vector2f direcao) {
		diretor = direcao;
	}

	void FireState(bool isOnFire) {
		if (isOnFire) {
			this->isOnFire = true;
			bola.setFillColor(sf::Color(240, 160, 50));
		}
		else {
			this->isOnFire = false;
			bola.setFillColor(sf::Color::White);
		}
	}

	void draw(sf::RenderWindow& janela) {
		janela.draw(bola);
	}
};

