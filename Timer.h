#pragma once
#include <ctime>

class Timer
{
private:
	int game_end_t; // время окончания игры относительно запуска программы
	int setup_t; // выбранное пользователем время 
public:
	void init();
	void setup(int t) { setup_t = t; };
	int remains();
};

