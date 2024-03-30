//#include "ge211.hxx"
#include "view.hxx"
#include <unordered_map>



using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;


View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return {750,750};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "2048";
}



View::Position
View::board_to_screen(Model::Position board_pos)
{
    const int board_dim = 4;
    const int window_width = 750;
    const int window_height = 750;
    const int offset = 0;

    int x_scale = window_width / board_dim;
    int y_scale = (window_height - offset) / board_dim;
    return {board_pos.x * x_scale, board_pos.y * y_scale + offset};
}

View::Position
View::screen_to_board(View::Position screen_pos)
{

    const int board_dim = 4;
    const int window_width = 750;
    const int window_height = 750;
    const int offset = 0;

    int x_scale = window_width / board_dim;
    int y_scale = (window_height - offset) / board_dim;
    return {screen_pos.x / x_scale, (screen_pos.y - offset) / y_scale};
}



static ge211::Color const background_sprite_color {183,173,161};
static ge211::Color const score_block_color {0,0,0};
static ge211::Color const tile_sprite_color {222, 238, 227};
ge211::geometry::Dims<int> background_dims = {750,750};

static ge211::Color const two_c {235,228,219};
static ge211::Color const four_c {234,225,204};
static ge211::Color const eight_c {226,180,131};
static ge211::Color const sixteen_c {224,154,109};
static ge211::Color const thirtytwo_c {221,130,102};
static ge211::Color const sixtyfour_c {222, 238, 227};
static ge211::Color const onetwentyeight_c {234,214,153};
static ge211::Color const twofiftysix_c {232,212,141};
static ge211::Color const fivetwelve_c {241,213,113};
static ge211::Color const onethousandtwentyfour_c {231,207,125};
static ge211::Color const twothousandfourtyeight_c {230,197,66};


View::View(Model const& model)
        : model_(model),
          background_sprite(background_dims, background_sprite_color),
          tile_sprite({180,180}, tile_sprite_color),

          two({180,180}, two_c),
          four({180,180}, four_c),
          eight({180,180}, eight_c),
          sixteen({180,180}, sixteen_c),
          thirtytwo({180,180}, thirtytwo_c),
          sixtyfour({180,180}, sixtyfour_c),
          onetwentyeight({180,180}, onetwentyeight_c),
          twofiftysix({180,180}, twofiftysix_c),
          fivetwelve({180,180}, fivetwelve_c),
          onethousandtwentyfour({180,180}, onethousandtwentyfour_c),
          twothousandfourtyeight({180,180}, twothousandfourtyeight_c)

{

}




