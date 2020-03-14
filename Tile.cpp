#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;


struct Tile {

	//holds the data about the 400 tiny tiles, not the big ones
	//no methods within it, just holds data
	//every Tile has a three Sprites: tile hidden, tile clicked (background and number), and tile flagged
	//every sprite will have a texture, that holds the data for the actual image

	sf::Sprite foreground;
	sf::Sprite background;
	sf::Sprite flagged;

	//make booleans describing the tiles
	bool isMine = false;
	bool isFlagged = false;
	bool isVisited = false;
	bool isClicked = false;

	int mineCount = 0;

	int x = 0;
	int y = 0;

	//sf::Vector2f location; <-could be used 
	//someTile.flag.move(location)  <-one use of it

	vector<Tile*> neighbors; //file with the following pointers
	

	Tile() { 

		bool isMine = false;
		bool isFlagged = false;
		bool isClicked = false;

		int x = 0;
		int y = 0;

	}


	Tile(map<string, sf::Texture> textures) {

		background.setTexture(textures["unclicked"]);

		
	}
};
