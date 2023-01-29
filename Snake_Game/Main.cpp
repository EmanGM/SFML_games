#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Background.h"
#include "Snake.h"
#include "Food.h"


#ifndef HEAD
#define HEAD 0
#endif
#define vel 0.15f

int main() {

	sf::Vector2f cellSize(25.0f, 25.0f);
	sf::RenderWindow window(sf::VideoMode(550, 750), "Jogo da Cobra", sf::Style::Default);
	window.setFramerateLimit(80);

	sf::Clock clock1;
	sf::Clock clock2;
	sf::Time tempo1;
	sf::Time tempo2;
	srand(time(NULL));

restart:

	Food apple(window, cellSize, sf::Color::Green);
	Food blueBerry(window, cellSize, sf::Color::Blue);

	Snake snake(cellSize);
	snake.velocity = vel;

	sf::Font font;
	font.loadFromFile("Fonts\\tecnico_regular.ttf");
	sf::Text texto;
	texto.setFont(font);
	texto.setString("Perdeste!");
	texto.setCharacterSize(100);
	texto.setFillColor(sf::Color::Green);
	texto.setPosition(sf::Vector2f(60.0f, 280.0f));

	bool runGame = true;
	bool specialFoood = false;

	int probability;


	while (window.isOpen()) {

		sf::Event evento;
		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (runGame == true) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
				snake.changeDirection(Left);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
				snake.changeDirection(Right);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
				snake.changeDirection(Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
				snake.changeDirection(Down);
			}

			tempo1 = clock1.getElapsedTime();
			if (tempo1.asSeconds() >= snake.velocity) {
				clock1.restart();
				snake.move();
				if (snake.velocity <= vel) {
					snake.velocity += 0.001f;
				}
			}

			if (snake.checkFoodColision(apple) == true) {
				snake.aumentarTamanho(1, apple);
				apple.newPosition(snake);

			}


			tempo2 = clock2.getElapsedTime();
			if (specialFoood == false && tempo2.asSeconds() >= 2.0f && snake.length > (5 + 4)) {
				probability = rand() % 100;
				if (probability < 10) {
					specialFoood = true;
				}
				clock2.restart();
			}

			if (specialFoood) {
				if (snake.checkFoodColision(blueBerry) == true) {
					snake.aumentarTamanho(2, blueBerry);
					snake.velocity -= 0.05f;
					blueBerry.newPosition(snake);
					specialFoood = false;
				}
			}

			if (snake.stopGame(window)) {
				runGame = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			runGame = true;
			goto restart;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			return 0;
		}

		window.clear();
		Background(window, cellSize);
		snake.draw(window);
		apple.draw(window);
		if (specialFoood) {
			blueBerry.draw(window);
		}
		if (!runGame) {
			window.draw(texto);
		}
		window.display();

	}
	return 0;
}