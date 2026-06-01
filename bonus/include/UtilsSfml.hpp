/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** UtilsSfml
*/

#ifndef UTILSSFML_HPP
    #define UTILSSFML_HPP

    #include <SFML/Graphics.hpp>

namespace StoneAnalysis {
    constexpr std::size_t FPS = 120;
    constexpr unsigned int WINDOW_SIZE_X = 1920;
    constexpr unsigned int WINDOW_SIZE_Y = 1080;
    constexpr unsigned int WINDOW_BITS = 32;
    constexpr double SAMPLE_RATE = 48000.0;
    inline const sf::Color LIGHTGREY = sf::Color(150, 150, 150);
    inline const sf::Color DARKBLUE = sf::Color(51, 75, 99);
    inline const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 75);
    inline const sf::Color LINE_COLOR = sf::Color(70, 130, 255);
    constexpr int MSG_SIZE = 40;
    constexpr int TITLE_SIZE = 22;
    constexpr int CHAR_SIZE = 18;
    constexpr float BOX_TITLE_SIZE = 40.0;
    constexpr float BOX_SIDE_SIZE = 20.0;
    constexpr float LEGEND_GAP = 10.0;
};

#endif
