#include "Mediator.h"

Mediator::Mediator(RenderWindow *a, Menu *m, Field *f, Timer *t)
{
	p_app = a;
	p_menu = m;
	p_field = f;
	p_timer = t;
	p_message_box = new EMessage();
}

void Mediator::Left_Mouse_Pressed(int x, int y) //нажатие левой кнопи
{
	p_field->Copy_Logic_To_View(x, y);
}

void Mediator::Right_Mouse_Pressed(int x, int y) //нажатие правой кнопки, ставим(убираем) флажок
{
	if (p_field->Get_Field_View(x, y) == 10) p_field->Set_Field_View(x, y, 11);
	else if (p_field->Get_Field_View(x, y) == 11) p_field->Set_Field_View(x, y, 10);
}

void Mediator::New_Game() //новая игра
{
	p_field->Create_Mines();
	//Подсчет мин вокруг каждой клетки
	p_field->Calculate_Mines();
	p_timer->init();
	//меняем размер и вид окна
	p_app->setSize(Vector2u(p_field->Get_N()*p_field->Get_width() + 96, p_field->Get_N()*p_field->Get_width() + 96));
	p_app->setView(View(Vector2f((p_field->Get_N()*p_field->Get_width() + 96) / 2, (p_field->Get_N()*p_field->Get_width() + 96) / 2), Vector2f(p_field->Get_N()*p_field->Get_width() + 96, p_field->Get_N()*p_field->Get_width() + 96)));
	Game_Ended = false;
}
void Mediator::Check_End_Game()
{
	if (p_timer->remains() < 0) // проверка на окончание времени
	{
		Game_Ended = true;
		p_app->setTitle(L"Minesweeper! Вы проиграли :(");
		return;
	}

	for (int i = 1; i <= p_field->Get_N(); i++) // проверка на нажатие на мину
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 9)
			{
				Open_Mine();
				Game_Ended = true;
				p_app->setTitle(L"Minesweeper! Вы проиграли :(");
				return;
			}

	Game_Ended = true;
	for (int i = 1; i <= p_field->Get_N(); i++) // проверка на выигрыш (на всех минах флажки)
		for (int j = 1; j <= p_field->Get_N(); j++)
			if (p_field->Get_Field_View(i, j) == 11 && p_field->Get_Field_Logic(i, j) != 9 ||
				p_field->Get_Field_View(i, j) != 11 && p_field->Get_Field_Logic(i, j) == 9)
				Game_Ended = false;
	if (Game_Ended) p_app->setTitle(L"Minesweeper! Вы выиграли !!!");
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

	//Загрузка текстуры и создание спрайта
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
		//Получаем координаты мыши относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(*p_app);
		int x = pos.x / p_field->Get_width();
		int y = pos.y / p_field->Get_width();

		Event event;
		while (p_app->pollEvent(event))
		{
			if (event.type == Event::Closed)
				p_app->close();
			//Была нажата кнопка мыши…?
			if (event.type == Event::MouseButtonPressed && !Game_Ended)
				//Если это - левая кнопка мыши, то передаем в медиатор левую кнопку
				if (event.key.code == Mouse::Left) Left_Mouse_Pressed(x, y);
			//Если это – правая кнопка мыши, то передаем в медиатор правую кнопку
				else if (event.key.code == Mouse::Right) Right_Mouse_Pressed(x, y);

			// Была ли нажата клавиша на клавиатуре?
			if (event.type == Event::KeyPressed)
				// Эта кнопка – N?
				if (event.key.code == Keyboard::N) //тогда новая игра
				{
					Data_From_Menu(p_menu->Display_Menu()); New_Game();
				}
			// Эта кнопка – EScape?
				else if (event.key.code == Keyboard::Escape)
				{
					Data_From_Menu(p_menu->Display_Menu()); New_Game();
				}
		}

		//Устанавливаем белый фон
		p_app->clear(Color::White);

		for (int i = 1; i <= p_field->Get_N(); i++)
			for (int j = 1; j <= p_field->Get_N(); j++)
			{
				if (p_field->Get_Field_View(i, j) == 9) p_field->Copy_Logic_To_View(i, j);
				//Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(p_field->Get_Field_View(i, j) * p_field->Get_width(), 0, p_field->Get_width(), p_field->Get_width()));
				//Устанавливаем его заданную позицию…
				s.setPosition(i*p_field->Get_width(), j*p_field->Get_width());
				//… и отрисовываем
				p_app->draw(s);
			}
		Check_End_Game();
		//отображаем всю композицию на экране
		p_app->display();

	}
}
