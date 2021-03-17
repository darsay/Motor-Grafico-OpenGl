#include "GHScene.h"
#include "Song.h"

void GHScene::Update(const float& time)
{
	//Se aplica la gravedad a todos
	for (int idx = 0; idx < this->gameObjects.size(); idx++)
		this->gameObjects[idx]->Update(time, this->GetGravity());


	//Si no es título y no se está reproduciendo, se pone en marcha
	if (!bPlaying && !bAmITitle)
		bPlaying = songs[activeSong]->Play();

	//Si se está reproduciendo...
	if (bPlaying)
	{
		//Para que coincida el tiempo con el de la nota, se establece un ritmo y se le suma al tiempo total de reproducción del juego
		timePlaying += time/24.19;
		//Las notas se instanciarán si se llega al tiempo establecido y quedan notas
		if (songs[activeSong]->GetActualNoteNum() < songs[activeSong]->GetNoteCount() && (timePlaying >= songs[activeSong]->GetNoteTime(songs[activeSong]->GetActualNoteNum()) - TIME_OFFSET))
		{
			this->AddGameObject(songs[activeSong]->GetNoteGO(songs[activeSong]->GetActualNoteNum()));
			this->songs[activeSong]->NextNote();
		}
		
		//Si la última nota se ha creado, sumo el tiempo al contador de salida
		if (songs[activeSong]->GetActualNoteNum() == songs[activeSong]->GetNoteCount())
		{
			//Se suma tiempo al contador de salida
			this->timeToEnd += time / 24.19;
			//Si el tiempo supera los 20
			if (timeToEnd >= 20)
			{
				this->manager->Save(this->playerName);
				bPlaying = false;
				bFinished = true;

			}
		}
		
		//Limpieza de las notas que se han ido para abajo sin ser tocadas
		for (int i = 0; i < this->gameObjects.size(); i++)
		{
			if (gameObjects[i]->GetPosition().GetY() < -20)
			{
				gameObjects.erase(gameObjects.begin() + i);//Borro el GO
			}
		}
	}
}

void GHScene::Render()
{
	cameras[activeCam].Render();

	// tres formas de recorrer el vector de s�lidos
	//1.- bucle for con �ndice comprobando con el tama�o del vector
	for (int idx = 0; idx < this->gameObjects.size(); idx++)
	{
		this->gameObjects[idx]->Render();
	}
}

void GHScene::AddGameObject(GameObject* object)
{
	this->gameObjects.push_back(object);
}

void GHScene::AddSong(Song* song)
{
	this->songs.push_back(song);
}

void GHScene::ProcessMouseClick(const int& button, const int& state, const int& x, const int& y)
{
	if (this->activeCam == 0)
		SetCamera(1);
	else
		SetCamera(0);

}

void GHScene::ProcessKeyPressed(unsigned char key, int px, int py)
{
	bool bFound = false;
	float fNoteOffset = -4.f; //Establecemos un valor imposible para que encuentre la nota
	
	//Dependiendo de la tecla pulsada pone la posición X debajo de la columna correspondiente
	key = tolower(key);
	switch (key)
	{
	case 'q':
		fNoteOffset = 0.f;
		break;
	case 'w':
		fNoteOffset = 4.f;
		break;
	case 'e':
		fNoteOffset = 8.f;
		break;
	case 'r':
		fNoteOffset = 12.f;
		break;
	}
	
	//Comprueba que haya algún GO en la columna que hemos seleccionado y a la altura 0, ambas con un margen de error
	for (int i = 4; i < gameObjects.size(); i++)
		if (this->gameObjects[i]->GetPosition().GetY() > -1.f && this->gameObjects[i]->GetPosition().GetY() < 1.f && //Si hay una nota en el toroide en Y
			this->gameObjects[i]->GetPosition().GetX() > -0.2f + fNoteOffset && this->gameObjects[i]->GetPosition().GetX() < 0.2f + fNoteOffset && //también en X
			this->gameObjects[i]->GetPosition().GetZ() == 1.f) //Utilizo de LayerMask la Z, puesto que las bolas son las únicas con 1
		{
			manager->sumarPuntos();	//Si está, sumo puntos			
			this->gameObjects.erase(gameObjects.begin()+i);//Borro el GO
			bFound = true;//Marco como encontrado

		}

	//Si no se ha encontrado, fallo.
	if (!bFound)
	{
		manager->fallo();
	}

	manager->Log();
}

void GHScene::SetCamera(int camIndex)
{
	if (camIndex<this->cameras.size())
	{
		maincam = cameras[camIndex];
		activeCam = camIndex;
	}
}

void GHScene::AddCamera(FlyingCamera cam, bool isMain)
{
	cameras.push_back(cam);
	if (isMain)
		SetCamera(cameras.size() - 1);
}

GHScene::~GHScene()
{
	if (manager)
		delete manager;
	
	for (int i = 0; i < songs.size(); i++)
		delete songs[i];

	if (!songs.empty())
		songs.clear();
}