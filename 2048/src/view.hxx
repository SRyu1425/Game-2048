#pragma once

#include "model.hxx"
#include <unordered_map>
//#include <ge211.hxx>



class View : public ge211::Abstract_game
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Position board_to_screen(Position pos);
    Position screen_to_board(Position pos);
    void add_to_sum(int num);


private:
    Model const& model_;
    ge211::Rectangle_sprite const background_sprite;
    //ge211::Rectangle_sprite const score_block;
    ge211::Rectangle_sprite const tile_sprite;

    ge211::Rectangle_sprite const two;
    ge211::Rectangle_sprite const four;
    ge211::Rectangle_sprite const eight;
    ge211::Rectangle_sprite const sixteen;
    ge211::Rectangle_sprite const thirtytwo;
    ge211::Rectangle_sprite const sixtyfour;
    ge211::Rectangle_sprite const onetwentyeight;
    ge211::Rectangle_sprite const twofiftysix;
    ge211::Rectangle_sprite const fivetwelve;
    ge211::Rectangle_sprite const onethousandtwentyfour;
    ge211::Rectangle_sprite const twothousandfourtyeight;

    //font
    ge211::Font sans28_{"sans.ttf", 50};

    ge211::Text_sprite text_sprite_[12];

    int calculate_sum();
    void add_number_sprite(ge211::Sprite_set& set, Position pos, Number n);



    };
