#include "GHGame.h"
#include "Sphere.h"
#include "Torus.h"
#include "Model.h"
#include "song.h"
#include <iostream>

using namespace std;

void GHGame::Create()
{
	cout << "\n\nBienvenido a Guitar Hero, version de Ignacio Molina y Jesus Robles para la practica de Programacion Avanzada en la URJC, curso 2020." <<endl;
	cout << "En esta pantalla aparecerán datos importantes, como el log y la puntuacion, no la ocultes con la del juego." << endl;
	cout << "\nA continuacion escribe tu nombre, en cuanto pulses enter el juego se iniciara: " << endl;
	cin >> playername;

	GHScene* mainScene = LoadTitleScene();

	this->scenes.push_back(mainScene);
	this->activeScene = mainScene;
}


void GHGame::Render() 
{
	this->activeScene->Render();
}

void GHGame::Update()
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD)
	{
		this->activeScene->Update(TIME_INCREMENT);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
		if (this->activeScene->isFinished())
			BackToTitle();
	}
}

void GHGame::ProcessKeyPressed(const unsigned char& key, const int& xPosition, const int& yPosition)
{
	//Primero miro que la tecla no sea un nº del 1 al 3 (las canciones)
	if (key > 48 && key < 52 && activeScene == scenes[0])
	{
		GHScene* scene = LoadGameScene(key - 48);
		scenes.push_back(scene);
		activeScene = scene;
	}
	else
		this->activeScene->ProcessKeyPressed(key, xPosition, yPosition);
}

GHScene* GHGame::LoadGameScene(int songNumber)
{
	
	GHScene* mainScene = new(nothrow) GHScene();
	//Cámara principal
	FlyingCamera mainCamera = mainScene->GetCamera();
	mainScene->AddCamera(mainCamera, true);
	//Cámara secundaria
	FlyingCamera secCamera = mainScene->GetCamera();
	secCamera.SetPosition(Vector3D(mainCamera.GetPosition().GetX(), mainCamera.GetPosition().GetY()-10, mainCamera.GetPosition().GetZ()));
	secCamera.SetOrientation(Vector3D(-30.0f, 0.0f, 0.0f));
	mainScene->AddCamera(secCamera);

	//Carga de la canción
	Song* song = nullptr;
	switch (songNumber)
	{
	case 1:
		song = new Song(Song::SmokeEasy);
		break;
	case 2:
		song = new Song(Song::Smell);
		break;
	case 3:
		song = new Song(Song::Smoke);
	}
	mainScene->AddSong(song);

	//Carga de los toroides de traste
	Torus* torus = new Torus();
	torus->SetPosition(Vector3D(0.0f, 0.0f, 1.0f));
	torus->SetColor(Color(1.f, 0.f, 0.f));
	torus->SetOrientationSpeed(Vector3D(0.0f, 6.0f, 0.0f));
	torus->SetIsAffectedByGravity(false);
	mainScene->AddGameObject(torus);

	Torus* torus2 = new Torus();
	torus2->SetPosition(Vector3D(4.0f, 0.0f, 1.0f));
	torus2->SetColor(Color(0.f, 1.f, 0.f));
	torus2->SetOrientationSpeed(Vector3D(0.0f, 6.0f, 0.0f));
	torus2->SetIsAffectedByGravity(false);
	mainScene->AddGameObject(torus2);

	Torus* torus3 = new Torus();
	torus3->SetPosition(Vector3D(8.0f, 0.0f, 1.0f));
	torus3->SetColor(Color(0.f, 0.f, 1.f));
	torus3->SetOrientationSpeed(Vector3D(0.0f, 6.0f, 0.0f));
	torus3->SetIsAffectedByGravity(false);
	mainScene->AddGameObject(torus3);

	Torus* torus4 = new Torus();
	torus4->SetPosition(Vector3D(12.0f, 0.0f, 1.0f));
	torus4->SetColor(Color(0.f, 1.f, 1.f));
	torus4->SetOrientationSpeed(Vector3D(0.0f, 6.0f, 0.0f));
	torus4->SetIsAffectedByGravity(false);
	mainScene->AddGameObject(torus4);
	//-------------------------------------------------------
	//Carga de los elementos auxiliares
	Model* guitar = new Model();
	guitar->LoadModel(".\\Models\\guitar.obj");
	guitar->SetColor(Color(0.7f, 0.7f, 0.7f));
	guitar->SetPosition(Vector3D(5.f, 12.f, -4.f));
	guitar->SetIsAffectedByGravity(false);
	guitar->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(guitar);

	Model* logo = new Model();
	logo->LoadModel(".\\Models\\gh.obj");
	logo->SetColor(Color(0.6f, 0.0f, 0.9f));
	logo->SetPosition(Vector3D(2.5f, 3.f, -2.f));
	logo->SetIsAffectedByGravity(false);
	logo->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(logo);
	//--------------------------------------------------------
	//Carga de los textos de ayuda
	Model* qText = new Model();
	qText->LoadModel(".\\Models\\q.obj");
	qText->SetColor(Color(1, 0, 0));
	qText->SetPosition(Vector3D(-.5f, -2.f, 1.5f));
	qText->SetIsAffectedByGravity(false);
	qText->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(qText);

	Model* wText = new Model();
	wText->LoadModel(".\\Models\\w.obj");
	wText->SetColor(Color(0, 1, 0));
	wText->SetPosition(Vector3D(3.5f, -2.f, 1.5f));
	wText->SetIsAffectedByGravity(false);
	wText->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(wText);

	Model* eText = new Model();
	eText->LoadModel(".\\Models\\e.obj");
	eText->SetColor(Color(0, 0, 1));
	eText->SetPosition(Vector3D(7.5f, -2.f, 1.5f));
	eText->SetIsAffectedByGravity(false);
	eText->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(eText);

	Model* rText = new Model();
	rText->LoadModel(".\\Models\\r.obj");
	rText->SetColor(Color(0, 1, 1));
	rText->SetPosition(Vector3D(11.5f, -2.f, 1.5f));
	rText->SetIsAffectedByGravity(false);
	rText->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(rText);
	//-------------------------------------------------------

	ScoreManager* scrManager = new ScoreManager();
	if (scrManager)
		mainScene->SetScoreMgr(scrManager);

	mainScene->SetPlayername(playername);

	return mainScene;
}

