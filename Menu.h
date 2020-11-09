#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground;
	menuTexture1.loadFromFile("Images/111.png");
	menuTexture2.loadFromFile("Images/222.png");
	menuTexture3.loadFromFile("Images/333.png");
	menuBackground.loadFromFile("Images/BK.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(0, 30);
	menu2.setPosition(0, 90);
	menu3.setPosition(0, 150);
	menuBg.setPosition(0, 0);

	//////////////////////////////����///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(0, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(0, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(0, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) {window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}
