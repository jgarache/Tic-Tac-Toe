#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Shape.h"
#include "rectangle.h"
#include <vector>
#include <string>
#include <time.h>

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

	//AImode - determines which mode: 2 human players (false) || playing against the AI (true)
	//AImove - calculates AI's move on the 3x3 grid
	//AIcalculate - the AI will recalculate its move if a player icon is occupying a space
	//tie - keeps track if there is a tie (when tie = 9)
	bool AImode, AIcalculate;
	char AImove;
	int tie;

	//Winner - determines which player is the victor
	//declare winner - determines if there is a win
	char winner;
	bool declareWinner;

	//enum turn - determines whose turn it is. i.e. P1 turn || P2 turn || AI's turn
	enum class Turn { player1 = 0, player2, AI }playerTurn;

	//playerIcons - stores and keeps track of the x/o and which positions they are on the 3x3 gride
	//gridRegions - creates the regions of the 3x3 where the mouse clicks and props other functions to create 
	//and x or o in 1 of the regions of the 3x3 grid
	//AIchatter - An array of cool phrases for the AI to say
	std::vector<Shape*> playerIcons;
	std::vector<rectangle*> gridRegions;
	std::vector<std::string> AIchatter;

public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    //draw function with helper functions
	void draw();
	void drawYellowLines();
	void drawBlackRectangles();
	void drawPlayerIcons();
	void checkWin(Shape shape);
	void clearBoard();

    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);

};

#endif
