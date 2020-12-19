#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>


using namespace sf;
using namespace std;

class Field
{
public:
	void Create_Mines();  //–асстановка мин
	void Calculate_Mines(); //ѕодсчет мин вокруг каждой клетки
	int Get_Field_View(int i, int j) { return gridView[i][j]; }
	int Get_Field_Logic(int i, int j) { return gridLogic[i][j]; }
	void Set_Field_View(int i, int j, int value) { gridView[i][j] = value; }
	void Set_num_mines(int n) { num_mines = n; }
	void Set_Field_Logic(int i, int j, int value) { gridLogic[i][j] = value; }
	void Copy_Logic_To_View(int i, int j); // опирование логического элемента пол€ в видимое
	void Resize(int n);
	const int Get_width() { return w; }
	int Get_N() { return N; }
	Field() { gridLogic = NULL; gridView = NULL; }
	~Field();

private:
	int N = 0;
	int const w = 32; // ширина клетки в пиксел€х
	int** gridLogic; // логический массив или то, что скрыто
	int** gridView; // то что видим
	int num_mines=0; // количество мин
};

