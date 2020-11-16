#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void menu(RenderWindow & window) 
{
	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuBackground;
	menuTexture1.loadFromFile("Images/111.png");
	menuTexture2.loadFromFile("Images/Field.png");
	menuTexture3.loadFromFile("Images/mines.png");
	menuTexture4.loadFromFile("Images/333.png");
	menuBackground.loadFromFile("Images/BK.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(0, 30);
	menu2.setPosition(0, 90);
	menu3.setPosition(0, 150);
	menu4.setPosition(0, 210);
	menuBg.setPosition(0, 0);

	//////////////////////////////лемч///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(0, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(0, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(0, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(0, 210, 300, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) 
			{	
				while (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					Texture menuTexture1, menuTexture2, menuTexture3, menuBackground;
					menuTexture1.loadFromFile("Images/6field.png");
					menuTexture2.loadFromFile("Images/8field.png");
					menuTexture3.loadFromFile("Images/10field.png");
					menuBackground.loadFromFile("Images/BK.jpg");
					Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
					int menuNum = 0;
					menu1.setPosition(0, 30);
					menu2.setPosition(0, 90);
					menu3.setPosition(0, 150);
					menuBg.setPosition(0, 0);


					menu1.setColor(Color::White);
					menu2.setColor(Color::White);
					menu3.setColor(Color::White);
					menuNum = 0;
					window.clear(Color(129, 181, 221));

					if (IntRect(0, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
					if (IntRect(0, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
					if (IntRect(0, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

					window.draw(menuBg);
					window.draw(menu1);
					window.draw(menu2);
					window.draw(menu3);

					window.display();
				}
				
				
			
			}
			if (menuNum == 3)
			{
				while (!Keyboard::isKeyPressed(Keyboard::Escape))
				{
					Texture menuTexture1, menuTexture2, menuTexture3, menuBackground;
					menuTexture1.loadFromFile("Images/15mines.png");
					menuTexture2.loadFromFile("Images/30mines.png");
					menuTexture3.loadFromFile("Images/40mines.png");
					menuBackground.loadFromFile("Images/BK.jpg");
					Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
					int menuNum = 0;
					menu1.setPosition(0, 30);
					menu2.setPosition(0, 90);
					menu3.setPosition(0, 150);
					menuBg.setPosition(0, 0);


					menu1.setColor(Color::White);
					menu2.setColor(Color::White);
					menu3.setColor(Color::White);
					menuNum = 0;
					window.clear(Color(129, 181, 221));

					if (IntRect(0, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
					if (IntRect(0, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
					if (IntRect(0, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

					window.draw(menuBg);
					window.draw(menu1);
					window.draw(menu2);
					window.draw(menu3);

					window.display();
				}
			}
			if (menuNum == 4) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
	////////////////////////////////////////////////////
}
