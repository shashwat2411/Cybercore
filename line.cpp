#include "line.h"

#define NUM_VERTEX 2
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// 頂点情報

void InitLine()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//頂点1個＊頂点数のサイズで作る
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
	// 頂点バッファ更新
	D3DXVECTOR3 start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 end = D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
	D3DXCOLOR colorS = D3DXCOLOR(1.0, 0.0f, 1.0f, 1.0f);
	D3DXCOLOR colorE = D3DXCOLOR(0.0, 1.0f, 1.0f, 1.0f);
	SetVertex(start, end, colorS, colorE);
}

void UnInitLine()
{
	// 頂点バッファの解放
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//使い終わったので解放する
		g_VertexBuffer = NULL;
	}
}

void DrawLine()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// ２Ｄ表示をするためのマトリクスを設定
	
	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);// LINELIST);

	
}

void UpdateLine()
{

}

void SetVertex(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR colorStart, D3DXCOLOR colorEnd)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//一本目の直線の頂点をセット
	vertex[0].Position = start;
	vertex[0].Diffuse = colorStart;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = end;
	vertex[1].Diffuse = colorEnd;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//二本目の直線の頂点をセット

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
