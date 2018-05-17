#pragma once
#include <glad/glad.h>
#include <stdio.h>

void gl_clear_error()
{
	while (glGetError() != GL_NO_ERROR);
}

int gl_log(const char * function, const char *file, const int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		fprintf(stderr, "[OpenGL Error] %d\nfunction: %s file: %s line: %d\n", error, function, file, line);
		return -1;
	}
	return 0;
}

#define ASSERT(x) if(!x) exit(0);
#define GL_CALL(x) gl_clear_error();\
    x;\
    ASSERT(gl_log(#x, __FILE__, __LINE__))