#include "App.h"
#include "Shape.h"
#include "rectangle.h"

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
	
	//Print menu into terminal window
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Welcome to Tic-Tac-Toe      |" << std::endl;
	std::cout << "-----------Details-----------"  << std::endl;
	std::cout << "The game starts in A.I. Mode|" << std::endl;
	std::cout << "Player 1 is X               |" << std::endl;
	std::cout << "Player 2/A.I is O           |" << std::endl;
	std::cout << "-----------Modes-------------" << std::endl;
	std::cout << "Press 'a' for A.I. Mode     |" << std::endl;
	std::cout << "Press 's' for 2 Player Mode |" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	
	// Initialize state variables
    mx = 0.0;
    my = 0.0;

	//Tie occurs when tie = 9
	tie = 0;

	//starts game with player 1's move
	playerTurn = Turn::player1;

	//starts game in AI mode
	AImode = true;
	AImove = ' ';
	AIcalculate = true;
	srand(time(0));

	//Win variables
	winner = ' ';
	declareWinner = false;

	//Initializing black rectangles in each sector of the board
	gridRegions.push_back(new rectangle(-0.24 - .5, .24 + .5, 0.48, 0.48, 0.0, 0.0, 0.0)); // upper left
	gridRegions.push_back(new rectangle(-0.24, 0.24 + .5, 0.48, 0.48, 0.0, 0.0, 0.0)); // upper middle
	gridRegions.push_back(new rectangle(0.26, 0.24 + .5, 0.48, 0.48, 0.0, 0.0, 0.0)); // upper right

	gridRegions.push_back(new rectangle(-0.24 - .5, 0.24, 0.48, 0.48, 0.0, 0.0, 0.0)); // middle left
	gridRegions.push_back(new rectangle(-0.24, 0.24, 0.48, 0.48, 0.0, 0.0, 0.0)); // middle center
	gridRegions.push_back(new rectangle(0.26, 0.24, 0.48, 0.48, 0.0, 0.0, 0.0)); // middle right

	gridRegions.push_back(new rectangle(-0.24 - .5, -.26, 0.48, 0.48, 0.0, 0.0, 0.0)); // bottom left
	gridRegions.push_back(new rectangle(-0.24, -0.26, 0.48, 0.48, 0.0, 0.0, 0.0)); // bottom middle
	gridRegions.push_back(new rectangle(0.26, -0.26, 0.48, 0.48, 0.0, 0.0, 0.0)); // bottom right

	//Fill the vector with 9 spaces 
	//3 x 3 grid:
	//0 1 2
	//3 4 5
	//6 7 8
	playerIcons.push_back((new Shape(-0.5, 0.5, 0.0, 0.0, 0.0, '0'))); //0
	playerIcons.push_back((new Shape(0.0, 0.5, 0.0, 0.0, 0.0, '1'))); //1
	playerIcons.push_back((new Shape(0.5, 0.5, 0.0, 0.0, 0.0, '2'))); //2

	playerIcons.push_back((new Shape(-0.5, 0.0, 0.0, 0.0, 0.0, '3'))); //3
	playerIcons.push_back((new Shape(0.0, 0.0, 0.0, 0.0, 0.0, '4'))); //4
	playerIcons.push_back((new Shape(0.5, 0.0, 0.0, 0.0, 0.0, '5'))); //5

	playerIcons.push_back((new Shape(-0.5, -0.5, 0.0, 0.0, 0.0, '6'))); //6
	playerIcons.push_back((new Shape(0.0, -0.5, 0.0, 0.0, 0.0, '7'))); //7
	playerIcons.push_back((new Shape(0.5, -0.5, 0.0, 0.0, 0.0, '8'))); //8

	//Gives AI personality
	AIchatter.push_back("Hmm, interesting move.");
	AIchatter.push_back("You're a thousand years too early to beat me!");
	AIchatter.push_back("Seems like the victor is clear.");
	AIchatter.push_back("I'm not going to lose.");

	AIchatter.push_back("Wow! This game is intense!");
	AIchatter.push_back("I'll show you what I'm made of.");
	AIchatter.push_back("Oh no.");
	AIchatter.push_back("The end is near.");

}

void App::drawYellowLines() {

	//draw yellow lines that make the board
	glBegin(GL_LINES);

	//line above x axis
	glVertex2f(0.7, .25);
	glVertex2f(-0.7, .25);

	//line below x axis
	glVertex2f(0.7, -.25);
	glVertex2f(-0.7, -.25);

	//line right of y axis
	glVertex2f(0.25, 0.7);
	glVertex2f(0.25, -0.7);

	//line left of y axis
	glVertex2f(-0.25, 0.7);
	glVertex2f(-0.25, -0.7);

	glEnd();
}

