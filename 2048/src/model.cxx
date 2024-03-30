#include "model.hxx"
#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace ge211;

//CONSTRUCTOR
Model::Model()
{
    std::srand(std::time(0));

    // Initialize the board with all positions set to none
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            Position posn{x, y};
            //do we need to overload operator []? or use setter/getter
            board_[posn] = Number::none;
        }
    }

    // Add initial random numbers to the board
    add_random_number();
    add_random_number();
}



Model::Position
Model::board_to_screen(Position board_pos) const
{
    const int board_dim = 4;
    const int window_width = 750;
    const int window_height = 750;
    const int offset = 0;

    int x_scale = window_width / board_dim;
    int y_scale = (window_height - offset) / board_dim;
    return {board_pos.x * x_scale, board_pos.y * y_scale + offset};
}

//SETTER FOR BOARD
void
Model::setter(Position posn, Number number)
{
    board_[posn] = number;
}

//GETTER FOR BOARD
Number
Model::getter(Position posn) const
{
    if (!good_position(posn)) {
        throw Client_logic_error("Board: position out of bounds");
    }

    auto ind = board_.find(posn);
    if (ind != board_.end()) {
        return ind->second;
    }
    // Return Number::none if the position is not found
    return Number::none;
}

std::vector<Model::Position>
Model::all_posns() const
{
    std::vector<Model::Position> all_pos;
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            Position posn{x, y};
            all_pos.push_back(posn);
        }
    }
    return all_pos;
}

//all for the [ ] operator
bool
Model::good_position(Position pos) const
{
    Position screen_pos = board_to_screen(pos);
    return 0 <= screen_pos.x && screen_pos.x <= 570 &&
           0 <= screen_pos.y && screen_pos.y <= 570;
}

void
Model::bounds_check_(Position pos) const
{
    if (!good_position(pos)) {
        throw Client_logic_error("Board: position out of bounds");
    }
}




int
Model::rand_int(int min, int max)
{

    // Generate a random integer within the range (excludes max)
    int random_number = min + std::rand() % (max - min);

    return random_number;
}


//adds a random number to the board at an empty position
void
Model::add_random_number()
{
    std::vector<Model::Position> empty_positions = get_empty_positions();
    //if there are empty positions
    if (!empty_positions.empty()) {
        //get a random index from the empty position vector
        int length = empty_positions.size();
        int index = rand_int(0, length);
        //use rand index to get an empty position from empty position vector
        Model::Position rand_pos = empty_positions[index];
        //choose either 2 or 4 to add (get random number)
        Number rand_num = two_or_four();

        //add this to the board at the chosen random posn
        board_[{rand_pos}] = rand_num;

    }
}


std::vector<Model::Position>
Model::get_empty_positions() const
{
    std::vector<Position> empty_pos;
    for (auto& pair : board_) {
        if (pair.second == Number::none) {
            empty_pos.push_back(pair.first);
        }
    }
    return empty_pos;
}

Number
Model::two_or_four() const
{

    //randomly returns 2 or 4 block
    int random_number = std::rand() % 2;
    if(random_number == 1){
        return Number::two;
    }else{
        return Number::four;
    }
}

bool
Model::adj_num(Position posn, Number number) const
{

    //check left and right
    if (posn.x > 0 && getter(Position{posn.x - 1, posn.y}) == number) {
        return true;
    }else if (posn.x < 3 && getter(Position{posn.x + 1, posn.y}) == number) {
        return true;
        //check top and bottom
    } else if (posn.y > 0 && getter(Position{posn.x, posn.y - 1}) == number) {
        return true;
    }else if (posn.y < 3 && getter(Position{posn.x, posn.y + 1}) == number) {
        return true;
    }

    return false;
}


bool
Model::game_over() const
{
    // Game over if no empty positions and no adjacent numbers can be merged
    for (Position posn: all_posns()){
        if(getter(posn) == Number::twothousandfourtyeight){
            return true;
        }
    }

    //first checks if there are no empty positions to add new numbers
    if (get_empty_positions().empty()) {
        for (const auto& pair : board_) {
            Position posn = pair.first;
            Number number = pair.second;

            //checking adjacent number possibilities
            if (adj_num(posn, number)) {
                return false;
            }
        }
        return true;

    }
    return false;
}

void
Model::merge_nums(Position end_pos, Position posn2)
{

    setter(end_pos, add(getter(end_pos)));
    setter(posn2, Number::none);
}


void
Model::do_move(std::string direction)
{
    if (!game_over()) {
        if (direction == "up") {
            if (valid_move() && move_up()) {
                add_random_number();
            }
        } else if (direction == "left") {
            if (valid_move() && move_left()) {
                add_random_number();

            }
        } else if (direction == "right") {
            if (valid_move() && move_right()) {
                add_random_number();
            }
        } else if (direction == "down") {
            if (valid_move() && move_down()) {
                add_random_number();
            }
        }
    }

}

bool
Model::valid_move() const
{
    // Check if any empty posns or mergeable
    for (const auto& pair : board_) {
        Position posn = pair.first;
        Number number = pair.second;

        if (number == Number::none) {
            return true;
        }

        // Check if there are adjacent positions with the same number
        if (adj_num(posn, number)) {
            return true;
        }
    }

    return false;
}


//1) didn't move b/c of wall
//2) didn't move b/c of diff number

//3) moved up until hit wall
//4) moved up until it merged
//5) moved up until hit diff num


//if it did move (if it didn't move don't do anything)
//case where already next to same num


