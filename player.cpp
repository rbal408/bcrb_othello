#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    Board this_board = new Board();

    Side our_side = side;



    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    /* I am adding a comment so that I can see the canges made in github and get 5
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
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // A copy board from which to check move values for the Heuristic values.
    Board board_copy = this_board.copy();


    /* Theoretically, instead of having two vectors which had Moves and scores
     * respecitively, we could create a linked list which had three values,
     * the move, the value and a pointer to the next. This would liekly be
     * much more efficient. I have implemented this type of list in the 
     * player.hpp file.
     */
    std::vector<Move> moves; // Vector of possible moves
    std::vector<int> scores; // Vector of scores for each move
    Move our_move;           // The move we decide to make

    /* This checks for all possible moves and adds them to a vector of moves.
     * We can then check this vector to see which move we want to actually
     * make.
     */
    while(this_board.hasMoves(our_side)){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move curr = (i, j);
                if (checkMove(curr, our_side) == true)
                {
                    moves.push_back(curr);
                }
            }
        }

        /* This assignes a Heuristic score to each possible move by our_side.
         * We will iterate through all moves to determine the scores for each.
         */
        for (int i = 0; i < moves.size(); i++){
            /* TODO
             * Ideas:
             * Assign a _score_ based on the number of stones captured by the
             * move, then:
             *
             * If the square is a side: (score * 3)
             * If the square is a corner: (score * 4)?
             * If the square is one before a side/corner: (score * (-3))
             */

            board_copy.doMove()
        }

        this_board.doMove(our_move, our_side);
        moves.clear();
    }

    return nullptr;
}
