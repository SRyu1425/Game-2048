#include "model.hxx"

#include "number.hxx"

#include <catch.hxx>

using namespace ge211;

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

struct Test_access
{
    Model& model;

    Model::BoardMap& board()
    {
        return model.board_;
    }

    Number getter(Model::Position posn) const
    {
        return model.getter(posn);
    }

    std::vector<Model::Position> all_posns() const
    {
        return model.all_posns();
    }

    void setter(Model::Position posn, Number number)
    {
        model.setter(posn, number);
    }

    void do_move(std::string direction)
    {
        return model.do_move(direction);
    }

    bool move_up()
    {
        return model.move_up();
    }

    bool move_right()
    {
        return model.move_right();
    }

    bool move_left()
    {
        return model.move_left();
    }

    bool move_down()
    {
        return model.move_down();
    }

};
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.



//If a 2048 block is on the board, then the game should end once a move is
// performed
TEST_CASE("Game ends when 2048 is on the board")
{
    Model model;
    Test_access t{model};

    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    // Place a number 2048 on the board
    t.setter({0, 0}, Number::twothousandfourtyeight);

    t.move_left();

    // Check if the game is over
    CHECK(model.game_over() == true);
}

//If two blocks are adjacent to each other, and the correct arrow key is
// pressed, the two blocks should combine into the sum of the two blocks.
// The blocks should sum up and take the position of the end of the
// respective arrow key pressed, leaving the original position empty.

TEST_CASE("Two blocks combine")
{
    Model model;
    Test_access t{model};

    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::eight);
    t.setter({1, 0}, Number::eight);

    t.move_left();

    CHECK(t.getter({1,0}) == Number::none);
    CHECK(t.getter({0,0}) == Number::sixteen);



    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::sixteen);
    t.setter({1, 0}, Number::sixteen);

    t.move_left();

    CHECK(t.getter({1,0}) == Number::none);
    CHECK(t.getter({0,0}) == Number::thirtytwo);




    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::thirtytwo);
    t.setter({1, 0}, Number::thirtytwo);

    t.move_left();

    CHECK(t.getter({1,0}) == Number::none);
    CHECK(t.getter({0,0}) == Number::sixtyfour);




    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::sixtyfour);
    t.setter({1, 0}, Number::sixtyfour);

    t.move_left();

    CHECK(t.getter({1,0}) == Number::none);
    CHECK(t.getter({0,0}) == Number::onetwentyeight);
}

//All the blocks placed on the board should move according to the arrow key
// that is pressed. This means that the spot that the block was just in will
// now be empty and the end location will have the block that moved.
TEST_CASE("All blocks move with the arrow keys")
{
    Model model;
    Test_access t{model};

    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::eight);
    t.setter({0, 1}, Number::thirtytwo);
    t.setter({0, 2}, Number::sixteen);
    t.setter({0, 3}, Number::onetwentyeight);

    t.move_right();

    CHECK(t.getter({0,0}) == Number::none);
    CHECK(t.getter({0,1}) == Number::none);
    CHECK(t.getter({0,2}) == Number::none);
    CHECK(t.getter({0,3}) == Number::none);

    CHECK(t.getter({3,0}) == Number::eight);
    CHECK(t.getter({3,1}) == Number::thirtytwo);
    CHECK(t.getter({3,2}) == Number::sixteen);
    CHECK(t.getter({3,3}) == Number::onetwentyeight);


    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({3, 0}, Number::eight);
    t.setter({3, 1}, Number::thirtytwo);
    t.setter({3, 2}, Number::sixteen);
    t.setter({3, 3}, Number::onetwentyeight);

    t.move_left();

    CHECK(t.getter({3,0}) == Number::none);
    CHECK(t.getter({3,1}) == Number::none);
    CHECK(t.getter({3,2}) == Number::none);
    CHECK(t.getter({3,3}) == Number::none);

    CHECK(t.getter({0,0}) == Number::eight);
    CHECK(t.getter({0,1}) == Number::thirtytwo);
    CHECK(t.getter({0,2}) == Number::sixteen);
    CHECK(t.getter({0,3}) == Number::onetwentyeight);

    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 3}, Number::twofiftysix);
    t.setter({1, 3}, Number::sixtyfour);
    t.setter({2, 3}, Number::eight);
    t.setter({3, 3}, Number::twofiftysix);

    t.move_up();

    CHECK(t.getter({0,3}) == Number::none);
    CHECK(t.getter({1,3}) == Number::none);
    CHECK(t.getter({2,3}) == Number::none);
    CHECK(t.getter({3,3}) == Number::none);

    CHECK(t.getter({0,0}) == Number::twofiftysix);
    CHECK(t.getter({1,0}) == Number::sixtyfour);
    CHECK(t.getter({2,0}) == Number::eight);
    CHECK(t.getter({3,0}) == Number::twofiftysix);

    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }
    t.setter({0, 0}, Number::twofiftysix);
    t.setter({1, 0}, Number::sixtyfour);
    t.setter({2, 0}, Number::eight);
    t.setter({3, 0}, Number::twofiftysix);

    t.move_down();

    CHECK(t.getter({0,0}) == Number::none);
    CHECK(t.getter({1,0}) == Number::none);
    CHECK(t.getter({2,0}) == Number::none);
    CHECK(t.getter({3,0}) == Number::none);

    CHECK(t.getter({0,3}) == Number::twofiftysix);
    CHECK(t.getter({1,3}) == Number::sixtyfour);
    CHECK(t.getter({2,3}) == Number::eight);
    CHECK(t.getter({3,3}) == Number::twofiftysix);


}


// If two blocks aren't the same value, they should both move positions,
// but not merge.
TEST_CASE("Two blocks don't do anything if diff value")
{
    Model model;
    Test_access t{model};


    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({0, 0}, Number::eight);
    t.setter({1,0}, Number::sixtyfour);

    t.move_left();

    CHECK(t.getter({0,0}) == Number::eight);
    CHECK(t.getter({1,0}) == Number::sixtyfour);


    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({2,0}, Number::two);
    t.setter({2,1}, Number::four);

    t.move_up();

    CHECK(t.getter({2,0}) == Number::two);
    CHECK(t.getter({2,1}) == Number::four);


    for(Model::Position pos: t.all_posns()){
        t.setter(pos, Number::none);
    }

    t.setter({2,0}, Number::two);
    t.setter({2,1}, Number::onetwentyeight);

    t.move_down();

    CHECK(t.getter({2,2}) == Number::two);
    CHECK(t.getter({2,3}) == Number::onetwentyeight);


}

//When the model is constructed, the board starts with two random blocks of
// either value 2 or 4. We can iterate through the positions and check if two
// blocks of either 2 or 4 are generated.
TEST_CASE("The starting blocks have a value of 2 or 4")
{
    Model model;
    Test_access t{model};

    int count = 0;
    for(Model::Position pos: t.all_posns()){
        if(t.getter(pos) == Number::two || t.getter(pos) == Number::four){
            count++;
        }
    }

    CHECK(count == 2);

}
