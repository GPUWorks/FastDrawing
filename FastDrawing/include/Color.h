#pragma once


#define RED Color(1,0,0,1)
#define BLUE Color(0,0,1,1)
#define COLOR_SPLIT_PTR(x) x->r, x->g, x->b, x->a

typedef struct Color{

public:
	float r,g,b,a;
	
	Color(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	/*Color(const Color &color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}*/
} Color;