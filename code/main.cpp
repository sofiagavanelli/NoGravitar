#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "menu.h"


using namespace std;


int main()
{
	try
	{

		menu MainMenu;
		MainMenu.draw();

	}
	catch (exception & e)
	{
		cout << "\nEXCEPTION: " << e.what() << endl;
	}
	return 0;
}