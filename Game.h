#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

	class Game {

	public:
		// This default constructor initializes a board with the standard
		// piece positions, and sets the state to white's turn
		Game();
			
		Game(const Game& copy) : is_white_turn(copy.is_white_turn){

			//iterate through the copy board, and if there's a piece, add it to the new board
			//with this constructor, a board copy constructor is not needed

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
						const Piece* piece = copy.board(Position('A'+i, '1'+j));
        				if(piece){
							this->board.add_piece(Position('A'+i, '1'+j), piece->to_ascii());
        				}
        			
			}
			}
		}
		

		~Game(){
			//game automatically calls the board destructor, which contains all piece deletion
			//because game has a board, which has Piece pointers (dynamically allocated)
		}

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }
		
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Displays the game by printing it to stdout
		void display() const { board.display(); }
    
    /////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    // Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Attempts to make a move. If successful, the move is made and
		// the turn is switched white <-> black. Otherwise, an exception is thrown
		void make_move(const Position& start, const Position& end);

		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		//returns the piece that's putting the player in check
		Position in_check_piece(const bool& white) const;

		//declares our general valid_move function that checks for all valid_move exceptions
		void valid_move(const Position& start, const Position& end, bool white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

		void change_turn();
	private:
		// The board
		Board board;

		// Is it white's turn?
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);

        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
