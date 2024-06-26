#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <windows.h>

namespace hue {
    constexpr int DEFAULT_COLOR = 7;
    constexpr int BAD_COLOR = -256;

    const std::map<std::string, int> CODES = {
            {"black",        0},
            {"k",            0},
            {"blue",         1},
            {"b",            1},
            {"green",        2},
            {"g",            2},
            {"aqua",         3},
            {"a",            3},
            {"red",          4},
            {"r",            4},
            {"purple",       5},
            {"p",            5},
            {"yellow",       6},
            {"y",            6},
            {"white",        7},
            {"w",            7},
            {"grey",         8},
            {"e",            8},
            {"light blue",   9},
            {"lb",           9},
            {"light green",  10},
            {"lg",           10},
            {"light aqua",   11},
            {"la",           11},
            {"light red",    12},
            {"lr",           12},
            {"light purple", 13},
            {"lp",           13},
            {"light yellow", 14},
            {"ly",           14},
            {"bright white", 15},
            {"bw",           15}
    };

    inline bool is_good(int c) {
        return 0 <= c && c < 256;
    }

    // std::string to color
    int stoc(std::string a) {
        // convert s to lowercase, and format variants like  "light_blue"
        std::transform(a.begin(), a.end(), a.begin(), [](char c) {
            if ('A' <= c && c <= 'Z') {
                c -= 'A';
                c += 'a';
            } else if (c == '_' || c == '-')
                c = ' ';
            return c;
        });

        // operator[] on std::map is non-const, use std::map::at instead
        return (CODES.find(a) != CODES.end()) ? CODES.at(a) : BAD_COLOR;
    }

    int get() {
        CONSOLE_SCREEN_BUFFER_INFO i;
        return GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &i) ?
               i.wAttributes : BAD_COLOR;
    }

    int get_text() {
        return (get() != BAD_COLOR) ? get() % 16 : BAD_COLOR;
    }

    int get_background() {
        return (get() != BAD_COLOR) ? get() / 16 : BAD_COLOR;
    }

    void set(int c) {
        if (is_good(c))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    void set(int a, int b) {
        set(a + b * 16);
    }

    void set_text(std::string a) {
        set(stoc(std::move(a)), get_background());
    }

    void set_background(std::string b) {
        set(get_text(), stoc(std::move(b)));
    }

    void reset() {
        set(DEFAULT_COLOR);
    }
}
#endif
