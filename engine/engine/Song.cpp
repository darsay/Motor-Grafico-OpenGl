#include "Song.h"
#include <fstream>
#include <iostream>
#include "Color.h"

using namespace std;

Song::Song()
{
	notes = NULL;
	noteCount = 0;
}

Song::Song(SongName name)
{
	notes = NULL;
	noteCount = 0;
	Load(name);
}

Song::~Song()
{
	Unload();
}

bool Song::Load(SongName name)
{
	string filename;
	switch (name)
	{
	case SongName::Smoke:
		filename = ".\\Songs\\t3.txt";
		LoadToken = L"open \".\\Music\\smoke.mp3\" type mpegvideo alias mp3";
		PlayToken = L"play .\\Music\\smoke.mp3";
		break;
	case SongName::SmokeEasy:
		filename = ".\\Songs\\t1.txt";
		LoadToken = L"open \".\\Music\\smoke.mp3\" type mpegvideo alias mp3";
		PlayToken = L"play .\\Music\\smoke.mp3";
		break;
	case SongName::Smell:
		filename = ".\\Songs\\t2.txt";
		LoadToken = L"open \".\\Music\\gh2.mp3\" type mpegvideo alias mp3";
		PlayToken = L"play .\\Music\\gh2.mp3";
		break;
	}

	
	ifstream file(filename);
		
	if (file.is_open())																	//(Comprobación tipo para fstream, aunque esté el try-catch)
	{
		//Carga de la parte de fichero
		file >> noteCount;
		notes = new Note[noteCount];

		for (int i = 0; i < noteCount; i++)
		{
			//Se leen valores de nota y tiempo
			int note;
			float time;
			file >> note >> time;

			//Se genera un color dependiendo de la nota
			Color color;
			switch (note)
			{
			case 0:
				color = Color((1.f), (0.f), (0.f));
				break;
			case 1:
				color = Color((0.f), (1.f), (0.f));
				break;
			case 2:
				color = Color((0.f), (0.f), (1.f));
				break;
			case 3:
				color = Color((0.f), (1.f), (1.f));
				break;
			}
			//Se genera un GameObject, en este caso una esfera, con el color calculado y posición con offset= nota (las notas van de 0 a 3)
			Sphere* sphPtr= new(nothrow) Sphere(
				Vector3D((note*4.f), (21.f), (1.f)),
				color,
				Vector3D((0.0), (-0.28), (0.0)),
				Vector3D(),
				1);
			sphPtr->SetIsAffectedByGravity(false);
			//Una vez generados todos los datos, se le asignan a la nota
			notes[i].SetNote(note);
			notes[i].SetTime(time);
			notes[i].SetGO(sphPtr);
		}
		file.close();
		//Carga del archivo de sonido
		int error1 = mciSendString(LoadToken, NULL, 0, NULL);
			
		//Si se carga bien todo, devolverá true
		return (error1==0?true:false);
	}
	
	
	return false;
}

void Song::Unload()
{
	if (notes)
	{
		for (int i = 0; i < noteCount; i++)
		{
			delete notes[i].GetGO();
		}
		delete[] notes;
	}
}

bool Song::Play()
{
	if (noteCount)																			//Si se ha cargado la canción con anterioridad noteCount no es 0, ergo no es false
	{
		int error2 = mciSendString(PlayToken, NULL, 0, NULL);
		if (error2 == 0)
			return true;
	}
	return false;
}

int Song::NextNote()
{
	if (actualNote < noteCount)
		actualNote++;
	else
		actualNote = -1;

	return actualNote;
}