// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Piece.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  // operator () returns the piece at the position, nullptr if theres no piece there
  const Piece* Board::operator()(const Position& position) const {
   // occ.at will throw an exception if there is no piece at that position, so try to make a piece
   // and catch the exception if theres none, and return nullptr.
    try {
      Piece * check = occ.at(position);
      if (check) {
        return check;
      }
    }
    catch (std::out_of_range const&) {
      return nullptr;
    }

    return nullptr;
  }

  void Board::add_piece(const Position& position, const char& piece_designator) {
    //checking for piece designator
    if (!piece_designator) {
      throw Exception("invalid designator");
    }
    //checking that the position is on the board (that it is within the letters availabe)
    if (position.first < 65 || position.first > 72) {
      throw Exception("invalid position");
    }
    //checking that the position is within the number bounds
    if (position.second < 49 || position.second > 56 ) {
      throw Exception("invalid position");
    }

    //check if a piece at that position exists, if it does then throw the exception that its occupied
    //using the operator() function
    const Piece * check = (*this)(position);
    if (check != nullptr && (piece_designator != '-')) {
      throw Exception("position is occupied");
    } else {
      occ[position] = create_piece(piece_designator);
    } 
  }

  void Board::display() const {
    //displaying the top border
    Terminal::color_bg(Terminal::GREEN);
    Terminal::color_fg(false, Terminal::WHITE);
    std::cout<<"ABCDEFGH-";
    Terminal::set_default();
    std::cout<<std::endl;

    //iterate through the board and set the background checkerboard of magenta/blue
    for (Board::const_iterator it = this->begin(); it != this->end(); ++it) {
      char c = it.get().first;
      if ((it.get().second%2 == 0 &&(c == 'A' || c=='C' || c=='E' || c=='G'))
      ||(it.get().second%2 != 0 && (c == 'B' || c=='D' || c=='F' || c=='H'))) {
        Terminal::color_bg(Terminal::MAGENTA);
        } else {
          Terminal::color_bg(Terminal::BLUE);
      }
      try {
        Piece* piece = this->occ.at(*it);
        if (piece) {
          if (piece->is_white()) {
            Terminal::color_fg(false, Terminal::CYAN);
          } else {
            Terminal::color_fg(false, Terminal::RED);
          }
        }
	      std::cout << piece->to_unicode();
      }
      catch (std::out_of_range const&) {
          Terminal::color_fg(false, Terminal::BLACK);
	      std::cout << '-';      
      }
    //setting the border color
    if (it.get().first == 'H') {
      Terminal::color_bg(Terminal::GREEN);
      Terminal::color_fg(false, Terminal::WHITE);
      std::cout<<it.get().second;
      Terminal::set_default();
      std::cout<<std::endl;
    }
    
    }
    Terminal::set_default();
  }
    
//checks if the board has a valid number of kings for both sides 
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    //iterate through the board
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      //check if it is either a white king or a black king, and then add it to th count variables respectively. 
      if (it->second) {
        switch (it->second->to_ascii()) {
        case 'K':
          white_king_count++;
          break;
        case 'k':
          black_king_count++;
          break;
        }
      }
    }
    //white and black must each have exactly one king on board for it to return true. 
    return ((white_king_count == 1) && (black_king_count == 1));
  }

  //this is the function to erase the key from the map itself, not just the piece that was at that position
  void Board::erase_key(const Position& pos){ 
    occ.erase(pos);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (char r = '8'; r >= '1'; r--) {
      for( char c = 'A'; c <= 'H'; c++) {
	      const Piece* piece = board(Position(c, r));
	      if (piece) {
	          os << piece->to_ascii();
	      } else {
	          os << '-';
	      }
      }
      os << std::endl;
    }
    return os;
  }
}