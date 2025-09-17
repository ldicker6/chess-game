// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Queen.h"

namespace Chess
{
  bool Queen::legal_move_shape(const Position& start, const Position& end) const {
    //changed 1-8 to '1'-'8'
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



}
