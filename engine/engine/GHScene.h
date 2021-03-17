#pragma once
#include "Scene.h"
#include "Song.h"
#include "ScoreManager.h"
#include <string>


class GHScene : public Scene
{
private:
	
	const float TIME_OFFSET = 3; //Tiempo para que se empiecen a crear las esferas antes de la reproducción
	vector<FlyingCamera> cameras;
	FlyingCamera maincam;
	vector<GameObject*> gameObjects;
	vector<Song*> songs;
	ScoreManager* manager;

	bool bPlaying;				//Se está jugando?
	bool bFinished;				//Se ha acabado la canción?
	bool bAmITitle;				//Como las escenas pueden ser título o canción, se las identifica con esto.
	float timePlaying;			//Tiempo de reproducción para sincronizar con la canción
	int activeSong;				//Índice del vector songs
	int activeCam;
	float timeToEnd;			//Una vez acaba la canción... el tiempo para volver al menú
	string playerName;			//El nombre del jugador, para el archivo de puntuación

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

	//Override vacío porque no nos interesa que se pueda mover la cámara con el ratón
	void ProcessMouseMovement(const int& x, const int& y) {};

	inline void SetScoreMgr(ScoreManager* manager) { this->manager = manager; }
	inline void SetTitle(const bool title) { this->bAmITitle = title; }
	inline bool isFinished() const { return bFinished; }
	inline void SetPlayername(const string name) { this->playerName = name; }

	
};

