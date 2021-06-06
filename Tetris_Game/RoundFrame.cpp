#include "RoundFrame.h"
#include <iostream>



template <class Temp>

Moldura<Temp>::Moldura(sf::IntRect tam, std::string texto, Temp in_midle) : frame (tam) , temp(&in_midle) {

	font.loadFromFile("Fonts\\homespun.ttf");
	description.setFont(font);
	description.setCharacterSize(24);
	description.setString(texto);
	description.setPosition(sf::Vector2f(tam.left + 2.0f, tam.top - 30.0f));
	//description.setColor(sf::Color::White);
}



//Esta Linha é necessária porque é assim que os templates funcionam 
//(a declaração tem de ser visível) para não gerar "linking errors", 
//ver: https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//chama-se inicialização explícita de templates
template class Moldura<Tetromio>;
template class Moldura<sf::Text>;


template <class T>
void drawEsp(sf::RenderWindow &window, T &t) { }

template <>
void drawEsp<Tetromio>(sf::RenderWindow& window, Tetromio &peca) {
	peca.draw(window);
}

template <>
void drawEsp<sf::Text>(sf::RenderWindow& window, sf::Text &text) {
	window.draw(text);
}

template <class Temp> 

void Moldura<Temp>::draw(sf::RenderWindow &janela) {
	janela.draw(description);
	frame.draw(janela);
	drawEsp(janela, temp);
}



RoundFrame::RoundFrame(sf::IntRect tam_and_pos) {

	textura.loadFromFile("RoundFrame.png");

	sprite.setTexture(textura);
	sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	sf::Vector2f escala;
	escala.x = tam_and_pos.width / textura.getSize().x;
	escala.y = tam_and_pos.height / textura.getSize().y;
	sprite.setScale(escala);

	sprite.setPosition(tam_and_pos.left, tam_and_pos.top);
}


void RoundFrame::setColor(sf::Color cor) {
	sprite.setColor(cor);
}

void RoundFrame::draw(sf::RenderWindow& janela) {
	janela.draw(sprite);
}