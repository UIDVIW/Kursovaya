#include "Menu.h"

int Menu::Display_Menu()
{
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground;
	if (!menuTexture1.loadFromFile("Images/6field.png") || !menuTexture2.loadFromFile("Images/8field.png") || !menuTexture3.loadFromFile("Images/10field.png") || !menuBackground.loadFromFile("Images/BK.jpg"))
		throw "The texture was lost or the texture was not loaded.";

	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(0, 30);
	menu2.setPosition(0, 90);
	menu3.setPosition(0, 150);
	menuBg.setPosition(0, 0);

	//////////////////////////////ÌÅÍŞ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		p_app->clear(Color(129, 181, 221));

		if (IntRect(0, 30, 300, 50).contains(Mouse::getPosition(*p_app))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(0, 90, 300, 50).contains(Mouse::getPosition(*p_app))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(0, 150, 300, 50).contains(Mouse::getPosition(*p_app))) { menu3.setColor(Color::Blue); menuNum = 3; }

		Event event;
		while (p_app->pollEvent(event))
		{
			if (event.type == Event::Closed)
				p_app->close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					if (menuNum == 1) { isMenu = false; }
					if (menuNum == 2) { isMenu = false; }
					if (menuNum == 3) { isMenu = false; }
				}
		}

		p_app->draw(menuBg);
		p_app->draw(menu1);
		p_app->draw(menu2);
		p_app->draw(menu3);

		p_app->display();
	}

	return menuNum;
}
