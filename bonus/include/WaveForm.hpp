/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** WaveForm
*/

#ifndef WAVEFORM
    #define WAVEFORM

    #include <SFML/Graphics.hpp>
    #include "../include/Wav.hpp"
    #include "UtilsSfml.hpp"

namespace StoneAnalysis {
    class WaveForm {
        public:
            WaveForm(sf::Font &font);

            void analize(const Wav &wav);
            void draw(sf::RenderWindow &win);

        private:
            void drawBox(sf::RenderWindow &win);
            void drawAmpAxe(sf::RenderWindow &win);
            void drawTickAxe(sf::RenderWindow &win);

            sf::VertexArray _waveform;
            sf::RectangleShape _rec;
            sf::Text _text;
            double _duration;
            static const std::vector<double> _ampSteps;

            constexpr static float TICK_SIZE = 6.0;
            constexpr static float TICK_SIZE_SM = 3.0;
            constexpr static int TIME_STEPS = 10;
            constexpr static float BOX_LEFT = 40.0;
            constexpr static float BOX_RIGHT = WINDOW_SIZE_X - 20.0;
            constexpr static float BOX_CENTER_Y = WINDOW_SIZE_Y / 3.0;
            constexpr static float BOX_HALF_H = 150.0;
            constexpr static float BOX_TOP = BOX_CENTER_Y - BOX_HALF_H;
            constexpr static float BOX_BOTTOM = BOX_CENTER_Y + BOX_HALF_H;
            constexpr static float BOX_WIDTH = BOX_RIGHT - BOX_LEFT;
    };
}

#endif
