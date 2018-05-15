#pragma once


#define RED Color(1,0,0,1)
#define BLUE Color(0,0,1,1)

typedef struct Color{

public:
	float r,g,b,a;
	
	Color(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
} Color;