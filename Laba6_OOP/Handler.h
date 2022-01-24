#pragma once
#include "Figures.h"
#include "Circle.h"
#include "Rectanglee.h"
#include "Ellipse.h"
#include "Triangle.h"
enum figType { CIRCLE, ELLIPSE, RECTANGLE, TRIANGLE };
ref class Handler {
private:
	List<Figures> figures;
	bool multiSelect = false;
	bool collision = false;
	bool paint = false;
	int type;
	System::Drawing::Color color;
public:
	Handler() :type(0), color(System::Drawing::Color::Black) {}
	~Handler() {}
	void setType(int i) { type = i; }
	void setColor(System::Drawing::Color j) {
		color = j;
		for (int i=0; i < figures.GetSize(); i++) {
			if (figures[i]->getSelect()) {
				figures[i]->setColor(j);
			}
		}
	}
	void setMultiSelect(bool i) { multiSelect = i; }
	bool getMultiSelect() { return multiSelect; }
	void setCollision(bool i) { collision = i; }
	bool checkCollisions(int xC, int yC) {
		bool col = false;
		for (int i = figures.GetSize() - 1; i >= 0; i--) {
			if (!col) {
				if (figures[i]->checkCollision(xC, yC)) {
					figures[i]->setSelect(!figures[i]->getSelect());
					col = true;
				}
				else if (!multiSelect)
					figures[i]->setSelect(false);
			}
			else if (!multiSelect)
				figures[i]->setSelect(false);
			else break;
		}
		return col;
	}
	void paintAll(System::Windows::Forms::PaintEventArgs^ e) {
		for (int i = 0; i < figures.GetSize(); i++)
			figures[i]->draw(e);
	}
	void resizeAll(int xC, int yC, int w, int h, bool sign) {
		for (int i = 0; i < figures.GetSize(); i++)
			if (figures[i]->getSelect())
				figures[i]->resize(xC, yC, w, h, sign);
	}
	void deleteSelected() {
		for (int i = 0; i < figures.GetSize();) {
			if (figures[i]->getSelect()) {
				figures.removeAt(i);
			}
			else {
				i++;
			}
		}
	}
	void paintClick(int xC, int yC) {
		collision = this->checkCollisions(xC, yC);
		if (!collision) {
			this->startDraw(xC, yC);
		}
	}
	void startDraw(int xC, int yC) {
		Figures* a;
		switch (this->type) {
		case CIRCLE:
			a = new Circle(xC, yC, 100, color);
			figures.push_back(a);
			break;
		case ELLIPSE:
			a = new Ellipse(xC, yC, 10, 10, color);
			figures.push_back(a);
			break;
		case RECTANGLE:
		    a = new Rectanglee(xC, yC, 10, 10, color);
			figures.push_back(a);
			break;
		case TRIANGLE:
			a = new Triangle(xC, yC, color);
			figures.push_back(a);
			break;
		default:
			a = new Circle(xC, yC, 100, color);
			figures.push_back(a);
		}
		paint = true;
	}
	void proccessDraw(int xC, int yC, int w, int h) {
		if ((!collision) && (paint)) {
			figures[figures.GetSize()-1]->setSize(xC, yC, w, h);
		}
	}
	void endDraw() {
		paint = false;
	}
	void move(int x, int y, int w, int h) {
		for (int i = 0; i < figures.GetSize(); i++) {
			if (figures[i]->getSelect()) {
				figures[i]->move(x, y, w, h);
			}
		}
	}
};