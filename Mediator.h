#pragma once
#include "Playing_Field.h"
#include "Timer.h"
#include "Menu.h"
#include "TextBox.h"

class Mediator
{
public:
	Mediator(RenderWindow *a, Menu *m, Field *f, Timer *t);
	void Data_From_Menu(int n);
	void Left_Mouse_Pressed(int x, int y);
	void Right_Mouse_Pressed(int x, int y);
	void New_Game();
	void Check_End_Game();
	void Open_Mine();
	void Work();


private:
	EMessage *p_message_box;
	Field *p_field;
	Menu *p_menu;
	Timer *p_timer;
	RenderWindow *p_app;
	bool Game_Ended;
};

