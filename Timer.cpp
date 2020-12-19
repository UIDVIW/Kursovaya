#include "Timer.h"

void Timer::init()
{
	int game_start = clock(); // ����� ������ ����� ����
	game_end_t = setup_t + game_start / CLOCKS_PER_SEC;
}

int Timer::remains()
{
	int current_t = clock(); // ������� ����� �� ������� ���������
	return game_end_t - current_t / CLOCKS_PER_SEC;
}