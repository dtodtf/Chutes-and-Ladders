class Game {
    private:
        //these data members deal with the actual board
        struct square {
            int squareNum;
            square *adjacent;
            square *otherPath;
        };    
        square *boardHead;

        //these data members deal with players
        struct player {
            std::string name;
            square *currentPos;
        };
        int numPlayers;
        player *players[4];
        player * newPlayer(std::string name);
        void createPlayerArray(int numPlayers);

        //these data members all have to do with creating the board
        square * createSquare(int sqNum, square *adjacentSq, square *otherSq);
        void createBoard();
        square * goTo(int desiredNum);
        void linkSquares(int src, int dest);
        void createLinks();

        //these data members deal with moving the player
        int rollDie();
        void movePlayer(player *player);

    public:
        //only three things in the client file.
        Game();
        ~Game();
        void play();

        //these functions are for debugging purposes only.
        void printBoardTest(); 
        void printChutesLadders();
        void printPlayerInfo(player *player);
};