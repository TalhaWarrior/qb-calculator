#ifndef QB_BANNERS_HPP
#define QB_BANNERS_HPP

#include "../APIs/ASCII_ART_API.hpp"
#include "paint.hpp"

using Termwriter::type;

class QB_Banners {
public:
    static void calculator_Banner() {
        paintText::light_red();
        type("QB Calculator");
        paintText::default_color();
    }

    static void editMenu_Banner() {
        paintText::yellow();
        type("Edit Query");
        paintText::default_color();
    }

    static void syntaxHelp_Banner() {
        paintText::aqua();
        type("General Help");
        paintText::default_color();
    }

    static void output_Banner() {
        paintText::light_green();
        type("Output");
        paintText::default_color();
    }

    static void queryPad_Banner() {
        paintText::light_blue();
        type("Query Pad");
        paintText::default_color();
    }

    static void exit_Banner() {
        paintText::red();
        type("Exit Calculator ?");
        paintText::default_color();
    }

    static void credits_Banner() {
        paintText::light_purple();
        type("Credits");
        paintText::default_color();
    }
};

#endif
