#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <deque>
#include <string.h>
#include "bird.h"
#include "tubo.h"


#define WIDTH 900
#define HEIGTH 550


class Nuvem
{
public:
	Nuvem(const std::string textname, short ID) {
		Tex.loadFromFile(textname);
		s.setTexture(Tex);
		s.setScale(sf::Vector2f(0.2f, 0.2f));
		s.setPosition(sf::Vector2f((rand() % 20) * 50.0f + (WIDTH + ((ID - 1) * 360.0f)) , float(rand() % 240)));
	}

	void draw(sf::RenderWindow& janela) {
		janela.draw(s);
	}

	void UpDate() {
		s.move(sf::Vector2f(-2.5f, 0.0f));
		if (s.getPosition().x < -100.0f) {
			s.setPosition(sf::Vector2f((rand() % 20) * 20.0f + 700.0f, float(rand() % 240)));
		}
	}

private:
	sf::Sprite s;
	sf::Texture Tex;
};


int main() {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "Flappy Duck"); 
	window.setFramerateLimit(60);

	sf::RectangleShape relva(sf::Vector2f(WIDTH, 120));
	relva.setPosition(sf::Vector2f(0.0f, HEIGTH - 120));
	relva.setFillColor(sf::Color(30, 200, 12, 200));

	srand(time(NULL));

restart:

	Bird passaro;
	int a = rand() % 370 + 10;
	std::deque<Tubo> tubos;
	for (int i = 0; i < 3; i++) {
		int a = rand() % 370 + 10;
		tubos.emplace_back(a, 700.0f + i * 300.0f);
	}

	bool runGame = true;
	bool plus1 = true;

	int score = 0;
	sf::Font font;
	if (!font.loadFromFile("LetraNormal.ttf")) {
		//font.loadFromFile("C:\\Users\\Emanuel\\source\\repos\\Jogos\\FlappyDuck_Game\\LetraNormal.ttf")
	}

	sf::Text texto;
	texto.setFont(font);
	std::string pontos = "score: ";
	texto.setString(pontos);
	texto.setCharacterSize(25);
	texto.setFillColor(sf::Color::Red);
	texto.setPosition(sf::Vector2f(10.0f, HEIGTH - 40.0F));

	sf::VertexArray skyShade(sf::Quads, 4);
	skyShade[0].position = sf::Vector2f(0.0f, 0.0f); skyShade[1].position = sf::Vector2f(WIDTH, 0.0f);
	skyShade[2].position = sf::Vector2f(WIDTH, HEIGTH - relva.getSize().y); 
	skyShade[3].position = sf::Vector2f(0.0f, HEIGTH - relva.getSize().y);
	skyShade[0].color = sf::Color(92, 118, 255); skyShade[1].color = sf::Color(92, 118, 255);
	skyShade[2].color = sf::Color::Blue; skyShade[3].color = sf::Color::Blue;

	std::deque<Nuvem*> nuvens;
	nuvens.push_back(new Nuvem("C:\\Users\\Emanuel\\source\\repos\\Jogos\\FlappyDuck_Game\\NuvemC.png", 1));
	nuvens.push_back(new Nuvem("C:\\Users\\Emanuel\\source\\repos\\Jogos\\FlappyDuck_Game\\NuvemC.png", 2));
	nuvens.push_back(new Nuvem("C:\\Users\\Emanuel\\source\\repos\\Jogos\\FlappyDuck_Game\\NuvemC.png", 3));


	while (window.isOpen()) {

		sf::Event evento;
		while (window.pollEvent(evento))
		{
			if (evento.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (runGame == true) {
			passaro.getDown();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
				passaro.Up();
			}

			for (int i = 0; i < tubos.size(); i++) {
				tubos[i].UpDate();

				runGame = !passaro.Colizion(tubos[i]);
				if (runGame == false) {
					//texto.scale(sf::Vector2f(2.0f, 1.5f));
					texto.setCharacterSize(60);
					texto.Bold;
					texto.setPosition(sf::Vector2f(350.0f, 180.0f));
					break;
				}
			}
			if (tubos.front().getXPosistion() <= -50.0f) {
				tubos.erase(tubos.begin());
				int a = rand() % 370 + 10;
				tubos.emplace_back(a, 870.0f);
				plus1 = true;
			}
			if (tubos.front().getXPosistion() <= 350.0f) {
				if (plus1) {
					score++;
					plus1 = false;
				}
			}
			for (int i = 0; i < nuvens.size(); i++) {
				nuvens[i]->UpDate();
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
				runGame = true;
				goto restart;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
				return 0;
			}
		}
		pontos = "score: " + std::to_string(score);
		texto.setString(pontos);

		//std::cout << runGame << "\n";
		//std::cout << tubos.size() << "\n";

		window.clear();
		window.draw(skyShade);
		window.draw(relva);
		for (int i = 0; i < nuvens.size(); i++) {
			nuvens[i]->draw(window);
		}
		for (int i = 0; i < tubos.size(); i++) {
			tubos[i].draw(window);
		}
		passaro.draw(window);
		window.draw(texto);
		window.display();
	}
}