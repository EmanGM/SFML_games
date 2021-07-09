#include <SFML/Graphics.hpp>
#include "player.h"

class Ball {

public:
	sf::CircleShape bola;
	sf::Vector2f position;
	sf::Vector2f diretor;
	sf::Color cor;
	int corAtual;
	int changeColor;
	float velocity;
	const int maxVel;
	const int minVel;
	float speed;
	float raio;

	Ball(sf::Vector2f direcao);
	void move();
	void setColor(sf::Color cor);
	void checkCollision(Player& player);
	void reset();
	void draw(sf::RenderWindow& janela);
};

