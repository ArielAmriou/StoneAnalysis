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
#include "StoneAnalysis.hpp"

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static const char *testMain(std::queue<std::string> args)
{
    try {
        StoneAnalysis::StoneAnalysis tmp;
        tmp.run(args);
    } catch (StoneAnalysis::StoneAnalysisException &e) {
        std::string *tmp = new std::string(e.what());
        return tmp->c_str();
    }
    return "No Error";
}

Test(Parsing, noArgs, .init = redirect_all_std)
{
    cr_assert_str_eq(testMain({}), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, help, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "--help",
    });
    cr_assert_str_eq(testMain(args), "No Error");
}

Test(Parsing, WrongMode, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "--mode",
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, AnalizenoArgs, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "--analyze",
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, AnalizeNoSuchFile, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-a",
    "no.wav", "3"
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: No Such file: no.wav.");
}

Test(Parsing, AnalizeNan, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-a",
    "tests/testSounds/basic.wav", "NAN"
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, AnalizeSuccess, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-a",
    "tests/testSounds/basic.wav", "3"
    });
    cr_assert_str_eq(testMain(args), "No Error");
}

Test(Parsing, CyphernoArgs, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "--cypher",
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, CypherSuccess, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-c",
    "tests/testSounds/basic.wav", "tests/output.wav", "hello"
    });
    cr_assert_str_eq(testMain(args), "No Error");
}

Test(Parsing, DecyphernoArgs, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "--decypher",
    });
    cr_assert_str_eq(testMain(args), "Stone Analysis Error: Wrongs Args.");
}

Test(Parsing, DecypherSuccess, .init = redirect_all_std)
{
    std::queue<std::string> args(std::deque<std::string>{
    "-d",
    "tests/testSounds/basic.wav"
    });
    cr_assert_str_eq(testMain(args), "No Error");
}