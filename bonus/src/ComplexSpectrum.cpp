/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** ComplexSpectrum
*/

#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "ComplexSpectrum.hpp"

namespace StoneAnalysis {
    ComplexSpectrum::ComplexSpectrum(sf::Font &font)
        : _maxReal(1.0), _maxImag(1.0)
    {
        _text.setFont(font);
    }

    void ComplexSpectrum::buildPanel(const std::vector<double> &values, double maxVal,
        float panelCenter, float panelHalf, sf::VertexArray &outLine) const
    {
        int cols = static_cast<int>(BOX_WIDTH);
        std::vector<double> colVal(cols, 0.0);
        std::vector<bool> colSet(cols, false);
        double N = values.size() * 2.0;
        for (std::size_t i = 0; i < values.size(); ++i) {
            double hz = static_cast<double>(i) * SAMPLE_RATE / N;
            if (hz < MIN_HZ || hz > MAX_HZ)
                continue;
            int col = static_cast<int>(std::round(hzToX(hz) - BOX_LEFT));
            if (col < 0 || col >= cols)
                continue;
            if (!colSet[col]) {
                colVal[col] = values[i];
                colSet[col] = true;
            } else {
                colVal[col] = (colVal[col] + values[i]) * 0.5;
            }
        }
        for (int col = 1; col < cols - 1; ++col) {
            if (!colSet[col]) {
                colVal[col] = (colVal[col - 1] + colVal[col + 1]) * 0.5;
                colSet[col] = true;
            }
        }
        outLine = sf::VertexArray(sf::LinesStrip);
        for (int col = 0; col < cols; ++col) {
            float x = BOX_LEFT + static_cast<float>(col);
            double norm = static_cast<double>(colVal[col] / maxVal);
            norm = std::max(-1.0, std::min(1.0, norm));
            float y = panelCenter - norm * panelHalf;
            outLine.append(sf::Vertex({x, y}, LINE_COLOR));
        }
    }

    void ComplexSpectrum::analize(const std::vector<std::complex<double>> &complex)
    {
        std::size_t usable = complex.size() / 2;
        std::vector<double> reals(usable);
        std::vector<double> imags(usable);
        _maxReal = 1.0;
        _maxImag = 1.0;
        for (std::size_t i = 1; i < usable; ++i) {
            reals[i] = complex[i].real();
            imags[i] = complex[i].imag();
            _maxReal = std::max(_maxReal, std::abs(reals[i]));
            _maxImag = std::max(_maxImag, std::abs(imags[i]));
        }
        float panelHalf = PANEL_H / 2.0;
        buildPanel(reals, _maxReal, REAL_CENTER, panelHalf, _realLine);
        buildPanel(imags, _maxImag, IMAG_CENTER, panelHalf, _imagLine);
    }

    void ComplexSpectrum::draw(sf::RenderWindow &win)
    {
        drawBox(win);
        drawAmpAxe(win, REAL_TOP, REAL_BOTTOM, REAL_CENTER, _maxReal);
        drawFreqAxe(win, REAL_BOTTOM);
        win.draw(_realLine);
        drawAmpAxe(win, IMAG_TOP, IMAG_BOTTOM, IMAG_CENTER, _maxImag);
        drawFreqAxe(win, IMAG_BOTTOM);
        win.draw(_imagLine);
    }

