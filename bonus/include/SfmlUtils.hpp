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

            static sf::Font loadFromFile(std::string file)
            {
                sf::Font font;
                font.loadFromFile(file);
                return font;
            }

            static sf::Texture loadTextureFromFile(std::string file)
            {
                sf::Texture texture;
                texture.loadFromFile(file);
                return texture;
            }
    };
}

#endif
