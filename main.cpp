#include "Playing_Field.h"
#include "Menu.h"
#include "Timer.h"
#include "Mediator.h"
#include <iostream>




int main()
{
	//��������� ��������� �����
	srand(time(0));

	RenderWindow app(VideoMode(384, 384), "Minesweeper!   ", Style::Close);
	app.setPosition(Vector2i(500, 250));

	Field field; //����
	Timer timer; //������
	Menu menu(&app); //����
	Mediator mediator(&app, &menu, &field, &timer); //��������

	mediator.Work();

	return 0;
}