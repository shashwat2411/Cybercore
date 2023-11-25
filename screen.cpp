#include "screen.h"
#include "polygon.h"
#include "game.h"
#include "title.h"
#include "result.h"

static SCENE g_SceneIndex = SCENE::SCENE_NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

HRESULT InitScene(SCENE ScreenNo)
{
	g_SceneIndex = g_SceneNextIndex = ScreenNo;
	InitPolygon();		//�|���S���̏����������s

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;
	case SCENE_MAIN:
		InitTitle();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	default:
		exit(999);
		break;
	}

	return S_OK;
}

void UnInitScene()
{
	UninitPolygon();

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;
	case SCENE_MAIN:
		UnInitTitle();
		break;
	case SCENE_GAME:
		UnInitGame();
		break;
	case SCENE_RESULT:
		UnInitResult();
		break;
	default:
		exit(999);
		break;
	}
}

void DrawScene()
{
	DrawPolygon();	//�|���S���̍X�V����

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;
	case SCENE_MAIN:
		DrawTitle();
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	default:
		exit(999);
		break;
	}
}

void UpdateScene()
{
	UpdatePolygon();	//�|���S���̍X�V����

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;
	case SCENE_MAIN:
		UpdateTitle();
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	default:
		exit(999);
		break;
	}
}

void SetScene(SCENE No)
{
	g_SceneNextIndex = No;
}

void CheckScene()
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		UnInitScene();
		InitScene(g_SceneNextIndex);
	}
}