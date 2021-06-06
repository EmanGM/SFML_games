#define _USE_MATH_DEFINES

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Objetos.h"
#include "Nivel.h"
#include "Aparencia.h"



int main() {

	float offsetY = 30.0f;

	sf::RenderWindow window(sf::VideoMode(int(WIDTH), int(HEIGTH + offsetY)), "Arkanoid");
	window.setFramerateLimit(80);

	Aparencia ape;

	int tijolos_grid[12][7];

	//Array of 5 pointers, for the 5 levels
	Nivel* niveis[5];

	std::fstream FicheiroNiveis;
	FicheiroNiveis.open("niveis.txt", std::ios::in);
	std::string s;
	int nivelAtual = 1;
restart:
	while (std::getline(FicheiroNiveis, s)) {
		std::string nivelN = "nivel " + std::to_string(nivelAtual);
		if (s == nivelN) {
			int vida;
			for (int colum = 0; colum < 7; colum++) {
				for (int i = 0; i < 12; i++) {
					FicheiroNiveis >> std::skipws >> vida;
					tijolos_grid[i][colum] = vida;
				}
			}
			niveis[nivelAtual - 1] = new Nivel(tijolos_grid, 3.0f + 0.5f * (nivelAtual - 1));
			nivelAtual++;
		}
		if (nivelAtual == 6) {
			break;
		}
	}
	FicheiroNiveis.close();

	sf::Font font;
	sf::Text DefeatText;
	font.loadFromFile("RegularFont\\tecnico_regular.ttf");
	DefeatText.setFont(font);
	DefeatText.setString("You Lost!");
	DefeatText.setCharacterSize(100);
	DefeatText.setFillColor(sf::Color(100, 100, 100));
	DefeatText.setPosition(sf::Vector2f(150.0f, 180.0f));
	bool game_run = true;

	srand(time(NULL));


	sf::Color cor;
	for (int i = 0; i < 7; i++) {
		switch (i) {

		case 0:
			cor = sf::Color::White;
			break;
		case 1:
			cor = sf::Color(255, 0, 0, 100);
			break;
		case 2:
			cor = sf::Color::Blue;
			break;
		case 3:
			cor = sf::Color::Yellow;
			break;
		case 4:
			cor = sf::Color::Green;
			break;
		case 5:
			cor.r = 250;
			cor.g = 10;
			cor.b = 250;
			break;
		case 6:
			cor.r = 70;
			cor.g = 25;
			cor.b = 17;
			break;
		default:
			break;
		}
		for (int j = 0; j < 12; j++) {
			niveis[4]->setBlockColor(j, i, cor);
		}
	}

	nivelAtual = 1;
	int exitStatus = 0;


	while (window.isOpen()) {
		sf::Event evento;
		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
			if (evento.type == sf::Event::KeyPressed) {
				switch(evento.key.code)
				{
				case sf::Keyboard::Key::Add:
					nivelAtual++;
					ape.changeLevel(nivelAtual);
					break;
				case sf::Keyboard::Key::R:
					return 0;
					break;
				case sf::Keyboard::Key::Enter:
					goto restart;
					break;
				default:
					break;
				}
			}
		}

		if (game_run) {
			game_run = ape.getLifes();
			exitStatus = niveis[nivelAtual - 1]->run();

			if (exitStatus == 1) {
				nivelAtual++;
				ape.changeLevel(nivelAtual);
				niveis[nivelAtual - 1]->restart();
			}
			else if (exitStatus == 2) {
				ape.lose_life();
			}
			if (nivelAtual > 5) {
				break;
			}
		}

		window.clear();
		ape.draw(window);
		niveis[nivelAtual - 1]->draw(window);
		if (game_run == false) {
			window.draw(DefeatText);
		}
		window.display();
	}


	//Como o array de ponteiros não é dinâmico,
	//Acho que não tenho de deletar a memória:
	//delete[] *niveis;

}