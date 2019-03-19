// Zaryad.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "SFML/Graphics.hpp"
#include "Vector2.h"

#include <vector>
#include <cmath>

#include <iostream>


//ВНИМАНИЕ
//Далее супер важно
//нужно переделать распределение файлов проекта по папкам

const double ShowConstant = -200000.0;
const double Precision = 5.0;

bool IsInsideWindow(sf::Vector2u WSize, Point Position) {
	if (Position.x >= 0 && Position.y >= 0 &&
		Position.x <= WSize.x && Position.y <= WSize.y) {
		return true;
	}
	else {
		return false;
	}
}


struct Charge {
	Charge(const sf::Vector2i& pos, const short& s) {
		Position.x = pos.x;
		Position.y = pos.y;
		sign = s;
	}

	Vector2 CailculateField(const Point& pos) {		//pos - position of a point in which field is calculated
		
		Vector2 Distance(pos, Position);
		double L = Distance.Length();
		Vector2 E(pos, ShowConstant * sign * Distance.x / (L * L * L), 
					ShowConstant * sign * Distance.y / (L * L * L));
		return E;
	}

	Point Position;
	short sign;
};


void DrawField(sf::RenderWindow& win, const Point& pt, std::vector<Charge>& charges) {
	Vector2 E;

	for (auto& c : charges) {
		E = E + c.CailculateField(pt);
	}

	if (E.Length() < 10000.0 && E.Length() > 0.01) {

		E = E * (Precision / E.Length());

		sf::Vertex line[] =
		{
		sf::Vertex(sf::Vector2f(pt.x, pt.y)),
		sf::Vertex(sf::Vector2f(pt.x + E.x, pt.y + E.y))		//point plus Vector E
		};

		line->color = (sf::Color::White);
		win.draw(line, 2, sf::Lines);


		Point NewPoint(pt.x + E.x, pt.y + E.y);
		if (IsInsideWindow(win.getSize(), NewPoint)) {
			DrawField(win, NewPoint, charges);
		}
	}
}

void DrawReverse(sf::RenderWindow& win, const Point& pt, std::vector<Charge>& charges) {
					//baisicly DrawField, but going in opposite to vector E direction
	Vector2 E;

	for (auto& c : charges) {
		E = E + c.CailculateField(pt);
	}

	if (E.Length() < 10000.0 && E.Length() > 0.01) {

		E = E * (Precision / E.Length());

		sf::Vertex line[] =
		{
		sf::Vertex(sf::Vector2f(pt.x, pt.y)),
		sf::Vertex(sf::Vector2f(pt.x + E.x, pt.y + E.y))		//point minus Vector E
		};

		line->color = (sf::Color::White);
		win.draw(line, 2, sf::Lines);


		Point NewPoint(pt.x - E.x, pt.y - E.y);
		if (IsInsideWindow(win.getSize(), NewPoint)) {
			DrawReverse(win, NewPoint, charges);
		}
	}
}


void DrawAroundCharge(sf::RenderWindow& win, std::vector<Charge>& charges) {		//создаем точки вокруг зарядов и для них чертим поле
	for (const auto c : charges) {
		Vector2 Var = { {0, 0}, 25.0, 0.0 };
		for (int i = 0; i < 16; i++) {
			Var.Rotate(3.1415 * i / 8);
			Point NewPt(c.Position.x + Var.x, c.Position.y + Var.y);
			if (c.sign > 0) {
				DrawField(win, NewPt, charges);
			}
			if (c.sign < 0) {
				DrawReverse(win, NewPt, charges);
			}
		}
	}
}


int main() {
	std::vector<Charge> charges;
	std::vector<Point> points;

	sf::RenderWindow window(sf::VideoMode(1500, 900), "Some random charges...");

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		for (auto c : charges) {
			sf::CircleShape Ch(25.f);
			if (c.sign > 0) {
				Ch.setFillColor(sf::Color::Red);
			}
			if(c.sign < 0) {
				Ch.setFillColor(sf::Color::Blue);
			}

			Ch.setPosition(c.Position.x - 25, c.Position.y - 25);
			window.draw(Ch);
		}
		//testin
		DrawAroundCharge(window, charges);

		for (auto pt : points) {
			sf::CircleShape Point(5.f);
			Point.setFillColor(sf::Color::Green);
			Point.setPosition(pt.x - 5, pt.y - 5);

			window.draw(Point);

			//drawig E field for each point 
			DrawField(window, pt, charges);

			DrawReverse(window, pt, charges);

		}

		sf::Vector2i MousePos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Right) {
					charges.push_back(Charge(MousePos, -1));
				}

				if (event.mouseButton.button == sf::Mouse::Left) {
					charges.push_back(Charge(MousePos, 1));
				}
			}
		}

		//old method
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			charges.push_back(Charge(MousePos, 1));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			charges.push_back(Charge(MousePos, -1));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			points.push_back(Point(MousePos));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {		//clearing the picture
			charges.clear();
			points.clear();
		}
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			charges.pop_back();
		}*/

		window.display();
	}

    std::cout << "Hello World!\n"; 
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
