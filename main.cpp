#include "Mediator.h"

int main()
{
	//Генератор случайных чисел
	srand(time(0));

	RenderWindow app(VideoMode(384, 384), "Minesweeper!   ", Style::Close);
	app.setPosition(Vector2i(500, 250));

	Field field; //поле
	Timer timer; //таймер
	Menu menu(&app); //меню
	Mediator mediator(&app, &menu, &field, &timer); //Медиатор

	mediator.Work();

	return 0;
}