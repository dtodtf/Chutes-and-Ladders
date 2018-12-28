#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Game.h"
using namespace std;

/*
 * Name        Game
 * Purpose:    Constructor.
 * Parameters: None
 * Returns:    None
 * Effects:    Creates the board and the players.
 * Notes:      None
 */
Game::Game() {
    srand(time(NULL));
    
    //createBoard needs to be in front of everything else!
    createBoard();
    
    bool validPlayerNum = false;
    cout << "You can have between 2 and 4 players. How many do you want?";
    cout << endl;
    cin >> numPlayers;
    while (not validPlayerNum) {
        if (numPlayers >= 2 and numPlayers <= 4) {
            validPlayerNum = true;
            createPlayerArray(numPlayers);
        } else {
            cout << "Invalid player number. Please enter a number between ";
            cout << "2 and 4." << endl;
            cin >> numPlayers;
        }
    }
    
    cout << endl;
}

/*
 * Name        ~Game
 * Purpose:    Destructor
 * Parameters: None
 * Returns:    None
 * Effects:    Deletes all of the squares in the board that are allocated on
 *             the heap.
 * Notes:      None
 */
Game::~Game() {
    //delete the squares
    square *currPtr = boardHead->adjacent;
    square *prevPtr = boardHead;
    while(currPtr != nullptr) {
        delete prevPtr;
        prevPtr = currPtr;
        currPtr = currPtr->adjacent;
    }

    //delete the players
    for (int i = 0; i < numPlayers; i++) {
        delete players[i];
    }
}

/*
 * Name        play
 * Purpose:    The driver code for the whole game. Calls the private functions.
 * Parameters: None
 * Returns:    None
 * Effects:    None
 * Notes:      None.
 */
void Game::play() {
    cin.ignore(); //clears the buffer so that newline from when you entered 
    //number of players doesn't mess it all up.
    player *winner = nullptr;
    bool didWin = false;
    while (not didWin) {
        for (int i = 0; i < numPlayers; i++) {
            cout << players[i]->name << ", press enter to begin your turn.";
            cin.get();
            movePlayer(players[i]);

            //check to see if there's a winner.
            if ((players[i]->currentPos)->squareNum == 100) {
                winner = players[i];
                didWin = true;
                break;
            }
        }
    }
    cout << winner->name <<" won! Congratulations!" << endl;
}

/*
 * Name        createSquare
 * Purpose:    Create a new square struct.
 * Parameters: square num as int, a pointer to the next square, and a pointer 
 *             to another square if there's a chute or ladder
 * Returns:    Pointer to a square struct
 * Effects:    None.
 * Notes:      None.
 */
Game::square * Game::createSquare(int sqNum, square *adjacentSq, 
  square *otherSq) {
    square *newSquare = new square;
    newSquare->squareNum = sqNum;
    newSquare->adjacent = adjacentSq;
    newSquare->otherPath = otherSq;
    return newSquare;      
}

/*
 * Name        createBoard
 * Purpose:    Create a linked list of squares. I'll add the chutes and ladders
 *             later.
 * Parameters: None. 
 * Returns:    None.
 * Effects:    Creates the linked list starting at boardHead.
 * Notes:      I'm not counting from zero in my for loop because in c&l square 
 *             numbers start at 1
 */
void Game::createBoard() {
    boardHead = createSquare(0, nullptr, nullptr);
    square * prevPtr = boardHead;
    square * currPtr = nullptr;

    for (int i = 1; i <= 100; i++) {
        currPtr = createSquare(i, nullptr, nullptr);
        prevPtr->adjacent = currPtr;
        prevPtr = currPtr;
    }

    createLinks();
}

/*
 * Name        goTo
 * Purpose:    set a pointer to a square in the linked list
 * Parameters: A square number. 
 * Returns:    A pointer to the square with said number.
 * Effects:    None
 * Notes:      None
 */
Game::square * Game::goTo(int desiredNum) {
    square *currPtr = boardHead;
    while (currPtr->squareNum != desiredNum)
        currPtr = currPtr->adjacent;
    return currPtr;
}

/*
 * Name        linkSquares
 * Purpose:    Make a pointer from source sq to destination sq. Represents a 
 *             chute or a ladder
 * Parameters: The square nums of the src and the dest
 * Returns:    None
 * Effects:    Creates a pointer in the src sq to the dest sq
 * Notes:      Uses the goTo function to return ptrs to certain squares.
 */
void Game::linkSquares(int src, int dest) {
    square *srcSq = goTo(src);
    square *destSq = goTo(dest);
    srcSq->otherPath = destSq;
}

/*
 * Name        createLinks
 * Purpose:    Creates the pointers that act as chutes and ladders
 * Parameters: None because the spots are predetermined on the board 
 * Returns:    None
 * Effects:    Sets otherPath on some squares as pointers to other squares
 * Notes:      Serves as helper function to createBoard
 */
