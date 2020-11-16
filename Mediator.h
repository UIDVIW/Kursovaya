#pragma once
#include "Playing_Field.h"
#include "Timer.h"

class Mediator
{
public:
	Mediator();
	Mediator(Field&) { p_field = new Field; };
	//Mediator(Timer&);
	void size_from_menu(int n) { p_field->Resize(n); };
	void mines_from_menu(int n) { p_field->Set_num_mines(n); }
	
private:
	Field *p_field;
	Timer *p_timer;

};

Mediator::Mediator()
{
	p_field=NULL;
	p_timer=NULL;
}
