#include "line.h"

#define NUM_VERTEX 2
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// ���_���

void InitLine()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//���_1�����_���̃T�C�Y�ō��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
	// ���_�o�b�t�@�X�V
	D3DXVECTOR3 start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 end = D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
	D3DXCOLOR colorS = D3DXCOLOR(1.0, 0.0f, 1.0f, 1.0f);
	D3DXCOLOR colorE = D3DXCOLOR(0.0, 1.0f, 1.0f, 1.0f);
	SetVertex(start, end, colorS, colorE);
}

void UnInitLine()
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//�g���I������̂ŉ������
		g_VertexBuffer = NULL;
	}
}

void DrawLine()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	
	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);// LINELIST);

	
}

void UpdateLine()
{

}

void SetVertex(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR colorStart, D3DXCOLOR colorEnd)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[0].Position = start;
	vertex[0].Diffuse = colorStart;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = end;
	vertex[1].Diffuse = colorEnd;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//��{�ڂ̒����̒��_���Z�b�g

	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
}
