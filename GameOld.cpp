// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include <cassert>
#include <cctype>
#include "Game.h"
#include "Piece.h"
#include "Queen.h" 

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

	void Game::make_move(const Position& start, const Position& end) {
		//start valid_move
	   if(!(end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')){
		throw Exception("end position is not on board");
	   }
	   if(!(start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
		throw Exception("start position is not on board");
	   }
	   if(!(this->board(start))){
		throw Exception("no piece at start position");
	   }
	   if(!((is_white_turn && this->board(start)->is_white())||(!is_white_turn && !this->board(start)->is_white()))){
		throw Exception("piece color and turn do not match");
	   }
	   if(this->board(end)){
		//legal_capture_shape returns returns legal_move shape unless pawn
		if(!(this->board(start)->legal_capture_shape(start, end))){
			throw Exception("illegal capture shape");
		}
	   }else if(!(this->board(end))){
		if(!(this->board(start)->legal_move_shape(start, end))
		//should we check if start == end? is that illegal???
		||(start == end)){
			throw Exception("illegal move shape");
		}
	   }
	   if((this->board(end)->is_white()&&this->board(start)->is_white())||(!this->board(end)->is_white()&&!this->board(start)->is_white())){
		throw Exception("cannot capture own piece");
	   }
	   char p = this->board(start)->to_ascii();
	   //vertical moves
	   //I'm only going to check every space until the last space
	   if((start.first == end.first) && (p=='p' || p=='P' || p=='q' || p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		//checks the difference between the two positions: ASCII arithmatic
		//assumes that legal moves has already been called and works
		int t = end.second - start.second;
		//if positive number, move "up" on board
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
				}
			}
		}else if(t<0){//if negative number, moves "down" on board
			for(int i= -1; i>t; i--){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
				}
			}
		}
	   }
	   //check for horizontal moves
	   else if((start.second == end.second)&&(p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
				}
			}
	    }else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
				}
			}
		}
		}
		//checks the diagonal for bishop, queen or mystery
	   else if(p=='B' || p=='b' || p=='m' || p=='M' || p=='Q' || p=='q'){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				//add i to both of them
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
				}
			}
		}else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
				}
			}
	   }
	   }

	   //checks for in check by making a copy of the game and then playing it
	   Game* GameCopy = new Game;
	   GameCopy->board = board;
	   GameCopy->is_white_turn = is_white_turn;
		//might not have needed to add "this" so many times
		delete GameCopy->board(end);
		GameCopy->board.add_piece(end, board(start)->to_ascii());
		delete GameCopy->board(start);
		//is null piece always this '-' piece?
		GameCopy->board.add_piece(start, '-');
	   if((GameCopy->is_white_turn && GameCopy->in_check(is_white_turn)) || (!GameCopy->is_white_turn && GameCopy->in_check(!is_white_turn))){
			throw Exception("move exposes check");
			//does it need to reset pieces to start and end and keep going??

	   }
	   delete GameCopy;
	   //end valid_move

	   //move the piece on the actual board
		delete board(end);
		board.add_piece(end, board(start)->to_ascii());
		delete board(start);
		//do i need this line or does it revert to null?
		board.add_piece(start, '-');

		//checks for piece promotion
		if(this->board(end)->is_white() && this->board(end)->to_ascii()=='P' && end.second == '8'){
			delete board(end);
			board.add_piece(end, 'Q');
		}else if(!this->board(end)->is_white() && this->board(end)->to_ascii()=='p' && end.second=='1'){
			delete board(end);
			board.add_piece(end, 'q');
		}
	}

	bool Game::in_check(const bool& white) const {
		// go through each space on the board and check if there is a piece
			// if there is a piece, call helper function with current position, king's position, and piece type to see
			// if the capture move would be legal
				// if legal, then in_check is true
		bool in_check = false;
		
		char k = 'k';
		if (white) {
			k = 'K';
		}
		
		int k_col = 0;
		int k_row = 0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				//edited to check if there's a piece at that position (avoids seg fault)
				if (board(Position('A' + i, '1' + j)) && board(Position('A' + i, '1' + j))->to_ascii() == k){
					k_col = 'A' + i;
					k_row = '1' + j;
					break;
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board(Position('A' + i, '1' + j))){
					if (valid_move(Position('A' + i, '1' + j), Position(k_col, k_row))) {
						in_check = true;
						break;
					}
				}
			}
		}

		return in_check;
		
	}
	bool Game::valid_move(const Position& start, const Position& end) const {
		if(!(end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')){
		throw Exception("end position is not on board");
		return false;
	   }
	   if(!(start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
		throw Exception("start position is not on board");
		return false;
	   }
	   if(!(this->board(start))){
		throw Exception("no piece at start position");
		return false;
	   }
	   if(!((is_white_turn && this->board(start)->is_white())||(!is_white_turn && !this->board(start)->is_white()))){
		throw Exception("piece color and turn do not match");
		return false;
	   }
	   if(this->board(end)){
		//legal_capture_shape returns returns legal_move shape unless pawn
		if(!(this->board(start)->legal_capture_shape(start, end))){
			throw Exception("illegal capture shape");
			return false;
		}
	   }else if(!(this->board(end))){
		if(!(this->board(start)->legal_move_shape(start, end))
		//should we check if start == end? is that illegal???
		||(start == end)){
			throw Exception("illegal move shape");
			return false;
		}
	   }
	   if((this->board(end)->is_white()&&this->board(start)->is_white())||(!this->board(end)->is_white()&&!this->board(start)->is_white())){
		throw Exception("cannot capture own piece");
		return false;
	   }
	   char p = this->board(start)->to_ascii();
	   //vertical moves
	   //I'm only going to check every space until the last space
	   if((start.first == end.first) && (p=='p' || p=='P' || p=='q' || p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		//checks the difference between the two positions: ASCII arithmatic
		//assumes that legal moves has already been called and works
		int t = end.second - start.second;
		//if positive number, move "up" on board
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}else if(t<0){//if negative number, moves "down" on board
			for(int i= -1; i>t; i--){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}
	   }
	   //check for horizontal moves
	   else if((start.second == end.second)&&(p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
	    }else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}
		}
		//checks the diagonal for bishop, queen or mystery
	   else if(p=='B' || p=='b' || p=='m' || p=='M' || p=='Q' || p=='q'){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				//add i to both of them
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
	   }
	   }

	   //checks for in check by making a copy of the game and then playing it
	   Game* GameCopy = new Game;
	   GameCopy->board = board;
	   GameCopy->is_white_turn = is_white_turn;
		//might not have needed to add "this" so many times
		delete GameCopy->board(end);
		GameCopy->board.add_piece(end, board(start)->to_ascii());
		delete GameCopy->board(start);
		//is null piece always this '-' piece?
		GameCopy->board.add_piece(start, '-');
	   if((GameCopy->is_white_turn && GameCopy->in_check(is_white_turn)) || (!GameCopy->is_white_turn && GameCopy->in_check(!is_white_turn))){
			throw Exception("move exposes check");
			return false;
		

	   }
	   delete GameCopy;
	   return true;

		// if knight or pawn, return true since they can skip over pieces

		// else, check which piece it is and see if there are other pieces in the path
	}
	/*
	bool Game::valid_move(const bool& white, const Position& start, const Position& end, const Piece* piece) const {
		if(!(end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')){
		throw Exception("end position is not on board");
		return false;
	   }
	   if(!(start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
		throw Exception("start position is not on board");
		return false;
	   }
	   if(!(this->board(start))){
		throw Exception("no piece at start position");
		return false;
	   }
	   if(!((is_white_turn && this->board(start)->is_white())||(!is_white_turn && !this->board(start)->is_white()))){
		throw Exception("piece color and turn do not match");
		return false;
	   }
	   if(this->board(end)){
		//legal_capture_shape returns returns legal_move shape unless pawn
		if(!(this->board(start)->legal_capture_shape(start, end))){
			throw Exception("illegal capture shape");
			return false;
		}
	   }else if(!(this->board(end))){
		if(!(this->board(start)->legal_move_shape(start, end))
		//should we check if start == end? is that illegal???
		||(start == end)){
			throw Exception("illegal move shape");
			return false;
		}
	   }
	   if((this->board(end)->is_white()&&this->board(start)->is_white())||(!this->board(end)->is_white()&&!this->board(start)->is_white())){
		throw Exception("cannot capture own piece");
		return false;
	   }
	   char p = this->board(start)->to_ascii();
	   //vertical moves
	   //I'm only going to check every space until the last space
	   if((start.first == end.first) && (p=='p' || p=='P' || p=='q' || p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		//checks the difference between the two positions: ASCII arithmatic
		//assumes that legal moves has already been called and works
		int t = end.second - start.second;
		//if positive number, move "up" on board
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}else if(t<0){//if negative number, moves "down" on board
			for(int i= -1; i>t; i--){
				if(board(Position(start.first, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}
	   }
	   //check for horizontal moves
	   else if((start.second == end.second)&&(p=='Q' || p=='q' || p=='r' || p=='R' || p=='m' || p=='M')){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
	    }else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}
		}
		//checks the diagonal for bishop, queen or mystery
	   else if(p=='B' || p=='b' || p=='m' || p=='M' || p=='Q' || p=='q'){
		int t = end.first - start.first;
		if(t>0){
			for(int i=1; i<t; i++){
				//add i to both of them
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
		}else if(t<0){
			for(int i= -1; i>t; i--){
				if(board(Position(start.first+i, start.second+i))){
					throw Exception("illegal move shape: piece in path");
					return false;
				}
			}
	   }
	   }

	   //checks for in check by making a copy of the game and then playing it
	   Game* GameCopy = new Game;
	   GameCopy->board = board;
	   GameCopy->is_white_turn = is_white_turn;
		//might not have needed to add "this" so many times
		delete GameCopy->board(end);
		GameCopy->board.add_piece(end, board(start)->to_ascii());
		delete GameCopy->board(start);
		//is null piece always this '-' piece?
		GameCopy->board.add_piece(start, '-');
	   if((GameCopy->is_white_turn && GameCopy->in_check(is_white_turn)) || (!GameCopy->is_white_turn && GameCopy->in_check(!is_white_turn))){
			throw Exception("move exposes check");
			return false;
		

	   }
	   delete GameCopy;
	   return true;

		// if knight or pawn, return true since they can skip over pieces

		// else, check which piece it is and see if there are other pieces in the path
	}*/


	
	/*
	bool Game::in_check(const bool& white) const {
		bool in_check = false;
		int pawn_pos = -1;
		char k = 'k'; char k_op = 'K'; char q = 'Q'; char b = 'B'; char n = 'N'; char r = 'R'; char p = 'P';
		if (white) {
			k = 'K'; k_op = 'k'; q = 'q'; b = 'b'; n = 'n'; r = 'r'; p = 'p';
			pawn_pos = 1;
		}

		int k_col = 0;
		int k_row = 0;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board(Position('A' + i, '1' + j))->to_ascii() == k){
					k_col = 'A' + i;
					k_row = '1' + j;
					break;
				}
			}
		}

		// check for pawns
		if ((board(Position(k_col+pawn_pos, k_row+1))->to_ascii() == p) || (board(Position(k_col+pawn_pos, k_row+1))->to_ascii() == p)) {
			in_check = true;
		}
		
		int check = 0;
		int side = 1;
		while (check < 2) {
			// check for bishops and queens (diagonal)
			for (int i = 1; i < 9; i++) {
				int j = side * i;
				if (!(k_col + j > 'H' || k_row + j > 8 || k_col + j < 'A' || k_row + j < 1)) {
					if ((board(Position(k_col + j, k_row + j)) != nullptr) || (board(Position(k_col + j, k_row + j)) != nullptr)) {
						if ((board(Position(k_col + j, k_row + j))->to_ascii() == b) || (board(Position(k_col + j, k_row + j))->to_ascii() == q)) {
							in_check = true;
						} else {
							break;
						}
					}
				} else {
					break;
				}
			}
			for (int i = 1; i < 9; i++) {
				int j = side * i;
				if (!(k_col + j > 'H' || k_row + j > 8 || k_col + j < 'A' || k_row + j < 1)) {
					if ((board(Position(k_col + j, k_row - j)) != nullptr)) {
						if ((board(Position(k_col + j, k_row - j))->to_ascii() == b) || (board(Position(k_col - j, k_row + j))->to_ascii() == q)) {
							in_check = true;
						} else {
							break;
						}
					}
				} else {
					break;
				}
			}

			// check for rooks and queen (horizontal and vertical)
			for (int i = 1; i < 9; i++) {
				int j = side * i;
				if (!(k_col + j > 'H' || k_row + j > 8 || k_col + j < 'A' || k_row + j < 1)) {
					if ((board(Position(k_col, k_row + j)) != nullptr)) {
						if ((board(Position(k_col, k_row + j))->to_ascii() == r) || (board(Position(k_col, k_row + j))->to_ascii() == q)) {
							in_check = true;
						} else {
							break;
						}
					}
				} else {
					break;
				}
			}
			for (int i = 1; i < 9; i++) {
				int j = side * i;
				if (!(k_col + j > 'H' || k_row + j > 8 || k_col + j < 'A' || k_row + j < 1)) {
					if ((board(Position(k_col + j, k_row)) != nullptr)) {
						if ((board(Position(k_col + j, k_row))->to_ascii() == r) || (board(Position(k_col + j, k_row))->to_ascii() == q)) {
							in_check = true;
						} else {
							break;
						}
					}
				} else {
					break;
				}
			}

			// check for king
			if ((board(Position(k_col + side, k_row + side))->to_ascii() == k_op) 
			|| (board(Position(k_col + side, k_row + side))->to_ascii() == k_op)
			|| (board(Position(k_col, k_row + side))->to_ascii() == k_op)
			|| (board(Position(k_col + side, k_row))->to_ascii() == k_op)
			) {
				in_check = true;
			}

			// check for knight
			if ((board(Position(k_col + 1, k_row + side * 2))->to_ascii() == n) 
			|| (board(Position(k_col - 1, k_row + side * 2))->to_ascii() == n)
			|| (board(Position(k_col + 2, k_row + side))->to_ascii() == n)
			|| (board(Position(k_col -2,  k_row + side))->to_ascii() == n)
			) {
				in_check = true;
			}

			side = -side;
			check++;
		}

		return in_check;
	}
	*/

	bool Game::in_mate(const bool& white) const {
	 //first see if it is in check
	//then see if the king has a valid move to each square around it and if it is moved to each square around it that it will still be in check
	//then see if there are any other pieces in their hand 
		//if any of those pieces have a legal move at any space around the king
			//make that move, and see if it is still in check, if so, move on to the next piece. 
	 // if after all this it is still in check, then it is in mate . 
		if(!in_check(white)){ 
			return false; 
		} //if its not in check at this position, it can't be in mate
		
	  
	  //check is valid move for each space around the kings current spot, because that function checks if its in check at that position as well
	  //find position of the king and save it in a variable
	  //king in question is:
	  char king = 'k';
	  if(white){ king = 'K';}
	  
		//I DIDNT DELETE THIS COPY YET , is it necessary
	  	Game * Copy = new Game;
		Copy->board = board;
		Copy->is_white_turn = is_white_turn;
		//go through board and find the current position of the king, save it in the variable curr below
		
		Chess::Position curr;
		for(int c = 0; c < 8; c++){
			for(int r = 0; r < 8; r++){
				if(board(Position('A' + c, '1' + r))->to_ascii() == king){
					curr = Position('A' + c, '1' + r);
				}
			}
		}
		//test all moves around curr position for king to move
		Chess::Position next = curr;
		//start with one space rightward
			next.first = curr.first + 1; 
			//if its a possible move without being in check, then its not in mate.
			if(valid_move(curr, next)){ return false; } 
		// one space rightward and upward (right-up diagonal)
			next.second = curr.second + 1; // one space rightward and upward (right-up diagonal)
			if(valid_move(curr, next)){ return false; }
		//directly upward: 
			next.first = curr.first;
			next.second = curr.second + 1; 
			if(valid_move(curr, next)){ return false; }
		//up-left diagonal:
			next.first = curr.first -1;
			if(valid_move(curr, next)){ return false; }
		//directly left by one space:
			next.second = curr.second;// next.first is already curr -1;
			if(valid_move(curr, next)){ return false; }
		//diagonal left-down:
			next.second = curr.second -1;
			if(valid_move(curr, next)){ return false; }
		//directly downward one space
			next.first = curr.first; // its already down one space from before
			if(valid_move(curr, next)){ return false; }
		//diagonal right-down:
			next.first = curr.first + 1;
			if(valid_move(curr, next)){ return false; }
	//reset the next variable, and use it for  moving of pieces other than king.
	next.first = curr.first;
	next.second = curr.second;
	//next check if any other pieces can save the king, if not then its in mate. 
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			//if the piece is the same color as the king in check 
			if(white == isupper(board(Position('A' + i, '1' + j))->to_ascii())){
			//make a variable to see if the piece can legally move to any space around the king using 
			//need to do this if statement multiple times to check if it can move to any space around the king.
				next.first = curr.first + 1; //checking directly rightward first 
				if( valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				next.second = curr.second + 1; // checking up-right diagonal
				if( valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//need to do this for every space. 
				//checking directly upward:
				next.first = curr.first - 1; 
				if(valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//checking up-left diagnoal
				next.first = curr.first - 1;
				if(valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//checking directly left 
				next.second = curr.second;
				if(valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//checking left-down diagonal
				next.second = curr.second -1;
				if(valid_move(Position('A' + i, '1' + j), next)){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//checking directly down
				next.first = curr.first;
				if(valid_move(Position('A' + i, '1' + j), next)){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
						return false;
					}
					delete temp;
				}
				//checking down-right diagonal 
				next.first = curr.first + 1;
				if(valid_move(Position('A' + i, '1' + j), next) ){
					Game * temp = new Game;
					temp->board = board;
					temp->is_white_turn = is_white_turn;
					temp->make_move(Position('A' + i, '1' + j), next);
					//if another piece can move to the king, and then the king not be in check, then its not in mate
					if(!in_check(white)){
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
		//is brute force for stalemate also permitted?
		Game* GameCopy = new Game;
	   GameCopy->board = board;
	   GameCopy->is_white_turn = is_white_turn;
		
		//iterates through every space on the board. if there's a piece there of the correct color,
		//it checks every space on the board to see if that end position is a legal move. If no legal moves,
		//in stalemate.
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				char n = GameCopy->board(Position('A' + i, '1' + j))->to_ascii();
			//use isupper/islower instead of writing out if the piece equals each separate piece (K, B, Q, etc)
				if (white && (isupper(n))){
					for (int t = 0; t < 8; t++) {
						for (int n = 0; n < 8; n++) {
							if(valid_move(Position('A'+i, '1'+j), Position('A'+i, '1'+j))){
								delete GameCopy;
								return false;
							}
						}
					}
				}else if(!white && (islower(n))){
					for (int t = 0; t < 8; t++) {
						for (int n = 0; n < 8; n++) {
							if(valid_move(Position('A'+i, '1'+j), Position('A'+i, '1'+j))){
								delete GameCopy;
								return false;
							}
						}
					}
				}
			}
		}

		delete GameCopy;

		return true;
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		
		int point_value = 0;
	
		for (int i = 'A'; i <= 'H'; i++) {
			for (int j = '0'; j <= '8'; j++) {
				//const Piece* piece1 = board(Position(i,j));
				if(board(Position(i,j))){
					const Piece* piece1 = board(Position(i,j));
					//should it be white or is_white_turn ??
					if(isupper(piece1->to_ascii())&& white){
						point_value += piece1->point_value();
					}
					if(islower(piece1->to_ascii())&& !white){
						point_value += piece1->point_value();
					}
				}

				}
			}

        return point_value;
    }


    std::istream& operator>> (std::istream& is, Game& game) {
		if (!is) {
			throw Exception("Cannot load the game!");
		}

		char piece;
		char col = 'A';
		char row = '1';
		int pos = 0;

		while (is >> piece && pos < 65) {
			is >> piece;
			game.board(Position(col + pos, row + (pos/8)));
		}

		if (pos != 64) {
			throw Exception("Cannot load the game!");
		}

		if (is >> piece) {
			if (isupper(piece)) {
				game.is_white_turn = true;
			} else {
				game.is_white_turn = false;
			}
		} else {
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