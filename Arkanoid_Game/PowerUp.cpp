#include "PowerUp.h"



PowerUp::PowerUp(sf::Vector2f tijoloPosition, sf::Texture *Text)
{
	raio = 10.0f;
	powerUp.setRadius(raio);
	powerUp.setOrigin(sf::Vector2f(raio / 2, raio / 2));
	position.x = tijoloPosition.x;
	position.y = tijoloPosition.y;
	powerUp.setPosition(position);
	visivel = true;

	tipo = rand() % 4;
	this->text = (Text + tipo);
	if (tipo == 0 || tipo == 1) {
		tempo = 6;
	}
	else {
		tempo = 5;
	}
	powerUp.setTexture(text);
}

void PowerUp::move() {
	powerUp.move(sf::Vector2f(0.0f, 1.0f));
}

sf::Vector2f PowerUp::getPosition() {
	return powerUp.getPosition();
}


bool PowerUp::UpTime() {
	if (visivel == false) {
		time = clock.getElapsedTime();
		//std::cout << time.asSeconds() << " ";
		if (time.asSeconds() >= tempo) {
			std::cout << "Acabou!";
			clock.restart();
			return false;
		}
	}
	return true;
}

void PowerUp::setInvisible() {
	visivel = false;
	clock.restart();
}

bool PowerUp::colisaoRaquete(Racket& raquete) {

	sf::FloatRect bola = powerUp.getGlobalBounds();
	sf::FloatRect raquet = raquete.racket.getGlobalBounds();
	if (bola.intersects(raquet)) {
		clock.restart();
		return true;
	}
	return false;
}

void PowerUp::draw(sf::RenderWindow& janela) {
	if (visivel == true) {
		janela.draw(powerUp);
	}
}

PowerUp::~PowerUp()
{
}
