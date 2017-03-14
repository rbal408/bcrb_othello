#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <tuple>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Side our_side;
    Side their_side;
    Board *this_board;

    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int Heuristic_calc(Board curr, Move move, Side side);
    int minimax_decision(Board after_move, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
