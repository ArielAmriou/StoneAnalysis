/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** tests_parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

#include "Exception.hpp"
#include "Wav.hpp"

#define test_throw(path, ex) try {StoneAnalysis::Wav(path);} catch (const ex &e) { cr_assert(true); return; } catch (const std::exception &e) { std::cerr << e.what() << std::endl; cr_assert(false); return; } std::cerr << "No throw"; cr_assert(false);

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Parsing, empty, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/empty.wav"));
}

Test(Parsing, no_ext, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/no_ext.wav"));
}

Test(Parsing, riff_no_chunk_id, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/riff_no_chunk_id.wav"));
}

Test(Parsing, riff_chunk_size_little, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/riff_chunk_size_little.wav"));
}

Test(Parsing, riff_wrong_format, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/riff_wrong_format.wav"));
}

Test(Parsing, fmt_no_chunk_id, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_no_chunk_id.wav"));
}

Test(Parsing, fmt_wrong_subchunk_size, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_wrong_subchunk_size.wav"));
}

Test(Parsing, fmt_not_pcm, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_not_pcm.wav"));
}

Test(Parsing, fmt_two_channels, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_two_channels.wav"));
}

Test(Parsing, fmt_wrong_sample_rate, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_wrong_sample_rate.wav"));
}

Test(Parsing, fmt_wrong_byte_rate, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_wrong_byte_rate.wav"));
}

Test(Parsing, fmt_wrong_byte_per_sample, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/fmt_wrong_byte_per_sample.wav"));
}

Test(Parsing, data_no_chunk_id, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/data_no_chunk_id.wav"));
}

Test(Parsing, complete_print, .init = redirect_all_std)
{
    StoneAnalysis::Wav w("tests/testSounds/untitled.wav");
    std::cout << w << std::flush;
    cr_assert_stdout_eq_str(
        "RIFF {\n"
        "    ID: \"RIFF\";\n"
        "    Size: 19236;\n"
        "    Format: \"WAVE\";\n"
        "}\n"
        "fmt {\n"
        "    ID: \"fmt \";\n"
        "    Size: 16;\n"
        "    Format: 1;\n"
        "    Number of channel: 1;\n"
        "    Sample rate: 48000;\n"
        "    Byte rate: 96000;\n"
        "    Block align: 2;\n"
        "    Bits per sample: 16;\n"
        "}\n"
        "data {\n"
        "    ID: \"data\";\n"
        "    Size: 19200;\n"
        "    Waves: 0, 1509, 3013, 4507, 5985, ..., -1511, -3011, -4508, -5986, -7446;\n"
        "}");
}

Test(Parsing, riff_to_much_data, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/riff_to_much_data.wav"));
}

Test(Parsing, riff_not_much_data, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/riff_not_much_data.wav"));
}

Test(Parsing, data_not_much_data, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/data_not_much_data.wav"));
}

Test(Parsing, data_too_much_data, .init = redirect_all_std)
{
	cr_assert_any_throw(StoneAnalysis::Wav("tests/testSounds/errors/data_too_much_data.wav"));
}
