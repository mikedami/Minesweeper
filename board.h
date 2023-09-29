#pragma once
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Board {
public:

	int rowAmt;
	int columnAmt;
	int mineCount;
	int tileCount;
	sf::Texture boardTextures[20];
	vector<vector<Tile>> vect;
	bool gameOver = false;
	bool winW = false;
	bool debugToggle = false;
	int winCount = 0;
	bool isTest = false;
	sf::Sprite digitSprites[11];
	vector<sf::Sprite> displayDigits;

	Board();
	void Draw(sf::Texture arr[]);
	void Reveal(Tile t, sf::Texture arr[]);
	bool inRange(int row_, int column_);
	int setAdjacent(int row, int column);
	Tile placeFlag(Tile t, sf::Texture arr[]);
	Tile removeFlag(Tile t, sf::Texture arr[]);
	void lose(Tile t, sf::Texture arr[]);
	void win(sf::Texture arr[]);
	void debug(sf::Texture arr[]);
	void DrawTest(sf::Texture arr[], int idex);
	void setDigits(sf::Texture arr[]);
	void writeDigits(sf::Texture arr[]);
	void setAdjacentTiles();
};