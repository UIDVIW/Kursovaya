#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>


using namespace sf;

class Field
{
public:
	void Create_Mines();  //Расстановка мин
	void Calculate_Mines(); //Подсчет мин вокруг каждой клетки
	int Get_Field_View(int i, int j);
	int Get_Field_Logic(int i, int j);
	void Set_Field_View(int i, int j, int value); 
	void Set_num_mines(int n);
	void Set_Field_Logic(int i, int j, int value) { gridLogic[i][j] = value; }
	void Copy_Logic_To_View(int i, int j); //Копирование логического элемента поля в видимое
	void Resize(int n);
	const int Get_width() { return w; }
	int Get_N() { return N; }
	Field();
	~Field();

private:
	int N = 0;
	int const w = 32; // ширина клетки в пикселях
	int** gridLogic; // логический массив или то, что скрыто
	int** gridView; // то что видим
	int num_mines=0; // количество мин
};

Field::Field()
{
	gridLogic = NULL; 
	gridView = NULL;
}

Field::~Field()
{
	for (int i = 0; i < N + 2; i++)
	{
		delete[] gridLogic[i];
		delete[] gridView[i];
	}

	delete[] gridLogic;
	delete[] gridView;
}


void Field::Create_Mines()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			gridView[i][j] = 10;
			gridLogic[i][j] = 0;
		}
	int x, y = 0;
	for (int i = 0; i < num_mines; i++)
	{
		x = rand() % N + 1;
		y = rand() % N + 1;
		if (gridLogic[x][y] == 9)
			i--;
		else gridLogic[x][y] = 9;
	}
}

void Field::Calculate_Mines()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}
}

int Field::Get_Field_View(int i, int j)
{
	return gridView[i][j];
}

int Field::Get_Field_Logic(int i, int j)
{
	return gridLogic[i][j];
}

void Field::Set_Field_View(int i, int j, int value)
{
	gridView[i][j] = value;
}

// открытие островка без мин 
void Field::Copy_Logic_To_View(int i, int j)
{
	if ((i > 0) && (i < N+1) && (j > 0) && (j < N+1))
	{
		gridView[i][j] = gridLogic[i][j];
		if (gridLogic[i][j] == 0) 
		{
			if (gridView[i - 1][j] > 0) Copy_Logic_To_View(i - 1, j);
			if (gridView[i - 1][j - 1] > 0) Copy_Logic_To_View(i - 1, j - 1);
			if (gridView[i - 1][j + 1] > 0) Copy_Logic_To_View(i - 1, j + 1);
			if (gridView[i + 1][j] > 0) Copy_Logic_To_View(i + 1, j);
			if (gridView[i + 1][j - 1] > 0) Copy_Logic_To_View(i + 1, j - 1);
			if (gridView[i + 1][j + 1] > 0) Copy_Logic_To_View(i + 1, j + 1);
			if (gridView[i][j - 1] > 0) Copy_Logic_To_View(i, j - 1);
			if (gridView[i][j + 1] > 0) Copy_Logic_To_View(i, j + 1);
		}
	}
}

void Field::Resize(int n)
{
	N = n;
	gridLogic = new int*[N+2];
	gridView = new int*[N + 2];

	for (int i = 0; i < N + 2; i++)
	{
		gridLogic[i] = new int[N+2];
		gridView[i] = new int[N + 2]; 
	}
}

void Field::Set_num_mines(int n) 
{
	//if (n >= N*N*0.6)
		//n = (int)(N*N*0.6);
	num_mines = n;
	
}