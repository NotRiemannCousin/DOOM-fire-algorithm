#include <SFML/Graphics.hpp>
#include "Button.h"
#include <stdlib.h>
#include <unistd.h>

using namespace sf;

int screenSizeX = 1080, screenSizeY = 2340;
int fireSize = 37, gridSize = 40, cellSize = 20;
int fireIntesive = 0;

RectangleShape Grid(int indexX, int indexY);

int main()
{
	Font font;
	if (!font.loadFromFile("/storage/emulated/0/my-project/src/arialceb.ttf"))
	{
		fprintf(stderr, "Couldn't load font\n");
		return EXIT_FAILURE;
	}

	Text fi("fire intensive: " + std::to_string(fireIntesive), font, 38);
	fi.setColor(Color::Black);
	fi.setOutlineColor(Color::Black);
//	fi.setOutlineThickness(6);
	fi.setPosition(30, 600);

	Button plusBtn(font, ("+"), 70, Vector2f(screenSizeX / 2 - 35 * 0.912 * 1.5 + 250, screenSizeY / 2 + 500), 1.5);
	Button minusBtn(font, ("-"), 70, Vector2f(screenSizeX / 2 - 35 * 0.912 * 1.5 - 250, screenSizeY / 2 + 500), 1.5);

	Button maxBtn(font, ("++"), 70, Vector2f(screenSizeX / 2 - 35 * 0.912 * 1.5 + 250, screenSizeY / 2 + 600), 1.5);
	Button minBtn(font, ("--"), 70, Vector2f(screenSizeX / 2 - 35 * 0.912 * 1.5 - 250, screenSizeY / 2 + 600), 1.5);

	fireIntesive = fireSize - 1;
	srand(13);

	RenderWindow window(VideoMode(screenSizeX, screenSizeY), "sfml");
	window.setFramerateLimit(60);

	Color colorArray[37] = {
		sf::Color(7, 7, 7), sf::Color(31, 7, 7), sf::Color(47, 15, 7),
		sf::Color(71, 15, 7), sf::Color(87, 23, 7), sf::Color(103, 31, 7),
		sf::Color(119, 31, 7), sf::Color(143, 39, 7), sf::Color(159, 47, 7),
		sf::Color(175, 63, 7), sf::Color(191, 71, 7), sf::Color(199, 71, 7),
		sf::Color(223, 79, 7), sf::Color(223, 87, 7), sf::Color(223, 87, 7),
		sf::Color(215, 95, 7), sf::Color(215, 95, 7), sf::Color(215, 103, 15),
		sf::Color(207, 111, 15), sf::Color(207, 119, 15), sf::Color(207, 127, 15),
		sf::Color(207, 135, 23), sf::Color(199, 135, 23), sf::Color(199, 143, 23),
		sf::Color(199, 151, 31), sf::Color(191, 159, 31), sf::Color(191, 159, 31),
		sf::Color(191, 167, 39), sf::Color(191, 167, 39), sf::Color(191, 175, 47),
		sf::Color(183, 175, 47), sf::Color(183, 183, 47), sf::Color(183, 183, 55),
		sf::Color(207, 207, 111), sf::Color(223, 223, 159), sf::Color(239, 239, 199),
		sf::Color(255, 255, 255)};
		
	RectangleShape grid[gridSize][gridSize];
	int fire[gridSize][gridSize];

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = Grid(i, j);

			fire[i][j] = fireIntesive;
		}
	}

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::TouchBegan:

				plusBtn.click(Touch(), +[]() {
					if (fireIntesive < 36)
						fireIntesive++;
				});
				minusBtn.click(Touch(), +[]() {
					if (fireIntesive > 0)
						fireIntesive--;
				});
				maxBtn.click(Touch(), +[](){
					fireIntesive = 36;
				});
				minBtn.click(Touch(), +[](){
					fireIntesive = 0;
				});
				break;
			}
		}

		fi.setString("fire intensive: " + std::to_string(fireIntesive));

		for (int j = 0; j < gridSize; j++)
		{
			for (int i = 0; i < gridSize; i++)
			{
				int decay = rand() % 4;

				if (i != gridSize - 1)
				{
					fire[j][i] = fire[j][i + 1] - decay;
				}
				else
				{
					fire[j][i] = fireIntesive;
				}
				if (fire[j][i] < 0)
				{
					fire[j][i] = 0;
				}

				int k = j - decay;
				if (k < 0)
				{
					k = gridSize - 1 + k;
				}
				grid[j][i].setFillColor(colorArray[0]);
				grid[j][i].setFillColor(colorArray[fire[j][i]]);
			}
		}

		window.clear(Color(10, 50, 70));

		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				window.draw(grid[j][i]);
			}
		}
		window.draw(fi);

		plusBtn.draw(window);
		minusBtn.draw(window);
		maxBtn.draw(window);
		minBtn.draw(window);

		window.display();
		usleep(20000);
	}
}

RectangleShape Grid(int indexX, int indexY)
{
	RectangleShape cell;

	cell.setSize(Vector2f(cellSize, cellSize));
	cell.setOutlineColor(Color(27, 27, 27));
	cell.setFillColor(Color(20, 20, 20));
	cell.setPosition(Vector2f(screenSizeX / 2 + cellSize * indexX - (gridSize * cellSize) / 2, screenSizeY / 2 + cellSize * indexY - (gridSize * cellSize) / 2));

	return cell;
}