/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** FrequencySpectrum
*/

#ifndef FREQUENCYSPECTRUM_HPP
    #define FREQUENCYSPECTRUM_HPP

    #include <SFML/Graphics.hpp>
    #include <complex>
    #include <vector>
    #include "UtilsSfml.hpp"

namespace StoneAnalysis {
    class FrequencySpectrum {
        public:
            FrequencySpectrum(sf::Font &font);

            void analize(const std::vector<std::complex<double>> &complex);
            void draw(sf::RenderWindow &win);

        private:
            void drawBox(sf::RenderWindow &win);
            void drawFreqAxe(sf::RenderWindow &win);
            void drawMagAxe(sf::RenderWindow &win);

            double hzToX(double hz) const;

            sf::RectangleShape _rec;
            sf::Text _text;
            sf::VertexArray _spectrum;
            double _maxMag;

            static const std::vector<float> _freqMarkers;
            static const std::vector<double> _magSteps;

            constexpr static double MIN_HZ = 20.0;
            constexpr static double MAX_HZ = 24000.0;
            constexpr static float BOX_LEFT = 50.0;
            constexpr static float BOX_RIGHT = WINDOW_SIZE_X / 2.0 - BOX_SIDE_SIZE * 2;
            constexpr static float BOX_HALF_H = 180;
            constexpr static float BOX_CENTER_Y = WINDOW_SIZE_Y - BOX_HALF_H - BOX_SIDE_SIZE - BOX_TITLE_SIZE;
            constexpr static float BOX_TOP = BOX_CENTER_Y - BOX_HALF_H;
            constexpr static float BOX_BOTTOM = BOX_CENTER_Y + BOX_HALF_H;
            constexpr static float BOX_WIDTH = BOX_RIGHT - BOX_LEFT;
    };
}

#endif