#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Tile.cpp"
#include <sstream>
using namespace std;

struct Board {

	vector<Tile> tiles;
	map<string, sf::Texture> textures;

	bool gameOver = false;
	int notMines = 350;

	bool toggle = false;
//	int tilesRevealed = 0;

	sf::Sprite sun;
	//sf::Sprite frown;
	//sf::Sprite sunglasses;
	sf::Sprite numDisplay;
	sf::Sprite showMines;
	sf::Sprite testOne;
	sf::Sprite testTwo;
	sf::Sprite testThree;

	sf::Sprite digit1;
	sf::Sprite digit2;
	sf::Sprite digit3;
	sf::Sprite digit4;

	int numOfFlags = 50;
	

	Board() {
	
		for (int i = 0; i < 400; i++) {

			Tile newT;
			//newT.background.setTexture(textures["unclicked"]);
		
			int Column = i % 25;
			int Row = i / 25;

			newT.foreground.move(Column * 32, Row * 32);
			newT.flagged.move(Column * 32, Row * 32);
			newT.background.move(Column * 32, Row * 32);
			
			newT.x = Column * 32;
			newT.y = Row * 32;
			tiles.push_back(newT);
		}
	
	}

	void countMines(vector<Tile>& tiles) {
		
		for (int i = 0; i < 400; i++) {
			if (tiles[i].isMine) {
			
				continue;
			}
			else {
				for (int j = 0; j < tiles[i].neighbors.size(); j++) {
				
					if (tiles[i].neighbors[j]->isMine) {
						tiles[i].mineCount++;
					}
				}
				
				if (tiles[i].mineCount == 1) {
					tiles[i].foreground.setTexture(textures["one"]);
					
				}
				else if (tiles[i].mineCount == 2) {
					tiles[i].foreground.setTexture(textures["two"]);
					
				}
				else if (tiles[i].mineCount == 3) {
					tiles[i].foreground.setTexture(textures["three"]);
					
				}
				else if (tiles[i].mineCount == 4) {
					tiles[i].foreground.setTexture(textures["four"]);
					
				}
				else if (tiles[i].mineCount == 5) {
					tiles[i].foreground.setTexture(textures["five"]);
					
				}
				else if (tiles[i].mineCount == 6) {
					tiles[i].foreground.setTexture(textures["six"]);
					
				}
				else if (tiles[i].mineCount == 7) {
					tiles[i].foreground.setTexture(textures["seven"]);
					
				}
				else if (tiles[i].mineCount == 8) {
					tiles[i].foreground.setTexture(textures["eight"]);
				

				}
			}
		}
	}

	void loadTextures() {

		//map<string, sf::Texture> textures;

		sf::Texture unclicked;
		unclicked.loadFromFile("images/tile_hidden.png");
		textures.emplace("unclicked", unclicked);
		sf::Texture clicked;
		clicked.loadFromFile("images/tile_revealed.png");
		textures.emplace("clicked", clicked);
		sf::Texture one;
		one.loadFromFile("images/number_1.png");
		textures.emplace("one", one);
		sf::Texture two;
		two.loadFromFile("images/number_2.png");
		textures.emplace("two", two);
		sf::Texture three;
		three.loadFromFile("images/number_3.png");
		textures.emplace("three", three);
		sf::Texture four;
		four.loadFromFile("images/number_4.png");
		textures.emplace("four", four);
		sf::Texture five;
		five.loadFromFile("images/number_5.png");
		textures.emplace("five", five);
		sf::Texture six;
		six.loadFromFile("images/number_6.png");
		textures.emplace("six", six);
		sf::Texture seven;
		seven.loadFromFile("images/number_7.png");
		textures.emplace("seven", seven);
		sf::Texture eight;
		eight.loadFromFile("images/number_8.png");
		textures.emplace("eight", eight);
		sf::Texture mine;
		mine.loadFromFile("images/mine.png");
		textures.emplace("mine", mine);
		sf::Texture flag;
		flag.loadFromFile("images/flag.png");
		textures.emplace("flag", flag);
		sf::Texture smiling;
		smiling.loadFromFile("images/face_happy.png");
		textures.emplace("smiling", smiling);
		sf::Texture sunglasses;
		sunglasses.loadFromFile("images/face_win.png");
		textures.emplace("sunglasses", sunglasses);
		sf::Texture frown;
		frown.loadFromFile("images/face_lose.png");
		textures.emplace("frown", frown);

		sf::Texture numDisplay;
		numDisplay.loadFromFile("images/digits.png");
		textures.emplace("numDiplay", numDisplay);

		sf::Texture debugButton;
		debugButton.loadFromFile("images/debug.png");
		textures.emplace("debugButton", debugButton);
		sf::Texture test1;
		test1.loadFromFile("images/test_1.png");
		textures.emplace("test1", test1);
		sf::Texture test2;
		test2.loadFromFile("images/test_2.png");
		textures.emplace("test2", test2);
		sf::Texture test3;
		test3.loadFromFile("images/test_3.png");
		textures.emplace("test3", test3);

		sf::Texture digit1;
		digit1.loadFromFile("images/digits.png");
		textures.emplace("digit1", digit1);

		sf::Texture digit2;
		digit2.loadFromFile("images/digits.png");
		textures.emplace("digit2", digit2);

		sf::Texture digit3;
		digit3.loadFromFile("images/digits.png");
		textures.emplace("digit3", digit3);

		sf::Texture digit4;
		digit4.loadFromFile("images/digits.png");
		textures.emplace("digit4", digit4);

	}
	
