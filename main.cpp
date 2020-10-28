#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


int main()
{
	//Генератор случайных чисел
	srand(time(0));

	RenderWindow app(VideoMode(400, 400), "Minesweeper!");

	//Ширина клетки
	int w = 32;
	int gridLogic[12][12];
	int gridView[12][12];

	bool newgame = false;

	//Загрузка текстуры и создание спрайта
	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 5 == 0)  gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}
	//Подсчет мин вокруг каждой клетки
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}

	while (app.isOpen())
	{
		//Получаем координаты мыши относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			//Была нажата кнопка мыши…?
			if (event.type == Event::MouseButtonPressed)
				//Если это - левая кнопка мыши, то открываем клетку
				if (event.key.code == Mouse::Left) gridView[x][y] = gridLogic[x][y];
			//Если это – правая кнопка мыши, то отображаем флажок
				else if (event.key.code == Mouse::Right) gridView[x][y] = 11;

			// Была ли нажата клавиша на клавиатуре?
			if (event.type == Event::KeyPressed)
				// Эта кнопка – N?
				if (event.key.code == Keyboard::N) newgame = true; //тогда новая игра
		}

		if (newgame)  //новая игра
		{
			for (int i = 1; i <= 10; i++)
				for (int j = 1; j <= 10; j++)
				{
					gridView[i][j] = 10;
					if (rand() % 5 == 0)  gridLogic[i][j] = 9;
					else gridLogic[i][j] = 0;
				}
			//Подсчет мин вокруг каждой клетки
			for (int i = 1; i <= 10; i++)
				for (int j = 1; j <= 10; j++)
				{
					int n = 0;
					if (gridLogic[i][j] == 9) continue;
					if (gridLogic[i + 1][j] == 9) n++;
					if (gridLogic[i][j + 1] == 9) n++;
					if (gridLogic[i - 1][j] == 9) n++;
					if (gridLogic[i][j - 1] == 9) n++;
					if (gridLogic[i + 1][j + 1] == 9) n++;
					if (gridLogic[i - 1][j - 1] == 9) n++;
					if (gridLogic[i - 1][j + 1] == 9) n++;
					if (gridLogic[i + 1][j - 1] == 9) n++;
					gridLogic[i][j] = n;
				}
			newgame = false;
		}

		//Устанавливаем белый фон
		app.clear(Color::White);

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				if (gridView[i][j] == 9) gridView[i][j] = gridLogic[i][j];
				//Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));
				//Устанавливаем его заданную позицию…
				s.setPosition(i*w, j*w);
				//… и отрисовываем
				app.draw(s);
			}
		//отображаем всю композицию на экране
		app.display();
	}

	return 0;
}





