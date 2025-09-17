///////////////////////////////////
// IT IS OK TO MODIFY THIS FILE, //
// YOU WON'T HAND IT IN!!!!!     //
///////////////////////////////////
#ifndef MYSTERY_H
#define MYSTERY_H

#include "Piece.h"

namespace Chess
{
	class Mystery : public Piece {

	public:
		bool legal_move_shape(const Position& start, const Position& end) const override{
		if (start.first < 'A' || start.first > 'H' || start.second < '1' || start.second > '8') {
      return false;
    }

    if (end.first < 'A' || end.first > 'H' || end.second < '1' || end.second > '8')	{
      return false;
    }

    int	hor_move = abs(end.first - start.first);
    int ver_move = abs(end.second -	start.second);

    if (hor_move == ver_move)	{
	    return true;
    } else if (hor_move == 0 || ver_move == 0) {
      return true;
    }

    return false;
  }


		char to_ascii() const override { return is_white() ? 'M' : 'm';	}

		int point_value() const override { return 3; }

		virtual ~Mystery(){}
    
    std::string to_unicode() const override { return is_white() ? "\u2687" : "\u2689"; }

	private:
		Mystery(bool is_white) : Piece(is_white) {}

		friend Piece* create_piece(const char& piece_designator);
	};
}
#endif // MYSTERY_H
