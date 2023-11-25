
#include	"LineCircle.h"

//プロトタイプ宣言


#define VERTEXES 16
#define RADIUS 250.0f
//グローバル変数
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// 頂点情報
//static -> you can use a global variable even if there is another global variable in another file
//================================
//
//=================================
void	InitLineCircle()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * (VERTEXES + 1);//頂点1個＊頂点数のサイズで作る
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
	// 頂点バッファ更新
	D3DXVECTOR3	pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	SetVertexCircle(pos, RADIUS, VERTEXES);
}

//================================
//
//=================================
void	UnInitLineCircle()
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//使い終わったので解放する
		g_VertexBuffer = NULL;
	}

}

//================================
//
//=================================
void	DrawLineCircle()
{
	// 表示したいポリゴンの頂点バッファを設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	//表示処理
	D3DXVECTOR3	pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	SetVertexCircle(pos, RADIUS, VERTEXES);

	//startposX = cosf(D3DXToRadian(Kakudo)) * 100.0f;//開始座標を適当に変更する
	//startposY = sinf(D3DXToRadian(Kakudo)) * 100.0f;

	// ポリゴン描画
	GetDeviceContext()->Draw((VERTEXES+1), 0);

}

//================================
//
//=================================
void	UpdateLineCircle()
{

}


//=============================================================================
// 頂点データ設定
//
//in
// 開始座標, 終了座, カラー
//
//=============================================================================
void SetVertexCircle(D3DXVECTOR3 Position, float radius, int vertexN)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float angle = 0.0f;
	D3DXCOLOR color = (0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < vertexN; i++)
	{
		vertex[i].Position.x = (cosf(D3DXToRadian(angle)) * radius) + Position.x;
		vertex[i].Position.y = (sinf(D3DXToRadian(angle)) * radius) + Position.y;
		vertex[i].Position.z = Position.z;
			
		vertex[i].Diffuse = color;
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		color.r += 0.01f;
		color.g += 0.05f;
		color.b += 0.1f;
		color.a = 1.0f;
		angle += (360.0f / VERTEXES);
	}

	vertex[vertexN] = vertex[0];

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}