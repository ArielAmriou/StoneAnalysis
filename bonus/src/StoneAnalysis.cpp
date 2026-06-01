/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** StoneAnalysis
*/

#include <gtk/gtk.h>
#include <sstream>
#include <filesystem>
#include <iomanip>
#include "StoneAnalysis.hpp"
#include "SfmlUtils.hpp"

namespace StoneAnalysis {
    StoneAnalysis::StoneAnalysis() : _window(sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
        "StoneAnalysis", sf::Style::Close | sf::Style::Resize)),
        _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y)),
        _font(SfmlUtils::SfmlUtils::loadFromFile("public/Font.ttf")),
        _waveForm(_font),
        _fs(_font),
        _spectrum(_font),
        _loadingAnim({WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2}, _font),
        _loadButton(_font, CHAR_SIZE, {5, 5}, {80, 40}, "Load", LIGHTGREY)
    {
        gtk_init(NULL, NULL);
        _window.setFramerateLimit(FPS);
        _window.setView(_view);
        _rec.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
        _rec.setFillColor(BACKGROUND_COLOR);
        _toolBar.setSize({WINDOW_SIZE_X, TOOLBAR_HEIGHT});
        _toolBar.setFillColor(LIGHTGREY);
        _text.setFont(_font);
        // _file = "../tests/testSounds/basic.wav";
        // load();
    }

    StoneAnalysis::~StoneAnalysis()
    {
        if (_loading)
            _thread.detach();
        else if (_thread.joinable())
            _thread.join();
    }

    void StoneAnalysis::run()
    {
        while (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            drawToolBar();
            if (!_loading) {
                if (_file) {
                    _waveForm.draw(_window);
                    _fs.draw(_window);
                    _spectrum.draw(_window);
                } else {
                    drawNoFile();
                }
            } else {
                _loadingAnim.draw(_window);
            }
            _window.display();
        }
    }

    void StoneAnalysis::event()
    {
        sf::Event event;
        sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        while (_window.pollEvent(event)) {
            _loadButton.click(mousePos, event);
            _waveForm.event(event, mousePos);
            handleResize(event);
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::Escape))
                _window.close();
            if ((event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::O)
                || _loadButton.getPush()) {
                auto before = _file;
                openFileDialog();
                if (!before || (before && _file && *before != *_file))
                    load();
                _loadButton.reset();
            }
        }
    }

    void StoneAnalysis::handleResize(sf::Event event)
    {
        if (event.type != sf::Event::Resized)
            return;
        const float gameW = static_cast<float>(WINDOW_SIZE_X);
        const float gameH = static_cast<float>(WINDOW_SIZE_Y);
        float windowRatio = static_cast<float>(_window.getSize().x) /
                            static_cast<float>(_window.getSize().y);
        float viewRatio = gameW / gameH;
        sf::Vector2f size = {1, 1};
        sf::Vector2f pos = {0, 0};

        if (windowRatio >= viewRatio) {
            size.x = viewRatio / windowRatio;
            pos.x = (1.0 - size.x) / 2.0;
        } else {
            size.y = windowRatio / viewRatio;
            pos.y = (1.0 - size.y) / 2.0;
        }
        _view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
        _window.setView(_view);
    }

    void StoneAnalysis::analyze()
    {
        if (!_wav)
            return;
        _waveForm.analize(*_wav, *_file);
        _complex = _wav->analize();
        _fs.analize(_complex);
        _spectrum.analize(_complex);
    }

    void StoneAnalysis::openFileDialog()
    {
        GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Select WAV file", NULL,
            GTK_FILE_CHOOSER_ACTION_OPEN,
            "_Cancel", GTK_RESPONSE_CANCEL,
            "_Open",   GTK_RESPONSE_ACCEPT,
            NULL
        );
        GtkFileFilter* filter = gtk_file_filter_new();
        gtk_file_filter_add_pattern(filter, "*.wav");
        gtk_file_filter_set_name(filter, "WAV files");
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
        std::string result;
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        if (response == GTK_RESPONSE_ACCEPT) {
            char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            result = filename;
            g_free(filename);
        }
        gtk_widget_hide(dialog);
        while (gtk_events_pending())
            gtk_main_iteration();
        gtk_widget_destroy(dialog);
        if (!result.empty())
            _file = result;
    }

    void StoneAnalysis::load()
    {
        if (!_loading && _file) {
            _wav = Wav(*_file);
            if (_thread.joinable())
                _thread.join();
            _loading = true;
            _thread = std::thread([this]() {
                analyze();
                _loading = false;
            });
        }
    }

    void StoneAnalysis::drawNoFile()
    {
        _text.setStyle(sf::Text::Bold);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(MSG_SIZE);
        _text.setString("No Sound File Load");
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setPosition(WINDOW_SIZE_X / 2.0, WINDOW_SIZE_Y / 2.0 - MSG_SIZE);
        _window.draw(_text);
        _text.setString("Press O or Load to load a file");
        rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
        _text.setPosition(WINDOW_SIZE_X / 2.0, WINDOW_SIZE_Y / 2.0 + MSG_SIZE);
        _window.draw(_text);
    }

    void StoneAnalysis::drawToolBar()
    {
        _window.draw(_toolBar);
        _loadButton.draw(_window);
        if (_file) {
            _text.setStyle(sf::Text::Bold);
            _text.setCharacterSize(TITLE_SIZE);
            _text.setFillColor(sf::Color::Black);
            std::filesystem::path file(*_file);
            _text.setString(std::string(file.filename()));
            sf::Rect rc = _text.getLocalBounds();
            _text.setOrigin(rc.left + rc.width / 2.0, rc.top + rc.height / 2.0);
            _text.setPosition(WINDOW_SIZE_X / 2.0, TOOLBAR_HEIGHT / 2.0);
            _window.draw(_text);
        }
    }
}