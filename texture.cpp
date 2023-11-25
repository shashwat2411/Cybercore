#include "texture.h"
//============================
//マクロ定義
//============================
#define MAX_TEXTURE_NUM 100		//ロード限界数


//===============================
//グローバル変数
//===============================
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];	//テクスチャ情報のポインタの配列

static UINT g_TextureIndex;		//ロード済みのテクスチャー数

static char g_TextureName[MAX_TEXTURE_NUM][256];	//テクスチャファイル名のバッファ　ファイル名255文字まで



int TextureNo = 0;

void InitTexture()
{
	TextureNo = 0;
	if (TextureNo == -1)
	{
		exit(999);	//強制終了
	}
}

void UnInitTexture()
{
	for (int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
	
}


void SetTexture(int Texture)
{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(Texture));
}



//テクスチャ関連

//______________________________________________________________
//|指定のテクスチャ情報を取得									|
//|In：使用したいテクスチャハンドル								|
//|Out：テクスチャ情報のポインタの入ったポインタ変数のポインタ__|
ID3D11ShaderResourceView ** GetTexture(int index)
{
	//エラーチェック
	if (index < 0 || index >= g_TextureIndex)//0未満　｜｜　ロード数オーバー
	{
		return NULL;
	}

	return &g_pTexture[index];
}

//_______________________________________________
//|In：テクスチャファイル名の先頭ポインタ	     |
//|Out：ロードしたテクスチャハンドル_____________|
int LoadTexture(char * filename)
{
	//すでに読み込まれたテクスチャ名を調べて同名のテクスチャ名が保存した場合は、テクスチャ名の格納された配列の番号を返す
	for (int i = 0; i < g_TextureIndex; i++)
	{//テクスチャ名を比較
		if (strcmp(&g_TextureName[i][0], filename) == 0)	//&g_TextureName[i][0] → g_TextureName[i]
		{
			return i;
		}
	}
	//読み込み数が限界を超えていないか？
	if (g_TextureIndex >= MAX_TEXTURE_NUM)
	{
		return -1;	//エラーコードを返す
	}

	//テクスチャのロード
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(GetDevice(), filename, NULL, NULL, &g_pTexture[g_TextureIndex], NULL);
	if (hr != S_OK)
	{
		return -1;			
	}

	//ロードしたテクスチャ名の登録
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);
	g_TextureIndex++;

	return (g_TextureIndex - 1);

	return g_TextureIndex;
}