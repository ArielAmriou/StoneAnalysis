/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** Loading
*/

#include "Loading.hpp"

namespace SfmlUtils {
    Loading::Loading(sf::Vector2f pos, sf::Font &font, sf::Color color)
    {
        _texture.loadFromFile(std::string(LOADING));
        _sprite.setTexture(_texture);
        _sprite.setOrigin(LOADING_SIZE / 2.0, LOADING_SIZE / 2.0);
        _sprite.setPosition(pos);
        _sprite.setScale(LOADING_SCALE, LOADING_SCALE);
        _sprite.setColor(color);
        _text.setFont(font);
        _text.setCharacterSize(TEXT_SIZE);
        _text.setString(std::string(LOADING_TEXT));
        sf::Rect rect = _text.getLocalBounds();
        _text.setOrigin(rect.left + rect.width / 2.0, rect.top + rect.height / 2.0);
        _text.setPosition(pos.x, pos.y);
        _text.setFillColor(color);
        _clock.restart();
    }

    void Loading::draw(sf::RenderWindow &win)
    {
        if (_clock.getElapsedTime().asMilliseconds() > 100) {
            _sprite.rotate(LOADING_ROTATE);
            _clock.restart();
        }
        win.draw(_sprite);
        win.draw(_text);
    }
}