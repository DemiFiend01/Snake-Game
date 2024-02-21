#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void start(int width, int heigth);

void print(bool gameover, int width, int heigth);

void Advance(char& direction, bool& gameover, int width, int heigth);

void HELP(double& speed, int& width, int& heigth);

void OPTIONS(double& speed, int& width, int& heigth);

void directioninput(char& dir);

void ScoreMess();

#endif /* functions_h */