	void placeMines(vector<Tile>& tiles) {
		
		int counter = 0;
		while (counter < 50) {
			int index = rand() % 400;
			if (tiles[index].isMine) {
				
				continue;
			}
			else {
				
				tiles[index].foreground.setTexture(textures["mine"]);
				
				tiles[index].isMine = true;
				counter++;
			}
		}
	}

	void setNeighbors(vector<Tile>& tiles) {
	//	cout << "Within FindNeighbors" << endl;
		int i = 0;
		for (i = 0; i < 400; i++) {
			//the edges will suck , both end rows and columns 
			//corners Suck Worse
			//CHECK within forloop for these special conditions
			//for top row, protect against the things above it
			//top left corner
			if (i == 0) {
				//cout << "top left" << endl;
				//tiles[i].neighbors[0] = nullptr;
				//tiles[i].neighbors[1] = nullptr;
				//tiles[i].neighbors[2] = nullptr;
				//tiles[i].neighbors[3] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				//tiles[i].neighbors[5] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				tiles[i].neighbors.push_back(&tiles[i + 26]);
			}
			else if (0 < i && i < 24) {
				//top row
					//cout << "top row" << endl;
					//tiles[i].neighbors[0] = nullptr;
					//tiles[i].neighbors[1] = nullptr;
					//tiles[i].neighbors[2] =nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				tiles[i].neighbors.push_back(&tiles[i + 24]);
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				tiles[i].neighbors.push_back(&tiles[i + 26]);
			}
			else if (i == 24) {
				//top right corner
				//cout << "top right" << endl;
				//tiles[i].neighbors[0] = nullptr;
				//tiles[i].neighbors[1] = nullptr;
				//tiles[i].neighbors[2] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				//tiles[i].neighbors[4] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 24]);
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				//tiles[i].neighbors[7] = nullptr;
			}
			else if (i == 375) {
				//bottom left
				//cout << "bottom left" << endl;
				//tiles[i].neighbors[0] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				tiles[i].neighbors.push_back(&tiles[i - 24]);
				//tiles[i].neighbors[3] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				//tiles[i].neighbors[5] = nullptr;
				//tiles[i].neighbors[6] = nullptr;
				//tiles[i].neighbors[7] = nullptr;
			}
			else if (i > 375 && i < 399) {
				//bottom
			//  cout << "Bottom row" << endl;
				tiles[i].neighbors.push_back(&tiles[i - 26]);
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				tiles[i].neighbors.push_back(&tiles[i - 24]);
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				//tiles[i].neighbors[5] = nullptr;
				//tiles[i].neighbors[6] = nullptr;
				//tiles[i].neighbors[7] = nullptr;
			}
			else if (i == 399) {
				//bottom right
			//  cout << "bottom right" << endl;
				tiles[i].neighbors.push_back(&tiles[i - 26]);
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				//tiles[i].neighbors[2] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				//tiles[i].neighbors[4] = nullptr;
				//tiles[i].neighbors[5] = nullptr;
				//tiles[i].neighbors[6] = nullptr;
				//tiles[i].neighbors[7] = nullptr;
			}
			else if (i % 25 == 0 && i != 375) {
				//left
			   //cout << "Left column" << endl;
			   //tiles[i].neighbors[0] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				tiles[i].neighbors.push_back(&tiles[i - 24]);
				//tiles[i].neighbors.push_back = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				//tiles[i].neighbors[5] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				tiles[i].neighbors.push_back(&tiles[i + 26]);
			}
			else if (i % 25 == 24 && i != 399) {
				//right
			//  cout << "Right column" << endl;
				tiles[i].neighbors.push_back(&tiles[i - 26]);
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				//tiles[i].neighbors[2] =nullptr;
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				//tiles[i].neighbors[4] = nullptr;
				tiles[i].neighbors.push_back(&tiles[i + 24]);
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				//tiles[i].neighbors[7] = nullptr;
			}
			else {
				//default cases go under all the checks 
				//cout << "Normal Tiles" << endl;
				tiles[i].neighbors.push_back(&tiles[i - 26]);
				tiles[i].neighbors.push_back(&tiles[i - 25]);
				tiles[i].neighbors.push_back(&tiles[i - 24]);
				tiles[i].neighbors.push_back(&tiles[i - 1]);
				tiles[i].neighbors.push_back(&tiles[i + 1]);
				tiles[i].neighbors.push_back(&tiles[i + 24]);
				tiles[i].neighbors.push_back(&tiles[i + 25]);
				tiles[i].neighbors.push_back(&tiles[i + 26]);
			}
		}
	}
	
