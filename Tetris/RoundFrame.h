#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromio.h"


class RoundFrame
{
private:
	sf::Sprite sprite;
	sf::Texture textura;
public:
	RoundFrame(sf::IntRect tam_and_pos);
	void setColor(sf::Color cor);
    void draw(sf::RenderWindow& janela);
};


template <class Temp>

class Moldura {
public:
	RoundFrame frame;
	sf::Font font;
	sf::Text description;
	Temp *temp;

	Moldura(sf::IntRect tam, std::string texto, Temp in_midle);
	void draw(sf::RenderWindow& janela);
};



