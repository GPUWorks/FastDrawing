#pragma once
#include <string>
#include "Window.h"

class Engine {

public:
	Engine(const std::string &title, int w, int h) {
		this->window = new Window(title, w, h);

	}
	~Engine() {
		delete this->window;
	}

	void Run() {
		while (this->window->IsOpened())
		{
			window->Clear();
			

			window->Blit();
		}
	}

private:
	Window * window;
	int GetWindowWidth() const {
		return this->window->GetWidth();
	}
	int GetWindowHeight() const {
		return this->window->GetHeight();
	}
}; 
