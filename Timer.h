#pragma once
#include <ctime>

class Timer
{
private:
	int game_end_t; // ����� ��������� ���� ������������ ������� ���������
	int setup_t; // ��������� ������������� ����� 
public:
	void init();
	void setup(int t) { setup_t = t; };
	int remains();
};

