/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** WaveForm
*/

#include <iomanip>
#include <sstream>
#include "WaveForm.hpp"

namespace StoneAnalysis{
    WaveForm::WaveForm(sf::Font &font)
    {
        _text.setFont(font);
    }

    void WaveForm::analize(const Wav &wav)
    {
        auto &samples = wav._waves._data;
        _duration = samples.size() / SAMPLE_RATE;
        _waveform = sf::VertexArray(sf::LinesStrip, samples.size());

        for (std::size_t i = 0; i < samples.size(); ++i) {
            float x = BOX_LEFT + (double)i / samples.size() * BOX_WIDTH;
            float y = BOX_CENTER_Y - (samples[i] / 32768.0f) * BOX_HALF_H;
            _waveform[i] = sf::Vertex({x, y}, sf::Color(70, 130, 255));
        }
    }

    void WaveForm::draw(sf::RenderWindow &win)
    {
        drawBox(win);
        drawAmpAxe(win);
        drawTickAxe(win);
        win.draw(_waveform);
    }

    void WaveForm::drawBox(sf::RenderWindow &win)
    {
        _rec.setSize({WINDOW_SIZE_X, BOX_HALF_H * 2 + BOX_TITLE_SIZE * 2});
        _rec.setFillColor(LIGHTGREY);
        _rec.setPosition(0, BOX_TOP - BOX_TITLE_SIZE);
        win.draw(_rec);
        _rec.setSize({BOX_WIDTH, BOX_HALF_H * 2});
        _rec.setFillColor(sf::Color::White);
        _rec.setPosition(BOX_LEFT, BOX_TOP);
        win.draw(_rec);
        _text.setCharacterSize(TITLE_SIZE);
        _text.setString("Waveform");
        _text.setStyle(sf::Text::Bold);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2, rc.top + rc.height / 2);
        _text.setFillColor(sf::Color::Black);
        _text.setPosition(WINDOW_SIZE_X / 2, BOX_TOP - BOX_TITLE_SIZE / 2);
        win.draw(_text);
        _text.setStyle(sf::Text::Regular);
        _rec.setSize({BOX_WIDTH, 1.5f});
        _rec.setFillColor(sf::Color(200, 200, 200));
        _rec.setPosition(BOX_LEFT, BOX_CENTER_Y);
        win.draw(_rec);
    }

    void WaveForm::drawAmpAxe(sf::RenderWindow &win)
    {
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        for (double amp : _ampSteps) {
            double y = BOX_CENTER_Y - amp * BOX_HALF_H;
            if (amp != 0.0) {
                _rec.setSize({BOX_WIDTH, 1.0});
                _rec.setFillColor(sf::Color(220, 220, 220));
                _rec.setPosition(BOX_LEFT, y);
                win.draw(_rec);
            }
            _rec.setSize({TICK_SIZE, 1.5});
            _rec.setFillColor(sf::Color(80, 80, 80));
            _rec.setPosition(BOX_LEFT - TICK_SIZE, y);
            win.draw(_rec);
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(1) << amp;
            _text.setString(ss.str());
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width, rc.top + rc.height / 2);
            _text.setPosition(BOX_LEFT - TICK_SIZE - 4.0, y);
            win.draw(_text);
        }
    }

    void WaveForm::drawTickAxe(sf::RenderWindow &win)
    {
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        for (int t = 0; t <= TIME_STEPS; ++t) {
            double ratio = (double)t / TIME_STEPS;
            double x = BOX_LEFT + ratio * BOX_WIDTH;
            double secs = ratio * _duration;
            _rec.setSize({1.5, TICK_SIZE});
            _rec.setFillColor(sf::Color(80, 80, 80));
            _rec.setPosition(x, BOX_BOTTOM);
            win.draw(_rec);
            if (t > 0 && t < TIME_STEPS) {
                _rec.setSize({1.0f, BOX_HALF_H * 2});
                _rec.setFillColor(sf::Color(220, 220, 220));
                _rec.setPosition(x, BOX_TOP);
                win.draw(_rec);
            }
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << secs;
            _text.setString(ss.str());
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width / 2, rc.top);
            _text.setPosition(x, BOX_BOTTOM + TICK_SIZE * 2);
            win.draw(_text);
        }
    }

    const std::vector<double> WaveForm::_ampSteps = {1.0, 0.5, 0.0, -0.5, -1.0};
};
