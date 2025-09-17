// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "King.h"

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {

    int hor_move = abs(end.first - start.first);
    int ver_move = abs(end.second - start.second);

    if (hor_move == ver_move) {
      if (hor_move == 1) {
        return true;
      }
    } else if (hor_move == 0) {	
      if (ver_move == 1) {
	return true;
      }
    } else if (ver_move == 0) {
      if (hor_move == 1) {
        return true;
      }
    }

    return false;
  }

}
