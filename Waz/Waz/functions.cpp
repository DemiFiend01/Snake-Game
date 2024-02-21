#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <Xinput.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
/*
0 = Black       8 = Gray
1 = Blue        9 = Light Blue
2 = Green       10 = Light Green
3 = Aqua		11 = Light Aqua
4 = Red         12 = Light Red
5 = Purple      13 = Light Purple
6 = Yellow      14 = Light Yellow
7 = White       15 = Bright White
*/

//the no array approach

//const int width = 4;
//const int heigth = 5;
int x, y;//snake coords
int applex, appley;//apple coords
int taillength=0;
int score;
int tailx[400],taily[400]; //instead of messing around with the sizes //tail coords, have to be two seperate arrays for checking

void start(int width, int heigth)
{
	x = width / 2; y = heigth / 2;
	applex = rand() % width; appley = rand() % heigth;
	taillength = 0;
	score = 0;
}

void print(bool gameover,int width, int heigth)
{
	srand(time(NULL));
	system("cls");
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, 13 );
	std::cout << "||";
	for (int i = 0; i <= 2*width-1; i++) //top wall
		std::cout << "=";
	std::cout << "||";
	std::cout << std::endl;
	for (int yaxis = 0; yaxis <= heigth; yaxis++)
	{
		for (int xaxis = 0; xaxis <= width; xaxis++)
		{
			if (xaxis == 0)
			{
				SetConsoleTextAttribute(hconsole, 13);
				std::cout << "||"; //side walls
			}
			else if ((x > width-1 && xaxis == width-1) && y == yaxis)
			{
				SetConsoleTextAttribute(hconsole, 2); //change
				std::cout << "X ";
				SetConsoleTextAttribute(hconsole, 13);
				std::cout << "||";
				break;
			}
			else if (xaxis == width)
			{
				SetConsoleTextAttribute(hconsole, 13);
				std::cout << "||";
			}
			if ((x == -1 && xaxis == 0 && y == yaxis) || (y == -1 && yaxis == 0 && x == xaxis) || (y == heigth+1 && yaxis == heigth && x == xaxis))
			{
				SetConsoleTextAttribute(hconsole, 2);
				std::cout << "X ";
			}
			else if (xaxis == x && yaxis == y)
			{
				if (gameover)
				{
					SetConsoleTextAttribute(hconsole, 2);
					std::cout << "X "; //snake head dead
				}		
				else
				{
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "O "; //snake head
				}
					
			}
			else if (xaxis == applex && yaxis == appley) //else in case the snake has just eaten it? maybe we'll see
			{
				SetConsoleTextAttribute(hconsole, 6);
				std::cout << "a ";
			}
			else
			{
				bool tailended=false;
				for (int t = 0; t < taillength; t++)
				{
					if (tailx[t] == xaxis && taily[t] == yaxis)
					{
						SetConsoleTextAttribute(hconsole, 10);
						std::cout << "o "; //snake body
						tailended = true;
					}
					
				}
				if (tailended == false)
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "  ";
				}
					
			}
		}
		std::cout << std::endl; //after each row
	}
	SetConsoleTextAttribute(hconsole, 13);
	std::cout << "||";
	for (int i = 0; i <= 2*width-1; i++)
		std::cout << "="; //bottom wall
	std::cout << "||";
	SetConsoleTextAttribute(hconsole, 7);
	std::cout << std::endl <<"SCORE: "<< score << std::endl;
	

}

