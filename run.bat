@echo off
g++ -I src/include -c *.cpp -c cells/*.cpp
g++ *.o -o main.exe -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
START main.exe
exit