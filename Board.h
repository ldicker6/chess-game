#ifndef BOARD_H
#define BOARD_H

#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


namespace Chess
{
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();


		//iterates through board and deletes a piece if it is there
		//virtual so delete piece can be called
		virtual ~Board(){
			
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					//try/catch because occ.at is a map, throws out of range if there is no matching key
					try{
						Piece* piece = occ.at(Position('A'+i, '1'+j));
        				if(piece){
							delete piece;
        				}
        			}
       				catch(std::out_of_range const&){
					}
				}
			}
			
			
		}

		// Returns a const pointer to the piece at a prescribed location if it exists,
		// or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		// Displays the board by printing it to stdout
		void display() const;

		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;
		
		//function to erase key from map 
		void erase_key(const Position& pos); 
		

		//iterator implementation, iterates through the board by position, returns the position
		class const_iterator {
			Position it;

			public:
			
			//constructs a const iterator by position it
			const_iterator(Position initial) : it(initial) { }
			
			//moves to the next row if at column 'H'
			const_iterator& operator++() {
				if (it.first == 'H') {
					--it.second;
					it.first = 'A';
					return *this;
				} else {
					++it.first;
					return *this;
				}

				
			}

				bool operator!=(const const_iterator& o) const { return it!=o.it; }

				//functions to get the value of it from the code
				Position operator*() { return it;}

				Position get(){return it;}

		};

		//iterates through the board starting at A8 so display() starts from A8 not A1
		const_iterator begin(void)const {return const_iterator(Position('A','8'));}
		
		const_iterator end(void)const {return const_iterator(Position('A', '0'));};
		

    
	private:
		// The sparse map storing the pieces, keyed off locations
		std::map<Position, Piece*> occ;

        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};

}
#endif // BOARD_H