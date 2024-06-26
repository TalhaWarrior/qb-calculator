#ifndef PAINT_HPP
#define PAINT_HPP

#include "../APIs/COLOR_CODING_API.hpp" // for hut::set_text , hut::set_background , huw::reset

using hue::set_text;
using hue::set_background;
using hue::reset;

/*
 * Simplified text and background colors for QBCalculator
 * instead  of using manipulators in COLOR_CODING_API.hpp
 * */

class paintText {
public:
    static void red() {
        set_text("r");
    }

    static void green() {
        set_text("g");
    }

    static void yellow() {
        set_text("y");
    }

    static void aqua() {
        set_text("a");
    }

    static void gray() {
        set_text("e");
    }

    static void light_blue() {
        set_text("lb");
    }

    static void light_green() {
        set_text("lg");
    }

    static void light_purple() {
        set_text("lp");
    }

    static void light_yellow() {
        set_text("ly");
    }

    static void light_red() {
        set_text("lr");
    }

    static void default_color() {
        reset();
    }
};

#endif
