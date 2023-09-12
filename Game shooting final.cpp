#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#define LOCATE(row,column) (cout << "\033[" << row << ';' << column << 'H')
#define COLOR(f, b) (cout << "\033[1;3" << (f) << ";4" << (b) << 'm' << flush)
#define CLS (cout << "\033[2J")
#define DELAY 18000000
#define BLACK 0
#define GREEN 2

class arr_obj 
{
public:
	int obj_y, obj_x;
};

void score(int count);
void lives_of_0(int value);
void shield(int value);

int main()
{
	string text;
	
	while (true)
	{
		COLOR(GREEN, BLACK);
		string text, answer;

		do
		{
			LOCATE(7, 40), cout << "Do you want to play this game (yes/no)?: ";
			getline(cin, text);
			CLS;
		} while (text != "yes" && text != "no");

		if (text == "yes")
		{
			LOCATE(7, 40), cout << "Instruction:";
			LOCATE(8, 40), cout << "-Use arrow buttons to control the object.";
			LOCATE(9, 40), cout << "-Use space button to shoot.";
			LOCATE(10, 40), cout << "-Press ESC to stop the game.";
			LOCATE(11, 40), cout << "-You have ten lives and 100% of shield persistence.";
			LOCATE(12, 40), cout << "-Do not let the enemy hit you or hit the shield.";
			LOCATE(13, 40), cout << "-You will win if you get 10 scores.";
			LOCATE(15, 40), cout << "GOOD LUCK!";
			LOCATE(18, 40), cout << "Press any button to continue!";
		}

		while (text == "yes")
		{
			if (_kbhit() != 0)
			{
				CLS;
				break;
			}
		}


		bool collision = false;
		int x = 28, y = 13, old_x, old_y, c, d{}, row_number, count = 0, pre_y = 13,
			shield_persistence = 100, lives = 10;
		string line(99, '_'), edge("|"), arrow("-->");

		LOCATE(1, 2); cout << line;
		LOCATE(25, 2); cout << line;

		for (row_number = 2; row_number <= 25; ++row_number)
			LOCATE(row_number, 1), cout << edge;
		for (row_number = 2; row_number <= 25; ++row_number)
			LOCATE(row_number, 101), cout << edge;

		LOCATE(3, 105), cout << "Score: " << count;
		LOCATE(4, 105), cout << "Lives left:" << lives;
		LOCATE(5, 105), cout << "Shield:" << shield_persistence << "%";
		LOCATE(7, 105), cout << "Press ESC";
		LOCATE(8, 103), cout << "to end the game!";

		int a, object_x = 98, random_y = 1;
		arr_obj arrow_y, arrow_x;

		time_t sec;
		time(&sec);
		srand((unsigned)sec);

		arrow_y.obj_y = 0, arrow_x.obj_x = 0;


		while (true)
		{
			a = rand();
			if (a >= 3 && a <= 24)
			{
				random_y = a;
				LOCATE(random_y, object_x); cout << "|_|";
				break;
			}
		}

		while (text == "yes")
		{
			for (long wait = 0; wait < DELAY; ++wait);

			LOCATE(random_y, object_x); cout << "   ";
			--object_x;
			LOCATE(random_y, object_x); cout << "|_|";

			LOCATE(y, x), cout << "0";
			old_y = y, old_x = x;

			if (_kbhit() != 0)
			{
				c = _getch();

				if (c == 75)
					x = x - 3;
				else if (c == 77)
					x = x + 3;
				else if (c == 80)
				{
					pre_y = y;
					++y;
				}
				else if (c == 72)
				{
					pre_y = y;
					--y;
				}
				else if ((c == 32) && (collision == false))
				{
					LOCATE(y, x), cout << arrow;
					arrow_y.obj_y = y, arrow_x.obj_x = x;
					d = c, collision = true;
				}
				else if (c == 27)
				{
					CLS;
					LOCATE(7, 40), cout << "Thanks for playing the game!";
					LOCATE(26, 1);
					break;
				}

				LOCATE(old_y, old_x); cout << " ";
			}


			if (object_x == 1)
			{
				shield_persistence -= 10;
				shield(shield_persistence);

				LOCATE(random_y, object_x); cout << "   ";
				LOCATE(random_y, 1), cout << edge;
				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}

			if (random_y == arrow_y.obj_y && object_x == arrow_x.obj_x)
			{
				LOCATE(random_y, object_x); cout << "   ";

				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}
			else if (random_y == arrow_y.obj_y && ((object_x - arrow_x.obj_x) <= 1) && object_x >= x)
			{
				LOCATE(random_y, object_x); cout << "   ";
				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}


			if (random_y == y && object_x == x)
			{
				--lives;
				lives_of_0(lives);

				LOCATE(y, x); cout << " ";
				y = 13, x = 28;
				LOCATE(y, x); cout << "0";
				LOCATE(random_y, object_x); cout << "   ";

				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}
			else if (random_y == y && ((object_x - x) == 1))
			{
				--lives;
				lives_of_0(lives);

				LOCATE(y, x); cout << " ";
				y = 13, x = 28;
				LOCATE(y, x); cout << "0";
				LOCATE(random_y, object_x); cout << "   ";
				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}
			else if (random_y == y && ((object_x - x) == -1) && y == pre_y)
			{
				--lives;
				lives_of_0(lives);

				LOCATE(y, x); cout << " ";
				y = 13, x = 28;
				LOCATE(y, x); cout << "0";
				LOCATE(random_y, object_x); cout << "   ";
				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}
			else if (random_y == y && ((object_x - x) == -2) && y == pre_y)
			{
				--lives;
				lives_of_0(lives);

				LOCATE(y, x); cout << " ";
				y = 13, x = 28;
				LOCATE(y, x); cout << "0";
				LOCATE(random_y, object_x); cout << "   ";
				object_x = 98;

				while (true)
				{
					a = rand();
					if (a >= 3 && a <= 24 && a != random_y)
					{
						random_y = a;
						break;
					}
				}

				LOCATE(random_y, object_x); cout << "|_|";
			}

			pre_y = y;

			if (d == 32)
			{
				LOCATE(arrow_y.obj_y, arrow_x.obj_x); cout << "   ";
				arrow_x.obj_x += 5;
				LOCATE(arrow_y.obj_y, arrow_x.obj_x); cout << arrow;

				if (arrow_x.obj_x >= 99)
				{
					d = 0, collision = false;
					LOCATE(arrow_y.obj_y, arrow_x.obj_x); cout << "   ";
					LOCATE(arrow_y.obj_y, 101), cout << "|";
				}

				if (random_y == arrow_y.obj_y && ((object_x - arrow_x.obj_x) <= 3) && object_x >= x)
				{
					++count;
					score(count);
					d = 0, collision = false;
					LOCATE(arrow_y.obj_y, arrow_x.obj_x); cout << "   ";
				}
			}

			if (y == 1)
			{
				LOCATE(y, x), cout << '_';
				++y;
			}
			else if (y == 25)
			{
				LOCATE(y, x), cout << '_';
				--y;
			}
			else if (x == 1)
			{
				LOCATE(y, 1), cout << '|';
				x = x + 3;
			}
			else if (x == 100)
			{
				LOCATE(y, 1), cout << '|';
				x = x - 3;
			}

			if (lives == 0)
			{
				CLS;
				LOCATE(7, 48), cout << "Game over!";
				LOCATE(10, 40), cout << "Press any key to continue";
				break;
			}

			if (shield_persistence == 0)
			{
				CLS;
				LOCATE(7, 48), cout << "Game over!";
				LOCATE(10, 40), cout << "Press any key to continue";
				break;
			}

			if (count == 15)
			{
				CLS;
				LOCATE(7, 49), cout << "You win!";
				LOCATE(10, 40), cout << "Press any key to continue";
				break;
			}
		}


		while (text == "yes")
		{
			if (_kbhit() != 0)
			{
				CLS;
				do
				{
					CLS;
					LOCATE(7, 40), cout << "Do you want to continue to play (yes/no)?: ";
					getline(cin, answer);
				} while (answer != "yes" && answer != "no");
				
				CLS;
				break;
			}
		}

		if (answer == "no")
		{
			CLS;
			LOCATE(7, 40), cout << "Thanks for playing the game!";
			LOCATE(9, 49), cout << "Goodbye!";
			LOCATE(26, 1);
			break;
		}

		if (text == "no")
		{
			CLS;
			LOCATE(7, 40), cout << "Goodbye!";
			LOCATE(26, 1);
			break;
		}

	}

	return 0;
}

void score(int count)
{
	LOCATE(3, 105), cout << "Score: " << count;
}

void lives_of_0(int value)
{
	LOCATE(4, 105), cout << "Lives left: " << value;
}

void shield(int value)
{
	LOCATE(5, 105), cout << "Shield: " << value << "%";
}

/*The end*/
/*Written by Zuki Erudo*/