	void emptyTileRecursion(Tile& currentTile) {

		for (int i = 0; i < currentTile.neighbors.size(); i++) { 

			if (!(currentTile.neighbors[i]->isClicked)) {

				currentTile.neighbors[i]->isClicked = true;
				currentTile.neighbors[i]->isVisited = true;
			//	tilesClicked++;
				checkVictory();
				if (currentTile.neighbors[i]->mineCount == 0) {

					if (currentTile.neighbors[i]->isClicked == true) {

						//notMines--;

						currentTile.neighbors[i]->foreground.setTexture(textures["clicked"]);
						emptyTileRecursion(*currentTile.neighbors[i]);
						checkVictory();
					}
					
				}
				else if (currentTile.neighbors[i]->mineCount > 0) {


					currentTile.neighbors[i]->background.setTexture(textures["clicked"]);


					if (tiles[i].mineCount == 1) {
						tiles[i].foreground.setTexture(textures["one"]);
						
					}
					else if (tiles[i].mineCount == 2) {
						tiles[i].foreground.setTexture(textures["two"]);
						
					}
					else if (tiles[i].mineCount == 3) {
						tiles[i].foreground.setTexture(textures["three"]);
						
					}
					else if (tiles[i].mineCount == 4) {
						tiles[i].foreground.setTexture(textures["four"]);
					
					}
					else if (tiles[i].mineCount == 5) {
						tiles[i].foreground.setTexture(textures["five"]);
						
					}
					else if (tiles[i].mineCount == 6) {
						tiles[i].foreground.setTexture(textures["six"]);
						
					}
					else if (tiles[i].mineCount == 7) {
						tiles[i].foreground.setTexture(textures["seven"]);

					}
					else if (tiles[i].mineCount == 8) {
						tiles[i].foreground.setTexture(textures["eight"]);
						
					}

				}
			}
		}
		return;
	}
	
	void  loadTest1() {

		vector<char> minePos;
		int testMines = 0;

		ifstream testUno;
		testUno.open("boards/testboard1.brd");

		//while there are things to read
		while (!testUno.eof()) {

			char mine;
			testUno.get(mine);
			minePos.push_back(mine);

		}

		
		for (int i = 0; i < 400; i++)
		{
			if (minePos[i] == '1') {
				tiles[i].isMine = true;
				tiles[i].foreground.setTexture(textures["mine"]);
				testMines++;
			}
		}
		numOfFlags = testMines;
		notMines = 400 - testMines;
	}

	void  loadTest2() {


		vector<char> minePos;
		int testMines = 0;

		ifstream testDos;
		testDos.open("boards/testboard2.brd");

		

		while(!testDos.eof()){
	
			//char mine;
			string charStuff;
			//testDos.get(mine);
			getline(testDos, charStuff);

			for(int i = 0; i < 25; i++) {

				minePos.push_back(charStuff[i]);
			}
		}


		for (int i = 0; i < 400; i++)
		{
			
			 if (minePos[i] == '1') {
				tiles[i].isMine = true;
				tiles[i].foreground.setTexture(textures["mine"]);
				testMines++;
			}
		}
		numOfFlags = testMines;
		notMines = 400 - testMines;
	}