void App::drawBlackRectangles() {

	for (int i = 0; i < gridRegions.size(); i++) {
		glColor3d(gridRegions[i]->r, gridRegions[i]->g, gridRegions[i]->b);
		glBegin(GL_LINES);

		// Draw the vertex in the right position
		//top line
		glVertex2f(gridRegions[i]->x, gridRegions[i]->y);//top left
		glVertex2f(gridRegions[i]->x + gridRegions[i]->w, gridRegions[i]->y);//top right

		//bottom line
		glVertex2f(gridRegions[i]->x, gridRegions[i]->y - gridRegions[i]->h);//bottom left
		glVertex2f(gridRegions[i]->x + gridRegions[i]->w, gridRegions[i]->y - gridRegions[i]->h);//bottom right

		//left line
		glVertex2f(gridRegions[i]->x, gridRegions[i]->y);//top left
		glVertex2f(gridRegions[i]->x, gridRegions[i]->y - gridRegions[i]->h);//bottom left

		//right line
		glVertex2f(gridRegions[i]->x + gridRegions[i]->w, gridRegions[i]->y);//top right
		glVertex2f(gridRegions[i]->x + gridRegions[i]->w, gridRegions[i]->y - gridRegions[i]->h);//bottom right

		glEnd();
	}
}

void App::drawPlayerIcons() {

	for (int i = 0; i < playerIcons.size(); i++) {

		if (playerIcons[i]->type == 'x') {
		
			glColor3d(playerIcons[i]->r, playerIcons[i]->g, playerIcons[i]->b);
			glBegin(GL_LINES);

			// slash /
			glVertex2f(playerIcons[i]->x + .2, playerIcons[i]->y + .2); //top right

			glVertex2f(playerIcons[i]->x - .2, playerIcons[i]->y - .2);//bottom left

			/* slash \ */
			glVertex2f(playerIcons[i]->x - .2, playerIcons[i]->y + .2);//top left
			glVertex2f(playerIcons[i]->x + .2, playerIcons[i]->y - .2);//bottom right

			glEnd();
		}

		else { // type == 'o'

			glColor3d(playerIcons[i]->r, playerIcons[i]->g, playerIcons[i]->b);
			glBegin(GL_LINE_LOOP);

			for (double j = 0; j < 2 * 3.1415926535897932384; j += 0.01) {
				glVertex2f(playerIcons[i]->x + (cos(j) * .2), playerIcons[i]->y + (sin(j) * .2));
			}

			glEnd();

		}
		
	}

}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(1.0, 1.0, 1.0);
        
    // Draw a yellow cross
    glColor3d(1.0, 1.0, 0.0);
    
    glBegin(GL_LINES);
    
    glVertex2f(mx - 0.05f, my);
    glVertex2f(mx + 0.05f, my);
    
    glVertex2f(mx, my - 0.05f);
    glVertex2f(mx, my + 0.05f);
    
    glEnd();

	//Draw the game board
	drawYellowLines();
	drawBlackRectangles();
	drawPlayerIcons();
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::clearBoard() {

	//reset the board to not have any objects with x or o character types
	playerIcons[0] = new Shape(-0.5, 0.5, 0.0, 0.0, 0.0, '0'); //0
	playerIcons[1] = new Shape(0.0, 0.5, 0.0, 0.0, 0.0, '1'); //1
	playerIcons[2] = new Shape(0.5, 0.5, 0.0, 0.0, 0.0, '2'); //2

	playerIcons[3] = new Shape(-0.5, 0.0, 0.0, 0.0, 0.0, '3'); //3
	playerIcons[4] = new Shape(0.0, 0.0, 0.0, 0.0, 0.0, '4'); //4
	playerIcons[5] = new Shape(0.5, 0.0, 0.0, 0.0, 0.0, '5'); //5

	playerIcons[6] = new Shape(-0.5, -0.5, 0.0, 0.0, 0.0, '6'); //6
	playerIcons[7] = new Shape(0.0, -0.5, 0.0, 0.0, 0.0, '7'); //7
	playerIcons[8] = new Shape(0.5, -0.5, 0.0, 0.0, 0.0, '8'); //8

	//resets turn back to player 1
	playerTurn = Turn::player1;

	//tie back to 0
	tie = 0;

	//resets win variables
	winner = ' ';
	declareWinner = false;

}

