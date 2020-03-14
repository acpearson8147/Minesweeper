
/* As you'll see throughout this code, there are a lot of red underlines showing errors.
	Please ignore these for now! They are simply occuring because I moved the files of this project from one place to another
	to better categorize/keep track of my submissions for BAS. 
	I will show the last successful build of the code and the window of Minesweeper it produces.
	Also note that this program will most likely not run on your computer unless you install SFML and set it up properly in your IDE,
	I had trouble with that aspect myself. But I will send the source code/images of my project so that if you do install SFML, you can run it.
*/


#include <SFML/Graphics.hpp>
#include "Board.cpp"
#include <string>
#include <iostream>

using namespace std;


int main() {


	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	srand(time(NULL));

	//bool toggle = false;

	Board newB;
	//map<string, sf::Texture> textures2 = newB.loadTextures();
	newB.loadTextures();
	for (int i = 0; i < 400; i++) {

		newB.tiles[i].background.setTexture(newB.textures["unclicked"]);

	}

	newB.sun.setTexture(newB.textures["smiling"]);
	//frown.setTexture(textures["frown"]);
	//sunglasses.setTexture(textures["sunglasses"]);
	//newB.numDisplay.setTexture(newB.textures["numDisplay"]);
	newB.showMines.setTexture(newB.textures["debugButton"]);
	newB.testOne.setTexture(newB.textures["test1"]);
	newB.testTwo.setTexture(newB.textures["test2"]);
	newB.testThree.setTexture(newB.textures["test3"]);

	newB.digit1.setTexture(newB.textures["digit1"]);
	newB.digit2.setTexture(newB.textures["digit2"]);
	newB.digit3.setTexture(newB.textures["digit3"]);
	newB.digit4.setTexture(newB.textures["digit4"]);

	newB.placeMines(newB.tiles);
	newB.setNeighbors(newB.tiles);
	newB.countMines(newB.tiles);


	bool currentlyClicking = false;
	sf::Event click;

	//cout << "Window colored white" << endl;

	while (window.isOpen()) {

		window.clear(sf::Color::White);

		newB.sun.setPosition(11.5 * 32, 16 * 32);
		newB.showMines.setPosition(15.5 * 32, 16 * 32);
		newB.testOne.setPosition(17.5 * 32, 16 * 32);
		newB.testTwo.setPosition(19.5 * 32, 16 * 32);
		newB.testThree.setPosition(21.5 * 32, 16 * 32);

		newB.digit1.setPosition(0, 16 * 32);
		newB.digit2.setPosition(21, 16 * 32);
		newB.digit3.setPosition(42, 16 * 32);
		newB.digit4.setPosition(63, 16 * 32);

		newB.updateNumDisplay();
		//cout << "UI Sprites drawn" << endl;
		window.draw(newB.sun);
		//window.draw(newB.numDisplay);
		window.draw(newB.showMines);
		window.draw(newB.testOne);
		window.draw(newB.testTwo);
		window.draw(newB.testThree);

		window.draw(newB.digit1);
		window.draw(newB.digit2);
		window.draw(newB.digit3);
		window.draw(newB.digit4);


		for (int i = 0; i < newB.tiles.size(); i++) {
			//if hidden, do this

			if (newB.toggle == true) {

				if (newB.tiles[i].isMine) {

					
					window.draw(newB.tiles[i].background);
					window.draw(newB.tiles[i].foreground);
					window.draw(newB.tiles[i].flagged);
				}
				else {
					
					if (!newB.tiles[i].isClicked && newB.tiles[i].isFlagged) {
						window.draw(newB.tiles[i].foreground);
						window.draw(newB.tiles[i].background);
						window.draw(newB.tiles[i].flagged);
					}
					else if (!newB.tiles[i].isClicked) {
						window.draw(newB.tiles[i].flagged);
						window.draw(newB.tiles[i].foreground);
						window.draw(newB.tiles[i].background);

					}
					else if (newB.tiles[i].isClicked == true) {
						window.draw(newB.tiles[i].flagged);
						window.draw(newB.tiles[i].background);
						window.draw(newB.tiles[i].foreground);

					}
				}

			}
			else {

				if (newB.tiles[i].isMine && newB.tiles[i].isClicked) {

					window.draw(newB.tiles[i].flagged);
					window.draw(newB.tiles[i].background);
					window.draw(newB.tiles[i].foreground);
					
				}
				else if (!newB.tiles[i].isClicked && newB.tiles[i].isFlagged) {
					window.draw(newB.tiles[i].foreground);
					window.draw(newB.tiles[i].background);
					window.draw(newB.tiles[i].flagged);
				}
				else if (!newB.tiles[i].isClicked) {
					window.draw(newB.tiles[i].flagged);
					window.draw(newB.tiles[i].foreground);
					window.draw(newB.tiles[i].background);

				}
				else if (newB.tiles[i].isClicked == true) {
					window.draw(newB.tiles[i].flagged);
					window.draw(newB.tiles[i].background);
					window.draw(newB.tiles[i].foreground);

				}
			
			}

		}


		window.display();


		while (window.pollEvent(click)) {

			//~~~~~~~~CLOSE WINDOW~~~~~~~~
			if (click.type == sf::Event::Closed) {

				window.close();

			}

			else if (click.type == sf::Event::MouseButtonPressed) {

				if (click.mouseButton.button == sf::Mouse::Right) {

					for (int i = 0; i < 400; i++) {
						//~~~~~~~~~~~~~FLAGGING~~~~~~~~~~~~~~~~~~~~~
						if ((newB.tiles[i].x / 32) == (click.mouseButton.x / 32) && ((newB.tiles[i].y / 32) * 25) == ((click.mouseButton.y / 32) * 25) && newB.gameOver == false) {

							if (newB.tiles[i].isFlagged && newB.tiles[i].isClicked == false) {

								newB.tiles[i].isFlagged = false;

								newB.tiles[i].flagged.setTexture(newB.textures["unclicked"]);

								newB.numOfFlags++;

								newB.updateNumDisplay();
							}
							else {

								if (newB.gameOver == false && newB.tiles[i].isClicked == false) {
									newB.tiles[i].background.setTexture(newB.textures["unclicked"]);

									newB.tiles[i].flagged.setTexture(newB.textures["flag"]);
									newB.tiles[i].isFlagged = true;
									newB.numOfFlags--;
									newB.updateNumDisplay();
								}
							}

						}

					}
				}

				//~~~~~~~~~~LEFT CLICK~~~~~~~~~
				else if (click.mouseButton.button == sf::Mouse::Left) {


					//~~~~~~~~~~~~~LEFT CLICK OVER TILE~~~~~~~~~~~~~~~~

					if ((newB.sun.getGlobalBounds().contains(click.mouseButton.x, click.mouseButton.y))) {


						newB.clear();

						newB.placeMines(newB.tiles);
						newB.setNeighbors(newB.tiles);
						newB.countMines(newB.tiles);

						newB.sun.setTexture(newB.textures["smiling"]);

						newB.gameOver = false;


						//toggle = false;

					}
					else if ((newB.showMines.getGlobalBounds().contains(click.mouseButton.x, click.mouseButton.y)) && newB.gameOver == false) {

					//	cout <<newB.toggle << endl;
						//bool toggle = false;

						if (newB.toggle == true) {

							/*
							for (int i = 0; i < 400; i++) {

								if (newB.tiles[i].isMine) {

									newB.tiles[i].background.setTexture(newB.textures["unclicked"]);
									newB.tiles[i].foreground.setTexture(newB.textures["unclicked"]);
									toggle = false;

								}
							}
							*/

							newB.toggle = false;
						}
						else {

							/*
							for (int i = 0; i < 400; i++) {

								if (newB.tiles[i].isMine) {

									newB.tiles[i].background.setTexture(newB.textures["mine"]);
									newB.tiles[i].foreground.setTexture(newB.textures["clicked"]);
									toggle = true;

								}
							}
						}
						*/
							newB.toggle = true;
						}
					}
					else if ((newB.testOne.getGlobalBounds().contains(click.mouseButton.x, click.mouseButton.y))) {

						newB.clear();
						newB.loadTest1();

						newB.setNeighbors(newB.tiles);
						newB.countMines(newB.tiles);
						newB.sun.setTexture(newB.textures["smiling"]);
						newB.gameOver = false;


						///	toggle = false;
					}
					else if ((newB.testTwo.getGlobalBounds().contains(click.mouseButton.x, click.mouseButton.y))) {

						newB.clear();
						newB.loadTest2();

						newB.setNeighbors(newB.tiles);
						newB.countMines(newB.tiles);
						newB.sun.setTexture(newB.textures["smiling"]);
						newB.gameOver = false;



						//toggle = false;
					}
					else if ((newB.testThree.getGlobalBounds().contains(click.mouseButton.x, click.mouseButton.y))) {

						newB.clear();
						newB.loadTest3();

						newB.setNeighbors(newB.tiles);
						newB.countMines(newB.tiles);
						newB.sun.setTexture(newB.textures["smiling"]);
						newB.gameOver = false;



						//toggle = false;

					}
					else {

						for (int i = 0; i < 400; i++) {

							if ((newB.tiles[i].x / 32) == (click.mouseButton.x / 32) && ((newB.tiles[i].y / 32) * 25) == ((click.mouseButton.y / 32) * 25) && !newB.tiles[i].isFlagged) {



								//~~~~~~~~~~~CLICKED A MINE~~~~~~~~~~~~~~

								if (newB.tiles[i].isMine && newB.gameOver == false) {

									newB.tiles[i].isClicked = true;
									newB.tiles[i].isVisited = true;

									newB.tiles[i].background.setTexture(newB.textures["clicked"]);
									//newB.tiles[i].foreground.setTexture(newB.textures["mine"]);
									newB.sun.setTexture(newB.textures["frown"]);

									newB.gameOver = true;

									for (int i = 0; i < 400; i++) {

										if (newB.tiles[i].isMine && !newB.tiles[i].isFlagged) {

											newB.tiles[i].isClicked = true;
											newB.tiles[i].isVisited = true;

											newB.tiles[i].background.setTexture(newB.textures["clicked"]);
											newB.tiles[i].foreground.setTexture(newB.textures["mine"]);

										}
									}
									newB.checkVictory();


								} //~~~~~~~~~CLICKED SPACE WITH MINES AROUND IT~~~~~~~~~~~~~~~~

								else if ((newB.tiles[i].mineCount > 0) && newB.gameOver == false) {

									newB.tiles[i].isClicked = true;
									newB.tiles[i].isVisited = true;
									newB.checkVictory();

									//newB.tilesClicked++;

									newB.tiles[i].background.setTexture(newB.textures["clicked"]);

								}//	~~~~~~~~~~~ CLICKED SPACE WITH NO MINES AROUND IT~~~~~~~~~~~~~~~

								else if ((newB.tiles[i].mineCount == 0) && newB.gameOver == false) {

									newB.tiles[i].isClicked = true;
									newB.tiles[i].isVisited = true;
									newB.checkVictory();
									//newB.tilesClicked++;

									newB.emptyTileRecursion(newB.tiles[i]);
									newB.tiles[i].foreground.setTexture(newB.textures["clicked"]);
									newB.tiles[i].background.setTexture(newB.textures["clicked"]);

									newB.checkVictory();

								}

							}
						}
					}

					
				}
			}
		}
	}
}