void Advance(char& direction, bool& gameover, int width, int heigth)
{
	int prevy = taily[0];
	int prevx = tailx[0];
	int prevy2, prevx2;
	taily[0]= y , tailx[0] = x;
	
	switch (direction)
	{
		case 'u':
		{
			y--;
			break;
		}
		case 'd':
		{
			y++;
			break;
		}
		case 'l':
		{
			x--;
			break;
		}
		case 'r':
		{
			x++;
			break;
		}
	}
	if (y == appley && x == applex) //sometimes the apple does still generate on the snake's tail somehow, do not know why
	{
		bool samecords;
		do{
			appley = rand() % heigth; applex = rand() % width;
			samecords = false;
			if (appley == y && applex == x)
			{
				samecords = true;
				continue;
			}
			for (int i = 0; i < taillength; i++)
			{
				if (tailx[i] == applex && taily[i] == appley)
				{
					samecords = true;
					break;
				}
			}
		} while (samecords); //random coord for the apple but with checking 
		taillength++;
		score += 100;
	}	
	for (int i = 1; i < taillength; i++)
		{
			prevy2 = taily[i]; prevx2 = tailx[i];
			taily[i] = prevy; tailx[i] = prevx;
			prevy = prevy2; prevx = prevx2;
		}
	if (y == -1 || y == heigth+1 || x == -1 || x == width) //has the snake hit a wall?
		gameover = true;
	for (int i = 0; i < taillength; i++)
		if (y == taily[i] && x == tailx[i])
			gameover = true;
	
	if (gameover)
	{
		return;
	}
	print(gameover, width, heigth);
	std::cout << "DIRECTION: ";
	switch (direction)
	{
		case 'u':
		{
			std::wcout << "^" << std::endl;
			break;
		}
		case 'd':
		{
			std::cout << "v" << std::endl;
			break;
		}
		case 'l':
		{
			std::cout << "<" << std::endl;
			break;
		}
		case 'r':
		{
			std::cout << ">" << std::endl;
			break;
		}
	}
}

