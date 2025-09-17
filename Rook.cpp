// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Rook.h"

namespace Chess{
    bool Rook::legal_move_shape(const Position& start, const Position& end) const{
        if((end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')&&
       (start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
        if(start.first == end.first || start.second == end.second){
            return true;
        }
       }return false;
    }

    //also have to declare legal capture???
}