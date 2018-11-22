cmake_minimum_required(VERSION 3.12)
project(SocialGame C)

set(CMAKE_C_STANDARD 99)

add_executable(SocialGame main.c players/naive.h decision.h players/tricker.h players/philosopher.h)