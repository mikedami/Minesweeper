#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class Tile {
public:

	sf::Sprite *tileStruct[4];
	bool isFlag = false;
	bool isMine = false;
	bool isNumber = false;
	bool isGameOver = false;
	bool isRevealed = false;
	int xPosition = 0;
	int yPosition = 0;
	int adjacentMines = 0;
	vector<Tile*> adjacentTiles;


	Tile();
	sf::Sprite* setHidden(sf::Texture arr[], int index);
	sf::Sprite* setClear(sf::Texture arr[], int index);
	sf::Sprite* setMine(sf::Texture arr[], int index);
	sf::Sprite* setFlag(sf::Texture arr[], int index);
	sf::Sprite* setNumber(sf::Texture arr[], int index);
};