void OPTIONS(double& speed, int& width, int& heigth)
{
	system("cls");
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD playerIndex = 0;
	XINPUT_STATE state;
	DWORD result = XInputGetState(playerIndex, &state);
	bool inputs = false;
	{
		SetConsoleTextAttribute(hconsole, 10);
		std::cout << "SNAKE" << std::endl<<std::endl; SetConsoleTextAttribute(hconsole, 7);
		std::cout << "OPTIONS:" << std::endl << "How to select:"<<std::endl<<"First input determines size, second input determines speed." << std::endl << "You need to press two inputs. Be careful - do";
		SetConsoleTextAttribute(hconsole, 13);
		std::cout << " not "; SetConsoleTextAttribute(hconsole, 7);
		std::cout<<"hold the button!" << std::endl << std::endl;
		std::cout << "Size of the map:" << std::endl << "SMALL ("; SetConsoleTextAttribute(hconsole, 11);
		std::cout << "Y"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")     - 8x8" << std::endl << "MEDIUM ("; SetConsoleTextAttribute(hconsole, 13);
		std::cout << "B"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")    - 12x12 ("; SetConsoleTextAttribute(hconsole, 10);
		std::cout << "default"; SetConsoleTextAttribute(hconsole, 7);
		std::cout<<")" << std::endl << "LARGE ("; SetConsoleTextAttribute(hconsole, 10);
		std::cout << "A"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")     - 18x18" << std::endl << "ENOURMOUS ("; SetConsoleTextAttribute(hconsole, 6);
		std::cout << "X"; SetConsoleTextAttribute(hconsole, 7);
		std::cout<<") - 24x24" << std::endl << std::endl; SetConsoleTextAttribute(hconsole, 7);
		std::cout << "Speed of the snake:" << std::endl << "SLOW ("; SetConsoleTextAttribute(hconsole, 11);
		std::cout << "Y"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")       - 1s" << std::endl << "NORMAL ("; SetConsoleTextAttribute(hconsole, 13);
		std::cout << "B"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")     - 0.5s ("; SetConsoleTextAttribute(hconsole, 10);
		std::cout << "default"; SetConsoleTextAttribute(hconsole, 7);
		std::cout<<")" << std::endl << "FAST ("; SetConsoleTextAttribute(hconsole, 10);
		std::cout << "A"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ")       - 0.35s" << std::endl << "USAIN BOLT ("; SetConsoleTextAttribute(hconsole, 6);
		std::cout << "X"; SetConsoleTextAttribute(hconsole, 7);
		std::cout << ") - 0.2s" << std::endl << std::endl << "Press firstly the desired size option then speed option: ";
	}

	bool size = false; bool sp = false;
		do
		{
			DWORD playerIndex = 0;
			XINPUT_STATE state;
			DWORD result = XInputGetState(playerIndex, &state);

			switch (state.Gamepad.wButtons)
			{
				case XINPUT_GAMEPAD_Y: //SMALL
				{
					SetConsoleTextAttribute(hconsole, 11);
					std::cout << "Y";
					width = 8; heigth = 8;
					size = true;
					break;
				}
				case XINPUT_GAMEPAD_B: //MEDIUM
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "B";
					width = 12; heigth = 12;
					size = true;
					break;
				}
				case XINPUT_GAMEPAD_A: //LARGE
				{
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "A";
					width = 18; heigth = 18;
					size = true;
					break;
				}
				case XINPUT_GAMEPAD_X: //ENOURMOUS
				{
					SetConsoleTextAttribute(hconsole, 6);
					std::cout << "X";
					width = 24; heigth = 24;
					size = true;
					break;
				}
			}
			if (_kbhit())
			{
				char c = _getch();
				switch (c)
				{
					case 'y': //SMALL
					{
						SetConsoleTextAttribute(hconsole, 11);
						std::cout << "Y";
						width = 8; heigth = 8;
						size = true;
						break;
					}
					case 'b': //MEDIUM
					{
						SetConsoleTextAttribute(hconsole, 13);
						std::cout << "B";
						width = 12; heigth = 12;
						size = true;
						break;
					}
					case 'a': //LARGE
					{
						SetConsoleTextAttribute(hconsole, 10);
						std::cout << "A";
						width = 18; heigth = 18;
						size = true;
						break;
					}
					case 'x': //ENOURMOUS
					{
						SetConsoleTextAttribute(hconsole, 6);
						std::cout << "X";
						width = 24; heigth = 24;
						size = true;
						break;
					}
				}
			}
		} while (!size);
		std::cout << " ";		
		Sleep(400);
		do
		{
			DWORD playerIndex = 0;
			XINPUT_STATE state;
			DWORD result = XInputGetState(playerIndex, &state);
			switch (state.Gamepad.wButtons)
			{
				case XINPUT_GAMEPAD_Y: //SLOW
				{
					SetConsoleTextAttribute(hconsole, 11);
					std::cout << "Y";
					speed = 2;
					sp = true;
					break;
				}
				case XINPUT_GAMEPAD_B: //NORMAL (default)
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "B";
					speed = 1;
					sp = true;
					break;
				}
				case XINPUT_GAMEPAD_A: //FAST
				{
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "A";
					speed = 0.7;
					sp = true;
					break;
				}
				case XINPUT_GAMEPAD_X: //USAIN BOLT
				{
					SetConsoleTextAttribute(hconsole, 6);
					std::cout << "X";
					speed = 0.4;
					sp = true;
					break;
				}
			}
			if (_kbhit())
			{
				char c = _getch();
				switch (c)
				{
				case 'y': //SLOW
				{
					SetConsoleTextAttribute(hconsole, 11);
					std::cout << "Y";
					speed = 2;
					sp = true;
					break;
				}
				case 'b': //NORMAL (default)
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "B";
					speed = 1;
					sp = true;
					break;
				}
				case 'a': //FAST
				{
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "A";
					speed = 0.7;
					sp  = true;
					break;
				}
				case 'x': //USAIN BOLT
				{
					SetConsoleTextAttribute(hconsole, 6);
					std::cout << "X";
					speed = 0.4;
					sp = true;
					break;
				}
				}
			}
		} while (!sp);
	
	Sleep(200);
}

