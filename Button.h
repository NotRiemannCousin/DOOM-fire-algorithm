#pragma once 
#include <SFML/Graphics.hpp>
#include <functional>
using namespace sf;

class Button
{
  public:
	Text text;
	RectangleShape box;

	Button(Font &font, char *str, int sizeChar, Vector2f pos, float size) : text(str, font, sizeChar), box(Vector2f(sizeChar * size * 0.912, sizeChar * 1.26))
	{
		text.setPosition(pos.x - (text.getGlobalBounds().left + text.getGlobalBounds().width / 2 - (sizeChar * 0.912 * size / 2)), pos.y);
		text.setFillColor(Color::Black);

		box.setPosition(pos);
		box.setFillColor(Color::White);
		box.setOutlineColor(Color(230, 230, 230));
		box.setOutlineThickness(10);
	};

	template<class ...Types>
	void click(Touch touch, void (*action)(Types... params), Types... args)
	{
		for (int i = 0; i < 5; i++)
		{
			if (box.getGlobalBounds().contains(Vector2f (touch.getPosition(i))))
			{
				action(args...);
				break;
			}
		}
	}
	void draw(RenderWindow &w)
	{
		w.draw(box);
		w.draw(text);
	};
};