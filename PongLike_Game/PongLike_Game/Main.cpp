#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <deque>
#include "Player.h"
#include "Obstaculos.h"


#define WIDTH 500.0f
#define HEIGHT 860.0f



int main() {

	sf::RenderWindow window(sf::VideoMode((int)WIDTH, (int)HEIGHT), "Pong", sf::Style::Default);
	window.setFramerateLimit(80);

	sf::SoundBuffer som1;
	sf::SoundBuffer som2;
	som1.loadFromFile("som1.wav");
	som2.loadFromFile("somgrave.wav");
	Player player1(HEIGHT - 35.0f, HEIGHT / 2 - 50, som1);
	Player player2(35.0f, HEIGHT / 2 + 15, som2);

	sf::Texture tex;
	tex.loadFromFile("Bordas.png");
	sf::Sprite borda;
	borda.setTexture(tex);
	sf::Color coresNeon[] = {sf::Color(208, 47, 157), sf::Color(160, 32, 162), sf::Color(97, 20, 148), sf::Color(46, 21, 138),
							sf::Color(25, 61, 169), sf::Color(26, 129, 173), sf::Color(113, 156, 249), sf::Color(240, 92, 178)};
	int currentColor = 0;
	int bolaCor = 4;
	borda.setColor(coresNeon[currentColor]);
	sf::Time tempoMudarCor;
	sf::Clock colorclock;

	sf::Vector2f direction;
	direction.x = 1.5f; direction.y = 3.6f;
	Ball bola(direction);

	srand(time(NULL));
	sf::Time gerarObst;
	sf::Clock obstclock;
	//Must be a pointer to use polymorphism
	std::deque<Obstaculo*> obts;
	//(time in milisseconds)
	const float aliveTime = 8000;
	const float animationTime = 500;


	while (window.isOpen()) {

		sf::Event evento;
		while (window.pollEvent(evento)) {
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		//Mudança de cor
		tempoMudarCor = colorclock.getElapsedTime();
		if (tempoMudarCor.asMilliseconds() >= 500) {
			tempoMudarCor = colorclock.restart();
			currentColor++;
			bolaCor++;
			if (currentColor == 8) {
				currentColor = 0;
			}
			if (bolaCor == 8) {
				bolaCor = 0;
			}
			borda.setColor(coresNeon[currentColor]);
			bola.setColor(coresNeon[bolaCor]);
		}

		//Gerar obstáculo
		gerarObst = obstclock.getElapsedTime();
		if (gerarObst.asMilliseconds() >= 1000) {
			gerarObst = obstclock.restart();
			if (rand() % 100 >= 75) {
				if (obts.size() <= 2) {
					if (rand() % 2) {
						obts.push_back(new Barrier(animationTime, aliveTime));
					}
					else {
						obts.push_back(new Oil(animationTime, aliveTime));
					}
				}
			}
		}
		for (unsigned int i = 0; i < obts.size(); i++) {
			obts[i]->checkCollision(bola);
			if (obts[i]->animate() == false) {
				obts.pop_front();
			}
		}

		if (player1.getTime() > 2000.0f && player2.getTime() > 2000.0f) {
			bola.move();
		}

		if (bola.position.x - bola.raio < 28.0f || bola.position.x + bola.raio > (WIDTH - 28.0f)) {
			bola.diretor.x = -bola.diretor.x;
		}
		if (bola.position.y < 0) {
			player2.score++;
			player1.reset();
			bola.reset();
		}
		if (bola.position.y > HEIGHT) {
			player1.score++;
			player2.reset();
			bola.reset();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			player1.paddle.move(4.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			player1.paddle.move(-4.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player2.paddle.move(4.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player2.paddle.move(-4.0f);
		}

		bola.checkCollision(player1);
		bola.checkCollision(player2);

		//std::cout << bola.velocity << std::endl;


		//desenhar
		window.clear();
		for (unsigned int i = 0; i < obts.size(); i++) {
			obts[i]->draw(window);
		}
		window.draw(borda);
		bola.draw(window);
		player1.draw(window);
		player2.draw(window);
		window.display();
	}

}