void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    set.add_sprite(background_sprite, {0, 0}, 0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Position pos {i, j};

            if (model_.game_over()) {
                std::cout << "game over";
                /*
                set.add_sprite(background_sprite, {0, 0}, 23);
                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder <<"Score: " << model_.get_sum();
                text_sprite_[11].reconfigure(number_builder);
                ge211::Posn<int> location = ge211::Posn<int>(0, 0) +
                                            (initial_window_dimensions()/2);
                set.add_sprite(text_sprite_[11], location, 24);
                 */
            }
                add_number_sprite(set, pos, model_.getter(pos));
            }
        }

    }


    void
    View::add_number_sprite(Sprite_set& set, View::Position pos, Number n)
    {

        Position screen_pos = board_to_screen(pos);
        Position text_pos = {screen_pos.x + 75, screen_pos.y + 50};

        if (!model_.game_over()) {
            //if game isn't over, check if each position is a specific number and
            // return that sprite.w
            if (n == Number::two) {
                //add number block
                set.add_sprite(two, screen_pos, 1);

                //add text
                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 2;
                text_sprite_[0].reconfigure(number_builder);
                set.add_sprite(text_sprite_[0], text_pos, 2);

            } else if (n == Number::four) {
                set.add_sprite(four, screen_pos, 3);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 4;
                text_sprite_[1].reconfigure(number_builder);
                set.add_sprite(text_sprite_[1], text_pos, 4);

            } else if (n == Number::eight) {
                set.add_sprite(eight, screen_pos, 5);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 8;
                text_sprite_[2].reconfigure(number_builder);
                set.add_sprite(text_sprite_[2], text_pos, 6);

            } else if (n == Number::sixteen) {
                set.add_sprite(sixteen, screen_pos, 7);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 16;
                text_sprite_[3].reconfigure(number_builder);
                set.add_sprite(text_sprite_[3],
                               {text_pos.x - 10, text_pos.y},
                               8);

            } else if (n == Number::thirtytwo) {
                set.add_sprite(thirtytwo, screen_pos, 9);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 32;
                text_sprite_[4].reconfigure(number_builder);
                set.add_sprite(text_sprite_[4],
                               {text_pos.x - 10, text_pos.y},
                               10);

            } else if (n == Number::sixtyfour) {
                set.add_sprite(sixtyfour, screen_pos, 11);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 64;
                text_sprite_[5].reconfigure(number_builder);
                set.add_sprite(text_sprite_[5],
                               {text_pos.x - 10, text_pos.y},
                               12);

            } else if (n == Number::onetwentyeight) {
                set.add_sprite(onetwentyeight, screen_pos, 13);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 128;
                text_sprite_[6].reconfigure(number_builder);
                set.add_sprite(text_sprite_[6],
                               {text_pos.x - 20, text_pos.y},
                               14);

            } else if (n == Number::twofiftysix) {
                set.add_sprite(twofiftysix, screen_pos, 15);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 256;
                text_sprite_[7].reconfigure(number_builder);
                set.add_sprite(text_sprite_[7],
                               {text_pos.x - 20, text_pos.y},
                               16);

            } else if (n == Number::fivetwelve) {

                set.add_sprite(fivetwelve, screen_pos, 17);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 512;
                text_sprite_[8].reconfigure(number_builder);

                set.add_sprite(text_sprite_[8],
                               {text_pos.x - 20, text_pos.y},
                               18);

            } else if (n == Number::onethousandtwentyfour) {

                set.add_sprite(onethousandtwentyfour, screen_pos, 19);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 1024;
                text_sprite_[9].reconfigure(number_builder);
                set.add_sprite(text_sprite_[9],
                               {text_pos.x - 30, text_pos.y},
                               20);

            } else if (n == Number::twothousandfourtyeight) {

                set.add_sprite(twothousandfourtyeight, screen_pos, 21);

                ge211::Text_sprite::Builder number_builder(sans28_);
                number_builder << 2048;
                text_sprite_[10].reconfigure(number_builder);
                set.add_sprite(text_sprite_[10],
                               {text_pos.x - 30, text_pos.y},
                               22);


                set.add_sprite(background_sprite, {0, 0}, 25);


                number_builder << "YOU WON! " << "Score: " << calculate_sum();
                text_sprite_[11].reconfigure(number_builder);
                set.add_sprite(text_sprite_[11], {120,150}, 30);

            }

        } else {
            set.add_sprite(background_sprite, {0, 0}, 25);

            ge211::Text_sprite::Builder number_builder(sans28_);
            number_builder <<"YOU LOST! " << "Score: " << calculate_sum();
            text_sprite_[11].reconfigure(number_builder);
            set.add_sprite(text_sprite_[11], {120,150}, 30);


        }
    }


int
View::calculate_sum()
{
    int sum = 0;

    for (Position posn : model_.all_posns()) {
        Number number = model_.getter(posn);

        if (number == Number::two) {
            sum += 2;
        } else if (number == Number::four) {
            sum += 4;
        } else if (number == Number::eight) {
            sum += 8;
        } else if (number == Number::sixteen) {
            sum += 16;
        } else if (number == Number::thirtytwo) {
            sum += 32;
        } else if (number == Number::sixtyfour) {
            sum += 64;
        } else if (number == Number::onetwentyeight) {
            sum += 128;
        } else if (number == Number::twofiftysix) {
            sum += 256;
        } else if (number == Number::fivetwelve) {
            sum += 512;
        } else if (number == Number::onethousandtwentyfour) {
            sum += 1024;
        } else if (number == Number::twothousandfourtyeight) {
            sum += 2048;
        }
    }

    return sum;
}
