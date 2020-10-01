#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#define WIDTH  880.0f
#define HEIGTH  560.0f

class Aparencia {
private:
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text texto;
	sf::Texture text;
	sf::Sprite * spr;
	std::string str;
	int vidas;

public:
	Aparencia() {

		rect.setSize(sf::Vector2f(WIDTH, 30.0f));
		rect.setFillColor(sf::Color(246, 246, 190, 255));

		vidas = 3;

		text.loadFromFile("coracao.png");
		spr = new sf::Sprite[vidas];
		for (int i = 0; i < vidas; i++) {
			spr[i].setTexture(text);
			spr[i].setPosition(sf::Vector2f(700.0f + 40.0f * i, 2.0f));
		}

		font.loadFromFile("RegularFont\\tecnico_regular.ttf");
		str = "Level 1 / 5";
		texto.setFont(font);
		texto.setString(str);
		texto.setCharacterSize(20);
		texto.setFillColor(sf::Color::Black);
		texto.setPosition(sf::Vector2f(2.0f, 2.0f));
	}

	void changeLevel(int level) {
		str = "Level " + std::to_string(level) + " / 5";
		texto.setString(str);
	}

	void lose_life() {
		vidas--;
	}

	int getLifes() {
		return vidas;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(rect);
		window.draw(texto);
		for (int i = 0; i < vidas; i++) {
			window.draw(spr[i]);
		}
	}

};