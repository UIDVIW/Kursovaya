#pragma once
#include <ctime>

class Timer
{
private:
	int game_end_t; // время окончания игры относительно запуска программы
	//int current_t; // текущее время от запуска программы
	int setup_t; // выбранное пользователем время 
public:
	void init();
	void setup(int t) { setup_t = t; };
	int remains();
};

void Timer::init()
{
	int game_start=clock(); // когда нажали новую игру
	game_end_t = setup_t + game_start/ CLOCKS_PER_SEC;
}

int Timer::remains()
{
	int current_t = clock(); // текущее время от запуска программы
	return game_end_t - current_t / CLOCKS_PER_SEC;
}