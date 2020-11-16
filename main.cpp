#include "Playing_Field.h"
#include "Menu.h"
#include "Timer.h"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

int main()
{

	//Генератор случайных чисел
	srand(time(0));
	
	bool f_menu = true;
	bool newgame = false;
	int q = 0;
	int min = 0;
	int time = 0;

	cin >> q;
	cin >> min;
	cin >> time;

	RenderWindow app(VideoMode(384, 384), "Minesweeper!");
	menu(app);

	Field f;
	Timer timer;
	timer.setup(time);
	

	//Загрузка текстуры и создание спрайта
	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);

	f.Resize(q);
	app.setSize(Vector2u(f.Get_N()*f.Get_width()+96, f.Get_N()*f.Get_width()+96 )); //меняем размер
	app.setView(View(Vector2f((f.Get_N()*f.Get_width()+96)/2 , (f.Get_N()*f.Get_width()+96)/2  ), Vector2f(f.Get_N()*f.Get_width()+96 , f.Get_N()*f.Get_width()+96 ))); //меняем вид
	
	f.Set_num_mines(min);
	f.Create_Mines();

	//Подсчет мин вокруг каждой клетки
	f.Calculate_Mines();

	timer.init();
	while (app.isOpen())
	{		
		app.setTitle("Minesweeper!   " + to_string(timer.remains()));
		//Получаем координаты мыши относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / f.Get_width();
		int y = pos.y / f.Get_width();

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			//Была нажата кнопка мыши…?
			if (!f_menu && event.type == Event::MouseButtonPressed)
				//Если это - левая кнопка мыши, то открываем клетку
				if (event.key.code == Mouse::Left) f.Copy_Logic_To_View(x, y);
			//Если это – правая кнопка мыши, то отображаем флажок
				else if (event.key.code == Mouse::Right) if (f.Get_Field_View(x, y) == 10) f.Set_Field_View(x, y, 11);
				else if (f.Get_Field_View(x, y) == 11) f.Set_Field_View(x, y, 10);

			// Была ли нажата клавиша на клавиатуре?
			if (event.type == Event::KeyPressed)
				// Эта кнопка – N?
				if (event.key.code == Keyboard::N) newgame = true; //тогда новая игра
				/*else if (event.key.code == Keyboard::Up) //если была нажата кнопка ВВЕРХ
				{
					app.setSize(Vector2u(700, 700)); //меняем размер
					app.setView(View(Vector2f(700 / 2.0, 700 / 2.0), Vector2f(700, 700))); //меняем вид
					newgame = true;
				}
				else if (event.key.code == Keyboard::Down) //если была нажата кнопка ВНИЗ
				{
					app.setSize(Vector2u(384, 384)); //меняем размер
					app.setView(View(Vector2f(384 / 2.0, 384 / 2.0), Vector2f(384, 384))); //меняем вид
					newgame = true;
				}*/
		}
		f_menu = false;

		if (newgame)  //новая игра
		{
			f.Create_Mines();
			//Подсчет мин вокруг каждой клетки
			f.Calculate_Mines();
			newgame = false;
			timer.init();
		}

		//Устанавливаем белый фон
		app.clear(Color::White);

		for (int i = 1; i <= f.Get_N(); i++)
			for (int j = 1; j <= f.Get_N(); j++)
			{
				//if (f.Get_Field_View(i, j) ==9) f.Copy_Logic_To_View(i, j);
				//Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(f.Get_Field_View(i, j) * f.Get_width(), 0, f.Get_width(), f.Get_width()));
				//Устанавливаем его заданную позицию…
				s.setPosition(i*f.Get_width(), j*f.Get_width());
				//… и отрисовываем
				app.draw(s);
			}
		//отображаем всю композицию на экране
		app.display();
		
	}

	return 0;
}