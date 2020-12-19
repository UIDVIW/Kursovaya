#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu
{
public:
	Menu(RenderWindow *a) { p_app = a; };
	int Display_Menu();

private:
	RenderWindow *p_app;
};

