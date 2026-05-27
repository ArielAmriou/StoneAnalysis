#ifndef STONEANALYSIS_HPP
    #define STONEANALYSIS_HPP

    #include <SFML/Graphics.hpp>
    #include <optional>
    #include <map>
    #include <vector>
    #include <complex>
    #include "../include/Wav.hpp"
    #include "UtilsSfml.hpp"
    #include "WaveForm.hpp"

namespace StoneAnalysis {
    class StoneAnalysis
    {
        public:
            StoneAnalysis();
            void run();
        private:
            sf::Font loadFromFile(std::string);
            void event();
            void handleResize(sf::Event event);
            void analyze();

            sf::RenderWindow _window;
            sf::View _view;
            sf::Font _font;
            sf::RectangleShape _rec;
            std::optional<Wav> _wav;
            std::map<double, std::size_t> _dists;
            std::vector<std::complex<double>> _complex;
            WaveForm _waveForm;
    };
};

#endif