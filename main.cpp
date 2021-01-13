#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow renderWindow{{640u, 480u}, "SFML"};
	sf::Event event;

	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				renderWindow.close();
			}
		}

		renderWindow.clear();
		renderWindow.display();
	}
}