	void  loadTest3() {

		vector<char> minePos;
		int testMines = 0;

		ifstream testTres;
		testTres.open("boards/testboard3.brd");

		//while there are things to read

		while (!testTres.eof()) {

			//char mine;
			string charStuff;
			//testDos.get(mine);
			getline(testTres, charStuff);

			for (int i = 0; i < 25; i++) {

				minePos.push_back(charStuff[i]);
			}
		}


		for (int i = 0; i < 400; i++)
		{
			if (minePos[i] == '\n') {

				continue;

			}
			else if (minePos[i] == '1') {
				tiles[i].isMine = true;
				tiles[i].foreground.setTexture(textures["mine"]);
				testMines++;
			}
		}
		numOfFlags = testMines;
		notMines = 400 - testMines;
	}

	void clear() {

		tiles.clear();

		for (int i = 0; i < 400; i++) {
			Tile newT;
			newT.background.setTexture(textures["unclicked"]);
		//	newT.foreground.setTexture(textures["unclicked"]);
		//	newT.flagged.setTexture(textures["unclicked"]);
			
			int Column = i % 25;
			int Row = i / 25;
			newT.foreground.move(Column * 32, Row * 32);
			newT.flagged.move(Column * 32, Row * 32);
			newT.background.move(Column * 32, Row * 32);
		
			newT.x = Column * 32;
			newT.y = Row * 32;
			tiles.push_back(newT);
		}

		numOfFlags = 50;
	}

	//I think I should make a sprite for each digit
	void updateNumDisplay() {

		if (numOfFlags > 0) {
			
	

		digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));
	


			if ((numOfFlags / 10) == 0) {

				int num = (numOfFlags % 10);

				digit3.setTextureRect(sf::IntRect(0, 0, 21, 32));
				digit4.setTextureRect(sf::IntRect(21 * num, 0, 21, 32));
			}
			else if ((numOfFlags / 10) > 0) {

				int num1 = (numOfFlags / 10);
				int num2 = (numOfFlags % 10);


				digit3.setTextureRect(sf::IntRect((21 * num1), 0, 21, 32));
				digit4.setTextureRect(sf::IntRect((21 * num2), 0, 21, 32));

			}

		}
		else if (numOfFlags == 0) {

			
			digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
			digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));
			digit3.setTextureRect(sf::IntRect(0, 0, 21, 32));
			digit4.setTextureRect(sf::IntRect(0, 0, 21, 32));
		

		}
		else if (numOfFlags < 0) {

		
			digit1.setTextureRect(sf::IntRect(210, 0, 21, 32));

			if (numOfFlags < 0 && numOfFlags > -10) {

			
				int num = numOfFlags * -1;

				digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));
				digit3.setTextureRect(sf::IntRect(0, 0, 21, 32));
				digit4.setTextureRect(sf::IntRect((21 * num), 0, 21, 32));

			
			}
			else if ((numOfFlags / 10) < 0 && (numOfFlags / 10) > -10) {
				
				int num1 = -(numOfFlags / 10);
				int num2 = -(numOfFlags % 10);

			
				digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));

				digit3.setTextureRect(sf::IntRect(21 * num1, 0, 21, 32));
				digit4.setTextureRect(sf::IntRect(21 * num2, 0, 21, 32));
			
			}
			else if ((numOfFlags / 10) <= -10) {

		

				int num1 = -(numOfFlags / 10) % 10;
				int num2 = -(numOfFlags % 10);
				int num3 = -((numOfFlags / 10) / 10);

			
				digit2.setTextureRect(sf::IntRect(21 * num3, 0, 21, 32));
				digit3.setTextureRect(sf::IntRect(21 * num1, 0, 21, 32));
				digit4.setTextureRect(sf::IntRect(21 * num2, 0, 21, 32));
			
			}
		}	
	}

	void checkVictory() {

		int num = 0;
		

		for (int i = 0; i < 400; i++) {

			if (tiles[i].isClicked) {
				num++;
			}

		}
		//cout << num << endl;
		
		 
		if (num == notMines) {

			gameOver = true;
			sun.setTexture(textures["sunglasses"]);

			for (int i = 0; i < 400; i++) {
				
				if (tiles[i].isMine && toggle == true) {

					tiles[i].isFlagged = true;
					tiles[i].background.setTexture(textures["clicked"]);
					tiles[i].foreground.setTexture(textures["mine"]);
					tiles[i].flagged.setTexture(textures["flag"]);

				}
				else if (tiles[i].isMine) {

					tiles[i].isFlagged = true;
					tiles[i].flagged.setTexture(textures["flag"]);
				}

			}

		}


	}
};

