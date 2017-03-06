#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <tuple>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Side *our_side;
    Board *this_board;

    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

class move_score {

public:
    Move *move = new Move(-1, -1);
    int score;

    move_score(Move *mv, int scr){
        move->setX(mv->getX());
        move->setY(mv->getY());
        score = scr;
    }

    ~move_score(){}

    Move getMove(){
        return *move;
    }
    int getScore(){
        return score;
    }
};

class two_node_ll {

    struct Node {
        Move *move = new Move(-1, -1);
        int score;
        Node *next;
    };

public:

    two_node_ll(){
        head = NULL;
    }

    void push(Move *mv, int scr)
    {
        Node *n = new Node();
        n->move->setX(mv->getX());
        n->move->setY(mv->getY());
        n->score = scr;
        head = n;
    }

    move_score pop()
    {
        Node *n = head;
        Move *mv = n->move;
        int scr = n->score;

        head = head->next;
        delete n;
        return move_score(mv, scr);
    }

private:
    Node *head;
};




#endif
