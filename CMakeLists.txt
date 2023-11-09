cmake_minimum_required(VERSION 3.25)
project(AuTex)

set(CMAKE_CXX_STANDARD 23)

add_executable(AuTex main.cpp include/lexer/lexer_defs.h include/lexer/lexer_utils.h lexer/lexer_utils.cpp include/lexer/lexer.h lexer/lexer.cpp include/parser/Grammar.h parser/Grammar.cpp include/parser/Parser.h parser/Parser.cpp)
