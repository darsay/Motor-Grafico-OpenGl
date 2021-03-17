#pragma once
#include "Scene.h"
#include "GHGame.h"

class TitleScene :
	public Scene
{
	private:
		GHGame game;
		FlyingCamera camera;
		vector<GameObject*> gameObjects;

	public:
		TitleScene() : Scene(), game(nullptr) {}
		TitleScene(GHGame parentGame) : Scene(),  game(parentGame) {}
		
		void ProcessMouseMovement(const int& x, const int& y);
		void ProcessMouseClick(const int& button, const int& state, const int& x, const int& y);
		void ProcessKeyPressed(unsigned char key, int px, int py);
};

