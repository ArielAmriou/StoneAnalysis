/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** FrequencySpectrum
*/

#include <cmath>
#include <sstream>
#include <iomanip>
#include "FrequencySpectrum.hpp"

namespace StoneAnalysis {
    FrequencySpectrum::FrequencySpectrum(sf::Font &font) : _maxMag(1.0)
    {
        _text.setFont(font);
    }

    void FrequencySpectrum::analize(const std::vector<std::complex<double>> &complex)
    {
        auto usable = complex.size() / 2;
        double sampleRate = SAMPLE_RATE;
        double N = complex.size();

        std::vector<double> mags(usable);
        _maxMag = 1.0;
        for (std::size_t i = 1; i < usable; ++i) {
            mags[i] = std::sqrt(std::pow(complex[i].real(), 2) + std::pow(complex[i].imag(), 2));
            if (mags[i] > _maxMag)
                _maxMag = mags[i];
        }
        int cols = static_cast<int>(BOX_WIDTH);
        std::vector<double> colMag(cols, 0.0);
        for (std::size_t i = 1; i < usable; ++i) {
            double hz = static_cast<double>(i) * sampleRate / N;
            if (hz < MIN_HZ || hz > MAX_HZ)
                continue;
            double x = hzToX(hz);
            int col = static_cast<int>(std::round(x - BOX_LEFT));
            if (col >= 0 && col < cols)
                colMag[col] = std::max(colMag[col], mags[i]);
        }
        _spectrum = sf::VertexArray(sf::Lines);
        for (int col = 0; col < cols; ++col) {
            float x = BOX_LEFT + col;
            float normalizedMag = static_cast<float>(colMag[col] / _maxMag);
            float barH = normalizedMag * BOX_HALF_H * 2.0;
            sf::Color color = sf::Color(70, 130, 255);
            _spectrum.append({{x, BOX_BOTTOM}, color});
            _spectrum.append({{x, BOX_BOTTOM - barH}, color});
        }
    }

    void FrequencySpectrum::draw(sf::RenderWindow &win)
    {
        drawBox(win);
        drawMagAxe(win);
        drawFreqAxe(win);
        win.draw(_spectrum);
    }

    void FrequencySpectrum::drawBox(sf::RenderWindow &win)
    {
        _rec.setSize({WINDOW_SIZE_X / 2.0, BOX_HALF_H * 2 + BOX_TITLE_SIZE * 2});
        _rec.setFillColor(LIGHTGREY);
        _rec.setPosition(0, BOX_TOP - BOX_TITLE_SIZE);
        win.draw(_rec);
        _rec.setSize({BOX_WIDTH, BOX_HALF_H * 2.0});
        _rec.setFillColor(sf::Color::White);
        _rec.setPosition(BOX_LEFT, BOX_TOP);
        win.draw(_rec);
        _text.setCharacterSize(TITLE_SIZE);
        _text.setString("Frequency Spectrum");
        _text.setStyle(sf::Text::Bold);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setFillColor(sf::Color::Black);
        _text.setPosition(BOX_LEFT + BOX_WIDTH / 2.0, BOX_TOP - BOX_TITLE_SIZE / 2.0);
        win.draw(_text);
        _text.setStyle(sf::Text::Regular);
        _text.setOrigin(0, 0);
    }

    void FrequencySpectrum::drawMagAxe(sf::RenderWindow &win)
    {
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));

        for (double mag : _magSteps) {
            float y = BOX_BOTTOM - static_cast<float>(mag) * BOX_HALF_H * 2.0;
            if (mag > 0.0) {
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
            ss << std::fixed << std::setprecision(2) << mag;
            _text.setString(ss.str());
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width, rc.top + rc.height / 2.0);
            _text.setPosition(BOX_LEFT - TICK_SIZE - 4.0, y);
            win.draw(_text);
        }
        _text.setOrigin(0, 0);
    }

    void FrequencySpectrum::drawFreqAxe(sf::RenderWindow &win)
    {
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        for (float hz : _freqMarkers) {
            double x = hzToX(hz);
            if (x < BOX_LEFT || x > BOX_RIGHT)
                continue;
            _rec.setSize({1, TICK_SIZE});
            _rec.setFillColor(sf::Color(80, 80, 80));
            _rec.setPosition(x, BOX_BOTTOM);
            win.draw(_rec);
            _rec.setSize({1.0, BOX_HALF_H * 2.0});
            _rec.setFillColor(sf::Color(220, 220, 220));
            _rec.setPosition(x, BOX_TOP);
            win.draw(_rec);
            std::string label = std::to_string(static_cast<int>(hz));
            _text.setString(label);
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width / 2.0, rc.top);
            _text.setPosition(x, BOX_BOTTOM + TICK_SIZE + 2.0);
            win.draw(_text);
        }
        _text.setOrigin(0, 0);
    }

    double FrequencySpectrum::hzToX(double hz) const
    {
        double logMin = std::log2(MIN_HZ);
        double logMax = std::log2(MAX_HZ);
        double logHz = std::log2(std::max(hz, MIN_HZ));
        return BOX_LEFT + (logHz - logMin) / (logMax - logMin) * BOX_WIDTH;
    }

    const std::vector<float> FrequencySpectrum::_freqMarkers = {
        20.0, 50.0, 100.0, 200.0, 500.0, 1000.0, 2000.0, 5000.0, 10000.0, 20000.0
    };

    const std::vector<double> FrequencySpectrum::_magSteps = {
        0.0, 0.25, 0.5, 0.75, 1.0
    };
}