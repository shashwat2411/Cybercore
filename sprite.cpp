#include "sprite.h"

#define NUM_TRIANGLE_VERTEX 4

static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;

int count = 0;

void InitTriangle()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_TRIANGLE_VERTEX;//頂点1個＊頂点数のサイズで作る
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
	//三角形用頂点格納処理

}

void UnInitTriangle()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//使い終わったので解放する
		g_VertexBufferTriangle = NULL;
	}
}

void DrawTriangle()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void UpdateTriangle()
{

}

void DrawSpriteColorRotate(float posX, float posY, int size_w, int size_h, float kakudo, D3DXCOLOR color, int* ImageNum, float* offsetX, float* offsetY, float yoko, float tate, float yoko_num, int flip, bool animate)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	static int imageNum = 0;
	imageNum = *ImageNum;

	float z = 0.0f;
	count += 1;

	vertex[0].Position = D3DXVECTOR3(-size_w / 2, -size_h / 2, z);
	vertex[1].Position = D3DXVECTOR3(+size_w / 2, -size_h / 2, z);
	vertex[2].Position = D3DXVECTOR3(-size_w / 2, +size_h / 2, z);
	vertex[3].Position = D3DXVECTOR3(+size_w / 2, +size_h / 2, z);

	vertex[0].Diffuse = color;
	vertex[1].Diffuse = color;
	vertex[2].Diffuse = color;
	vertex[3].Diffuse = color;

	vertex[0].TexCoord = D3DXVECTOR2(*offsetX, *offsetY);
	vertex[1].TexCoord = D3DXVECTOR2(yoko + *offsetX, *offsetY);
	vertex[2].TexCoord = D3DXVECTOR2(*offsetX, tate + *offsetY);
	vertex[3].TexCoord = D3DXVECTOR2(yoko + *offsetX, tate + *offsetY);


	if (flip == 1)
	{
		VERTEX_3D Temp;
		Temp.TexCoord = vertex[0].TexCoord;
		vertex[0].TexCoord = vertex[1].TexCoord;
		vertex[1].TexCoord = Temp.TexCoord;

		Temp.TexCoord = vertex[2].TexCoord;
		vertex[2].TexCoord = vertex[3].TexCoord;
		vertex[3].TexCoord = Temp.TexCoord;
	}

	if (animate == true)
	{
		SpriteSheet(offsetX, offsetY, &imageNum, yoko_num, yoko, tate, count, 5);
		*ImageNum = imageNum;
	}

	float rad = D3DXToRadian(kakudo);

	for (int i = 0; i < 4; i++)
	{
		float X = ((vertex[i].Position.x * cosf(rad)) - (vertex[i].Position.y * sinf(rad)));
		float Y = ((vertex[i].Position.x * sinf(rad)) + (vertex[i].Position.y * cosf(rad)));
		vertex[i].Position.x = posX + X;
		vertex[i].Position.y = posY + Y;
		vertex[i].Position.z = 0.0f;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了
}


void SpriteSheet(float * X, float * Y, int * imageNum, int yoko_num, float yoko, float tate, int count, int frame)
{
	if (count % frame == 0)
	{
		*X = ((*imageNum) % yoko_num) * yoko;
		*Y = ((*imageNum) / yoko_num) * tate;
		(*imageNum) += 1;
	}
}

float generateRandom(float min, float max) 
{
	float difference = max - min;

	float random = rand() % 2;

	random = floor(random * difference);
	random = random + min;

	return random;
}

