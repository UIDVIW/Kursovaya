#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>


using namespace sf;

class Field
{
public:
	void Create_Mines();  //–асстановка мин
	void Calculate_Mines(); //ѕодсчет мин вокруг каждой клетки
	int Get_Field_View(int i, int j);
	int Get_Field_Logic(int i, int j);
	void Set_Field_View(int i, int j, int value);
	void Set_Field_Logic(int i, int j, int value);
	void Copy_Logic_To_View(int i, int j); // опирование логического элемента пол€ в видимое
	void Set_Sprite_Texture();

private:
	int w = 32; // ширина клетки в пиксел€х
	int gridLogic[12][12]; // логический массив или то, что скрыто
	int gridView[12][12]; // то что видим
	//Texture t;
	//Sprite s;
};

void Field::Set_Sprite_Texture()
{
	//t.loadFromFile("images/tiles.jpg");
	//Sprite s(t);
}

void Field::Create_Mines()
{
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 5 == 0)  gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}
}

void Field::Calculate_Mines()
{
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
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

void Field::Set_Field_Logic(int i, int j, int value)
{
	gridLogic[i][j] = value;
}

void Field::Copy_Logic_To_View(int i, int j)
{
	if ((i > 0) && (i < 11) && (j > 0) && (j < 11))
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