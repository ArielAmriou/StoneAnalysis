/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** SfmlUtils
*/

#ifndef SFMLUTILS_HPP
    #define SFMLUTILS_HPP

    #include <SFML/Graphics.hpp>

namespace SfmlUtils {
    class SfmlUtils {
        public:
            static sf::Color colorOffset(const sf::Color &color, int offset)
            {
                return sf::Color(std::clamp(color.r + offset, 0, 255),
                    std::clamp(color.g + offset, 0, 255),
                    std::clamp(color.b + offset, 0, 255)
                );
            }
    };
}

#endif
