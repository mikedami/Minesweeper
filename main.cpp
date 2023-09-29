#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "tile.h"
#include "board.h"
using namespace std;

int main()
{
    sf::Texture textures[20];
    textures[0].loadFromFile("images/tile_revealed.png");
    textures[1].loadFromFile("images/tile_hidden.png");
    textures[2].loadFromFile("images/mine.png");
    textures[3].loadFromFile("images/flag.png");
    textures[4].loadFromFile("images/test_1.png");
    textures[5].loadFromFile("images/test_2.png");
    textures[6].loadFromFile("images/test_3.png");
    textures[7].loadFromFile("images/debug.png");
    textures[8].loadFromFile("images/digits.png");
    textures[9].loadFromFile("images/face_happy.png");
    textures[10].loadFromFile("images/face_lose.png");
    textures[11].loadFromFile("images/face_win.png");
    int j = 12;
    for (int i = 1; i <= 8; i++) {
        string temp = to_string(i);
        string path = "images/number_" + temp + ".png";
        textures[j].loadFromFile(path);
        j++;
    }

    ifstream file;
    file.open("boards/config.cfg", ios::in);
    int rows;
    int columns;
    int mineCount;
    int tileCount;
    int tile1;
    int tile2;
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    float xPos = 0.0f;
    float yPos = 0.0f;
    string line = "";

    getline(file, line);
    tile1 = stoi(line);
    rows = stoi(line) * 32;

    getline(file, line);
    tile2 = stoi(line);
    columns = (stoi(line) * 32) + 100;

    getline(file, line);
    mineCount = stoi(line);

    tileCount = tile1 * tile2;

    sf::RenderWindow game(sf::VideoMode(rows, columns), "Minesweeper");
    file.close();

    game.clear(sf::Color::White);
    Board board;
    board.Draw(textures);

    for (int i = 0; i < board.vect.size(); i++) {
        for (int j = 0; j < board.vect[i].size(); j++) {
            for (int k = 3; k >= 0; k--) {
                if (board.vect[i][j].tileStruct[k] != nullptr) {

                    board.vect[i][j].tileStruct[k]->setPosition(sf::Vector2f(xPos, yPos));
                    board.vect[i][j].xPosition = xPos;
                    board.vect[i][j].yPosition = yPos;
                    game.draw(*board.vect[i][j].tileStruct[k]);
                }
            }
            yPos += 32.0f;
        }
        yPos = 0.0f;
        xPos += 32.0f;
    }

    int breakpoint234;
    board.setAdjacentTiles();

    sf::Sprite test_1;
    test_1.setTexture(textures[4]);
    sf::Sprite test_2;
    test_2.setTexture(textures[5]);
    sf::Sprite test_3;
    test_3.setTexture(textures[6]);

    sf::Sprite debug;
    debug.setTexture(textures[7]);

    sf::Sprite happy_face;
    happy_face.setTexture(textures[9]);
    sf::Sprite lose_face;
    lose_face.setTexture(textures[10]);
    sf::Sprite win_face;
    win_face.setTexture(textures[11]);

    float bottom = columns - 100.0f;
    float right_pos = rows - 64.0f;

    test_3.setPosition(sf::Vector2f(right_pos, bottom));
    float test_3xPos = right_pos;
    float test_3yPos = bottom;
    right_pos -= 64.0f;
    game.draw(test_3);

    test_2.setPosition(sf::Vector2f(right_pos, bottom));
    float test_2xPos = right_pos;
    float test_2yPos = bottom;
    right_pos -= 64.0f;
    game.draw(test_2);

    test_1.setPosition(sf::Vector2f(right_pos, bottom));
    float test_1xPos = right_pos;
    float test_1yPos = bottom;
    right_pos -= 64.0f;
    game.draw(test_1);

    debug.setPosition(sf::Vector2f(right_pos, bottom));
    float debugxPos = right_pos;
    float debugyPos = bottom;
    right_pos -= 128.0f;
    game.draw(debug);

    happy_face.setPosition(sf::Vector2f(right_pos, bottom));
    float facexPos = right_pos;
    float faceyPos = bottom;
    game.draw(happy_face);


    float digitsxPos = 32.0f;
    float digitsyPos = bottom;

    board.setDigits(textures);
    board.writeDigits(textures);
    for (int i = 0; i < board.displayDigits.size(); i++) {
        board.displayDigits[i].setPosition(sf::Vector2f(digitsxPos, bottom));
        game.draw(board.displayDigits[i]);
        digitsxPos += 21.0f;
    }
    

    game.display(); 
    int m = 0; //used to stop breakpoint
    bool restart = false;
    int testIndex;


    while (game.isOpen()) {

        if (restart == true) {
            game.clear(sf::Color::White);
			Board temp;

            if (board.isTest == true) {
                board.isTest = false;
                temp.DrawTest(textures, testIndex);
            }
            else {
                temp.Draw(textures);
            }

			xPos = 0.0f;
			yPos = 0.0f;
			for (int i = 0; i < temp.vect.size(); i++) {
				for (int j = 0; j < temp.vect[i].size(); j++) {

					for (int k = 3; k >= 0; k--) {
						if (temp.vect[i][j].tileStruct[k] != nullptr) {

							temp.vect[i][j].tileStruct[k]->setPosition(sf::Vector2f(xPos, yPos));
							temp.vect[i][j].xPosition = xPos;
							temp.vect[i][j].yPosition = yPos;
							game.draw(*temp.vect[i][j].tileStruct[k]);
						}
					}
					yPos += 32.0f;
				}
				yPos = 0.0f;
				xPos += 32.0f;
			}

            temp.setAdjacentTiles();

			int breakpoint20 = 0;
			board = temp;

            

            test_3.setPosition(test_3xPos, test_3yPos);
            game.draw(test_3);
            test_2.setPosition(test_2xPos, test_2yPos);
            game.draw(test_2);
            test_1.setPosition(test_1xPos, test_1yPos);
            game.draw(test_1);
            debug.setPosition(debugxPos, debugyPos);
            game.draw(debug);
            happy_face.setPosition(facexPos, faceyPos);
            game.draw(happy_face);
            board.setDigits(textures);
            board.writeDigits(textures);
            digitsxPos = 32.0f;
            for (int i = 0; i < board.displayDigits.size(); i++) {
                board.displayDigits[i].setPosition(sf::Vector2f(digitsxPos, bottom));
                game.draw(board.displayDigits[i]);
                digitsxPos += 21.0f;
            }

            game.display();

            restart = false;
        }
        
        int breakpoint445;
        sf::Event event;
        while (game.pollEvent(event)) {

            if (board.vect[0][0].adjacentTiles[0]->adjacentTiles.size() == 0) {
                for (int i = 0; i < board.vect.size(); i++) {
                    for (int j = 0; j < board.vect[i].size(); j++) {
                        board.vect[i][j].adjacentTiles.clear();
                        board.vect[i][j].adjacentMines = 0;
                        /*for (int k = 0; k < board.vect[i][j].adjacentTiles.size(); k++) {
                            board.vect[i][j].adjacentTiles[k] = nullptr;
                        }*/
                    }
                }
                board.setAdjacentTiles();
            }

            if (event.type == sf::Event::Closed) {
                game.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                mouseX = (float)(event.mouseMove.x);
                mouseY = (float)(event.mouseMove.y);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (mouseY < (columns - 100.0f)) { //press was on board, (not on settings buttons on bottom 100 tiles)
                        if (board.gameOver == false && board.winW == false) {
                            for (int i = 0; i < board.vect.size(); i++) {
                                for (int j = 0; j < board.vect[i].size(); j++) {
                                    if (board.vect[i][j].xPosition < mouseX && (board.vect[i][j].xPosition + 32.0f) > mouseX) {
                                        if (board.vect[i][j].yPosition < mouseY && (board.vect[i][j].yPosition + 32.0f) > mouseY) {

                                            if (board.vect[i][j].isFlag == false) {
                                                board.Reveal(board.vect[i][j], textures);

                                                if (board.vect[i][j].isGameOver == true) {
                                                    board.lose(board.vect[i][j], textures);
                                                }
                                                int breakpoint1 = 0;
                                                break;
                                            }

                                        }
                                    }
                                }
                            }
                        }
                    }
                    else { //cases for settings options
                        if (test_3xPos < mouseX && (test_3xPos+64.0f) > mouseX) {
                            if (test_3yPos < mouseY && (test_3yPos+64.0f) > mouseY) {
                                restart = true;
                                board.isTest = true;
                                testIndex = 3;
                                break;
                            }
                        }
                        if (test_2xPos < mouseX && (test_2xPos + 64.0f) > mouseX) {
                            if (test_2yPos < mouseY && (test_2yPos + 64.0f) > mouseY) {
                                restart = true;
                                board.isTest = true;
                                testIndex = 2;
                                break;
                            }
                        }
                        if (test_1xPos < mouseX && (test_1xPos + 64.0f) > mouseX) {
                            if (test_1yPos < mouseY && (test_1yPos + 64.0f) > mouseY) {
                                restart = true;
                                board.isTest = true;
                                testIndex = 1;
                                break;
                            }
                        }
                        if (debugxPos < mouseX && (debugxPos + 64.0f) > mouseX) {
                            if (debugyPos < mouseY && (debugyPos + 64.0f) > mouseY) {
                                if (board.gameOver == false && board.winW == false) {
                                    board.debug(textures);
                                }
                            }
                        }
                        if (facexPos < mouseX && (facexPos + 64.0f) > mouseX) {
                            if (faceyPos < mouseY && (faceyPos + 64.0f) > mouseY) {

                                restart = true;
                                break;
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {  //right click to set a flag
                    if (board.gameOver == false && board.winW == false) {
                        for (int i = 0; i < board.vect.size(); i++) {
                            for (int j = 0; j < board.vect[i].size(); j++) {
                                if (board.vect[i][j].xPosition < mouseX && (board.vect[i][j].xPosition + 32.0f) > mouseX) {
                                    if (board.vect[i][j].yPosition < mouseY && (board.vect[i][j].yPosition + 32.0f) > mouseY) {

                                        if (board.vect[i][j].isFlag == false && board.vect[i][j].isRevealed == false) {
                                            board.vect[i][j] = board.placeFlag(board.vect[i][j], textures);
                                            board.mineCount--;

                                            for (int k = 3; k >= 0; k--) {
                                                if (board.vect[i][j].tileStruct[k] != nullptr) {
                                                    board.vect[i][j].tileStruct[k]->setPosition(sf::Vector2f(board.vect[i][j].xPosition, board.vect[i][j].yPosition));
                                                    game.draw(*board.vect[i][j].tileStruct[k]);

                                                }
                                            }

                                            break;
                                        }
                                        else if (board.vect[i][j].isFlag == true && board.vect[i][j].isRevealed == false) {
                                            board.vect[i][j] = board.removeFlag(board.vect[i][j], textures);
                                            board.mineCount++;

                                            for (int k = 3; k >= 0; k--) {
                                                if (board.vect[i][j].tileStruct[k] != nullptr) {
                                                    board.vect[i][j].tileStruct[k]->setPosition(sf::Vector2f(board.vect[i][j].xPosition, board.vect[i][j].yPosition));
                                                    game.draw(*board.vect[i][j].tileStruct[k]);
                                                }
                                            }

                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (restart == false) {
                    board.winCount = 0;
                    for (int i = 0; i < board.vect.size(); i++) {
                        for (int j = 0; j < board.vect[i].size(); j++) {
                            if (board.vect[i][j].isRevealed == true) {
                                board.winCount++;
                                if ((board.tileCount - board.mineCount) == board.winCount) {
                                    board.win(textures);
                                    board.mineCount = 0;
                                    break;
                                }
                            }
                        }
                    }
                    game.clear(sf::Color::White);
                    xPos = 0.0f;
                    yPos = 0.0f;
                    for (int i = 0; i < board.vect.size(); i++) {
                        for (int j = 0; j < board.vect[i].size(); j++) {
                            for (int k = 3; k >= 0; k--) {
                                if (board.vect[i][j].tileStruct[k] != nullptr) {

                                    board.vect[i][j].tileStruct[k]->setPosition(sf::Vector2f(xPos, yPos));
                                    board.vect[i][j].xPosition = xPos;
                                    board.vect[i][j].yPosition = yPos;
                                    game.draw(*board.vect[i][j].tileStruct[k]);
                                }
                            }
                            yPos += 32.0f;
                        }
                        yPos = 0.0f;
                        xPos += 32.0f;
                    }

                    test_3.setPosition(test_3xPos, test_3yPos);
                    game.draw(test_3);
                    test_2.setPosition(test_2xPos, test_2yPos);
                    game.draw(test_2);
                    test_1.setPosition(test_1xPos, test_1yPos);
                    game.draw(test_1);
                    debug.setPosition(debugxPos, debugyPos);
                    game.draw(debug);

                    if (board.winW == true) {
                        win_face.setPosition(facexPos, faceyPos);
                        game.draw(win_face);
                    }

                    if (board.gameOver == false && board.winW == false) {
                        happy_face.setPosition(facexPos, faceyPos);
                        game.draw(happy_face);
                    }

                    if (board.gameOver == true) {
                        lose_face.setPosition(facexPos, faceyPos);
                        game.draw(lose_face);
                    }

                    board.writeDigits(textures);
                    digitsxPos = 32.0f;
                    for (int i = 0; i < board.displayDigits.size(); i++) {
                        board.displayDigits[i].setPosition(sf::Vector2f(digitsxPos, bottom));
                        game.draw(board.displayDigits[i]);
                        digitsxPos += 21.0f;
                    }

                    game.display();
                }
            }
        }
    }
    return 0;
}
