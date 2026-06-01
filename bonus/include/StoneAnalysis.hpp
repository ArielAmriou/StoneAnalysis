/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** StoneAnalysis
*/

#ifndef STONEANALYSIS_HPP
    #define STONEANALYSIS_HPP

    #include <SFML/Graphics.hpp>
    #include <optional>
    #include <map>
    #include <vector>
    #include <complex>
    #include <thread>
    #include <atomic>
    #include "../include/Wav.hpp"
    #include "UtilsSfml.hpp"
    #include "WaveForm.hpp"
    #include "FrequencySpectrum.hpp"
    #include "ComplexSpectrum.hpp"
    #include "Loading.hpp"
    #include "PresseButton.hpp"

namespace StoneAnalysis {
    class StoneAnalysis
    {
        public:
            StoneAnalysis();
            ~StoneAnalysis();

            void run();
        private:
            sf::Font loadFromFile(std::string);
            void event();
            void handleResize(sf::Event event);
            void analyze();
            void openFileDialog();
            void load();
            void drawNoFile();

            sf::RenderWindow _window;
            sf::View _view;
            sf::Font _font;
            sf::Text _text;
            sf::RectangleShape _rec;
            sf::RectangleShape _toolBar;

            std::optional<Wav> _wav;
            std::map<double, std::size_t> _dists;
            std::vector<std::complex<double>> _complex;
            std::optional<std::string> _file;

            std::atomic<bool> _loading = false;
            std::thread _thread;

            WaveForm _waveForm;
            FrequencySpectrum _fs;
            ComplexSpectrum _spectrum;
            SfmlUtils::Loading _loadingAnim;

            SfmlUtils::PresseButton _loadButton;

            constexpr static float TOOLBAR_HEIGHT = 50;
    };
};

#endif