#pragma once
#include "Sphere.h"

class Note
{
private:
		float time;
		int note;
		Sphere* sphPtr;

public:
	Note() : sphPtr(nullptr), time(0.f), note(0) {}

	inline int GetNote() const { return note; };
	inline float GetTime() const { return time; };
	inline Sphere* GetGO() const { return sphPtr;};

	inline void SetNote(const int& noteToSet) { this->note = noteToSet; }
	inline void SetTime(const float& timeToSet) { this->time = timeToSet; }
	inline void SetGO(Sphere* GOToSet) { this->sphPtr = GOToSet; }
};

