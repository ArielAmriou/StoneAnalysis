/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** ComplexSpectrum
*/

#ifndef COMPLEXSPECTRUM_HPP
    #define COMPLEXSPECTRUM_HPP

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <complex>
    #include "UtilsSfml.hpp"

namespace StoneAnalysis {
    class ComplexSpectrum {
        public:
            ComplexSpectrum(sf::Font &font);

            void analize(const std::vector<std::complex<double>> &complex);
            void draw(sf::RenderWindow &win);

        private:
            void drawBox(sf::RenderWindow &win);
            void drawFreqAxe(sf::RenderWindow &win, float panelBottom);
            void drawAmpAxe(sf::RenderWindow &win, float panelTop, float panelBottom,
                float panelCenter, double maxVal);
            double hzToX(double hz) const;
            void buildPanel(const std::vector<double> &values, double maxVal,
                float panelCenter, float panelHalf, sf::VertexArray &outLine) const;

            sf::Text _text;
            sf::RectangleShape _rec;
            sf::VertexArray _realLine;
            sf::VertexArray _imagLine;
            double _maxReal;
            double _maxImag;
            static const std::vector<float> _freqMarkers;
            static const std::vector<double> _ampSteps;

            constexpr static int LABEL_SIZE = 15;
            constexpr static double MIN_HZ = 20.0;
            constexpr static double MAX_HZ = 24000.0;
            constexpr static float BOX_LEGENDE = 70.0;
            constexpr static float BOX_LEFT = WINDOW_SIZE_X / 2.0 + BOX_SIDE_SIZE + BOX_LEGENDE;
            constexpr static float BOX_RIGHT = WINDOW_SIZE_X - BOX_SIDE_SIZE;
            constexpr static float BOX_HALF_H = 180;
            constexpr static float BOX_CENTER_Y = WINDOW_SIZE_Y - BOX_HALF_H - BOX_SIDE_SIZE - BOX_TITLE_SIZE;
            constexpr static float BOX_TOP = BOX_CENTER_Y - BOX_HALF_H;
            constexpr static float BOX_BOTTOM = BOX_CENTER_Y + BOX_HALF_H;
            constexpr static float BOX_WIDTH = BOX_RIGHT - BOX_LEFT;
            constexpr static float GAP = 20;
            constexpr static float PANEL_H = (BOX_HALF_H * 2.0 - GAP) / 2.0;
            constexpr static float REAL_TOP = BOX_TOP;
            constexpr static float REAL_BOTTOM = BOX_TOP + PANEL_H;
            constexpr static float REAL_CENTER = (REAL_TOP + REAL_BOTTOM) / 2.0;
            constexpr static float IMAG_TOP = REAL_BOTTOM + GAP;
            constexpr static float IMAG_BOTTOM = BOX_BOTTOM;
            constexpr static float IMAG_CENTER = (IMAG_TOP + IMAG_BOTTOM) / 2.0;
    };
}

#endif