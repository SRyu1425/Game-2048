#pragma once
#include <ge211.hxx>
#include "number.hxx"
#include <iostream>
#include <vector>
#include <unordered_map>

class Model
{
public:

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    //for the board
    using BoardMap = std::unordered_map<Position, Number>;

    //constructor
    Model();


#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif


private:
    //PRIVATE MEMBER VARIABLE
    BoardMap board_;

    void setter(Position posn, Number number);
    void bounds_check_(Position pos) const;
    bool move_up();
    bool move_right();
    bool move_left();
    bool move_down();



    //helper functions
public:
    Position board_to_screen(Position pos) const;
    Number getter(Position posn) const;
    void add_random_number();
    int rand_int(int min, int max);
    std::vector<Position> get_empty_positions() const;
    Number two_or_four() const;
    bool adj_num(Position posn, Number number) const;
    bool good_position(Position pos) const;
    std::vector<Model::Position> all_posns() const;
    bool game_over() const;
    void merge_nums(Position posn1, Position posn2);
    Number get_merged_number(Number number1, Number number2) const;
    void do_move(std::string direction);
    bool valid_move() const;

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

};

