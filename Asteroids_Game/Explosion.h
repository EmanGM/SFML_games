#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
private:
	unsigned int imagemAtual;
	unsigned int numeroImagens;

	//float tempo_total;
	//float tempo_individual;


public:
	sf::IntRect xyRect;

	Animation(sf::Texture* text, unsigned int numeroImagens);
	bool Update();
	~Animation();
};


class Explosion {
private:
	sf::Sprite explosion;
	Animation animacao;

	sf::Clock contador_tempoExplosao;
	sf::Time tempoFrame;

public:
	Explosion(sf::Texture* text, sf::Vector2f position);
	bool Update();
	void draw(sf::RenderWindow& janela);
};