    void ComplexSpectrum::drawBox(sf::RenderWindow &win)
    {
        _rec.setSize({BOX_WIDTH + BOX_SIDE_SIZE + BOX_LEGENDE, BOX_HALF_H * 2.0 + BOX_TITLE_SIZE * 2.0});
        _rec.setFillColor(LIGHTGREY);
        _rec.setPosition(BOX_LEFT - BOX_LEGENDE, BOX_TOP - BOX_TITLE_SIZE);
        win.draw(_rec);
        _rec.setSize({BOX_WIDTH, BOX_HALF_H * 2.0});
        _rec.setFillColor(sf::Color::White);
        _rec.setPosition(BOX_LEFT, BOX_TOP);
        win.draw(_rec);
        _rec.setSize({BOX_WIDTH, GAP});
        _rec.setFillColor(LIGHTGREY);
        _rec.setPosition(BOX_LEFT, REAL_BOTTOM);
        win.draw(_rec);
        _text.setCharacterSize(TITLE_SIZE);
        _text.setString("Complex Spectrum");
        _text.setStyle(sf::Text::Bold);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setFillColor(sf::Color::Black);
        _text.setPosition(BOX_LEFT + BOX_WIDTH / 2.0, BOX_TOP - BOX_TITLE_SIZE / 2.0);
        win.draw(_text);
        _text.setStyle(sf::Text::Regular);
        _text.setCharacterSize(LABEL_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        _text.setString("real part");
        rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setRotation(-90.0);
        _text.setPosition(BOX_LEFT - 42.0, REAL_CENTER);
        win.draw(_text);
        _text.setRotation(0);
        _text.setString("imaginary part");
        rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setRotation(-90.0);
        _text.setPosition(BOX_LEFT - 42.0, IMAG_CENTER);
        win.draw(_text);
        _text.setRotation(0);
    }

    void ComplexSpectrum::drawAmpAxe(sf::RenderWindow &win,
        float panelTop, float panelBottom, float panelCenter, double maxVal)
    {
        float panelHalf = (panelBottom - panelTop) / 2.0;
        _rec.setSize({BOX_WIDTH, 1.0});
        _rec.setFillColor(sf::Color(180, 180, 180));
        _rec.setPosition(BOX_LEFT, panelCenter);
        win.draw(_rec);
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        for (float n : _ampSteps) {
            float y = panelCenter - n * panelHalf;
            double actualVal = n * maxVal;
            std::ostringstream ss;
            if (std::abs(actualVal) >= 1000000.0)
                ss << std::fixed << std::setprecision(1) << actualVal / 1000000.0 << "m";
            else if (std::abs(actualVal) >= 1000.0)
                ss << std::fixed << std::setprecision(1) << actualVal / 1000.0 << "k";
            else
                ss << std::fixed << std::setprecision(1) << actualVal;
            _text.setString(ss.str());
            sf::FloatRect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width, rc.top + rc.height / 2.0);
            _text.setPosition(BOX_LEFT - 3.0, y);
            win.draw(_text);
        }
        _text.setOrigin(0, 0);
    }

    void ComplexSpectrum::drawFreqAxe(sf::RenderWindow &win, float panelBottom)
    {
        _text.setCharacterSize(CHAR_SIZE);
        _text.setFillColor(sf::Color(60, 60, 60));
        for (float hz : _freqMarkers) {
            float x = static_cast<float>(hzToX(static_cast<double>(hz)));
            if (x < BOX_LEFT || x > BOX_RIGHT)
                continue;
            _rec.setSize({1.0, PANEL_H});
            _rec.setFillColor(sf::Color(230, 230, 230));
            _rec.setPosition(x, panelBottom - PANEL_H);
            win.draw(_rec);
            if (panelBottom == IMAG_BOTTOM) {
                std::string label = std::to_string(static_cast<int>(hz));
                _text.setString(label);
                sf::FloatRect rc = _text.getLocalBounds();
                _text.setOrigin(rc.left + rc.width / 2.0, rc.top);
                _text.setPosition(x, panelBottom + LEGEND_GAP);
                win.draw(_text);
            }
        }
        _text.setOrigin(0, 0);
    }

    double ComplexSpectrum::hzToX(double hz) const
    {
        double logMin = std::log2(MIN_HZ);
        double logMax = std::log2(MAX_HZ);
        double logHz = std::log2(std::max(hz, MIN_HZ));
        return BOX_LEFT + (logHz - logMin) / (logMax - logMin) * BOX_WIDTH;
    }

    const std::vector<float> ComplexSpectrum::_freqMarkers = {
        50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000
    };

    const std::vector<double> ComplexSpectrum::_ampSteps = {1.0, 0.0, -1.0};
}