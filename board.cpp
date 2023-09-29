#include "tile.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

Board::Board() {

	rowAmt = 0;
	columnAmt = 0;

	boardTextures[0].loadFromFile("images/tile_revealed.png");
	boardTextures[1].loadFromFile("images/tile_hidden.png");
	boardTextures[2].loadFromFile("images/mine.png");
	boardTextures[3].loadFromFile("images/flag.png");
	boardTextures[4].loadFromFile("images/test_1.png");
	boardTextures[5].loadFromFile("images/test_2.png");
	boardTextures[6].loadFromFile("images/test_3.png");
	boardTextures[7].loadFromFile("images/debug.png");
	boardTextures[8].loadFromFile("images/digits.png");
	boardTextures[9].loadFromFile("images/face_happy.png");
	boardTextures[10].loadFromFile("images/face_lose.png");
	boardTextures[11].loadFromFile("images/face_win.png");
	int j = 12;
	for (int i = 1; i <= 8; i++) {
		string temp = to_string(i);
		string path = "images/number_" + temp + ".png";
		boardTextures[j].loadFromFile(path);
		j++;
	}
}

bool Board::inRange(int row_, int column_) {
	bool temp = (row_ >= 0) && (column_ >= 0) && (row_ < rowAmt) && (column_ < columnAmt);
	return temp;
}

int Board::setAdjacent(int row, int column) {
	int countForTile = 0;
	int count = 0;
	if (inRange(row+1, column) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row + 1][column]);
		if (vect[row+1][column].isMine == true) {
			count++;
		}
	}
	if (inRange(row, column+1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row][column+1]);
		if (vect[row][column+1].isMine == true) {
			count++;
		}
	}
	if (inRange(row-1, column) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row-1][column]);
		if (vect[row-1][column].isMine == true) {
			count++;
		}
	}
	if (inRange(row, column-1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row][column-1]);
		if (vect[row][column-1].isMine == true) {
			count++;
		}
	}
	if (inRange(row+1, column+1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row+1][column+1]);
		if (vect[row+1][column+1].isMine == true) {
			count++;
		}
	}
	if (inRange(row-1, column-1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row-1][column-1]);
		if (vect[row-1][column-1].isMine == true) {
			count++;
		}
	}
	if (inRange(row+1, column-1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row+1][column-1]);
		if (vect[row+1][column-1].isMine == true) {
			count++;
		}
	}
	if (inRange(row-1, column+1) == true) {
		vect[row][column].adjacentTiles.push_back(&vect[row-1][column+1]);
		if (vect[row-1][column+1].isMine == true) {
			count++;
		}
	}
	return count;
}

void Board::setDigits(sf::Texture arr[]) {
	int left = 0;
	int top = 0;
	for (int i = 0; i < 11; i++) {
		sf::Sprite s;
		s.setTexture(arr[8]);
		s.setTextureRect(sf::IntRect(left, top, 21, 32));
		digitSprites[i] = s;
		left += 21;
	}
}

void Board::setAdjacentTiles() {
	//setting adjacent tiles
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			vect[i][j].adjacentMines = setAdjacent(i, j);
		}
	}
}

void Board::writeDigits(sf::Texture arr[]) {
	vector<sf::Sprite> newVec;
	displayDigits = newVec;
	int temp = mineCount;

	if (temp < 0) {
		displayDigits.push_back(digitSprites[10]);
		temp = abs(mineCount);
	}
	if (temp < 10) {
		for (int j = 0; j < 10; j++) {
			if (temp == j) {
				displayDigits.push_back(digitSprites[j]);
			}
		}
	}
	else if (temp < 100) {
		int num1 = temp / 10;
		int num2 = temp % 10;
		displayDigits.push_back(digitSprites[num1]);
		displayDigits.push_back(digitSprites[num2]);
	}
	else if (temp < 1000) { //if ex is 584
		int num1 = temp / 100; // = 5
		int num2 = (temp % 100) / 10;  // = 8
		int num3 = temp % 10;  // = 4
		displayDigits.push_back(digitSprites[num1]);
		displayDigits.push_back(digitSprites[num2]);
		displayDigits.push_back(digitSprites[num3]);
	}
	else if (temp < 10000) {
		int num1 = temp / 1000;
		int num2 = (temp % 1000) / 100;
		int num3 = (temp % 100) / 10;
		int num4 = temp % 10;
		displayDigits.push_back(digitSprites[num1]);
		displayDigits.push_back(digitSprites[num2]);
		displayDigits.push_back(digitSprites[num3]);
		displayDigits.push_back(digitSprites[num4]);
	}
}

void Board::Draw(sf::Texture arr[]) {
	ifstream file;
	file.open("boards/config.cfg", ios::in);
	int rows;
	int columns;
	int mineCount;
	string line = "";

	getline(file, line);
	rows = stoi(line);

	getline(file, line);
	columns = stoi(line);

	getline(file, line);
	mineCount = stoi(line);

	rowAmt = rows;
	columnAmt = columns;
	this->mineCount = mineCount;
	this->tileCount = rows * columns;

	vector<vector<Tile>> temp(rows, vector<Tile>(columns));
	vect = temp;

	//setting board (only clear and hidden spaces)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			Tile t;
			t.tileStruct[3] = t.setClear(arr, 0);
			t.tileStruct[2] = t.setHidden(arr, 1);
			vect[i][j] = t;

		}
	}

	//randomly placing mines
	while (mineCount > 0) {
		unsigned int rowX = rand() % rows;
		unsigned int rowY = rand() % columns;
		if (vect[rowX][rowY].isMine == false) {

			vect[rowX][rowY].tileStruct[2] = nullptr;
			vect[rowX][rowY].tileStruct[1] = vect[rowX][rowY].setHidden(arr, 1);
			vect[rowX][rowY].tileStruct[2] = vect[rowX][rowY].setMine(arr, 2);
			vect[rowX][rowY].isMine = true;
			mineCount--;
		}
	}

	file.close();
}

