#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include "functions.h"
#include <conio.h>


void snake()
{
	system("cls");
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int taillength = 0; int heigth = 12; int width = 12; double speed = 1.00;
	char direction = 'u';
	bool gameover = false;
	bool beginning = false; bool options = false; bool input = false;
	SetConsoleTextAttribute(hconsole, 10);
	std::cout << "SNAKE" << std::endl << std::endl;
	SetConsoleTextAttribute(hconsole, 7);
	std::cout << "Press ";
	SetConsoleTextAttribute(hconsole, 13);
	std::cout << "B ";
	SetConsoleTextAttribute(hconsole, 7);
	std::cout << "for help and options, ";
	SetConsoleTextAttribute(hconsole, 10);
	std::cout << "A ";
	SetConsoleTextAttribute(hconsole, 7);
	std::cout << "to play : ";
	do {
		do {
			options = false;
			input = false;
			DWORD playerIndex = 0;
			XINPUT_STATE state;
			DWORD result = XInputGetState(playerIndex, &state);
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				SetConsoleTextAttribute(hconsole, 10);
				beginning = true;
				input = true;
			}
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				SetConsoleTextAttribute(hconsole, 13);
				std::cout << "B";
				input = true;
				options = true;
			}
			if (_kbhit())
			{
				char c = _getch();
				if (c == 'a')
				{
					SetConsoleTextAttribute(hconsole, 10);
					beginning = true;
					input = true;
				}
				else if (c == 'b')
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "B";
					input = true;
					options = true;
				}
			}
		} while (!input);
		if (options == true)
		{
			Sleep(200);
			HELP(speed, width, heigth);
			system("cls");
			//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			Sleep(200);
			SetConsoleTextAttribute(hconsole, 10);
			std::cout << "SNAKE" << std::endl << std::endl;
			SetConsoleTextAttribute(hconsole, 7);
			std::cout << "Press ";
			SetConsoleTextAttribute(hconsole, 13);
			std::cout << "B ";
			SetConsoleTextAttribute(hconsole, 7);
			std::cout << "for help and options, ";
			SetConsoleTextAttribute(hconsole, 10);
			std::cout << "A ";
			SetConsoleTextAttribute(hconsole, 7);
			std::cout << "to play : ";
		}

	} while (!beginning);
	SetConsoleTextAttribute(hconsole, 10);
	std::cout << "A";
	Sleep(200);
	start(width, heigth);
	print(gameover, width, heigth);
	while(!gameover)
	{
		auto start = std::chrono::steady_clock::now();
		
		while(true)
		{
			auto end = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			if (duration > (speed*500))
				break;
			directioninput(direction);
			Sleep(10);
		}
		Advance(direction, gameover, width, heigth);
	}
	print(gameover, width, heigth);
	ScoreMess();
	SetConsoleTextAttribute(hconsole, 13);
	std::cout << "GAMEOVER" << std::endl;

}

int main()
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool replays = false;
	do {

		bool input = false;
		snake();
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "Do you want to replay? Press ";
		SetConsoleTextAttribute(hconsole, 10);
		std::cout << "A ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "to replay, ";
		SetConsoleTextAttribute(hconsole, 13);
		std::cout << "B ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout<<"to end : ";
		do {
			DWORD playerIndex = 0;
			XINPUT_STATE state;
			DWORD result = XInputGetState(playerIndex, &state);
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				SetConsoleTextAttribute(hconsole, 10);
				printf("A ");
				input = true;
				replays = true;
				Sleep(400);
			}
			else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				SetConsoleTextAttribute(hconsole, 13);
				printf("B ");
				input = true;
				replays = false;
			}
			if (_kbhit())
			{
				char c = _getch();
				if (c == 'a') 
				{
					replays = true;
					input = true;
				}
				else if (c == 'b')
				{
					replays = false;
					input = true;
				}
					
			}
		} while (!input);
	} while (replays);
	return 0;
}