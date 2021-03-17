#include "TitleScene.h"


void TitleScene::ProcessMouseMovement(const int& x, const int& y)
{

}
void TitleScene::ProcessMouseClick(const int& button, const int& state, const int& x, const int& y)
{

}
void TitleScene::ProcessKeyPressed(unsigned char key, int px, int py)
{
	if(key >48 && key < 52) //Si las teclas son 1, 2, 3
		game.LoadGameScene(key - 48);

}
