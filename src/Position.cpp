//
// Created by shiro on 06.06.20.
//

#include "Position.h"

bool Position::operator==(const Position &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

Position::Position(Position &position) {
    x = position.x.load();
    y = position.y.load();

}

Position::Position(int i, int i1) : x{i}, y{i1}{
}
