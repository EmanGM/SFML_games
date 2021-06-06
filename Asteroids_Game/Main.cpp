#include <SFML\Graphics.hpp>
#include <iostream>
#include <deque> // or vector
#include <cmath>
#include <ctime>
#include "Player.h"
#include "Asteroides.h"
#include "Explosion.h"

#include <list>
#include <ctime>



bool ColizaoTiroAstro(Tiro& tiro, Asteroides* astro) {

	sf::Vector2f distance;
	distance.x = tiro.position.x - astro->getPosition().x;
	distance.y = tiro.position.y - astro->getPosition().y;
	float distancia = pow(distance.x, 2) + pow(distance.y, 2);
	float delta = astro->raio + 100.0f;
	//std::cout << distancia << "\n";

	if (distancia < delta) {
		return true;
	}
	return false;
}

bool ColizaoPlayerAstro(Player& player, Asteroides* astro) {

	sf::Vector2f PlayerCenter = player.getCenter();
	float PlayerRaio = 15.0f;
	sf::Vector2f AstroCenter = astro->getPosition();
	float AstroRaio = astro->raio;
	float Distance = sqrt(pow(PlayerCenter.x - AstroCenter.x, 2) + pow(PlayerCenter.y - AstroCenter.y, 2));
	float delta = AstroRaio + PlayerRaio;
	if (Distance <= delta) {
		return true;
	}
	return false;
}


