#include "ScoreManager.h"
#include <iostream>
#include <fstream>
using namespace std;

int ScoreManager::sumarPuntos() {
	if (racha % 5 == 0 && racha!=0) {
		sumarMult();
	}
	racha++;
	puntos += 10 * mult;
	return puntos;
}

float ScoreManager::sumarMult() {
	mult+=0.5;
	return mult;
}

void ScoreManager::fallo() {
	racha = 0;
	mult = 1;
}

void ScoreManager::Log()
{
	cout << "Puntos: " << puntos << ". Racha de notas: " << racha << ". Multiplicador actual: " << mult << endl;
}

void ScoreManager::Save(string playername)
{
	ofstream file("scores.txt", std::ios_base::app); //Modo append para que no sustituya el fichero de puntos

	if (file.is_open())
	{
		file << "Jugador: " << playername << ". Puntuación total: " << puntos << endl;
		cout << "Puntuacion grabada en scores.txt." << endl;
		file.close();
	}
	else
	{
		cout << "Error abriendo fichero para añadir las puntuaciones." << endl;
	}
}