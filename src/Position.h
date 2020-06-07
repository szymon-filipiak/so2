#ifndef SO2_PROJECT_POSITION_H
#define SO2_PROJECT_POSITION_H


class Position {
public:
    int x;
    int y;

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;
};


#endif //SO2_PROJECT_POSITION_H