void App::checkWin(Shape shape) {

	//Win via Horizontal lines
	if (playerIcons[0]->type == shape.type && playerIcons[1]->type == shape.type && playerIcons[2]->type == shape.type ||
		playerIcons[3]->type == shape.type && playerIcons[4]->type == shape.type && playerIcons[5]->type == shape.type ||
		playerIcons[6]->type == shape.type && playerIcons[7]->type == shape.type && playerIcons[8]->type == shape.type) {
	
		winner = shape.type;
		declareWinner = true;

	}	
	
	//Win via Vertical lines
	if (playerIcons[0]->type == shape.type && playerIcons[3]->type == shape.type && playerIcons[6]->type == shape.type ||
		playerIcons[1]->type == shape.type && playerIcons[4]->type == shape.type && playerIcons[7]->type == shape.type ||
		playerIcons[2]->type == shape.type && playerIcons[5]->type == shape.type && playerIcons[8]->type == shape.type) {
	
		winner = shape.type;
		declareWinner = true;

	}

	//Win via Diagonals
	if (playerIcons[0]->type == shape.type && playerIcons[4]->type == shape.type && playerIcons[8]->type == shape.type ||
		playerIcons[2]->type == shape.type && playerIcons[4]->type == shape.type && playerIcons[6]->type == shape.type) {
	
		winner = shape.type;
		declareWinner = true;
	
	}

	//Print Winner of game
	if (declareWinner == true) {
		
		std::cout << "The winner is " << winner << "!" << std::endl;
		clearBoard();

	}

	//In the event of a Tie, restart the game
	if (tie == 9) {
		std::cout << "CATS GAME" << std::endl;
		clearBoard();
	}

}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
	for (int i = 0; i < gridRegions.size(); i++) {

		//Check which part of the 3x3 grid a player is trying to place their mark (either o or x)
		if (gridRegions[i]->contains(mx, my)) {

			//calculates midpoints x and y to find center of the black rectangles in the sector of the board to get point to create xmark or circle
			double midx = (gridRegions[i]->x + (gridRegions[i]->x + gridRegions[i]->w)) / (2);
			double midy = (gridRegions[i]->y + gridRegions[i]->y - gridRegions[i]->h) / (2);

			//It is Player 1's turn when true 
			if (playerTurn == Turn::player1) {
				
					//Check if a player icon (x or o) is already occupying that space
					for (int i = 0; i < playerIcons.size(); i++) {

						//If the section doesn't have an x || o and the midpoint exists within the vector, its a free spot to place an x || o
						if (playerIcons[i]->type != 'x' && playerIcons[i]->type != 'o' && playerIcons[i]->x == midx && playerIcons[i]->y == midy) {

							playerIcons[i] = new Shape(midx, midy, 1.0, 0.0, 0.0, 'x');
							tie++;
							
							if (AImode) {
								playerTurn = Turn::AI;
								AIcalculate = true;
							}
							else {
								playerTurn = Turn::player2;
							}

							checkWin(*playerIcons[i]);
							break;

						}
						else if (playerIcons[i]->type == 'x' && playerIcons[i]->x == midx && playerIcons[i]->y == midy ||
							playerIcons[i]->type == 'o' && playerIcons[i]->x == midx && playerIcons[i]->y == midy) {

							std::cout << playerIcons[i]->type << " is occupying this space. Try again!" << std::endl;
							break;
						}
					}
				
			}
			//It is Player 2's turn when false
			else if (playerTurn == Turn::player2){
				
				//Check if a player icon (x or o) is already occupying that space
				for (int i = 0; i < playerIcons.size(); i++) {
					if (playerIcons[i]->type != 'x' && playerIcons[i]->type != 'o' && playerIcons[i]->x == midx && playerIcons[i]->y == midy) {

						playerIcons[i] = new Shape(midx, midy, 0.0, 0.0, 1.0, 'o');
						tie++;
						playerTurn = Turn::player1;
						checkWin(*playerIcons[i]);
						break;
					}
					else if (playerIcons[i]->type == 'x' && playerIcons[i]->x == midx && playerIcons[i]->y == midy ||
						playerIcons[i]->type == 'o' && playerIcons[i]->x == midx && playerIcons[i]->y == midy) {

						std::cout << playerIcons[i]->type << " is occupying this space. Try again!" << std::endl;
						break;
					}
				}
			}
		}
	}

	if (playerTurn == Turn::AI) {
		
		//AI speaks
		std::cout << "A.I: " << AIchatter[rand() % 8 + 0] << std::endl;

		while (AIcalculate) {
			//Randomly calculate a int between 0-8 into a char to determine which spot on the grid the AI will pick
			AImove = '0' + rand() % 9 + 0;

			//Check if a player icon (x or o) is already occupying that space
			for (int i = 0; i < playerIcons.size(); i++) {
				if (playerIcons[i]->type != 'x' && playerIcons[i]->type != 'o' && playerIcons[i]->type == AImove) {

					playerIcons[i] = new Shape(playerIcons[i]->x, playerIcons[i]->y, 0.0, 0.0, 1.0, 'o');
					tie++;
					playerTurn = Turn::player1;
					checkWin(*playerIcons[i]);
					AIcalculate = false;
					break;
				}
			}
		}
	}

    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
	
	if (key == 'a') {
		if (tie == 0) {
			AImode = true;
			std::cout << "A.I Mode" << std::endl;
		}
		else {
			std::cout << "You can't change modes mid-game!" << std::endl;
		}
	}

	if (key == 's') {
		if (tie == 0) {
			AImode = false;
			std::cout << "2 Player Mode" << std::endl;
		}
		else {
			std::cout << "You can't change modes mid-game!" << std::endl;
		}
	}

}