int main() {

	sf::RenderWindow window(sf::VideoMode(VisionSize, VisionSize), "Asteróides");
	window.setFramerateLimit(40);

	srand(time(NULL));

	sf::Texture text;
	text.loadFromFile("fundo.png");
	sf::Sprite Fundo(text);
	Fundo.setPosition(sf::Vector2f(-(GameLimit / 2), -(GameLimit / 2)));
	sf::Vector2f fator((float)GameLimit / text.getSize().x, (float)GameLimit / text.getSize().y);
	Fundo.scale(fator);

	sf::Texture textura;
	textura.loadFromFile("SpaceShip.png");
	Player player(textura);

	sf::View visao;
	visao.setSize(sf::Vector2f(VisionSize, VisionSize));
	visao.setCenter(sf::Vector2f(VisionSize / 2, VisionSize / 2));
	//visao.zoom(2.5f);

	//Tiro tiro;
	//std::vector<Tiro> tiros;
	clock_t tiro_intervalo;
	tiro_intervalo = clock();

	sf::Texture Tex;
	Tex.loadFromFile("AsteroidesSpritesheet.png");

	//Criar n asteroides, mas apenas 50 dentro da área de jogo
	int AsteroidesInGame = 50;
	std::deque<Asteroides*> astros;
	for (int i = 0; i < 500 + AsteroidesInGame; i++) {
		if (i < 499) {
			astros.emplace_back(new Asteroides(1, false, &Tex));
		}
		else {
			astros.emplace_back(new Asteroides(1, true, &Tex));
		}
	}

	sf::Texture AnimationTex;
	AnimationTex.loadFromFile("Animação\\type_A.png");
	std::deque<Explosion*> explosions;

	sf::Vector2f alvo;

	sf::RectangleShape LimitZone(sf::Vector2f(NaveLimit, NaveLimit));
	LimitZone.setPosition(sf::Vector2f(-(NaveLimit / 2), -(NaveLimit / 2)));
	LimitZone.setOutlineThickness(2.0f);
	LimitZone.setOutlineColor(sf::Color::Red);
	LimitZone.setFillColor(sf::Color::Transparent);


	sf::Font font;
	font.loadFromFile("Font\\CT ProLamina.ttf");
	sf::Text Str_score;
	Str_score.setFont(font);
	Str_score.setString("P: 000000");
	Str_score.setCharacterSize(40);
	Str_score.setFillColor(sf::Color::Black);
	Str_score.setPosition(sf::Vector2f(20.0f, 10.0f));
	int score = 0;


	while (window.isOpen()) {

		alvo.x = sf::Mouse::getPosition(window).x - (VisionSize / 2);
		alvo.y = sf::Mouse::getPosition(window).y - (VisionSize / 2);
		alvo.x += visao.getCenter().x;
		alvo.y += visao.getCenter().y;
		player.ShootDirection(alvo);


		sf::Event evento;
		while (window.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
			if (evento.type == sf::Event::KeyPressed) {
				switch (evento.key.code) {

				case sf::Keyboard::Key::W:
					player.acelerar(frente);
					break;
				case sf::Keyboard::Key::S:
					player.acelerar(tras);
					break;
				case sf::Keyboard::Key::A:
					player.rotate(-15);
					break;
				case sf::Keyboard::Key::D:
					player.rotate(15);
					break;
				default:
					break;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (((float)(clock() - tiro_intervalo)) / CLOCKS_PER_SEC >= 0.5) {
				player.Shoot();
				tiro_intervalo = 0.0f;
			}
		}
		if ((float)tiro_intervalo/ CLOCKS_PER_SEC < 0.5) {
			tiro_intervalo = clock();
			//std::cout << (float)tiro_intervalo << "\n";
		}

		player.move();


		for (unsigned int i = 0; i < astros.size(); i++) {
			astros[i]->move();
			if (ColizaoPlayerAstro(player, astros[i])) {
				//std::cout << "C\n";
				player.restart();
				score = 0;
			}

			if (astros[i]->position.x < -(GameLimit / 2) - astros[i]->raio || astros[i]->position.y < -(GameLimit / 2) - astros[i]->raio ||
				astros[i]->position.x >(GameLimit / 2) + astros[i]->raio || astros[i]->position.y >(GameLimit / 2) + astros[i]->raio) {
				int nextTier = astros[i]->getTier();
				if (astros[i]->isInGame()) {
					astros.push_back(new Asteroides(nextTier, true, &Tex));
					//std::cout << "A\n";
					astros.erase(astros.begin() + i);
				}
				else {
					astros.insert(astros.begin() + i, new Asteroides(nextTier, false, &Tex));
					astros.erase(astros.begin() + i + 1);
				}
			}
		}
		while(AsteroidesInGame < 50) {
			astros.push_back(new Asteroides(1, true, &Tex));
			AsteroidesInGame++;
		}
		//std::cout << tiros.size() << "  A: " << astros.size() << "\n";
		//std::cout << player.getNavePosition().x << "  Y: " << player.getNavePosition().y << "\n";
		for (unsigned int i = 0; i < player.tiros.size(); i++)
		{
			player.tiros[i].move();
			if (player.tiros[i].position.x < -(GameLimit / 2) || player.tiros[i].position.y < -(GameLimit / 2) ||
				player.tiros[i].position.x >(GameLimit / 2) || player.tiros[i].position.y >(GameLimit / 2)) {
				player.tiros.erase(player.tiros.begin() + i);
				break;
			}
			//std::cout << "  A: " << astros.size() << "\n";

			for (unsigned int j = 499; j < astros.size(); j++) {
				//std::cout << "a: " << astros.size() << "  j: " << j << "\n ";

				if (ColizaoTiroAstro(player.tiros[i], astros[j])) {
					//std::cout << astros.size() << "\n";
					player.tiros.erase(player.tiros.begin() + i);
					int MotherTier = astros[j]->getTier();
					switch (MotherTier)
					{
					case 1:
						score += 50;
						break;
					case 2:
						score += 20;
						break;
					case 3:
						score += 5;
						break;
					}
					sf::Vector2f MotherDirection = astros[j]->getDirection();
					sf::Vector2f MotherPlace = astros[j]->getPosition();
					explosions.push_back(new Explosion(&AnimationTex, MotherPlace));
					astros.erase(astros.begin() + j);
					AsteroidesInGame--;
					if (MotherTier < 3) {
						astros.insert(astros.begin() + j, new Asteroides(MotherTier + 1, true, &Tex));
						astros[j]->setAngleDirection(MotherDirection, 330);
						astros[j]->setPosition(MotherPlace);
						astros.insert(astros.begin() + (j + 1), new Asteroides(MotherTier + 1, true, &Tex));
						astros[j + 1]->setAngleDirection(MotherDirection, -330);
						astros[j + 1]->setPosition(MotherPlace);
						j++;
						break;
					}
					break;
				}
			}
		}
		for (unsigned int i = 0; i < explosions.size(); i++) {
			if (explosions[i]->Update() == false) {
				explosions.pop_front();
			}
		}

		Str_score.setPosition(sf::Vector2f(visao.getCenter().x - (VisionSize / 2) + 20.0f, visao.getCenter().y - (VisionSize / 2)));
		Str_score.setString(std::string("P: " + std::to_string(score)));

		//Definir o centro da janela:
		sf::Vector2f centro = player.getNavePosition();
		if (player.getNavePosition().x < (VisionSize / 2) - (GameLimit / 2)) {
			centro.x = (VisionSize / 2) - (GameLimit / 2);
		}
		if (player.getNavePosition().y < (VisionSize / 2) - (GameLimit / 2)) {
			centro.y = (VisionSize / 2) - (GameLimit / 2);
		}
		if (player.getNavePosition().x > -(VisionSize / 2) + (GameLimit / 2)) {
			centro.x = -(VisionSize / 2) + (GameLimit / 2);
		}
		if (player.getNavePosition().y > -(VisionSize / 2) + (GameLimit / 2)) {
			centro.y = -(VisionSize / 2) + (GameLimit / 2);
		}
		visao.setCenter(centro);


		//draw
		window.clear();
		window.draw(Fundo);
		window.draw(LimitZone);
		for (unsigned int i = 0; i < astros.size(); i++) {
			if (astros[i]->getPosition().x + 50.0f > (visao.getCenter().x - VisionSize / 2) &&
				astros[i]->getPosition().x - 50.0f < (visao.getCenter().x + VisionSize / 2) &&
				astros[i]->getPosition().y + 50.0f > (visao.getCenter().y - VisionSize / 2) &&
				astros[i]->getPosition().y - 50.0f < (visao.getCenter().y + VisionSize / 2)) {
			astros[i]->draw(window);
			}
		}
		for (unsigned int i = 0; i < explosions.size(); i++) {
			explosions[i]->draw(window);
		}
		player.draw(window);
		window.draw(Str_score);
		window.setView(visao);
		window.display();
	}
}