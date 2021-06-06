#include "MyForm.h"
#include <iostream>
#include <Windows.h>


using namespace System;
using namespace System::Windows::Forms;

[STAThread]//leave this as is


void exeGame(int game) {

	if (game) {
		switch (game)
		{
		case 1:
			ShellExecuteA(NULL, "open", "Snake_Game.exe", NULL, "..\\Release\\ReleaseSnake", 10);
			break;
		case 2:
			ShellExecuteA(NULL, "open", "Tetris_Game.exe", NULL, "..\\Release\\ReleaseTetris", 10);
			break;
		case 3:
			ShellExecuteA(NULL, "open", "FlappyDuck_Game.exe", NULL, "..\\Release\\ReleaseFlappyDuck", 10);
			break;
		case 4:
			ShellExecuteA(NULL, "open", "Arkanoid_Game.exe", NULL, "..\\Release\\ReleaseArkanoid", 10);
			break;
		case 5:
			ShellExecuteA(NULL, "open", "Asteroids_Game.exe", NULL, "..\\Release\\ReleaseAsteroides", 10);
			break;
		case 6:
			ShellExecuteA(NULL, "open", "PongLike_Game.exe", NULL, "..\\Release\\ReleasePong", 10);
			break;
		default:
			break;
		}
	}
}



void Main(array<String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	StartGUI::MyForm form;
	Application::Run(% form);

}