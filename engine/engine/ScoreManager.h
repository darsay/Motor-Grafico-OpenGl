#pragma once
#include <string>

using namespace std;

class ScoreManager{

public:
	int puntos;
	float mult;
	int racha;

	ScoreManager() : puntos(0), mult(1), racha(0) {};
	inline int getPuntos() const { return puntos; }
	inline float getMult() const { return mult; }
	inline float getRacha() const { return racha; }

	inline void setPuntos(const int& ptsToSet) { puntos = ptsToSet; }
	inline void setMult(const int& multToSet) { mult = multToSet; }
	inline void setRacha(const int& rachaToSet) { racha = rachaToSet; }
	
	void Log();
	void Save(string playername);

	int sumarPuntos();
	void fallo();

private:
	
	float sumarMult();

};