void Game::createLinks() {
    linkSquares(1, 38);
    linkSquares(4, 14);
    linkSquares(9, 31);
    linkSquares(16, 6);
    linkSquares(21, 42);
    linkSquares(28, 84);
    linkSquares(36, 44);
    linkSquares(47, 26);
    linkSquares(49, 11);
    linkSquares(51, 67);
    linkSquares(56, 53);
    linkSquares(62, 19);
    linkSquares(64, 60);
    linkSquares(71, 91);
    linkSquares(80, 100);
    linkSquares(87, 24);
    linkSquares(93, 73);
    linkSquares(95, 75);
    linkSquares(98, 78);
}

/*
 * Name        newPlayer
 * Purpose:    Create a new player struct
 * Parameters: Player name as a string
 * Returns:    Pointer to a player struct
 * Effects:    None
 * Notes:      None
 */
Game::player * Game::newPlayer(string name) {
    player *newPlayer = new player;
    newPlayer->name = name;
    newPlayer->currentPos = boardHead;
}

/*
 * Name        createPlayerArray
 * Purpose:    Create an array of player structs
 * Parameters: Number of desired players as an int. 
 * Returns:    None.
 * Effects:    Initializes the players array
 * Notes:      returns true if provided a valid input, otherwise return false.
 *             Ask player for a valid value if not given proper one.
 */
void Game::createPlayerArray(int numPlayers) {
    if (numPlayers == 2) {
        players[0] = newPlayer("P1");
        players[1] = newPlayer("P2");
    } else if (numPlayers == 3) {
        players[0] = newPlayer("P1");
        players[1] = newPlayer("P2");
        players[2] = newPlayer("P3");
    } else if (numPlayers == 4) {
        players[0] = newPlayer("P1");
        players[1] = newPlayer("P2");
        players[2] = newPlayer("P3");
        players[3] = newPlayer("P4");
    }
}

/*
 * Name        rollDie
 * Purpose:    Generate a random number between 1 and 6 inclusive
 * Parameters: None. 
 * Returns:    An int.
 * Effects:    None
 * Notes:      Helper function to movePlayer
 */
int Game::rollDie() {
    int result = (rand() % 6) + 1;
    return result;
}

/*
 * Name        movePlayer
 * Purpose:    move the player on the main board
 * Parameters: the player struct to move. 
 * Returns:    None.
 * Effects:    Traverses the linked list by the number that the user rolls and
 *             updates the player struct's currentPos
 * Notes:      Accounts for the chutes and ladders too!
 */
void Game::movePlayer(player *player) {
    int numToMove = rollDie();
    cout << "You rolled a " << numToMove << "." << endl;

    //To win, the player must land on 100 exactly. Can't go over.
    if (numToMove + (player->currentPos)->squareNum > 100) {
        cout << "Uh oh! Your roll puts you over square 100, so you lose your ";
        cout << "turn." << endl;
    } else {
        for (int i = 0; i < numToMove; i++) {
            player->currentPos = (player->currentPos)->adjacent;
        }
    }
    cout << "You landed on square " << (player->currentPos)->squareNum << ".";
    cout << endl;

    //check to see if they landed on a chute or ladder
    if ((player->currentPos)->otherPath != nullptr) {
        if ((player->currentPos)->squareNum > 
          ((player->currentPos)->otherPath)->squareNum) {
              //if the src square num is greater than dest square num
              cout << "You landed on a chute! You're going down to square ";
              cout << ((player->currentPos)->otherPath)->squareNum << ".";
              cout << endl;
        } else {
            //if the src square num is less than the dest square num
            cout << "You landed on a ladder! You're going up to square ";
            cout << ((player->currentPos)->otherPath)->squareNum << ".";
            cout << endl;
        }
        player->currentPos = (player->currentPos)->otherPath;
    }
    cout << endl;
}

/*
 * Name        printBoardTest
 * Purpose:    just print out all of the square nums in the board
 * Parameters: None. 
 * Returns:    None.
 * Effects:    Prints the board linked list to the screen
 * Notes:      Debug only.
 */
void Game::printBoardTest() {
    square *currPtr = boardHead;
    while (currPtr != nullptr) {
        cerr << currPtr->squareNum << " ";
        currPtr = currPtr -> adjacent;
    }
}

/*
 * Name        printChutesLadders
 * Purpose:    Print out the chutes and ladders on the board
 * Parameters: None. 
 * Returns:    None.
 * Effects:    Prints the start square and end square of each chute/ladder 
 * Notes:      Debug only.
 */
void Game::printChutesLadders() {
    square *currPtr = boardHead;
    while (currPtr != nullptr) {
        if (currPtr->otherPath != nullptr) {
            cout << currPtr->squareNum<< "->";
            cout << (currPtr->otherPath)->squareNum << endl;
        }
        currPtr = currPtr->adjacent;
    }
}

/*
 * Name        printPlayerInfo
 * Purpose:    Print out the contents of the player struct
 * Parameters: A player struct 
 * Returns:    None.
 * Effects:    Ptrints to the screen.
 * Notes:      Debug only.
 */
void Game::printPlayerInfo(player *player) {
    cerr << "Player name: " << player->name << endl;
    cerr << "board head: " << boardHead->squareNum << endl;
    cerr << "Current postiion: " << (player->currentPos)->squareNum << endl;
}