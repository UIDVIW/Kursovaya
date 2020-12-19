#include "Playing_Field.h"

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

// открытие островка без мин 
void Field::Copy_Logic_To_View(int i, int j)
{
	if ((i > 0) && (i < N + 1) && (j > 0) && (j < N + 1))
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
	// если была выделена пам€ть, то очищаем дл€ выделени€ пам€ти другого размера
	if (gridLogic != NULL && gridView != NULL)
	{
		for (int i = 0; i < N + 2; i++)
		{
			delete[] gridLogic[i];
			delete[] gridView[i];
		}
		delete[] gridLogic;
		delete[] gridView;
	}

	N = n;
	gridLogic = new int*[N + 2];
	gridView = new int*[N + 2];

	if (gridLogic == NULL || gridView == NULL)
		throw "No memory was allocated.";

	for (int i = 0; i < N + 2; i++)
	{
		gridLogic[i] = new int[N + 2];
		gridView[i] = new int[N + 2];
		if (gridLogic[i] == NULL || gridView[i] == NULL)
			throw "No memory was allocated.";
	}
}

