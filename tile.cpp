#include "tile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

Tile::Tile() {
	tileStruct[3] = nullptr;
	tileStruct[2] = nullptr;
	tileStruct[1] = nullptr;
	tileStruct[0] = nullptr;
}

sf::Sprite* Tile::setHidden(sf::Texture arr[], int index) {
	sf::Sprite* hidden = new sf::Sprite();
	hidden->setTexture(arr[index]);
	return hidden;
}

sf::Sprite* Tile::setClear(sf::Texture arr[], int index) {
	sf::Sprite* clear = new sf::Sprite();
	clear->setTexture(arr[index]);
	return clear;
}

sf::Sprite* Tile::setMine(sf::Texture arr[], int index) {
	sf::Sprite* mine = new sf::Sprite();
	mine->setTexture(arr[index]);
	return mine;
}

sf::Sprite* Tile::setFlag(sf::Texture arr[], int index) {
	sf::Sprite* flag = new sf::Sprite();
	flag->setTexture(arr[index]);
	return flag;
}

sf::Sprite* Tile::setNumber(sf::Texture arr[], int index) {
	sf::Sprite* number = new sf::Sprite();
	number->setTexture(arr[index]);
	return number;
}