GHScene* GHGame::LoadTitleScene()
{

	GHScene* mainScene = new(nothrow) GHScene();
	FlyingCamera mainCamera = mainScene->GetCamera();
	mainScene->AddCamera(mainCamera);

	Model* titleText = new Model();
	titleText->LoadModel(".\\Models\\title.obj");
	titleText->SetColor(Color(0.5f, 1.f, 1));
	titleText->SetPosition(Vector3D(-4.f, 6.f, 2.f));
	titleText->SetIsAffectedByGravity(false);
	titleText->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(titleText);

	Model* guitar = new Model();
	guitar->LoadModel(".\\Models\\guitar.obj");
	guitar->SetColor(Color(0.7f, 0.7f, 0.7f));
	guitar->SetPosition(Vector3D(5.f, 12.f, -6.f));
	guitar->SetOrientationSpeed(Vector3D(0.f, 0.3f, 0.f));
	guitar->SetIsAffectedByGravity(false);
	guitar->SetSpeed(Vector3D(0.f, 0.f, 0.f));
	mainScene->AddGameObject(guitar);

	mainScene->SetTitle(true);

	return mainScene;
}

void GHGame::BackToTitle()
{
	activeScene = scenes[0];
	//Descargo la escena de la canción anterior. Siempre habrá 2 máximo, título y una cargada. Si hay más de una, borro la segunda.
	if (scenes.size() > 1)
		scenes.erase(scenes.begin() + 1);
}

void GHGame::ProcessMouseClick(const int& button, const int& state, const int& xPosition, const int& yPosition)
{
	this->activeScene->ProcessMouseClick(button, state, xPosition, yPosition);
}