void HELP(double& speed, int& width, int& heigth)
{	
	system("cls");
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD playerIndex = 0;
	XINPUT_STATE state;
	DWORD result = XInputGetState(playerIndex, &state);
	SetConsoleTextAttribute(hconsole, 10);
	{
		std::cout << "SNAKE" << std::endl <<"21.02.24 version"<<std::endl<<"made by DemiFiend01 (github)"<< std::endl<<std::endl;
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "HELP:" << std::endl << std::endl << "CONTROLS:" << std::endl << "Controller:" << std::endl << "Left joystick and D - PAD for movement." << std::endl;
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << std::endl << "Keyboard:" << std::endl << "W A S D and arrow keys for movement." << std::endl;
		std::cout << std::endl << "For Both:" << std::endl;
		SetConsoleTextAttribute(hconsole, 10);
		std::cout << "A ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "button for confirmation, ";
		SetConsoleTextAttribute(hconsole, 13);
		std::cout << "B ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "button for rejection and ";
		SetConsoleTextAttribute(hconsole, 6);
		std::cout << "X ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "for ending the program from the HELP page.";
		std::cout << std::endl << std::endl << "OPTIONS:" << std::endl;
		//std::cout << " ";

		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "Press ";
		SetConsoleTextAttribute(hconsole, 10);
		std::cout << "A ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "to go back, ";
		SetConsoleTextAttribute(hconsole, 13);
		std::cout << "B ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "to change the size and speed or ";
		SetConsoleTextAttribute(hconsole, 6);
		std::cout << "X ";
		SetConsoleTextAttribute(hconsole, 7);
		std::cout << "to end the program: ";
		Sleep(100);
	}
	bool input = false;
	do {
		DWORD playerIndex = 0;
		XINPUT_STATE state;
		DWORD result = XInputGetState(playerIndex, &state);
		switch (state.Gamepad.wButtons)
		{
			case XINPUT_GAMEPAD_A:
			{
				SetConsoleTextAttribute(hconsole, 10);
				std::cout << "A";
				input = true;
				break;
			}
			case XINPUT_GAMEPAD_X:
			{
				SetConsoleTextAttribute(hconsole, 6);
				std::cout << "X";
				SetConsoleTextAttribute(hconsole, 7);
				exit(0);
			}
			case XINPUT_GAMEPAD_B:
			{
				SetConsoleTextAttribute(hconsole, 13);
				std::cout << "B";
				Sleep(200);
				OPTIONS(speed, width, heigth);
				HELP(speed, width, heigth);
				return;
			}
		}
		if (_kbhit())
		{
			char c = _getch();
			switch (c)
			{
				case 'a':
				{
					SetConsoleTextAttribute(hconsole, 10);
					std::cout << "A";
					input = true;
					break;
				}
				case 'b':
				{
					SetConsoleTextAttribute(hconsole, 13);
					std::cout << "B";
					Sleep(200);
					OPTIONS(speed, width, heigth);
					HELP(speed, width, heigth);
					return;
				}
				case 'x':
				{
					SetConsoleTextAttribute(hconsole, 6);
					std::cout << "X";
					SetConsoleTextAttribute(hconsole, 7);
					exit(0);
				}
			}
		}
	} while (!input);

	Sleep(100);
	return;
}

