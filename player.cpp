#include "player.hpp"
#include <iostream>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
	
	this->board = Board();
	
	this->side = side;
	
	if(side == WHITE)
		this->opp_side = BLACK;
	else
		this->opp_side = WHITE;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    
	if(opponentsMove != nullptr)
		board.doMove(opponentsMove, opp_side);
     
    std::vector<Move*> moves;
    bool found = false;
    
    for(int i = 0; i < 8; i++)
    {
		for(int j = 0; j < 8; j++)
		{
			Move *move = new Move(i, j);
			if(board.checkMove(move, side))
			{
				moves.push_back(move);
				found = true;
				//board.doMove(move, side);
				//return move;
			}	
		}
	}
	
	if(!found)
		return nullptr;
	
	Move *best = heuristic(moves);
	board.doMove(best, side);
	
	return best;
    
    return nullptr;
}

Move *Player::heuristic(std::vector<Move*> moves)
{
	int bestscore = -9999999;
	Move *best = nullptr;
	
	for(unsigned int i = 0; i < moves.size(); i++)
	{
		Board *copy = board.copy();
		copy->doMove(moves[i], side);
		
		int score = copy->count(side) - copy->count(opp_side);	
		int x = moves[i]->x;
		int y = moves[i]->y;
		
		if (isCorner(moves[i]))
			score = score + 10; 
		else if(x == 0 || x == 7 || y == 0 || y == 7)
			score = score + 7;
		else if (adjacent(moves[i], Move(0,0)) == 2|| adjacent(moves[i], Move(7,0)) == 2|| adjacent(moves[i], Move(0,7)) == 2|| adjacent(moves[i], Move(7,7)) == 2)
			score = score - 10;
		else if (adjacent(moves[i], Move(0,0)) == 1|| adjacent(moves[i], Move(7,0)) == 1|| adjacent(moves[i], Move(0,7)) == 1|| adjacent(moves[i], Move(7,7)) == 1)
			score = score - 7;
		
		if(score > bestscore)
		{
			bestscore = score;
			best = moves[i];
		}	
	}
	
	return best;
	
}

bool Player::isCorner(Move* move)
{
	if (move->x == 0)
		if (move->y == 0 || move->y == 7)
			return true;
	if (move->x == 7)
		if (move->y == 0 || move->y == 7)
			return true;
	return false; 
}

int Player::adjacent(Move* pt1, Move pt2)
{
	if (sqrt(std::pow((pt1->x - pt2.x), 2) + std::pow((pt1->y - pt2.y), 2)) == 1)
		return 1; 
	if (sqrt(std::pow((pt1->x - pt2.x), 2) + std::pow((pt1->y - pt2.y), 2)) == sqrt(2))
		return 2; 
	return 0; 
}
