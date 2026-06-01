/*
** EPITECH PROJECT, 2026
** 
** File description:
** Exception
*/

#ifndef STONEANALYSISEXCEPTION_HPP
    #define STONEANALYSISEXCEPTION_HPP

#include <exception>
#include <string>

namespace StoneAnalysis {
    class StoneAnalysisException : public std::exception {
        public:
            StoneAnalysisException(std::string str) : _str("Stone Analysis Error: " + str) {};

            virtual const char *what() const noexcept override
                    { return _str.c_str(); };
        private:
            std::string _str;
    };

    class WrongArgsException : public StoneAnalysisException {
        public:
            WrongArgsException() : StoneAnalysisException("Wrongs Args.") {};
    };

    class NoSuchFileException : public StoneAnalysisException {
        public:
            NoSuchFileException(std::string str) : StoneAnalysisException("No Such file: " + str + ".") {};
    };

    class NotInitializeException : public StoneAnalysisException {
        public:
            NotInitializeException() : StoneAnalysisException("Not Initialize") {};
    };

    class MsgTooLongException : public StoneAnalysisException {
        public:
            MsgTooLongException() : StoneAnalysisException("Message too long") {};
    };

    class ParsingError : public StoneAnalysisException {
        public:
            ParsingError(std::string scope, std::string msg) :
                StoneAnalysisException("Parsing Error (" + scope + "): " + msg)
                {};
            ParsingError(std::string msg) :
                StoneAnalysisException("Parsing Error: " + msg)
                {};
    };

    class RiffParsingError : public ParsingError {
        public:
            RiffParsingError(std::string str) : ParsingError("RIFF chunk", str) {};
    };

    class FmtParsingError : public ParsingError {
        public:
            FmtParsingError(std::string str) : ParsingError("fmt subchunk", str) {};
    };

    class DataParsingError : public ParsingError {
        public:
            DataParsingError(std::string str) : ParsingError("Data subchunk", str) {};
    };

    class EmptyFile : public ParsingError{
        public:
            EmptyFile() : ParsingError("Emtpy file") {};
    };
};

#endif