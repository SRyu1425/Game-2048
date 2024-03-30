#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::up()) {
        model_.do_move("up");
    } else if (key == ge211::Key::down()) {
        model_.do_move("down");
    } else if (key == ge211::Key::left()) {
        model_.do_move("left");
    } else if (key == ge211::Key::right()) {
        model_.do_move("right");
    }
}


