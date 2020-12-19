#include "TextBox.h"

void EMessage::Run()
{
	bool running = true;
	RenderWindow ErrWindow(VideoMode(600, 130), "Error!", Style::Close);
	Font font;
	font.loadFromFile("9041.ttf");
	Text text;
	text.setFont(font);
	text.setColor(Color::Black);
	text.setStyle(Text::Bold);
	text.setPosition(50, 50);
	text.setCharacterSize(20);
	text.setString(Message);//задает строку тексту*/

	while (ErrWindow.isOpen())
	{
		Event event;
		while (ErrWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				ErrWindow.close();
		}
		ErrWindow.clear(Color::White);
		ErrWindow.draw(text);
		ErrWindow.display();
	}
}
