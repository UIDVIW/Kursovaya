#pragma once
#include <ctime>

class Timer
{
private:
	int game_end_t; // ����� ��������� ���� ������������ ������� ���������
	//int current_t; // ������� ����� �� ������� ���������
	int setup_t; // ��������� ������������� ����� 
public:
	void init();
	void setup(int t) { setup_t = t; };
	int remains();
};

void Timer::init()
{
	int game_start=clock(); // ����� ������ ����� ����
	game_end_t = setup_t + game_start/ CLOCKS_PER_SEC;
}

int Timer::remains()
{
	int current_t = clock(); // ������� ����� �� ������� ���������
	return game_end_t - current_t / CLOCKS_PER_SEC;
}