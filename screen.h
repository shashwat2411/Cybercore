#pragma once
#include "main.h"
#include "renderer.h"

enum SCENE
{
	SCENE_NONE = 0,
	SCENE_MAIN,
	SCENE_GAME,
	SCENE_RESULT,

	SCENE_MAX
};

HRESULT InitScene(SCENE ScreenNo);
void UnInitScene();
void DrawScene();
void UpdateScene();

void SetScene(SCENE No);
void CheckScene();