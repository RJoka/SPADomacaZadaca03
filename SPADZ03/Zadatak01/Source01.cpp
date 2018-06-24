#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;

struct Point
{
	Point(unsigned x, unsigned y, char type)
	{
		this->x = x;
		this->y = y;
		this->type = type;
	}
	unsigned x;
	unsigned y;
	char type;
};

inline void pause(unsigned secs = 1U)
{
	const int milsecs = 100;
	clock_t wait = secs * milsecs + clock();
	while (wait > clock())
	{
		continue;
	}
}

void prepare_field(vector<vector<Point>> &playfield)
{
	for (unsigned i = 0; i < 20; i++)
	{
		vector<Point> row;
		for (unsigned j = 0; j < 40; j++)
		{
			row.emplace_back(i, j, '-');
		}
		playfield.push_back(row);
	}
}

void adjust_playfield(vector<vector<Point>> &playfield, Point &A, Point &B, Point &X)
{
	if ((A.x == B.x && A.y == B.y) || (A.x < 1) || (B.x < 1) || (A.y < 1) || (B.x < 1) || (A.x > 20) || (B.x > 20) || (A.y > 40) || (B.y > 40))
	{
		throw exception("krivo unesene koordinate! ");
	}

	playfield[A.x - 1][A.y - 1] = A;
	playfield[B.x - 1][B.y - 1] = B;

	if (A.x > B.x && A.y > B.y)
	{
		X.x = A.x;
		X.y = A.y - 1;
	}
	else if (A.x < B.x && A.y > B.y)
	{
		X.x = A.x;
		X.y = A.y - 1;
	}
	else if (A.y == B.y && A.x < B.x)
	{
		X.x = A.x + 1;
		X.y = A.y;
	}
	else if (A.y == B.y && A.x > B.x)
	{
		X.x = A.x - 1;
		X.y = A.y;
	}
	else if (A.x == B.x && A.y < B.y)
	{
		X.x = A.x;
		X.y = A.y + 1;
	}
	else if (A.x == B.x && A.y > B.y)
	{
		X.x = A.x;
		X.y = A.y - 1;
	}
	else if (A.x == 1 && A.y == 1)
	{
		X.x = A.x;
		X.y = 2;
	}
	else if (A.x == 20 && A.y == 1)
	{
		X.x = A.x;
		X.y = 2;
	}
	else if (A.x == 1 && A.y == 40)
	{
		X.x = A.x;
		X.y = 39;
	}
	else if (A.x == 20 && A.y == 40)
	{
		X.x = A.x;
		X.y = 39;
	}
	else
	{
		X.x = A.x;
		X.y = A.y + 1;
	}
	playfield[X.x - 1][X.y - 1] = X;
}

void form_playfield(vector<vector<Point>> &playfield, Point &A, Point &B, Point &X)
{
	playfield[A.x - 1][A.y - 1] = A;
	playfield[B.x - 1][B.y - 1] = B;
	playfield[X.x - 1][X.y - 1] = X;
}

void print(vector<vector<Point>> &v)
{
	for (unsigned i = 0; i < 20; i++)
	{
		for (unsigned j = 0; j < 40; j++)
		{
			cout << v[i][j].type;
		}
		cout << endl;
	}
	cout << endl;
}

/*
	direction
	1 = ++
	2 = --
*/
void move(vector<vector<Point>> &playfield, Point &A, Point &B, Point &X, int direction, char variable)
{
	if (variable == 'x' && direction == 1)
	{
		X.x++;
	}
	else if (variable == 'x' && direction == 2)
	{
		X.x--;
	}
	else if (variable == 'y' && direction == 1)
	{
		X.y++;
	}
	else
	{
		X.y--;
	}
	form_playfield(playfield, A, B, X);
	print(playfield);
	pause(2);
	system("cls");
}

void travel(vector<vector<Point>> &playfield, Point &A, Point &B, Point &X)
{
#pragma region Distance
	unsigned x_distance;
	unsigned y_distance;
	if (A.x > B.x)
	{
		x_distance = A.x - B.x;
	}
	else
	{
		x_distance = B.x - A.x;
	}
	if (A.y > B.y)
	{
		y_distance = A.y - B.y;
	}
	else
	{
		y_distance = B.y - A.y;
	}
#pragma endregion
	if (A.y == B.y)
	{
		if (A.x < B.x)
		{
			print(playfield);
			for (unsigned i = 0; i < x_distance - 1; i++)
			{
				move(playfield, A, B, X, 1, 'x');
			}
			print(playfield);
		}
		else if (A.x > B.x)
		{
			print(playfield);
			for (unsigned i = 0; i < x_distance - 1; i++)
			{
				move(playfield, A, B, X, 2, 'x');
			}
			print(playfield);
		}
	}
	else if (A.x == B.x)
	{
		if (A.y < B.y)
		{
			print(playfield);
			for (unsigned i = 0; i < y_distance - 1; i++)
			{
				move(playfield, A, B, X, 1, 'y');
			}
			print(playfield);
		}
		else if (A.y > B.y)
		{
			print(playfield);
			for (unsigned i = 0; i < y_distance - 1; i++)
			{
				move(playfield, A, B, X, 2, 'y');
			}
			print(playfield);
		}
	}
	else
	{
		if (A.x > B.x)
		{
			if (A.y < B.y)
			{
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < y_distance - 1; i++)
				{
					move(playfield, A, B, X, 1, 'y');
				}
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < x_distance; i++)
				{
					move(playfield, A, B, X, 2, 'x');
				}
				print(playfield);
			}
			else if(A.y > B.y)
			{
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < y_distance - 1; i++)
				{
					move(playfield, A, B, X, 2, 'y');
				}
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < x_distance; i++)
				{
					move(playfield, A, B, X, 2, 'x');
				}
				print(playfield);
			}
		}
		else if (A.x < B.x)
		{
			if (A.y < B.y)
			{
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < y_distance - 1; i++)
				{
					move(playfield, A, B, X, 1, 'y');
				}
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < x_distance; i++)
				{
					move(playfield, A, B, X, 1, 'x');
				}
				print(playfield);
			}
			else if (A.y > B.y)
			{
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < y_distance - 1; i++)
				{
					move(playfield, A, B, X, 2, 'y');
				}
				print(playfield);
				pause(2);
				system("cls");
				for (unsigned i = 0; i < x_distance; i++)
				{
					move(playfield, A, B, X, 1, 'x');
				}
				print(playfield);
			}
		}
	}
}

int main()
{
	vector<vector<Point>> playfield;

	prepare_field(playfield);

	cout << "unesite A(x): ";
	int Ax;
	cin >> Ax;
	cout << "unesite A(y): ";
	int Ay;
	cin >> Ay;
	cout << "unesite B(x): ";
	int Bx;
	cin >> Bx;
	cout << "unesite B(y): ";
	int By;
	cin >> By;

	system("cls");
	
	Point A(Ax, Ay, 'A');
	Point B(Bx, By, 'B');
	Point X(-1, -1, 'x');

	try
	{
		adjust_playfield(playfield, A, B, X);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	travel(playfield, A, B, X);


	return 0;
}