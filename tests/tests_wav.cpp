/*
** EPITECH PROJECT, 2026
** The-Plazza
** File description:
** tests_parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>

#include "Exception.hpp"
#include "Wav.hpp"



static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(Parsing, empty, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("testSounds/errors/empty.wav"));
}

Test(Parsing, riff_no_chunk_id, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("testSounds/errors/riff_no_chunk_id.wav"));
}

Test(Parsing, riff_no_chunk_id, .init = redirect_all_std)
{
    cr_assert_any_throw(StoneAnalysis::Wav("testSounds/errors/riff_no_chunk_id.wav"));
}
