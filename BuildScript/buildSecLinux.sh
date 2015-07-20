#/usr/bin/bash

clang++ -o ../build_result/0xcc_sec_linux.bin ../0xCCSecurity/Linux/main.cpp ../0xCCSecurity/Linux/Window.cpp ../0xCCSecurity/Linux/WindowManager.cpp -lX11 -lGL -lGLU -I../0xCCSecurity/Linux/ -std=c++11
