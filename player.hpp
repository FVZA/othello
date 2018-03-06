#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
#include <cmath>
#include <math.h> 
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
    Board board;
    Side side;
    Side opp_side;
    
	int getScore(Move* move);
    Move *heuristic(std::vector<Move*> moves);
    int adjacent(Move* pt1, Move pt2);
    bool isCorner(Move* move);
	std::vector<Move*> getMoves(Board b);
};

#endif
