#include "number.hxx"

Number
add(Number num)
{
    if (num == Number::two) {
        return Number::four;
    } else if (num == Number::four) {
        return Number::eight;
    } else if (num == Number::eight) {
        return Number::sixteen;
    } else if (num == Number::sixteen) {
        return Number::thirtytwo;
    } else if (num == Number::thirtytwo) {
        return Number::sixtyfour;
    } else if (num == Number::sixtyfour) {
        return Number::onetwentyeight;
    } else if (num == Number::onetwentyeight) {
        return Number::twofiftysix;
    } else if (num == Number::twofiftysix) {
        return Number::fivetwelve;
    } else if (num == Number::fivetwelve) {
        return Number::onethousandtwentyfour;
    } else if (num == Number::onethousandtwentyfour) {
        return Number::twothousandfourtyeight;
    } else {
        return Number::none;
    }
}