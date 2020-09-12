#include <SFML\Graphics.hpp> 
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Tetromio.h"
#include "RoundFrame.h"


int tabuleiro[HEIGHT][WIDTH] = {0};


bool pecas[7][4][2] =
{ { { 1, 1 },	
{ 1, 1 },		// 0 0
{ 0, 0 },		// 0 0
{ 0, 0 } },     

{ { 0, 1 },     // 0
{ 0, 1 },       // 0
{ 0, 1 },       // 0
{ 0, 1 } },     // 0

{ { 1, 0 },		// 0
{ 1, 1 },		// 0 0
{ 1, 0 },		// 0
{ 0, 0 } },     

{ { 1, 0 },     // 0
{ 1, 1 },       // 0 0
{ 0, 1 },       //   0
{ 0, 0 } },     
  
{ { 0, 1 },     //   0
{ 1, 1 },		// 0 0
{ 1, 0 },		// 0
{ 0, 0 } },
 
{ { 1, 0 },     // 0
{ 1, 0 },       // 0
{ 1, 1 },       // 0 0
{ 0, 0 } },     

{ { 0, 1 },		//   0
{ 0, 1 },		//   0
{ 1, 1 },		// 0 0
{ 0, 0 } }
};


int main() {

	sf::RenderWindow window(sf::VideoMode(450, 704), "Tetris");
	window.setFramerateLimit(60);

	srand(time(NULL));

	Tetromio figuras[7] = { Tetromio(pecas[0], 0, sf::Color::Yellow),
						Tetromio(pecas[1], 1, sf::Color::Blue), 
						Tetromio(pecas[2], 2, sf::Color(179, 0 ,179)),
						Tetromio(pecas[3], 3, sf::Color::Red), 
						Tetromio(pecas[4], 4, sf::Color::Green),
						Tetromio(pecas[5], 5, sf::Color(255, 100, 0)), 
						Tetromio(pecas[6], 6, sf::Color(50, 160, 255)),
	};

	Tetromio *atual = new Tetromio(figuras[rand() % 7]);
	Tetromio *next = new Tetromio(figuras[rand() % 7]);
	next->setPlace(sf::Vector2f(330.0f, 80.0f));
	Tetromio* hold = NULL;

	sf::Clock relogio;
	float delay = 800;


	sf::Music theme;
	if (!theme.openFromFile("C:\\Users\\Emanuel\\source\\repos\\Jogos\\Tetris_Game\\TetrisMusic/TetrisTheme.ogg")) {
		std::cout << "ERROR!\n";
	}
	theme.play();
	theme.setLoop(true);
	theme.setVolume(10.0f);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("C:\\Users\\Emanuel\\source\\repos\\Jogos\\Tetris_Game\\TetrisMusic/potencial.wav");
	sf::Sound som;
	som.setBuffer(buffer);
	som.setVolume(5.0f);
	som.setPitch(0.6f);
	
	int score = 0;
	sf::Font font;
	font.loadFromFile("C:\\Users\\Emanuel\\source\\repos\\Jogos\\Tetris_Game\\Fonts/NEW LED DISPLAY ST.ttf");
	sf::Text pontuacao;
	pontuacao.setFont(font);
	pontuacao.setCharacterSize(30);
	pontuacao.setString(std::to_string(score));
	pontuacao.setPosition(sf::Vector2f(330.0f, 460.0f));
	pontuacao.setFillColor(sf::Color(10, 255, 10));

	std::string onFile;
	int high_score = 0;
	std::ifstream see_score("high score.txt");
	while (std::getline(see_score, onFile))
	{
		std::cout << onFile << "\n";
		high_score = std::stoi(onFile);
	}
	std::cout << "High Score: " << high_score << "\n";
	see_score.close();

	sf::Font font2;
	font2.loadFromFile("C:\\Users\\Emanuel\\source\\repos\\Jogos\\Tetris_Game\\Fonts/NEW LED DISPLAY ST.ttf");
	sf::Text HighScore;
	HighScore.setFont(font2);
	HighScore.setCharacterSize(30);
	HighScore.setString(std::to_string(high_score));
	HighScore.setPosition(sf::Vector2f(320.0f, 610.0f));
	HighScore.setFillColor(sf::Color(10, 255, 10));


	Moldura<Tetromio> molduraNextPiece(sf::IntRect(305.0f, 45.0f, 100.0f, 100.0f), "Next", *next);
	Moldura<Tetromio> molduraHoldPiece(sf::IntRect(305.0f, 215.0f, 100.0f, 100.0f), "Hold", figuras[3]);
	Moldura<sf::Text> molduraScore(sf::IntRect(305.0f, 405.0f, 100.0f, 100.0f), "Score", pontuacao);
	Moldura<sf::Text> molduraHighScore(sf::IntRect(305.0f, 585.0f, 100.0f, 100.0f), "High score!", HighScore);


	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					atual->move(0);
					break;
				case sf::Keyboard::Right:
					atual->move(1);
					break;
				case sf::Keyboard::Up:
					atual->rotate(90);
					break;
				case sf::Keyboard::Down:
					delay = 10;
					break;
				case sf::Keyboard::E:
					//Tetromio temp = *hold;
					hold = new Tetromio(*atual);
					hold->setPlace(sf::Vector2f(330.0f, 260.0f));
					if(hold == nullptr) {
					} else {
						atual = new Tetromio(*hold);
					}
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Down) {
					delay = 800;
				}
			}
		}
		//std::cout << delay << "\n";
		sf::Time tempo = relogio.getElapsedTime();
		if (tempo.asMilliseconds() > float(delay)) {
			if (!atual->isDown() && (atual->Collision(tabuleiro) == false)) {
				atual->getDown();
			}
			else {
				for (int i = 0; i < 4; i++) {
					int x = atual->getPosition(i).x / LadoQuadrados;
					int y = atual->getPosition(i).y / LadoQuadrados;
					tabuleiro[y][x] = atual->getColor();
				}
				score++;
				atual = new Tetromio(figuras[next->getID()]);
				next = new Tetromio(figuras[rand() % 7]);
				next->setPlace(sf::Vector2f(330.0f, 80.0f));
			}
			relogio.restart(); 
		}

		{
			bool fila = true;
			int linhas = 0;
			for (int row = HEIGHT - 1; row >= 0; row--) {
				fila = true;
				for (int colum = 0; colum < WIDTH; colum++) {
					if (tabuleiro[row][colum] == 0) {
						fila = false;
					}
				}
				if (fila) {
					linhas++;
					som.play();
					for (int m = row; m > 0; m--) {
						for (int n = 0; n < WIDTH; n++) {
							tabuleiro[m][n] = tabuleiro[m - 1][n];
						}
					}
				}
			}
			switch (linhas)
			{
			case 1: 
				score += 50;
				break;
			case 2:
				score += 150;
				break;
			case 3:
				score += 400;
				break;
			case 4:
				score += 1000;
				break;
			default:
				break;
			}
		}
		pontuacao.setString(std::to_string(score));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			break;
		}

		window.clear();
		for (int m = 0; m < HEIGHT; m++) {
			for (int n = 0; n < WIDTH; n++) {
				drawQ(window, m, n, tabuleiro[m][n]);
			}
		}
		atual->draw(window);
		next->draw(window);
		if (hold != nullptr) {
			hold->draw(window);
		}
		window.draw(HighScore);
		molduraNextPiece.draw(window);
		molduraHoldPiece.draw(window);
		molduraScore.draw(window);
		molduraHighScore.draw(window);
		window.draw(pontuacao);

		window.display();
	}

	std::ofstream max_score;
	max_score.open("high score.txt", std::ios::app);
	if (score > high_score) {
		std::cout << score << "\n";
		max_score << score << "\n";
	}
	max_score.close();
}