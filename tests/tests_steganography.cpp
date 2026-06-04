/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** tests_steganography
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>

#include "Exception.hpp"
#include "StoneAnalysis.hpp"

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static const char *testMain(std::queue<std::string> args)
{
    try {
        StoneAnalysis::StoneAnalysis tmp(args);
        tmp.run();
    } catch (StoneAnalysis::StoneAnalysisException &e) {
        std::string *tmp = new std::string(e.what());
        return tmp->c_str();
    }
    return "No Error";
}

Test(Steganography, CryptFail, .init = redirect_all_std)
{
    std::string msg;

    for (std::size_t i = 0; i < 12001; i++)
        msg += "a";
    std::queue<std::string> args(std::deque<std::string>{
    "-c",
    "tests/testSounds/basic.wav", "tests/testSounds/crypt.wav", msg
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Message too long");
}

Test(Steganography, CryptandDecrypt, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-c",
    "tests/testSounds/basic.wav", "tests/testSounds/crypt.wav", "Hello World! 123"
    });
    cr_assert_str_eq(testMain(args), "No Error");

    std::queue<std::string> args2(std::deque<std::string>{
    "-d",
    "tests/testSounds/crypt.wav"
    });
    cr_assert_str_eq(testMain(args2), "No Error");
    fflush(stdout);
    cr_assert_stdout_eq_str("HELLO WORLD! 123\n");
}
