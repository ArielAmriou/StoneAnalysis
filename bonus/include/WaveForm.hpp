/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** WaveForm
*/

#ifndef WAVEFORM
    #define WAVEFORM

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <optional>
    #include "../include/Wav.hpp"
    #include "UtilsSfml.hpp"
    #include "StateButton.hpp"

namespace StoneAnalysis {
    class WaveForm {
        public:

            enum State {
                Play,
                Pause,
                Stop,
                None
            };

            WaveForm(sf::Font &font);

            void analize(const Wav &wav, std::string path);
            void draw(sf::RenderWindow &win);

            void event(sf::Event &event, sf::Vector2f mousePos);

        private:
            void drawBox(sf::RenderWindow &win);
            void drawAmpAxe(sf::RenderWindow &win);
            void drawTickAxe(sf::RenderWindow &win);
            void drawCursor(sf::RenderWindow &win);

            sf::VertexArray _waveform;
            sf::RectangleShape _rec;
            sf::Text _text;
            sf::Music _music;
            double _duration;
            static const std::vector<double> _ampSteps;

            bool _start = false;
            sf::Texture _playTexture;
            sf::Texture _pauseTexture;
            sf::Texture _stopTexture;
            SfmlUtils::StateButton<State> _play;
            SfmlUtils::StateButton<State> _stop;

            sf::FloatRect _bound;

            constexpr static float TICK_SIZE_SM = 3.0;
            constexpr static int TIME_STEPS = 10;
            constexpr static float BOX_LEFT = 40.0;
            constexpr static float BOX_RIGHT = WINDOW_SIZE_X - 20.0;
            constexpr static float BOX_CENTER_Y = 375;
            constexpr static float BOX_HALF_H = 170.0;
            constexpr static float BOX_TOP = BOX_CENTER_Y - BOX_HALF_H;
            constexpr static float BOX_BOTTOM = BOX_CENTER_Y + BOX_HALF_H;
            constexpr static float BOX_WIDTH = BOX_RIGHT - BOX_LEFT;
            constexpr static float TOP = 80;
    };
}

#endif
