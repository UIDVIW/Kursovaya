#include "Playing_Field.h"
#include "Menu.h"
#include "Timer.h"
#include "Mediator.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

int main()
{

	//��������� ��������� �����
	srand(time(0));

	bool f_menu = true;
	bool newgame = false;
	int q = 0;
	int min = 0;
	int time = 0;

	/*cin >> q;
	cin >> min;
	cin >> time;*/

	RenderWindow app(VideoMode(384, 384), "Minesweeper!");
	

	Field f; //����
	Timer timer; //������
	//timer.setup(time);
	Mediator med(&f, &timer); //��������

	menu(app, med);
	
	//�������� �������� � �������� �������
	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);

	//f.Resize(q);
	app.setSize(Vector2u(f.Get_N()*f.Get_width() + 96, f.Get_N()*f.Get_width() + 96)); //������ ������
	app.setView(View(Vector2f((f.Get_N()*f.Get_width() + 96) / 2, (f.Get_N()*f.Get_width() + 96) / 2), Vector2f(f.Get_N()*f.Get_width() + 96, f.Get_N()*f.Get_width() + 96))); //������ ���

	//f.Set_num_mines(min);

	med.New_Game();

	while (app.isOpen())
	{
		app.setTitle("Minesweeper!   " + to_string(timer.remains()));
		//�������� ���������� ���� ������������ ���� ������ ����������
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / f.Get_width();
		int y = pos.y / f.Get_width();

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			//���� ������ ������ ����?
			if (!f_menu && event.type == Event::MouseButtonPressed)
				//���� ��� - ����� ������ ����, �� �������� � �������� ����� ������
				if (event.key.code == Mouse::Left) med.Left_Mouse_Pressed(x, y);
			//���� ��� � ������ ������ ����, �� �������� � �������� ������ ������
				else if (event.key.code == Mouse::Right) med.Right_Mouse_Pressed(x, y);

			// ���� �� ������ ������� �� ����������?
			if (event.type == Event::KeyPressed)
				// ��� ������ � N?
				if (event.key.code == Keyboard::N) med.New_Game(); //����� ����� ����
				/*else if (event.key.code == Keyboard::Up) //���� ���� ������ ������ �����
				{
					app.setSize(Vector2u(700, 700)); //������ ������
					app.setView(View(Vector2f(700 / 2.0, 700 / 2.0), Vector2f(700, 700))); //������ ���
					newgame = true;
				}
				else if (event.key.code == Keyboard::Down) //���� ���� ������ ������ ����
				{
					app.setSize(Vector2u(384, 384)); //������ ������
					app.setView(View(Vector2f(384 / 2.0, 384 / 2.0), Vector2f(384, 384))); //������ ���
					newgame = true;
				}*/
		}
		f_menu = false;

		//������������� ����� ���
		app.clear(Color::White);

		for (int i = 1; i <= f.Get_N(); i++)
			for (int j = 1; j <= f.Get_N(); j++)
			{
				//if (f.Get_Field_View(i, j) ==9) f.Copy_Logic_To_View(i, j);
				//�������� �� ������� ������ ��� ��������� ��������
				s.setTextureRect(IntRect(f.Get_Field_View(i, j) * f.Get_width(), 0, f.Get_width(), f.Get_width()));
				//������������� ��� �������� ��������
				s.setPosition(i*f.Get_width(), j*f.Get_width());
				//� � ������������
				app.draw(s);
			}
		//���������� ��� ���������� �� ������
		app.display();

		if (med.End_Game())
		{
			//med.New_Game();
		}
		
	}

	return 0;
}