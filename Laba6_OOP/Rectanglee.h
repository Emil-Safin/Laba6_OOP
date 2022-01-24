#pragma once
#include "likeAbox.h"

class Rectanglee : public likeAbox {
public:
	Rectanglee() {}
	Rectanglee(int x, int y, int w, int h) :likeAbox(x, y, w, h) {}
	Rectanglee(int x, int y, int w, int h, Color color) :likeAbox(x, y, w, h, color) {}
	virtual void draw(System::Windows::Forms::PaintEventArgs^ e) override {
		Brush^ brsh = gcnew System::Drawing::SolidBrush(color);
		e->Graphics->FillRectangle(brsh, x, y, width, height);
		if (select)
			e->Graphics->DrawRectangle(gcnew Pen(Brushes::Red, 6), x + 3, y + 3, width - 6, height - 6);
	}
	virtual bool checkCollision(int x, int y) override {
		if ((this->x <= x) && (this->x2 >= x))
			if ((this->y <= y) && (this->y2 >= y))
				return true;
		return false;
	}
};