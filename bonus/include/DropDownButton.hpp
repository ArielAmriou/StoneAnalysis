/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** DropDownButton
*/

#ifndef DROPDOWNBUTTON_HPP
    #define DROPDOWNBUTTON_HPP

    #include <optional>
    #include "AButton.hpp"
    #include "PresseButton.hpp"
    #include "SfmlUtils.hpp"

namespace SfmlUtils {
    template <typename T>
    class DropDownButton : public AButton {
        public:
            DropDownButton(sf::Font &font, unsigned int textSize, sf::Vector2f pos,
                sf::Vector2f size, const std::vector<std::string> &list)
                : AButton(ButtonType::DropDown), _pos(pos), _size(size),
                    _textSize(textSize)
            {
                std::size_t i = 1;
                for (const auto &info: list) {
                    _list.insert(std::make_pair(list,
                            PresseButton(font, textSize, {_pos.x, _pos.y + _size.y * i}, _size, )));
                    i++;
                }
                _text.setFont(font);
                _text.setCharacterSize(textSize);
                _text.setFillColor(sf::Color::Black);
                _rec.setSize(size);
                _rec.setFillColor(sf::Color::White);
                _rec.setOutlineColor(sf::Color::Black);
                _rec.setOutlineThickness(2);
                _rec.setPosition(_pos);
                setBound(_rec.getGlobalBounds());
            }

            void event(sf::Vector2f mousePos, sf::Event &event)
            {
                click(mousePos, event);
                if (_push) {
                    for (auto &info: _list) {
                        info.second.second.click(mousePos, event);
                        if (info.second.second.getPush()) {
                            info.second.second.reset();
                            _push = false;
                            _select = info.first;
                            break;
                        }
                    }
                }
            }

            void draw(sf::RenderWindow &win) override
            {
                if (_hover)
                    _rec.setFillColor(SfmlUtils::colorOffset(sf::Color::White, -50));
                else
                    _rec.setFillColor(sf::Color::White);
                win.draw(_rec);
                std::string str = "---";
                if (_select) {
                    auto find = _list.find(*_select);
                    if (find != _list.end())
                        str = find->second.first;
                }
                _text.setCharacterSize(_textSize);
                _text.setString(str);
                _text.setStyle(sf::Text::Regular);
                sf::FloatRect rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
                _text.setPosition(_pos.x + _size.x / 2.0, _pos.y + _size.y / 2.0);
                win.draw(_text);
                _text.setCharacterSize(_size.y / 2.0);
                _text.setStyle(sf::Text::Bold);
                _text.setString(">");
                rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
                _text.setPosition(_pos.x + _size.y / 4.0, _pos.y + _size.y / 2.0);
                if (_push) {
                    _text.setRotation(90);
                    for (auto info: _list)
                        info.second.second.draw(win);
                } else {
                    _text.setRotation(-90);
                }
                win.draw(_text);
                _text.setRotation(0);
            }

            void func() override
            {
                _push = !_push;
            }

            void reset()
            {
                _select = std::nullopt;
                for (auto &info: _list)
                    info.second.reset();
            }

            std::optional<T> getSelect() {return _select;}
            bool getPush() {return _push;}

        private:
            sf::Vector2f _pos;
            sf::Vector2f _size;
            sf::RectangleShape _rec;
            sf::Text _text;
            unsigned int _textSize;
            std::vector<std::pair<std::string, PresseButton>> _list;
            std::optional<std::string> _select;
            bool _push = false;
    };
}

#endif
