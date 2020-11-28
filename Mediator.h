#pragma once
#include "Playing_Field.h"
#include "Timer.h"

class Mediator
{
public:
	Mediator(Field *f, Timer *t);
	Mediator(Field&) { p_field = new Field; };
	void Data_From_Menu(int s, int n, int t) {p_field->Resize(s); p_field->Set_num_mines(n); p_timer->setup(t); }
	void Left_Mouse_Pressed(int x, int y);
	void Right_Mouse_Pressed(int x, int y);
	void New_Game();
	bool End_Game();
	void Open_Mine();


private:
	Field *p_field;
	Timer *p_timer;

};

Mediator::Mediator(Field *f, Timer *t)
{
	p_field = f;
	p_timer = t;
}

void Mediator::Left_Mouse_Pressed(int x, int y) //нажатие левой кнопи
{
	p_field->Copy_Logic_To_View(x, y);
}

void Mediator::Right_Mouse_Pressed(int x, int y) //нажатие правой кнопки, ставим(убираем) флажок
{
	if (p_field->Get_Field_View(x, y) == 10) p_field->Set_Field_View(x, y, 11);
	else if (p_field->Get_Field_View(x, y) == 11) p_field->Set_Field_View(x, y, 10);
}

void Mediator::New_Game() //новая игра
{
	p_field->Create_Mines();
	//Подсчет мин вокруг каждой клетки
	p_field->Calculate_Mines();
	p_timer->init();
}
bool Mediator::End_Game()
{
	if (p_timer->remains() < 0) // проверка на окончание времени
		return true;

	for (int i = 1; i <= p_field->Get_N(); i++) // проверка на нажатие на мину
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 9)
			{
				Open_Mine();
				return true;
			}

	for (int i = 1; i <= p_field->Get_N(); i++) // проверка на выигрыш (на всех минах флажки)
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 11 && p_field->Get_Field_Logic(i, j) != 9 || 
				p_field->Get_Field_View(i, j) != 11 && p_field->Get_Field_Logic(i, j) == 9)
				return false;

	return true;

}

void Mediator::Open_Mine()
{
	for (int i = 1; i <= p_field->Get_N(); i++)
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_Logic(i, j) == 9)
				p_field->Set_Field_View(i, j, 9);
}

