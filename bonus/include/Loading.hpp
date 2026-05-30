/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** Loading
*/

#ifndef LOADING_HPP
    #define LOADING_HPP

    #include <SFML/Graphics.hpp>
    #include <string_view>

namespace SfmlUtils {
    class Loading {
        public:
            Loading(sf::Vector2f pos, sf::Font &font,
                sf::Color color = sf::Color::White);

            void draw(sf::RenderWindow &win);

        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::Text _text;
            sf::Clock _clock;

            constexpr static std::string_view LOADING = "public/loading.png";
            constexpr static std::string_view LOADING_TEXT = "Loading";
            constexpr static float LOADING_SIZE = 360;
            constexpr static float LOADING_ROTATE = 360 / 20;
            constexpr static float LOADING_SCALE = 0.50;
            constexpr static unsigned int TEXT_SIZE = 25;
    };
}

#endif
