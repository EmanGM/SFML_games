#include "Explosion.h"



Animation::Animation(sf::Texture* text, unsigned int numeroImagens)
{
	this->numeroImagens = numeroImagens;
	imagemAtual = 0;

	xyRect.height = text->getSize().y / float(1);
	xyRect.width = (text->getSize().x - 24) / float(this->numeroImagens);
}

bool  Animation::Update() {
	imagemAtual++;
	if (imagemAtual + 1 == numeroImagens) {
		return false;
		imagemAtual = 0;
	}
	xyRect.left = imagemAtual * xyRect.width;

	return true;
}

Animation::~Animation()
{
}


Explosion::Explosion(sf::Texture* text, sf::Vector2f position) : animacao(text, 20) {

	explosion.setPosition(position);
	explosion.setTexture(*text);
	explosion.setOrigin((float)animacao.xyRect.width / 2, (float)animacao.xyRect.height / 2);
	explosion.setScale(2.0f, 2.0f);
}

bool Explosion::Update() {

	tempoFrame = contador_tempoExplosao.getElapsedTime();
	if (tempoFrame.asMilliseconds() >= 20.0f) {
		if (animacao.Update() == false) {
			return false;
		}
		contador_tempoExplosao.restart();
	}
	explosion.setTextureRect(animacao.xyRect);
	return true;
}


void Explosion::draw(sf::RenderWindow& janela) {
	janela.draw(explosion);
}

