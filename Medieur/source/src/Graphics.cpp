#include "Graphics.h"

#include <iostream>
#include <map>
#include <algorithm>

#include <SDL.h>

#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>

#include "Rectangle.h"
#include "World.h"
#include "units.h"
#include "Sprite.h"
#include "Tile.h"

namespace Graphics {
	namespace {
		// constants
		const int kWindowWidth = units::kScreenWidth * units::kTileSize;
		const int kWindowHeight = units::kScreenHeight * units::kTileSize;

		// SDL render variables
		SDL_Renderer* mainRenderer = nullptr;
		SDL_Window* mainWindow = nullptr;

		std::map<std::string, SDL_Texture*> textureMap;
		SDL_Texture* worldTexture;

		Sprite* grassSprite;

		// Helper functions
		SDL_Rect RectangleToSDL_Rect(const Rectangle & pRectangle) {
			return SDL_Rect{ pRectangle.getX(), pRectangle.getY() , pRectangle.getWidth(), pRectangle.getHeight() };
		}
	}

	SDL_Texture * loadImage(const std::string& filename)
	{
		const std::string filepath = "content\\sprites\\" + filename;
		if (textureMap[filepath] == false) {
			SDL_Texture* tempTexture = ::IMG_LoadTexture(mainRenderer, filepath.c_str());
			if (tempTexture == nullptr) {
				printf("Couldn't load: %s\n", filepath.c_str());
			}
			else {
				printf("Loaded: %s!\n", filepath.c_str());
			}
			textureMap[filepath] = tempTexture;
		}
		return textureMap[filepath];
	}

	void init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		mainWindow = SDL_CreateWindow("Medieur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			kWindowWidth, kWindowHeight, 0);

		if (mainWindow == nullptr) {
			printf("mainWindow is null! SDL_Error: %s\n", SDL_GetError());
			std::cin.get();
		}

		mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_TARGETTEXTURE);

		if (mainRenderer == nullptr) {
			printf("mainRenderer is null! SDL_Error: %s\n", SDL_GetError());
			std::cin.get();
		}

		SDL_RenderSetLogicalSize(mainRenderer, kWindowWidth, kWindowHeight);
		SDL_ShowWindow(mainWindow);

		printf("Window and Renderer initialized!\n");
	}

	void renderTexture(SDL_Texture * pTexture,
		const Rectangle & pSourceRectangle,
		const Rectangle & pDestinationRectangle)
	{

		if (SDL_RenderCopy(mainRenderer, pTexture,
			&(RectangleToSDL_Rect(pSourceRectangle)),
			&(RectangleToSDL_Rect(pDestinationRectangle))
		) == -1) printf("Error on rendering\n");

		
	}

	void clear()
	{
		SDL_RenderClear(mainRenderer);
	}

	void renderPresent()
	{
		SDL_RenderPresent(mainRenderer);
	}

	void targetWorldTexture()
	{
		SDL_SetRenderTarget(mainRenderer, worldTexture);
		SDL_RenderClear(mainRenderer);
	}

	void changeWorldTexture(int pWidth, int pHeight) {
		SDL_DestroyTexture(worldTexture);
		worldTexture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, pWidth, pHeight);
	}

	void resetTarget()
	{
		SDL_SetRenderTarget(mainRenderer, NULL);
		SDL_RenderCopy(mainRenderer, worldTexture, NULL, NULL);
	}


	void quit()
	{
		SDL_DestroyRenderer(mainRenderer);
		SDL_DestroyWindow(mainWindow);
		SDL_Quit();
	}

}