void directioninput(char& dir)
{
	DWORD playerIndex = 0;
	XINPUT_STATE state;
	DWORD result = XInputGetState(playerIndex, &state);
	if (state.Gamepad.sThumbLX || state.Gamepad.sThumbLY)
	{
		if (state.Gamepad.sThumbLY < -1000)
		{
			if (state.Gamepad.sThumbLY < state.Gamepad.sThumbLX)
			{
				dir = 'd';
				Sleep(50);
			}
			else
			{
				if (state.Gamepad.sThumbLX < -1000)
				{
					dir = 'l';
					Sleep(50);
				}
				else if (state.Gamepad.sThumbLX > 1000)
				{
					dir = 'r';
					Sleep(50);
				}

			}
		}
		else if (state.Gamepad.sThumbLY > 1000)
		{
			if (state.Gamepad.sThumbLY > state.Gamepad.sThumbLX)
			{
				dir = 'u';
				Sleep(50);
			}
			else
			{
				if (state.Gamepad.sThumbLX < -1000)
				{
					dir = 'l';
					Sleep(50);
				}
				else if (state.Gamepad.sThumbLX > 1000)
				{
					dir = 'r';
					Sleep(50);
				}

			}
		}
		else
		{
			if (state.Gamepad.sThumbLX < -1000)
				dir = 'l';
			else if (state.Gamepad.sThumbLX > 1000)
				dir = 'r';
		}
	}
	switch (state.Gamepad.wButtons)
	{
		case XINPUT_GAMEPAD_DPAD_UP:
		{
			dir = 'u';
			break;
		}
		case XINPUT_GAMEPAD_DPAD_DOWN:
		{
			dir = 'd';
			break;
		}
		case XINPUT_GAMEPAD_DPAD_LEFT:
		{
			dir = 'l';
			break;
		}
		case XINPUT_GAMEPAD_DPAD_RIGHT:
		{
			dir = 'r';
			break;
		}
	}
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
			case KEY_UP:
			case 'w':
			{
				dir = 'u';
				break;
			}
			case KEY_DOWN:
			case 's':
			{
				dir = 'd';
				break;
			}
			case KEY_LEFT:
			case 'a':
			{
				dir = 'l';
				break;
			}
			case KEY_RIGHT:
			case 'd':
			{
				dir = 'r';
				break;
			}
		}
	}

}

void ScoreMess()
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hconsole, 7);
	if (score >=1000) //i really really hate this but i cannot do the switch version.
	{
		if (score >= 1500)
		{
			if (score >= 2000)
			{
				if (score >= 2500)
				{
					if (score >= 3000)
					{
						if (score >= 3500)
						{
							if (score >= 4000)
							{
								std::cout << "DAMN! What an insane score, you're clearly a "; SetConsoleTextAttribute(hconsole, 10);
								std::cout << "CHAMPION"; SetConsoleTextAttribute(hconsole, 7); std::cout << "!" << std::endl << "There's no one quite like you! "; 
								SetConsoleTextAttribute(hconsole, 6); std::cout << "Marvelous"; SetConsoleTextAttribute(hconsole, 7);
								std::cout<<" work!!!" << std::endl << "Now stretch a bit, you deserve it!!!" << std::endl; 
								SetConsoleTextAttribute(hconsole, 10);  std::cout<<"     B R A V O"<<std::endl; SetConsoleTextAttribute(hconsole, 7);
								return;
							}
							std::cout << "Four grand?!? You are really good at this!" <<std::endl << "Keep on playing to see the "; SetConsoleTextAttribute(hconsole, 10); std::cout << "last"; SetConsoleTextAttribute(hconsole, 7); std::cout << " message at the end!!!" << std::endl;
							return;
						}
						std::cout << "Three grand??? Absolutely "; SetConsoleTextAttribute(hconsole, 13); std::cout << "glorious"; SetConsoleTextAttribute(hconsole, 7); std::cout << "!"<<std::endl<<"I am sure you can score higher!!!" << std::endl;
						return;
					}
					std::cout << "Woah! "; SetConsoleTextAttribute(hconsole, 6); std::cout << "Rest"; SetConsoleTextAttribute(hconsole, 7); std::cout<<" your fingers for a while!!!"<<std::endl<<"You're killing it!!!" << std::endl;
					return;
				}
				std::cout << "Spectacular work! Two grand sounds quite "; SetConsoleTextAttribute(hconsole, 10); std::cout << "lovely"; SetConsoleTextAttribute(hconsole, 7); std::cout<<"!!!" << std::endl;
				return;
			}
			std::cout << "Keep on eating that "; SetConsoleTextAttribute(hconsole, 6);
			std::cout << "apple"; SetConsoleTextAttribute(hconsole, 7);
			std::cout<<", you're good at it!!!" << std::endl;
			return;
		}
		std::cout << "That is a nice score, keep improving!!!" << std::endl;
		return;
	}
}
