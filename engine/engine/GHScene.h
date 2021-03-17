#pragma once
#include "Scene.h"
#include "Song.h"
#include "ScoreManager.h"
#include <string>


class GHScene : public Scene
{
private:
	
	const float TIME_OFFSET = 3; //Tiempo para que se empiecen a crear las esferas antes de la reproducci�n
	vector<FlyingCamera> cameras;
	FlyingCamera maincam;
	vector<GameObject*> gameObjects;
	vector<Song*> songs;
	ScoreManager* manager;

	bool bPlaying;				//Se est� jugando?
	bool bFinished;				//Se ha acabado la canci�n?
	bool bAmITitle;				//Como las escenas pueden ser t�tulo o canci�n, se las identifica con esto.
	float timePlaying;			//Tiempo de reproducci�n para sincronizar con la canci�n
	int activeSong;				//�ndice del vector songs
	int activeCam;
	float timeToEnd;			//Una vez acaba la canci�n... el tiempo para volver al men�
	string playerName;			//El nombre del jugador, para el archivo de puntuaci�n

public:
	GHScene (): Scene(), bPlaying(0), timePlaying(0.f), activeSong(0), manager(nullptr), bFinished(false), bAmITitle(false), timeToEnd(0), activeCam(0) {}
	GHScene(int songNumber) : Scene(), bPlaying(0), timePlaying(0.f), activeSong(songNumber), manager(nullptr), bFinished(false), timeToEnd(0), activeCam(0) {}
	~GHScene();
	void Update(const float& time);
	void Render();
	void AddGameObject(GameObject* object);
	void AddSong(Song* song);
	void SetCamera(int camIndex);
	void AddCamera(FlyingCamera cam, bool isMain=false);

	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessMouseClick(const int& button, const int& state, const int& x, const int& y);

	//Override vac�o porque no nos interesa que se pueda mover la c�mara con el rat�n
	void ProcessMouseMovement(const int& x, const int& y) {};

	inline void SetScoreMgr(ScoreManager* manager) { this->manager = manager; }
	inline void SetTitle(const bool title) { this->bAmITitle = title; }
	inline bool isFinished() const { return bFinished; }
	inline void SetPlayername(const string name) { this->playerName = name; }

	
};

