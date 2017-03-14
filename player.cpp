#include "player.hpp"
#include <vector>
#include <climits>
#define BOARDSIZE 8

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->this_board = new Board();

    this->our_side = side;
    if (our_side == WHITE)
    {
        this->their_side = BLACK;
    }
    else this->their_side = WHITE;



    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    /* I am adding a comment so that I can see the changes made in github and get 5
     * free points! - Brent Cahill
     */

    /* I am also adding a comment so that I can see the changes made in github and get 5
     * free points! - Roshan Bal
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete this_board;
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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    // Execute the other player's move on our local board.
    this_board->doMove(opponentsMove, their_side);

    // Create a copy board, a vector of moves, and initialize our move.
    Board *board_copy = this_board->copy();
    std::vector<Move*> moves;
    Move *our_move = nullptr;

    /* This checks for all possible moves and adds them to a vector of moves.
     * We can then check this vector to see which move we want to actually
     * make.
     */
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            Move *curr = new Move(i, j);
            if (this_board->checkMove(curr, our_side) == true)
            {
                moves.push_back(curr);
            }
        }
    }

    // If there are no possible moves, PASS
    if (moves.size() == 0)
    {
        return nullptr;
    }

    // Initializes our move to the last element of the moves vector.
    our_move = moves.back();

    /* Initializes a variable for the minimum score to be used in the
     * loop below. Also creates a vector of minimum scores from which
     * we will choose our move.
     */
    int this_min_score;
    std::vector<int> min_scores;
    /* Executes each possible move on a board copy and determines the
     * minimax valuation for each one.
     */
    for (int i = 0; i < moves.size(); i++){
        // Execute the move on our board copy
        board_copy->doMove(moves[i], our_side);

        // Get the minimax valuation.
        this_min_score = this->minimax_decision(*board_copy, their_side);

        // Add the minimum score to the vector.
        min_scores.push_back(this_min_score);

        // Reset our board copy.
        board_copy = this_board->copy();
    }

    /* Finds the maximum value of all possible minimum values, according
     * to the minimax definition.
     */
    int max_of_mins = min_scores[0];
    int max_index = 0;
    for (int i = 0; i < min_scores.size(); i++)
    {
        if (min_scores[i] > max_of_mins)
        {
            max_of_mins = min_scores[i];
            max_index = i;
        }
    }

    // Sets our move equal to the move with the maximum min.
    our_move = moves[max_index];
    
    // Executes our move on the local board, then returns it
    this_board->doMove(our_move, our_side);
    return our_move;
}

/* This function takes a board after a potential move and the side for which
 * the move was made. It then returns the absolute minimum possible Heuristic
 * score that could occur for that sideif that move is made.
 */
int Player::Heuristic_calc(Board curr, Move move, Side side){
    // Creates a copy board for us to make the move on
    Board *board_copy = curr.copy();

    // Executes the move on the copy board.
    board_copy->doMove(&move, side);

    /* Calculates and returns the score using the difference between the
     * stones of the side passed and the stones of the opponent.
     */
    int this_score = (board_copy->count(our_side)) -
    (board_copy->count(their_side));
    return this_score;
}

/* This function takes a board after a potential move and the side for which
 * the move was made. It then returns the absolute minimum possible Heuristic
 * score that could occur for that sideif that move is made.
 */
int Player::minimax_decision(Board after_move, Side side){
    int this_score;
    int min_score = 1000;
    std::vector<Move*> their_moves;
    Board *two_ply = after_move.copy();

    // Adds all of the opponent's possible moves to the vector.
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            Move *curr = new Move(i, j);
            if (after_move.checkMove(curr, side) == true)
            {
                their_moves.push_back(curr);
            }
        }
    }

    /* Calculates and returns the absolute minimum score after the opponent's
     * move.
     */
    for (int i = 0; i < their_moves.size(); i++)
    {
        this_score = Heuristic_calc(*two_ply, *their_moves[i], their_side);
        if (this_score < min_score)
        {
            min_score = this_score;
        }
    }

    return min_score;
}