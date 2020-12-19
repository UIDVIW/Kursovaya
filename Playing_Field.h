#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>


using namespace sf;
using namespace std;

class Field
{
public:
	void Create_Mines();  //����������� ���
	void Calculate_Mines(); //������� ��� ������ ������ ������
	int Get_Field_View(int i, int j) { return gridView[i][j]; }
	int Get_Field_Logic(int i, int j) { return gridLogic[i][j]; }
	void Set_Field_View(int i, int j, int value) { gridView[i][j] = value; }
	void Set_num_mines(int n) { num_mines = n; }
	void Set_Field_Logic(int i, int j, int value) { gridLogic[i][j] = value; }
	void Copy_Logic_To_View(int i, int j); //����������� ����������� �������� ���� � �������
	void Resize(int n);
	const int Get_width() { return w; }
	int Get_N() { return N; }
	Field() { gridLogic = NULL; gridView = NULL; }
	~Field();

private:
	int N = 0;
	int const w = 32; // ������ ������ � ��������
	int** gridLogic; // ���������� ������ ��� ��, ��� ������
	int** gridView; // �� ��� �����
	int num_mines=0; // ���������� ���
};

