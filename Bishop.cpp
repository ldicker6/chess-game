// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Bishop.h"

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {

    int height = abs(start.second - end.second);
    int width = abs(start.first - end.first);    

    if(height != width) {return false;}

    return true;
  }

  
}
