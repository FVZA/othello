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
std::vector<Move*> Player::getMoves(Board b, Side s)
{
    std::vector<Move*> moves;
    for(int i = 0; i < 8; i++)
    {
		for(int j = 0; j < 8; j++)
		{
			Move *move = new Move(i, j);
			if(b.checkMove(move, s))
			{
				moves.push_back(move);
			}	
		}
	}
	return moves; 
}

Move *Player::doMove(Move *opponentsMove, int msLeft) 
{

	if(opponentsMove != nullptr)
		board.doMove(opponentsMove, opp_side);
	std::vector<Move*> moves = getMoves(board, side); 
	if (moves.size() == 0) return nullptr; 
	
	//Random
	//return moves[0]; 

	//Heuristic 
	//Move *best = heuristic(moves);
	//board.doMove(best, side);
	//return best;    
	
	//Minimax
	int high = -99999;
	Move *best = moves[0];
	
	for(unsigned int i = 0; i < moves.size(); i++)
	{
		int score = minimax(board, moves[i], 1);
		if(score > high)
		{
			high = score;
			best = moves[i];
			
		}
		
		std::cerr << score << std::endl;
	}
	
	board.doMove(best, side);
	
	return best;
	
}

int Player::minimax(Board b, Move* move, int depth)
{	
	Side s = side;
	if(depth % 2 == 0)
		s = opp_side;
		
	if(depth == 0)
	{
		std::cerr << " " << simpleScore(b, move, s) << std::endl;
		return simpleScore(b, move, s);
		//return getScore(b, move, side);
	}
		
	Board *copy = b.copy();
	copy->doMove(move, s);
	
	s = opp_side;
	if(depth % 2 == 0)
		s = side;	
	
	std::vector<Move*> moves = getMoves(*copy, s);
	
	int low = 99999;
	for(unsigned int i = 0; i < moves.size(); i++)
	{
		int score = minimax(*copy, moves[i], depth - 1);
		if(score < low)
		{
			low = score;
		}
	}
	
	return low;
	
}

int Player::simpleScore(Board b, Move* move, Side s)
{
	Board *copy = b.copy();
	copy->doMove(move, s);
		
	//difference between player's and opponent's stones if move is made 
	int score = copy->count(side) - copy->count(opp_side);	
	return score;	
	
}

int Player::getScore(Board b, Move* move, Side s) 
{
	Board *copy = b.copy();
	copy->doMove(move, s);
		
	//difference between player's and opponent's stones if move is made 
	int score = copy->count(side) - copy->count(opp_side);	

	//number of moves possible if move is made 
	std::vector<Move*> new_moves = getMoves(*copy, s); 
	score += new_moves.size()/5; 
		
	//considers corners and edges captured by player and opponent if move is made 
	if (isCorner(move))
		score = score + 8; 
	else if (adjacent(move, Move(0,0)) == 2|| adjacent(move, Move(7,0)) == 2|| adjacent(move, Move(0,7)) == 2|| adjacent(move, Move(7,7)) == 2)
		score = score - 8;
	else if (adjacent(move, Move(0,0)) == 1|| adjacent(move, Move(7,0)) == 1|| adjacent(move, Move(0,7)) == 1|| adjacent(move, Move(7,7)) == 1)
		score = score - 10;
	else if(move->x == 0 || move->x == 7 || move->y == 0 || move->y == 7)
		score = score + 3; 
	
	return score; 
}

Move *Player::heuristic(std::vector<Move*> moves)
{
	int bestscore = -9999999;
	Move *best = nullptr;
	for (unsigned int i = 0; i < moves.size(); i++)
	{
		int score = getScore(board, moves[i], side); 
		
		if (score > bestscore)
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
