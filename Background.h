#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

void Background(sf::RenderWindow& window, sf::Vector2f cellSize) {

	int size[2] = { (int)(window.getSize().x / cellSize.x), (int)(window.getSize().y / cellSize.y) };
	//std::cout << "Size X " << size[0] << "Size Y " << size[1] << "\n";
	sf::RectangleShape* linhas = new sf::RectangleShape[size[0] + size[1]];

	for (int i = 0; i < size[0]; i++) {
		//Linhas Verticais 
		linhas[i].setSize(sf::Vector2f(1.0f, (float)window.getSize().y));
		linhas[i].setPosition(sf::Vector2f(cellSize.x * i, 0.0f));
		linhas[i].setFillColor(sf::Color(0, 150, 0, 100));
		window.draw(linhas[i]);
	}

	for (int i = 0; i < size[1]; i++) {
		//Linhas Horizontais 
		linhas[i + size[0]].setSize(sf::Vector2f((float)window.getSize().x, 1.0f));
		linhas[i + size[0]].setPosition(sf::Vector2f(0.0f, cellSize.y * i));
		linhas[i + size[0]].setFillColor(sf::Color(0, 150, 0, 100));
		window.draw(linhas[i + size[0]]);
	}
	delete[] linhas;
}
