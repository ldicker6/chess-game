// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include <cassert>
#include <cctype>
#include <cstddef>
#include "Exceptions.h"
#include "Game.h"

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );

	}

	// change_turn() switches the color to the current player
	void Game::change_turn(){
		is_white_turn = !is_white_turn;
	}


	void Game::make_move(const Position& start, const Position& end) {
		//start valid_move
		valid_move(start, end, is_white_turn);
	   //end valid_move

	   //move the piece on the actual board
		delete board(end);
		board.erase_key(end);
		board.add_piece(end, board(start)->to_ascii());
		delete board(start);
		board.erase_key(start);
		
		//checks for piece promotion
		if(this->board(end)->is_white() && this->board(end)->to_ascii()=='P' && end.second == '8'){
			delete board(end);
			board.erase_key(end);
			board.add_piece(end, 'Q');
		}else if(!this->board(end)->is_white() && this->board(end)->to_ascii()=='p' && end.second=='1'){
			delete board(end);
			board.erase_key(end);
			board.add_piece(end, 'q');
		}
	}

	// in_check determines whether the current player is in check
	bool Game::in_check(const bool& white) const {

		char k = 'k'; // k holds the character of the current player's king
		if (white) { k = 'K'; }
		
		int k_col = 0;
		int k_row = 0;

		// find the position of the king
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board(Position('A' + i, '1' + j)) && (board(Position('A' + i, '1' + j))->to_ascii() == k)){
					k_col = 'A' + i;
					k_row = '1' + j;
					break;
				}
			}
		}

		bool exceptions = true; // exceptions holds whether a valid move can be made or not

		// check whether each opposite side's piece can capture the king
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// if a piece is present, call valid_move with the current position and the king's position
				if (board(Position('A' + i, '1' + j))){
					try {
						valid_move(Position('A' + i, '1' + j), Position(k_col, k_row), !is_white_turn);
					}
					// if a valid move cannot be made, continue iterating through board
					catch(Chess::Exception const& err) {
						exceptions = false;
					}
					// if the current piece can capture the king, the game is in check
					if(exceptions){
						return true;
					}
				}
				exceptions = true;
			}
		}
		return false;
	}

	// in_check_piece returns the first piece (if not only) that is putting the current player in check
	Position Game::in_check_piece(const bool& white) const {

		char k = 'k'; // k holds the character of the current player's king
		if (white) {
			k = 'K';
		}
		
		int k_col = 0;
		int k_row = 0;

		// find the position of the king
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board(Position('A' + i, '1' + j)) && board(Position('A' + i, '1' + j))->to_ascii() == k){
					k_col = 'A' + i;
					k_row = '1' + j;
					break;
				}
			}
		}

		bool exceptions = true; // exceptions holds whether a valid move can be made or not

		// check whether each opposite side's piece can capture the king
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// if a piece is present, call valid_move with the current position and the king's position
				if (board(Position('A' + i, '1' + j))){
					try {
						valid_move(Position('A' + i, '1' + j), Position(k_col, k_row), !is_white_turn);
					}
					// if a valid move cannot be made, continue iterating through board
					catch(Chess::Exception const& err) {
						exceptions = false;
					}
					// if the current piece can capture the king, return the current position
					if(exceptions){
						return Position('A' + i, '1' + j);
					}
				}
				exceptions = true;
			}
		}
		return Position('0', '0');
	}

	// valid_move determines whether the piece can make a legal move from the start position to the end position
	void Game::valid_move(const Position& start, const Position& end, bool white) const {
		// check that the start position is on the board
		if(!(start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
			throw Exception("start position is not on board");
		}
		// check that the end position is on the board
		if(!(end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')){
			throw Exception("end position is not on board");
		}
		// check that there is a piece at the start position
		if(!(this->board(start))){
			throw Exception("no piece at start position");
		}
		// check that there is a piece at the end position
		if(!((white && this->board(start)->is_white())||(!white && !this->board(start)->is_white()))){
			throw Exception("piece color and turn do not match");
		}
		// check that the move is legal in terms of spaces moved
		if(!(this->board(end))|| this->board(end)== nullptr) {
			if(!(this->board(start)->legal_move_shape(start, end)) || (start == end)) {
				throw Exception("illegal move shape");
			}
		} else if(this->board(end) != nullptr) {
			// check that the move is not capturing their own piece
			if((this->board(end)->is_white()&&this->board(start)->is_white())||(!this->board(end)->is_white()&&!this->board(start)->is_white())){
				throw Exception("cannot capture own piece");
	   		}
			// check that the capture shape is legal
			if(!(this->board(start)->legal_capture_shape(start, end))){
				throw Exception("illegal capture shape");
			}
	  	}

		char p = this->board(start)->to_ascii(); // p holds the piece that is moving

	   	// check if there are pieces in the path
	  	// check vertical
	  	if((start.first == end.first) && (p=='p' || p=='P' || p=='q' || p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')) {
			// find the difference between the two positions: ASCII arithmatic
			int t = end.second - start.second;

			// if positive difference, move "up" on board
			if(t>0){
				for(int i=1; i<t; i++) {
					// if a piece is present, invalid move
					if(board(Position(start.first, start.second+i))){
						throw Exception("path is not clear");
					}
				}
			} else if(t<0) { //if negative difference, move "down" on board
				for(int i= -1; i>t; i--){
					// if a piece is present, invalid move
					if(board(Position(start.first, start.second+i))){
						throw Exception("path is not clear");
					}
				}
			}
	  	}
	 	// check horizontal
	 	else if((start.second == end.second)&&(p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')) {
			// find the difference between the two positions
			int t = end.first - start.first;

			// if positive difference, move "right" on board
			if (t > 0) {
				for(int i=1; i<t; i++){
					// if a piece is present, invalid move
					if(board(Position(start.first+i, start.second))){
						throw Exception("path is not clear");
					}
				}
	  		} else if ( t<0 ) { // if negative difference, move "right" on board
				for (int i= -1; i>t; i--) {
					// if a piece is present, invalid move
					if (board(Position(start.first+i, start.second))) {
						throw Exception("path is not clear");
					}
				}
			}
		}

		//check diagonal for bishop, queen or mystery
	 	else if(p=='B' || p=='b' || p=='m' || p=='M' || p=='Q' || p=='q') {
			int t = end.first - start.first;
			int n = end.second - start.second;

			if (t>0 && n>0) {
				for(int i=1; i<t; i++){
					if(board(Position(start.first+i, start.second+i))){
						throw Exception("path is not clear");
					}
				}
			} else if (t>0 && n<0) {
				for(int i=1; i<t; i++){
					if(board(Position(start.first+i, start.second-i))){
						throw Exception("path is not clear");
					}
				}
			} else if (t<0 && n>0) {
				for(int i=1; i<n; i++){
					if(board(Position(start.first-i, start.second+i))){
						throw Exception("path is not clear");
					}
				}
			} else if (t<0 && n<0) {
				for(int i= -1; i>t; i--){
					if(board(Position(start.first+i, start.second+i))){
						throw Exception("path is not clear");
					}
				}
	  		}
		}

		// check that the move does not put the player in check
	   	Game* GameCopy = new Game(*this); // GameCopy holds a copy of the game
		// make the move on copy
		delete GameCopy->board(end);
		GameCopy->board.erase_key(end);
		GameCopy->board.add_piece(end, board(start)->to_ascii());

		delete GameCopy->board(start);
		GameCopy->board.erase_key(start);
	
		// if the move puts the player in check, move is invalid
		if((GameCopy->in_check(white))){
			delete GameCopy;
			throw Exception("move exposes check");
	  	}

	 	delete GameCopy;
	}

	bool Game::in_mate(const bool& white) const {
		//if it is not in check, then its not mate 
		if(!in_check(white)){ 
			return false; 
		}
		//find the position of the piece that is checking the king
		Position checking_piece_position = in_check_piece(white);
		

		//check if valid move for each space around the kings current spot, because that function checks if its in check at that position as well
		//find position of the king and save it in a variable
		//this proves that the king can actually move to a different space so it is not in mate.
		
		//king in question is:
		char king = 'k';
		if(white){ king = 'K';}

		//go through board and find the current position of the king, save it in the variable curr below
		Chess::Position curr;
		for(int c = 0; c < 8; c++){
			for(int r = 0; r < 8; r++){
				if((board(Position('A' + c, '1' + r))) && board(Position('A' + c, '1' + r))->to_ascii() == king){
					curr = Position('A' + c, '1' + r);
					break;
				}
			}
		}

		//test all moves around curr position for king to move
		Chess::Position next = curr;

		//new bool for the valid_move exceptions
		bool exceptions = true;
		//start with one space rightward
		next.first = curr.first + 1; 
		//if its a possible move without being in check, then its not in mate.
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//one space rightward and upward (right-up diagonal)
		next.second = curr.second + 1; // one space rightward and upward (right-up diagonal)
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//directly upward: 
		next.first = curr.first;
		next.second = curr.second + 1; 
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//up-left diagonal:
		next.first = curr.first -1;
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//directly left by one space:
		next.second = curr.second;// next.first is already curr -1;
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//diagonal left-down:
		next.second = curr.second -1;
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; } 
		exceptions = true;

		//directly downward one space
		next.first = curr.first; // its already down one space from before
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; }
		exceptions = true;

		//diagonal right-down:
		next.first = curr.first + 1;
		try{valid_move(curr, next, white);}
		catch(Chess::Exception const&){exceptions = false;}
		if(exceptions){ return false; }
		exceptions = true; 

		//reset the next variable, and use it for  moving of pieces other than king.
		next.first = curr.first;
		next.second = curr.second;

		//next check if any other pieces can save the king, if not then its in mate. 
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				exceptions = true;
				//if the piece is the same color as the king in check 
				if(board(Position('A' + i, '1' + j))!= nullptr && white == isupper(board(Position('A' + i, '1' + j))->to_ascii())){
				//make a variable to see if the piece can legally move to any space around the king using 
				//need to do this if statement multiple times to check if it can move to any space around the king.
					next.first = curr.first + 1; //checking directly rightward first 
					
					try{valid_move(Position('A' + i, '1' + j), checking_piece_position, white);}
					catch(Chess::Exception const& err){
						exceptions = false;
					}

					if( exceptions ){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), checking_piece_position);
						//if another piece can move to the king, and then the king not be in check, then its not in mate
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}
					
					exceptions = true;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if( exceptions ){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						//if another piece can move to the king, and then the king not be in check, then its not in mate
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					next.second = curr.second + 1; // checking up-right diagonal
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if( exceptions ){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//need to do this for every space. 
					//checking directly upward:
					next.first = curr.first - 1; 
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//checking up-left diagnoal
					next.first = curr.first - 1;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//checking directly left 
					next.second = curr.second;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//checking left-down diagonal
					next.second = curr.second -1;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//checking directly down
					next.first = curr.first;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}

					exceptions = true;
					//checking down-right diagonal 
					next.first = curr.first + 1;
					try{valid_move(Position('A' + i, '1' + j), next, white);}
					catch(Chess::Exception const&){exceptions = false;}
					if(exceptions){
						Game * temp = new Game(*this);
						temp->make_move(Position('A' + i, '1' + j), next);
						if(!in_check(white)){
							delete temp;
							return false;
						}
						delete temp;
					}
				}
			}
		}

	return true;
	}

	bool Game::in_stalemate(const bool& white) const {
		//bool white means it's white's turn, checking if white is in stalemate

	   	//boolean for new valid_move function
	 	bool exceptions = true;
		
		//iterates through every space on the board. if there's a piece there of the correct color,
		//it checks every space on the board to see if that end position is a legal move. If no legal moves,
		//in stalemate.
		for(Board::const_iterator it = board.begin(); it != board.end(); ++it){
			if(board(*it) != nullptr){
				char n = board(*it)->to_ascii();
				//if white's turn, checks each position on the board to see if it's a valid move
				if ((white && (isupper(n)))){
					for(Board::const_iterator nit = board.begin(); nit != board.end(); ++nit){
						//resets exceptions to true every time it iterates so valid_move can work correctly
						exceptions = true;
						try{
							valid_move(*it, *nit, white);}
						catch(Chess::Exception const& e){
							exceptions = false;}
						if(exceptions){
							return false;
						}
					}
				}
				//same thing as for white's turn, but for black's turn
				else if(!white && (islower(n))){
					for(Board::const_iterator nit = board.begin(); nit != board.end(); ++nit){
						exceptions = true;
						try{valid_move(*it,*nit, white);}
						catch(Chess::Exception const&){exceptions = false;}
						if(exceptions){
							return false;
						}
					}
				}
			}
		}
		//if there are no valid moves for any piece of that color on the board, returns true
		return true;
	}

    // Return the total material point value of the designated player
	int Game::point_value(const bool& white) const {
		
		int point_value = 0;
	
		for(Board::const_iterator it = board.begin(); it != board.end(); ++it){
			//const Piece* piece1 = board(Position(i,j));
			if(board((*it))){
				const Piece* piece1 = board(*it);
				//should it be white or is_white_turn ??
				if(isupper(piece1->to_ascii())&& white){
					point_value += piece1->point_value();
				}
				if(islower(piece1->to_ascii())&& !white){
					point_value += piece1->point_value();
				}
				}
		}

        return point_value;
    }

   std::istream& operator>> (std::istream& is, Game& game) {
       	// check whether the file is valid
	  	if (!is) {
      	    throw Exception("Cannot load the game!");
       	}
 
		char piece; // piece holds the piece characters in the file
		char col = 'A';
		char row = '8';
		int pos = 0;

		// add each piece in the file onto the board
		while (pos < 64 && is >> piece) {
			// delete the current piece of the position on the board
			delete game.board(Position(col + (pos % 8), row - (pos/8)));
			game.board.erase_key(Position(col + (pos % 8), row - (pos/8)));

			// add the piece onto the board
			if (piece != '-') {
				game.board.add_piece(Position(col + (pos % 8), row - (pos/8)), piece);
			}

			pos++;
		}
 
		// if the files doesn't contain pieces for each position, invalid load
       	if (pos != 64) {
    		throw Exception("Cannot load the game!");
    	}
 
		// load the current player's color from the file
		if (is >> piece) {
			if (piece == 'w') {
				game.is_white_turn = true;
			} else {
				game.is_white_turn = false;
			}
		} else { // the current player's color isn't present, invalid load 
			throw Exception("Cannot load the game!");
		}
      
    	return is;
   }

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b',
		// depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}