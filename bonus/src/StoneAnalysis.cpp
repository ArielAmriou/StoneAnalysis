/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** StoneAnalysis
*/

#include <sstream>
#include <iomanip>
#include "StoneAnalysis.hpp"

namespace StoneAnalysis {
    StoneAnalysis::StoneAnalysis() : _window(sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
        "StoneAnalysis", sf::Style::Close | sf::Style::Resize)),
        _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y)),
        _font(loadFromFile("public/Font.ttf")),
        _wav("../tests/testSounds/basic.wav"),
        _waveForm(_font),
        _fs(_font),
        _spectrum(_font),
        _loadingAnim({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, _font)
    {
        _window.setFramerateLimit(FPS);
        _window.setView(_view);
        _rec.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
        _rec.setFillColor(BACKGROUND_COLOR);
        _loading = true;
        _thread = std::thread([this]() {
            analyze();
            _loading = false;
        });
    }

    StoneAnalysis::~StoneAnalysis()
    {
        if (_thread.joinable())
            _thread.join();
    }

    sf::Font StoneAnalysis::loadFromFile(std::string file)
    {
        sf::Font font;
        font.loadFromFile(file);
        return font;
    }

    void StoneAnalysis::run()
    {
        while (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            if (!_loading) {
                _waveForm.draw(_window);
                _fs.draw(_window);
                _spectrum.draw(_window);
            } else {
                _loadingAnim.draw(_window);
            }
            _window.display();
        }
    }

    void StoneAnalysis::event()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            handleResize(event);
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::Escape))
                _window.close();
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::A
                && !_loading) {
                if (_thread.joinable())
                    _thread.join();
                _loading = true;
                _thread = std::thread([this]() {
                    analyze();
                    _loading = false;
                });
            }
        }
    }

    void StoneAnalysis::handleResize(sf::Event event)
    {
        if (event.type != sf::Event::Resized)
            return;
        const float gameW = static_cast<float>(WINDOW_SIZE_X);
        const float gameH = static_cast<float>(WINDOW_SIZE_Y);
        float windowRatio = static_cast<float>(_window.getSize().x) /
                            static_cast<float>(_window.getSize().y);
        float viewRatio = gameW / gameH;
        sf::Vector2f size = {1, 1};
        sf::Vector2f pos = {0, 0};

        if (windowRatio >= viewRatio) {
            size.x = viewRatio / windowRatio;
            pos.x = (1.0 - size.x) / 2.0;
        } else {
            size.y = windowRatio / viewRatio;
            pos.y = (1.0 - size.y) / 2.0;
        }
        _view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
        _window.setView(_view);
    }

    void StoneAnalysis::analyze()
    {
        if (!_wav)
            return;
        _waveForm.analize(*_wav);
        _complex = _wav->analize();
        _fs.analize(_complex);
        _spectrum.analize(_complex);
    }
}