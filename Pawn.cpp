// Hawon Lee: hlee274
// Lulu Grubb: lgrubb3
// Lilah Dicker: ldicker6

#include "Pawn.h"

namespace Chess{
    bool Pawn::legal_move_shape(const Position& start, const Position& end) const{
        if((end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')&&
        (start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
            int hor_move = end.first - start.first;
            int ver_move = end.second - start.second;
            if (hor_move == 0) {
                if ((is_white() && start.second == '2' && ver_move == 2) || (!is_white() && start.second == '7' && ver_move == -2)) {
                        return true;
                }
                if ((is_white() && ver_move == 1) || (!is_white() && ver_move == -1)) {
                        return true;
                }
            }
       } 
       return false;
    }

    bool Pawn::legal_capture_shape(const Position& start, const Position& end) const{
        if((end.first >='A' && end.first<='H' && end.second>='1' && end.second <= '8')&&
        (start.first >='A' && start.first<='H' && start.second>='1' && start.second <= '8')){
            int hor_move = abs(end.first - start.first);
            int ver_move = end.second - start.second;
            if (hor_move == 1) {
                if ((is_white() && ver_move == 1) || (!is_white() && ver_move == -1)) {
                    return true;
                }
            }

        /*
        if(start.second +1 == end.second && (start.first +1 == end.first || start.first -1 == end.first)){
            return true;
        }*/
        }
        
        return false;
    }
}