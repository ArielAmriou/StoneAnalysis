/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** WaveForm
*/

#include <iomanip>
#include <sstream>
#include <iostream>
#include "WaveForm.hpp"
#include "SfmlUtils.hpp"

namespace StoneAnalysis{
    WaveForm::WaveForm(sf::Font &font) :
        _playTexture(SfmlUtils::SfmlUtils::loadTextureFromFile("public/play.png")),
        _pauseTexture(SfmlUtils::SfmlUtils::loadTextureFromFile("public/pause.png")),
        _stopTexture(SfmlUtils::SfmlUtils::loadTextureFromFile("public/stop.png")),
        _play({WINDOW_SIZE_X / 2.0 - 70, BOX_TOP - TOP + 10}, {60, 60}, {{Pause, _playTexture}, {Play, _pauseTexture}}),
        _stop({WINDOW_SIZE_X / 2.0 + 10, BOX_TOP - TOP + 10}, {60, 60}, {{Stop, _stopTexture}, {None, _stopTexture}})
    {
        _text.setFont(font);
        _rec.setSize({BOX_WIDTH, BOX_HALF_H * 2});
        _rec.setPosition(BOX_LEFT, BOX_TOP);
        _bound = _rec.getGlobalBounds();
    }

    void WaveForm::analize(const Wav &wav, std::string path)
    {
        auto &samples = wav._waves._data;
        _duration = samples.size() / SAMPLE_RATE;
        _waveform = sf::VertexArray(sf::LinesStrip, samples.size());

        for (std::size_t i = 0; i < samples.size(); ++i) {
            float x = BOX_LEFT + (double)i / samples.size() * BOX_WIDTH;
            float y = BOX_CENTER_Y - (samples[i] / 32768.0f) * BOX_HALF_H;
            _waveform[i] = sf::Vertex({x, y}, LINE_COLOR);
        }
        _music.openFromFile(path);
    }

    void WaveForm::event(sf::Event &event, sf::Vector2f mousePos)
    {
        _play.click(mousePos, event);
        _stop.click(mousePos, event);
        if (_stop.getState() == None) {
            _stop.reset();
            _music.stop();
            _play.reset();
            _start = false;
            return;
        }
        auto status = _music.getStatus();
        if (status != sf::Sound::Status::Playing && _play.getState() == Play)  {
            _music.play();
            _start = true;
        }
        else if (status == sf::Sound::Status::Playing && _play.getState() == Pause)
            _music.pause();
        if (_bound.contains(mousePos) && event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == sf::Mouse::Left) {
            float ratio = (mousePos.x - BOX_LEFT) / BOX_WIDTH;
            sf::Time offset = ratio * _music.getDuration();
            _music.setPlayingOffset(ratio * _music.getDuration());
            if (_music.getStatus() == sf::Sound::Status::Stopped) {
                _music.play();
                _music.setPlayingOffset(offset);
                _music.pause();
                _start = true;
            } else {
                _music.setPlayingOffset(offset);
            }
        }
    }


    void WaveForm::draw(sf::RenderWindow &win)
    {
        drawBox(win);
        drawAmpAxe(win);
        drawTickAxe(win);
        _play.draw(win);
        _stop.draw(win);
        win.draw(_waveform);
        drawCursor(win);
    }

    void WaveForm::drawBox(sf::RenderWindow &win)
    {
        _rec.setSize({WINDOW_SIZE_X, BOX_HALF_H * 2 + BOX_TITLE_SIZE * 2 + TOP});
        _rec.setFillColor(LIGHTGREY);
        _rec.setPosition(0, BOX_TOP - BOX_TITLE_SIZE - TOP);
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
        _text.setPosition(WINDOW_SIZE_X / 2, BOX_TOP - BOX_TITLE_SIZE / 2 - TOP);
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
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(1) << amp;
            _text.setString(ss.str());
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width, rc.top + rc.height / 2);
            _text.setPosition(BOX_LEFT - 4.0, y);
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
            _text.setPosition(x, BOX_BOTTOM + LEGEND_GAP);
            win.draw(_text);
        }
    }

    void WaveForm::drawCursor(sf::RenderWindow &win)
    {
        if (_music.getStatus() == sf::Sound::Status::Stopped
            && _play.getState() == Play && _start)
        {
            _play.reset();
            _start = false;
        }
        _rec.setSize({1.0, BOX_HALF_H * 2});
        _rec.setFillColor(sf::Color::Red);
        double ratio = _music.getPlayingOffset() / _music.getDuration();
        _rec.setPosition(BOX_LEFT + ratio * BOX_WIDTH, BOX_TOP);
        win.draw(_rec);
    }

    const std::vector<double> WaveForm::_ampSteps = {1.0, 0.5, 0.0, -0.5, -1.0};
};
