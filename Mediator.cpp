#include "Mediator.h"

Mediator::Mediator(RenderWindow *a, Menu *m, Field *f, Timer *t)
{
	p_app = a;
	p_menu = m;
	p_field = f;
	p_timer = t;
	p_message_box = new EMessage();
}

void Mediator::Left_Mouse_Pressed(int x, int y) //������� ����� �����
{
	p_field->Copy_Logic_To_View(x, y);
}

void Mediator::Right_Mouse_Pressed(int x, int y) //������� ������ ������, ������(�������) ������
{
	if (p_field->Get_Field_View(x, y) == 10) p_field->Set_Field_View(x, y, 11);
	else if (p_field->Get_Field_View(x, y) == 11) p_field->Set_Field_View(x, y, 10);
}

void Mediator::New_Game() //����� ����
{
	p_field->Create_Mines();
	//������� ��� ������ ������ ������
	p_field->Calculate_Mines();
	p_timer->init();
	//������ ������ � ��� ����
	p_app->setSize(Vector2u(p_field->Get_N()*p_field->Get_width() + 96, p_field->Get_N()*p_field->Get_width() + 96));
	p_app->setView(View(Vector2f((p_field->Get_N()*p_field->Get_width() + 96) / 2, (p_field->Get_N()*p_field->Get_width() + 96) / 2), Vector2f(p_field->Get_N()*p_field->Get_width() + 96, p_field->Get_N()*p_field->Get_width() + 96)));
	Game_Ended = false;
}
void Mediator::Check_End_Game()
{
	if (p_timer->remains() < 0) // �������� �� ��������� �������
	{
		Game_Ended = true;
		p_app->setTitle(L"Minesweeper! �� ��������� :(");
		return;
	}

	for (int i = 1; i <= p_field->Get_N(); i++) // �������� �� ������� �� ����
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 9)
			{
				Open_Mine();
				Game_Ended = true;
				p_app->setTitle(L"Minesweeper! �� ��������� :(");
				return;
			}

	Game_Ended = true;
	for (int i = 1; i <= p_field->Get_N(); i++) // �������� �� ������� (�� ���� ����� ������)
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 11 && p_field->Get_Field_Logic(i, j) != 9 ||
				p_field->Get_Field_View(i, j) != 11 && p_field->Get_Field_Logic(i, j) == 9)
				Game_Ended = false;
	if (Game_Ended) p_app->setTitle(L"Minesweeper! �� �������� !!!");
}

void Mediator::Open_Mine()
{
	for (int i = 1; i <= p_field->Get_N(); i++)
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_Logic(i, j) == 9)
				p_field->Set_Field_View(i, j, 9);
}

void Mediator::Data_From_Menu(int n)
{
	try {

		switch (n)
		{
		case 1:
		{
			p_field->Resize(10);
			p_field->Set_num_mines(15);
			p_timer->setup(300);
			break;
		}
		case 2:
		{
			p_field->Resize(15);
			p_field->Set_num_mines(30);
			p_timer->setup(600);
			break;
		}
		case 3:
		{
			p_field->Resize(20);
			p_field->Set_num_mines(45);
			p_timer->setup(900);
		}
		}
	}
	catch (const char* exception)
	{
		string s(exception);
		p_message_box->Set_Message(s);
		p_message_box->Run();
		exit(-1);
	}
}

void Mediator::Work()
{
	try
	{
		p_menu->Display_Menu();
	}
	catch (const char* exception)
	{
		string s(exception);
		p_message_box->Set_Message(s);
		p_message_box->Run();
		exit(-1);
	}
	Data_From_Menu(p_menu->Display_Menu());

	//�������� �������� � �������� �������
	Texture t;
	try
	{
		if (!t.loadFromFile("images/tiles.jpg"))
			throw "The texture was lost or the texture was not loaded.";
	}
	catch (const char* exception)
	{
		string s(exception);
		p_message_box->Set_Message(s);
		p_message_box->Run();
		exit(-1);
	}
	Sprite s(t);

	New_Game();

	while (p_app->isOpen())
	{
		if (!Game_Ended) p_app->setTitle("Minesweeper!   " + to_string(p_timer->remains()));
		//�������� ���������� ���� ������������ ���� ������ ����������
		Vector2i pos = Mouse::getPosition(*p_app);
		int x = pos.x / p_field->Get_width();
		int y = pos.y / p_field->Get_width();

		Event event;
		while (p_app->pollEvent(event))
		{
			if (event.type == Event::Closed)
				p_app->close();
			//���� ������ ������ ����?
			if (event.type == Event::MouseButtonPressed && !Game_Ended)
				//���� ��� - ����� ������ ����, �� �������� � �������� ����� ������
				if (event.key.code == Mouse::Left) Left_Mouse_Pressed(x, y);
			//���� ��� � ������ ������ ����, �� �������� � �������� ������ ������
				else if (event.key.code == Mouse::Right) Right_Mouse_Pressed(x, y);

			// ���� �� ������ ������� �� ����������?
			if (event.type == Event::KeyPressed)
				// ��� ������ � N?
				if (event.key.code == Keyboard::N) //����� ����� ����
				{
					Data_From_Menu(p_menu->Display_Menu()); New_Game();
				}
			// ��� ������ � EScape?
				else if (event.key.code == Keyboard::Escape)
				{
					Data_From_Menu(p_menu->Display_Menu()); New_Game();
				}
		}

		//������������� ����� ���
		p_app->clear(Color::White);

		for (int i = 1; i <= p_field->Get_N(); i++)
			for (int j = 1; j <= p_field->Get_N(); j++)
			{
				if (p_field->Get_Field_View(i, j) == 9) p_field->Copy_Logic_To_View(i, j);
				//�������� �� ������� ������ ��� ��������� ��������
				s.setTextureRect(IntRect(p_field->Get_Field_View(i, j) * p_field->Get_width(), 0, p_field->Get_width(), p_field->Get_width()));
				//������������� ��� �������� ��������
				s.setPosition(i*p_field->Get_width(), j*p_field->Get_width());
				//� � ������������
				p_app->draw(s);
			}
		Check_End_Game();
		//���������� ��� ���������� �� ������
		p_app->display();

	}
}
