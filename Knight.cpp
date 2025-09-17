// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Knight.h"

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    
    if(abs(start.first - end.first) == 1){
        if(abs(start.second - end.second) == 2){
            return true;
        }
    }
    else if(abs(start.first - end.first) == 2){
        if(abs(start.second - end.second) == 1){
            return true;
        }
    }

    return false;
    
  }
}
