#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <time.h>


#define HEIGHT (32)
#define WIDTH (12)

#define LadoQuadrados (22.0f)


void drawQ(sf::RenderWindow &window, int height, int width, int cor);


class Tetromio
{
private:

	sf::RectangleShape *quadrados;
	sf::Color cor;
	int ID;
	const int size;
	void CheckInsideGrid();


public:

	Tetromio(bool arr[][2], int Id, sf::Color cor);
	Tetromio(const Tetromio &exemplo); //copy constructor
	void setPlace(sf::Vector2f new_pos);
	void getDown();
	void move(bool go_to_right);
	void rotate(int graus);
	bool isDown();
	sf::Vector2f getPosition(int square);
	int getColor();
	int getID();
	bool Collision(int t[][WIDTH]);
	void draw(sf::RenderWindow &janela);
	~Tetromio();
};

