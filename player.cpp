#include "player.hpp"
#include <vector>
#include <climits>

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
    // Create a copy board, a vector of moves, and initialize our move.
    this_board->doMove(opponentsMove, their_side);
    if (opponentsMove == nullptr)
    {
        std::cerr << "opponent: PASS" << endl;
    }
    else{
        std::cerr << "opponent: (" << opponentsMove->x << ", " << opponentsMove->y << ")" << endl;
    }
    Board *board_copy = this_board->copy();
    std::vector<Move*> moves;
    Move *our_move = nullptr;

    /* This checks for all possible moves and adds them to a vector of moves.
     * We can then check this vector to see which move we want to actually
     * make.
     */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *curr = new Move(i, j);
            if (this_board->checkMove(curr, our_side) == true)
            {
                moves.push_back(curr);
                std::cerr << "pushed back: (" << curr->getX() << ", " << curr->getY() << ")" << endl;
            }
        }
    }

    // If there are no possible moves, PASS
    if (moves.size() == 0)
    {
        return nullptr;
    }

    // Initializes our move to a value, and this_min_score
    our_move = moves.back();
    int this_min_score;

    /* Creates a vector of minimum scores from which we will choose our
     * move.
     */
    std::vector<int> min_scores;

    /* Executes each move on a board copy and determines the minimax
     * valuation for each one.
     */
    for (int i = 0; i < moves.size(); i++){
        board_copy->doMove(moves[i], our_side);
        this_min_score = this->minimax_decision(*board_copy, their_side);

        // Add the minimum score to the vector.
        min_scores.push_back(this_min_score);
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

    // Sets our move equal to the move with the max min.
    our_move = moves[max_index];
    
    // Executes our move on the local board, then returns it
    std::cerr << "executed: (" << our_move->getX() << ", " << our_move->getY() << ")" << endl;
    this_board->doMove(our_move, our_side);
    return our_move;
}

int Player::Heuristic_calc(Board curr, Move move, Side side){
    Board *board_copy = curr.copy();
    board_copy->doMove(&move, side);
    int this_score = (board_copy->count(our_side)) - (board_copy->count(their_side));

    // X part
    /*if (testingMinimax == false)
    {
        if (move.getX() == 0 || move.getX() == 7)
        {
            this_score += 5;
        }
        if (move.getX() == 1 && move.getY() == 1)
        {
            this_score -= 20;
        }
        if (move.getX() == 6 && move.getY() == 6)
        {
            this_score -= 20;
        }
        if (move.getX() == 1 && move.getY() == 6)
        {
            this_score -= 20;
        }
        if (move.getX() == 6 && move.getY() == 1)
        {
            this_score -= 20;
        }
        if (move.getX() == 1 && move.getY() == 0)
        {
            this_score -= 15;
        }
        if (move.getX() == 0 && move.getY() == 1)
        {
            this_score -= 15;
        }
        if (move.getX() == 6 && move.getY() == 0)
        {
            this_score -= 15;
        }
        if (move.getX() == 7 && move.getY() == 1)
        {
            this_score -= 15;
        }
        if (move.getX() == 0 && move.getY() == 6)
        {
            this_score -= 15;
        }
        if (move.getX() == 1 && move.getY() == 7)
        {
            this_score -= 15;
        }
        if (move.getX() == 6 && move.getY() == 7)
        {
            this_score -= 15;
        }
        if (move.getX() == 7 && move.getY() == 6)
        {
            this_score -= 15;
        }
        if (move.getY() == 0 || move.getY() == 7)
        {
            this_score += 5;
        }
    }*/
    return this_score;
}


int Player::minimax_decision(Board after_move, Side side){
    int this_score;
    int min_score = 1000;
    std::vector<Move*> their_moves;
    Board *two_ply = after_move.copy();

    // Creates a vector of all of their possible moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *curr = new Move(i, j);
            if (after_move.checkMove(curr, side) == true)
            {
                their_moves.push_back(curr);
            }
        }
    }

    if (their_moves.size() == 0)
    {
        return 1000000;
    }

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