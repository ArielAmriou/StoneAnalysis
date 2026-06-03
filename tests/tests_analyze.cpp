/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** tests_analyze
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

Test(Analyse, Basic, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-a",
    "tests/testSounds/complex.wav", "1"
    });
    cr_assert_str_eq(testMain(args), "No Error");
    fflush(stdout);
    cr_assert_stdout_eq_str("Top 1 frequencies:\n"
                            "710.0 Hz\n");
}

Test(Analyse, Complex, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-a",
    "tests/testSounds/complex.wav", "3"
    });
    cr_assert_str_eq(testMain(args), "No Error");
    fflush(stdout);
    cr_assert_stdout_eq_str("Top 3 frequencies:\n"
                            "710.0 Hz\n"
                            "440.0 Hz\n"
                            "220.0 Hz\n");
}
