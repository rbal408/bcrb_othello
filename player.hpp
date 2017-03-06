#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <tuple>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

class two_node_ll {

    struct Node {
        Move move;
        int scr;
        Node *next;
    };

public:

    two_node_ll(){
        head = NULL;
    }

    void push(Move mv, int scr)
    {
        Node *n = new Node();
        n->move = mv;
        n->score = scr;
        head = n;
    }

    std::tuple<Move, int> pop();
    {
        Node *n = head;
        Move mv = n->move;
        int scr = n->score;

        head = head->next;
        delete n;
        std::tuple<Move, int> val = make_tuple(mv, scr);
        return val;
    }
}

#endif
