cmake_minimum_required(VERSION 2.8)
project(jmemo2-parser)

set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(
    jmemo2-parser
    main.cpp
    Jmemo2Parser.cpp
    Jmemo2Parser.h
    Lexer.cpp
    Lexer.h
    Token.h
)
