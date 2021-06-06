#include "Nivel.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cmath>

#define M_PI 3.14159268f

enum {
nivel_completo = 1,
perdeu_vida, 
};



Nivel::Nivel(int arr[][7], float velocidade) : totalBlocks(0), control(0), raquete(velocidade)
{
	//Bola
	BallVelocity = velocidade;
	bolas.push_back(Bola(velocidade));


	//Texturas
	BrickTexture.loadFromFile("brick.png");
	PowerUpsTexturas[0].loadFromFile("aumentarRaquete.png");
	PowerUpsTexturas[1].loadFromFile("diminuirRaquete.png");
	PowerUpsTexturas[2].loadFromFile("3balls.png");
	PowerUpsTexturas[3].loadFromFile("fireball.png");

	//Tijolos
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 12; j++) {
			blocos[j][i].vida = arr[j][i];
			if (blocos[j][i].vida > 0) {
				totalBlocks++;
			}
			blocos[j][i].setPosition(sf::Vector2f(60.0f + 70.0f * j, (40.0f + OFFSET_Y) + 35.0f * i));
			if (blocos[j][i].vida > 1) {
				blocos[j][i].brick.setTexture(&BrickTexture);
			}
		}
	}
	//std::cout << totalBlocks << "\n";

	//Sons
	buffer[0].loadFromFile("Som\\BlockCollision.wav");
	som.setBuffer(buffer[0]);
	som.setVolume(50.0f);

	buffer[1].loadFromFile("Som\\perder.wav");
	perder.setBuffer(buffer[1]);
	perder.setVolume(40.0f);

	buffer[2].loadFromFile("Som\\raquete.wav");
	Rackt.setBuffer(buffer[2]);
	Rackt.setVolume(50.0f);
}

void Nivel::setBlockColor(int posX, int posY, sf::Color& cor) {

	blocos[posX][posY].brick.setFillColor(cor);
}

void Nivel::restart() {

	bolas[0].setPosition(sf::Vector2f(WIDTH / 2, HEIGTH / 2 + OFFSET_Y + 20.0f));
	raquete.setPosition(WIDTH / 2);
	relogio.restart();
}

int Nivel::run() {

	tempoRestart = relogio.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		raquete.move(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		raquete.move(false);
	}

	if (tempoRestart.asMilliseconds() >= 1000.0) {
		for (int i = 0; i < bolas.size(); i++) {
			bolas[i].move();
			BolaColidirRaquete(bolas[i]);
			if (control > 10) {
				if (bolas[i].position.x - 8 < 0 || bolas[i].position.x + 8 > WIDTH) {
					bolas[i].diretor.x = -bolas[i].diretor.x;
					control = 0;
				}
				if (bolas[i].position.y - 8 < OFFSET_Y) {
					bolas[i].diretor.y = -bolas[i].diretor.y;
					control = 0;
				}
				if (bolas[i].position.y - 15 > HEIGTH) {
					if (bolas.size() == 1) {
						perder.play();
						restart();
						return perdeu_vida;
					}
					bolas.erase(bolas.begin() + i);
					break;
				}
			}
			for (int h = 0; h < 12; h++) {
				for (int j = 0; j < 7; j++) {
					if (blocos[h][j].vida > 0) {
						BolaColidirTijolos(bolas[i], h, j);
					}
				}
			}
		}

		for (int i = 0; i < PowerUps.size(); i++) {
			if (PowerUps[i].visivel == true) {
				PowerUps[i].move();
				if (PowerUps[i].colisaoRaquete(raquete) == true) {
					switch (PowerUps[i].tipo) {
						case 0:
							raquete.setSize(1.5f);
							break;
						case 1:
							raquete.setSize(0.5f);
							break;
						case 2:
							bolas.push_back(Bola(BallVelocity, bolas[0].position, -1));
							bolas.push_back(Bola(BallVelocity, bolas[0].position, 1));
							break;
						case 3:
							for (int i = 0; i < bolas.size(); i++) {
								bolas[i].FireState(true);
							}
							break;
						default:
							break;
					}
					PowerUps[i].setInvisible();
				}
				if (PowerUps[i].getPosition().y > HEIGTH + 10) {
					PowerUps.erase(PowerUps.begin() + i);
				}
			}
			else {
				if (PowerUps[i].UpTime() == false) {
					switch (PowerUps[i].tipo)
					{
					case 0:
						raquete.setSize(1.0f);
						break;
					case 1:
						raquete.setSize(1.0f);
						break;
					case 2:
						break;
					case 3:
						for (int i = 0; i < bolas.size(); i++) {
							bolas[i].FireState(false);
						}
						break;
					}
					PowerUps.erase(PowerUps.begin() + i);
				}
			}
		}
	}
	control++;

	if (totalBlocks == 0) {
		return nivel_completo;
	}
	return 0;
}