void Board::DrawTest(sf::Texture arr[], int index) {
	ifstream file;
	string testNum = to_string(index);
	string path = "boards/testboard" + testNum + ".brd";
	file.open(path, ios::in);
	int rows = 0;
	int columns = 0;
	int mineCount = 0;
	int mineIndex;
	char mineChar = '1';
	string line = "";

	while (true) {
		if (file.eof()) {
			break;
		}
		getline(file, line);
		rows = line.length();
		columns++;
	}
	
	file.close();
	rowAmt = rows;
	columnAmt = columns;
	this->tileCount = rows * columns;

	vector<vector<Tile>> temp(rows, vector<Tile>(columns));
	vect = temp;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			Tile t;
			t.tileStruct[3] = t.setClear(arr, 0);
			t.tileStruct[2] = t.setHidden(arr, 1);
			vect[i][j] = t;

		}
	}
	
	file.open(path, ios::in);
	for (int i = 0; i < columns; i++) {
		getline(file, line);
		for (int j = 0; j < rows; j++) {
			if (line.at(j) == mineChar) {
				if (vect[j][i].isMine == false) {
					vect[j][i].tileStruct[2] = nullptr;
					vect[j][i].tileStruct[1] = vect[j][i].setHidden(arr, 1);
					vect[j][i].tileStruct[2] = vect[j][i].setMine(arr, 2);
					vect[j][i].isMine = true;
					mineCount++;
				}
			}
		}
	}
	file.close();
	this->mineCount = mineCount;
}

void Board::Reveal(Tile t, sf::Texture arr[]) {

	int tempI = 0;
	int tempJ = 0;
	
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (t.tileStruct[3] == vect[i][j].tileStruct[3]) {
				tempI = i;
				tempJ = j;
			}
		}
	}

	if (t.isFlag == true) {
		return;
	}

	if (t.isRevealed == true) {
		return;
	}

	if (t.isMine == true) {
		t.tileStruct[1] = nullptr;
		t.tileStruct[0] = nullptr;
		t.isGameOver = true;
		t.isRevealed = true;
		vect[tempI][tempJ] = t;
		return;
	}

	else {

		if (t.adjacentMines == 1) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 12);
		}
		else if (t.adjacentMines == 2) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 13);
		}
		else if (t.adjacentMines == 3) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 14);
		}
		else if (t.adjacentMines == 4) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 15);
		}
		else if (t.adjacentMines == 5) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 16);
		}
		else if (t.adjacentMines == 6) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 17);
		}
		else if (t.adjacentMines == 7) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 18);
		}
		else if (t.adjacentMines == 8) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = t.setNumber(arr, 19);
		}
		else if (t.adjacentMines == 0) {
			t.tileStruct[0] = nullptr;
			t.tileStruct[1] = nullptr;
			t.tileStruct[2] = nullptr;
			t.isRevealed = true;
			vect[tempI][tempJ] = t;
			for (int i = 0; i < t.adjacentTiles.size(); i++) {
				if (t.adjacentTiles[i] != nullptr) {
					Reveal(*t.adjacentTiles.at(i), arr);
				}
				//Reveal(*t.adjacentTiles.at(i), arr); 
			}
		}
	}
	t.isRevealed = true;
	t.isNumber = true;
	vect[tempI][tempJ] = t;
}

void Board::lose(Tile t, sf::Texture arr[]) {
	
	int tempI = 0;
	int tempJ = 0;

	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (t.tileStruct[3] == vect[i][j].tileStruct[3]) {
				tempI = i;
				tempJ = j;
			}
		}
	}
	if (t.isGameOver == true) {
		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j < vect[i].size(); j++) {
				if(vect[i][j].isFlag == true && vect[i][j].isMine == true) {
					vect[i][j].tileStruct[1] = nullptr;
				}
				else if (vect[i][j].isMine == true) {
					Reveal(vect[i][j], arr);
				}
			}
		}
		gameOver = true;
	}
}

void Board::win(sf::Texture arr[]) {
	winW = true;
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (vect[i][j].isMine == true) {
				vect[i][j].tileStruct[0] = vect[i][j].setFlag(arr, 3);
			}
		}
	}
}

void Board::debug(sf::Texture arr[]) {
	if (debugToggle == false) {
		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j < vect[i].size(); j++) {
				if (vect[i][j].isMine == true) {
					vect[i][j].tileStruct[0] = vect[i][j].setMine(arr, 2);
				}
			}
		}
		debugToggle = true;
	}
	else if (debugToggle == true) {
		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j < vect[i].size(); j++) {
				if (vect[i][j].isMine == true) {
					vect[i][j].tileStruct[0] = nullptr;
				}
			}
		}
		debugToggle = false;
	}
}

Tile Board::placeFlag(Tile t, sf::Texture arr[]) {
	if (t.isMine == true) {
		t.tileStruct[0] = t.setFlag(arr, 3);
	}
	else {
		t.tileStruct[1] = t.setFlag(arr, 3);
	}
	t.isFlag = true;
	return t;
}

Tile Board::removeFlag(Tile t, sf::Texture arr[]) {
	if (t.isMine == true) {
		t.tileStruct[0] = nullptr;
	}
	else {
		t.tileStruct[1] = nullptr;
	}
	t.isFlag = false;
	return t;
}