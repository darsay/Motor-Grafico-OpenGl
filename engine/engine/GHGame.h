#pragma once
#include "Game.h"
#include "Song.h"
#include "GHScene.h"

	
using namespace std::chrono;

class GHGame: public Game
{
private:
	const double TIME_INCREMENT = 0.4; //ms tiempo en el juego
	const long UPDATE_PERIOD = 10; //ms tiempo en el mundo real

	milliseconds initialMilliseconds;
	long lastUpdatedTime;

	GHScene* activeScene;
	vector<GHScene*> scenes;

	string playername;

public:

	GHGame() : Game(), activeScene(nullptr),lastUpdatedTime(0), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())) {}
	GHScene* LoadTitleScene();
	GHScene* LoadGameScene(int songNumber);

	void BackToTitle();

	void Create();
	void Render();
	void Update();

	void ProcessKeyPressed(const unsigned char& key, const int& xPosition, const int& yPosition);
	void ProcessMouseClick(const int& button, const int& state, const int& xPosition, const int& yPosition);
	void ProcessMouseMovement(const int& xPosition, const int& yPosition) {};


};