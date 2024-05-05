#ifndef MEMORY_H
#define MEMORY_H
#endif

#include <SDL.h>
#undef main


const int resX = 150, resY = 100;
const int pixelSize = 5	;
const int StartingMemory = 0xA568;

struct Graphics {
	SDL_Window* window;
	SDL_Event event;
	SDL_Renderer* renderer;


	SDL_Rect rect;

	void Initialize() {
		//SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		window = SDL_CreateWindow("A*", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX * pixelSize, resY * pixelSize, SDL_WINDOW_ALLOW_HIGHDPI);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	}
	void UpdateColour(Memory &memory) {
		for (int i = 0; i <= resX * resY; i++) {

			

			
			int x = i % (resX * pixelSize);
			int y = i / (resX * pixelSize);

			switch (memory.ReadByte(0xA568 + i))
			{
			case 1: {
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
				break;
			}
			case 2: {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);//red
				break;
			}
			case 3: {
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//red
				break;
			}
			case 4: {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//red
				break;
			}
			default:
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				break;
			}
				
			}


			

			rect = { x * pixelSize, y * pixelSize, pixelSize, pixelSize };

			SDL_RenderFillRect(renderer, &rect);

		}
		
		SDL_RenderPresent(renderer);
	}

	void GetInput(Memory& memory) {
		if (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type)
			{
				memory.WriteByte(0x0002, 0x0001);

			}
			if (event.type == SDL_KEYDOWN) {
				memory.WriteByte(0x0001, (uint8_t)event.key.keysym.scancode);
			}
			if (event.type == SDL_KEYUP) {
				memory.WriteByte(0x0001, 0x0000);
			}

		}
	}

	void DestoryWindow() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};
