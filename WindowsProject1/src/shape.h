#pragma once

namespace lmb
{
struct Circle
{
public:
	int x;
	int y;
	int radius;
};

class Rectangle
{
public:
	int left;
	int top;
	int right;
	int bottom;
};

bool Intersect(const Rectangle& rect, const Circle& circle);
bool Intersect(const Circle& circle, const Rectangle& rect);
bool Intersect(const Rectangle& rect1, const Rectangle& rect2);
bool Intersect(const Circle& circle1, const Circle& circle2);

}
