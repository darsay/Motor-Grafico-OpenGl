#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Sphere.h"
#include "Note.h"



class Song {
public:
	enum SongName
	{
		SmokeEasy,
		Smell,
		Smoke

	};

	Song();
	Song(SongName name);
	~Song();
	bool Load(SongName name);
	void Unload();
	bool Play();
	int NextNote();
	inline float GetNoteTime(const int note) const { if(note<noteCount) return notes[note].GetTime(); };
	inline int GetNoteNum(const int noteNum) const { return notes[noteNum].GetNote(); };
	inline int GetNoteCount()const {return noteCount;};
	inline int GetActualNoteNum()const { return actualNote;};
	inline Sphere* GetNoteGO(const int note)const { return notes[note].GetGO();};
	
	

private:
	

	Note *notes;
	int noteCount;
	int actualNote;

	LPCWSTR LoadToken;
	LPCWSTR PlayToken;
};