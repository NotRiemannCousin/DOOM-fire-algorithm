#include <SFML/Graphics.hpp>
#include "Button.h"
#include <stdlib.h>
#include <unistd.h>
// #pragma warning(disable : Wwrite-strings)

using namespace sf;

#pragma region Global Variables
int fireSize = 37, gridCount = 40, cellSize = 20,
	gridSize = gridCount * cellSize;
int fireIntesity = 0;
Vector2i screenSize = Vector2i(VideoMode::getDesktopMode().width,
							   VideoMode::getDesktopMode().height);
Vector2f centerPos = Vector2f(screenSize.x / 2, screenSize.y / 2);
#pragma endregion

RectangleShape Grid(int indexX, int indexY);

int main()
{
	Font font;
	if (!font.loadFromFile("C:/Users/MARCE/OneDrive/Documentos/C++/REPO/DOOM-fire-algorithm/arialceb.ttf"))
	{
		fprintf(stderr, "Couldn't load font\n");
		return EXIT_FAILURE;
	}

	Text statusFire("fire intensive: " + std::to_string(fireIntesity), font, 38);
	statusFire.setFillColor(Color::Black);
	statusFire.setOutlineColor(Color::Black);
	//	fi.setOutlineThickness(6);
	statusFire.setPosition(30, 30);

	Button plusBtn(font, "+", 70, Vector2f(centerPos.x + gridSize * .5f, centerPos.y - 100), 1.5);
	Button minusBtn(font, "-", 70, Vector2f(centerPos.x - gridSize * .5f, centerPos.y - 100), 1.5);

	Button maxBtn(font, "++", 70, Vector2f(centerPos.x + gridSize * .5f, centerPos.y + 100), 1.5);
	Button minBtn(font, "--", 70, Vector2f(centerPos.x - gridSize * .5f, centerPos.y + 100), 1.5);

	fireIntesity = fireSize - 1;
	srand(13);

	RenderWindow window(sf::VideoMode::getDesktopMode(), "sfml", Style::Fullscreen);
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

	RectangleShape grid[gridCount][gridCount];
	int fire[gridCount][gridCount];

	for (int i = 0; i < gridCount; i++)
		for (int j = 0; j < gridCount; j++)
		{
			grid[i][j] = Grid(i, j);
			fire[i][j] = fireIntesity;
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

			case sf::Event::MouseButtonPressed:

				plusBtn.click(
					e.mouseButton, +[]()
								   {
					if (fireIntesity < 36)
						fireIntesity++; });
				minusBtn.click(
					e.mouseButton, +[]()
								   {
					if (fireIntesity > 0)
						fireIntesity--; });
				maxBtn.click(
					e.mouseButton, +[]()
								   { fireIntesity = 36; });
				minBtn.click(
					e.mouseButton, +[]()
								   { fireIntesity = 0; });
				break;
			}
		}

		statusFire.setString("fire intensive: " + std::to_string(fireIntesity));

		for (int j = 0; j < gridCount; j++)
		{
			for (int i = 0; i < gridCount; i++)
			{
				int decay = rand() % 4;

				if (i != gridCount - 1)
				{
					fire[j][i] = fire[j][i + 1] - decay;
				}
				else
				{
					fire[j][i] = fireIntesity;
				}
				fire[j][i] = std::max(0, fire[j][i]);

				int k = j - decay;
				if (k < 0)
				{
					k = gridCount - 1 + k;
				}
				grid[j][i].setFillColor(colorArray[0]);
				grid[j][i].setFillColor(colorArray[fire[j][i]]);
			}
		}
		window.clear(Color(10, 50, 70));

		for (int i = 0; i < gridCount; i++)
			for (int j = 0; j < gridCount; j++)
				window.draw(grid[j][i]);

#pragma region Rendering
		window.draw(statusFire);

		plusBtn.draw(window);
		minusBtn.draw(window);
		maxBtn.draw(window);
		minBtn.draw(window);

		window.display();
#pragma endregion

		usleep(20000);
	}
}

RectangleShape Grid(int indexX, int indexY)
{
	RectangleShape cell;
	static Vector2f posGrid = Vector2f(centerPos.x + -gridSize / 2,
									   centerPos.y + -gridSize / 2);

	cell.setSize(Vector2f(cellSize, cellSize));
	cell.setOutlineColor(Color(27, 27, 27));
	cell.setFillColor(Color(20, 20, 20));
	cell.setPosition(Vector2f(posGrid.x + cellSize * indexX,
							  posGrid.y + cellSize * indexY));

	return cell;
}