void Nivel::BolaColidirTijolos(Bola &bola, int a, int b) {

	sf::Vector2f BlocoPosition;
	BlocoPosition.x = blocos[a][b].getPosition().x;
	BlocoPosition.y = blocos[a][b].getPosition().y;
	sf::Vector2f otherHalfSize;
	otherHalfSize.x = blocos[a][b].getHalfSize().x;
	otherHalfSize.y = blocos[a][b].getHalfSize().y;

	float deltaX = BlocoPosition.x - bola.position.x;
	float deltaY = BlocoPosition.y - bola.position.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + bola.raio);
	float intersectY = abs(deltaY) - (otherHalfSize.y + bola.raio);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		som.play();
		if (!bola.isOnFire) {
			if (intersectX > intersectY) {
				bola.diretor.x = -bola.diretor.x;
			}
			else {
				if (deltaY < 0) {
					bola.diretor.y = abs(bola.diretor.y);
				}
				else {
					bola.diretor.y = -abs(bola.diretor.y);
				}
			}
		}

		//Criar Prémio
		int recompensa = rand() % 100;
		if (recompensa >= 80) {
			PowerUps.emplace_back(PowerUp(blocos[a][b].getPosition(), PowerUpsTexturas));
		}

		blocos[a][b].vida--;
		if (blocos[a][b].vida == 1) {
			blocos[a][b].brick.setTexture(NULL);
		}
		if (blocos[a][b].vida == 0) {
			totalBlocks--;
		}
		//bola.setDirection(diretor);
	}
}

void Nivel::BolaColidirRaquete(Bola &bola) {

	sf::Vector2f otherHalfSize;
	otherHalfSize.x = raquete.size.x / 2;
	otherHalfSize.y = raquete.size.y / 2;

	float deltaX = raquete.position.x - bola.position.x;
	float deltaY = raquete.position.y - bola.position.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + bola.raio);
	float intersectY = abs(deltaY) - (otherHalfSize.y + bola.raio);

	bola.TempoNovaBatida++;
	if(bola.TempoNovaBatida > 5) {
		if (intersectX < 0.0f && intersectY < 0.0f) {
			bola.TempoNovaBatida = 0;
			Rackt.play();
			if (intersectX < intersectY) {

				float point = bola.position.x - raquete.position.x;
				//std::cout << point << "  ";
				float teta = point * MAX_ANGLE / (raquete.size.x / 2);
				teta = teta * (M_PI / 180);
				//std::cout << teta * (180 / M_PI) << " New: ";
				float tempx = bola.diretor.x;
				float tempy = -bola.diretor.y;
				bola.diretor.x = (float)tempx * cos(teta) - tempy * sin(teta);
				bola.diretor.y = (float)tempx * sin(teta) + tempy * cos(teta);
				//std::cout << "x " << bola.diretor.x << "     y " << bola.diretor.y << "\n";
			}
			else {
				bola.diretor.x = -bola.diretor.x;
			}
		}
	}
}

void Nivel::draw(sf::RenderWindow& janela) {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			if (blocos[i][j].vida > 0) {
				blocos[i][j].draw(janela);
			}
		}
	}
	for (int i = 0; i < PowerUps.size(); i++) {
		PowerUps[i].draw(janela);
	}
	for (int i = 0; i < bolas.size(); i++) {
		bolas[i].draw(janela);
	}
	raquete.draw(janela);
}



Nivel::~Nivel()
{
}

