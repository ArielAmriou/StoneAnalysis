/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** StateButton
*/

#ifndef STATEBUTTON_HPP
    #define STATEBUTTON_HPP

    #include <vector>
    #include "AButton.hpp"
    #include "SfmlUtils.hpp"

namespace SfmlUtils {
    template <typename T>
    class StateButton : public AButton {
        public:
            StateButton(sf::Vector2f pos, sf::Vector2f size,
                std::vector<std::pair<T, std::reference_wrapper<sf::Texture>>> textures)
                : AButton(ButtonType::State), _pos(pos), _size(size),
                _textures(textures)
            {
                _sprite.setTexture(_textures[_id].second.get());
                sf::Vector2u tmp = _textures[_id].second.get().getSize();
                _sprite.setScale(_size.x / float(tmp.x), _size.y / float(tmp.y));
                _sprite.setPosition(_pos);
                setBound(_sprite.getGlobalBounds());
            }

            void draw(sf::RenderWindow &win) override
            {
                if (_hover)
                    _sprite.setColor(SfmlUtils::colorOffset(sf::Color::White, -50));
                else
                    _sprite.setColor(sf::Color::White);
                win.draw(_sprite);
            }

            void func() override
            {
                _id++;
                if (_id >= _textures.size())
                    _id = 0;
                _sprite.setTexture(_textures[_id].second.get());
                sf::Vector2u size = _textures[_id].second.get().getSize();
                _sprite.setScale(_size.x / float(size.x), _size.y / float(size.y));
            }

            void setState(T t)
            {
                for (std::size_t i = 0; i < _textures.size(); i++) {
                    if (t == _textures[i].first) {
                        _id = i;
                        _sprite.setTexture(_textures[_id].second.get());
                        sf::Vector2u size = _textures[_id].second.get().getSize();
                        _sprite.setScale(_size.x / float(size.x), _size.y / float(size.y));
                        break;
                    }
                }
            }

            void reset()
            {
                _id = 0;
                _sprite.setTexture(_textures[_id].second.get());
                sf::Vector2u size = _textures[_id].second.get().getSize();
                _sprite.setScale(_size.x / float(size.x), _size.y / float(size.y));
            }

            T getState() {return _textures[_id].first;}

        private:
            sf::Vector2f _pos;
            sf::Vector2f _size;
            std::size_t _id = 0;
            std::vector<std::pair<T, std::reference_wrapper<sf::Texture>>> _textures;
            sf::Sprite _sprite;
    };
}

#endif