// it won't move if the next pos is out of bounds or filled
//it didn't move b/c theres:  diff number, same number or wall

//it did move. check if it stopped b/c: diff, same, or wall

bool
Model::move_up()
{
    bool moved = false;
    //iterate through every posn
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            Position initial_posn {x, y};
            Number curr_number = getter(initial_posn);

            //if there is a number at this posn
            if (curr_number != Number::none) {
                int pos_y = initial_posn.y;

                //while the position is in bounds and its empty, keep setting
                // posn y - 1
                while (good_position({x, pos_y - 1}) &&
                       getter({x, pos_y - 1}) == Number::none) {
                    pos_y--;
                }

                //if next pos is in bounds or next pos isn't the starting pos
                if (good_position({x, pos_y - 1}) || pos_y != initial_posn.y) {
                    //if pos is out of bounds
                    if (!good_position({x, pos_y - 1})) {
                        setter({x, pos_y}, curr_number);
                        setter(initial_posn, Number::none);
                        moved = true;

                        //merged
                    } else if (curr_number == getter({x, pos_y - 1})) {
                        merge_nums({x, pos_y - 1}, initial_posn);
                        moved = true;

                    } else {
                        if (initial_posn.x == x && initial_posn.y == pos_y) {
                            setter(initial_posn, Number::none);
                            setter({x, pos_y}, curr_number);
                        } else {
                            setter(initial_posn, Number::none);
                            setter({x, pos_y}, curr_number);
                            moved = true;

                        }
                    }
                }
            }
        }
    }
    return moved;
}



bool
Model::move_down()
{
    bool moved = false;
    //iterate through every posn
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y >= 0; y--) {
            Position initial_posn{x, y};
            Number curr_number = getter(initial_posn);
            //if there is a number at this posn
            if (curr_number != Number::none) {
                int pos_y = initial_posn.y;
                //while the position is in bounds and its empty, keep setting
                // posn y - 1
                while (good_position({x,pos_y + 1 }) &&
                       getter({x, pos_y + 1}) == Number::none) {
                    pos_y++;
                }

                if (good_position({x,pos_y + 1}) || pos_y != initial_posn.y) {
                    //if pos is out of bounds,
                    if (!good_position({x, pos_y + 1})) {
                        setter({x, pos_y}, curr_number);
                        setter(initial_posn, Number::none);
                        moved = true;
                    } else if (curr_number == getter({x, pos_y + 1})) {
                        merge_nums({x, pos_y + 1}, initial_posn);
                        moved = true;
                    } else {

                        if (initial_posn.x == x && initial_posn.y == pos_y) {
                            setter(initial_posn, Number::none);
                            setter({x, pos_y}, curr_number);
                        } else {
                            setter(initial_posn, Number::none);
                            setter({x, pos_y}, curr_number);
                            moved = true;
                        }
                        }

                    }
                }
            }
        }
    return moved;

}


bool
Model::move_left()
{

    bool moved = false;
    //iterate through every posn
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            Position initial_posn {x, y};
            Number curr_number = getter(initial_posn);

            //if there is a number at this posn
            if (curr_number != Number::none) {
                int pos_x = initial_posn.x;

                //while the position is in bounds and its empty, keep setting
                // posn y - 1
                while (good_position({pos_x - 1, y}) &&
                       getter({pos_x - 1, y}) == Number::none) {
                    pos_x--;
                }

                if (good_position({pos_x - 1, y}) || pos_x != initial_posn.x) {
                    //if pos is out of bounds,
                    if (!good_position({pos_x - 1, y})) {
                        setter({pos_x, y}, curr_number);
                        setter(initial_posn, Number::none);
                        moved = true;
                    } else if (curr_number == getter({pos_x - 1, y})) {
                        merge_nums({pos_x - 1, y}, initial_posn);
                        moved = true;
                    } else {
                        if (initial_posn.x == pos_x && initial_posn.y == y) {
                            setter(initial_posn, Number::none);
                            setter({pos_x, y}, curr_number);
                        } else {
                            setter(initial_posn, Number::none);
                            setter({pos_x, y}, curr_number);
                            moved = true;

                        }
                    }
                }
            }
        }

    }
    return moved;

}

bool
Model::move_right()
{

    bool moved = false;
    //iterate through every posn
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x >= 0; x--) {
            Position initial_posn{x, y};
            Number curr_number = getter(initial_posn);

            //if there is a number at this posn
            if (curr_number != Number::none) {
                int pos_x = initial_posn.x;

                //while the position is in bounds and its empty, keep setting
                // posn y - 1
                while (good_position({pos_x + 1, y}) &&
                       getter({pos_x + 1, y}) == Number::none) {
                    pos_x++;
                }

                if (good_position({pos_x +1,y}) || pos_x !=
                initial_posn.x){
                    //if pos is out of bounds,
                    if (!good_position({pos_x +1,y})){
                        setter({pos_x,y},curr_number);
                        setter(initial_posn, Number::none);
                        moved = true;
                    } else if (curr_number == getter({pos_x +1,y})){
                        merge_nums({pos_x +1,y}, initial_posn);
                        moved = true;
                    } else {
                        if (initial_posn.x == pos_x && initial_posn.y == y) {
                            setter(initial_posn, Number::none);
                            setter({pos_x, y}, curr_number);
                        } else {
                            setter(initial_posn, Number::none);
                            setter({pos_x, y}, curr_number);
                            moved = true;

                        }


                    }
                }
            }
        }
    }
    return moved;

}


