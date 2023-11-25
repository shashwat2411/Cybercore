
#include	"LineCircle.h"

//�v���g�^�C�v�錾


#define VERTEXES 16
#define RADIUS 250.0f
//�O���[�o���ϐ�
static	ID3D11Buffer		*g_VertexBuffer = NULL;		// ���_���
//static -> you can use a global variable even if there is another global variable in another file
//================================
//
//=================================
void	InitLineCircle()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * (VERTEXES + 1);//���_1�����_���̃T�C�Y�ō��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);
	// ���_�o�b�t�@�X�V
	D3DXVECTOR3	pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	SetVertexCircle(pos, RADIUS, VERTEXES);
}

//================================
//
//=================================
void	UnInitLineCircle()
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();//�g���I������̂ŉ������
		g_VertexBuffer = NULL;
	}

}

//================================
//
//=================================
void	DrawLineCircle()
{
	// �\���������|���S���̒��_�o�b�t�@��ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	//�\������
	D3DXVECTOR3	pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	SetVertexCircle(pos, RADIUS, VERTEXES);

	//startposX = cosf(D3DXToRadian(Kakudo)) * 100.0f;//�J�n���W��K���ɕύX����
	//startposY = sinf(D3DXToRadian(Kakudo)) * 100.0f;

	// �|���S���`��
	GetDeviceContext()->Draw((VERTEXES+1), 0);

}

//================================
//
//=================================
void	UpdateLineCircle()
{

}


//=============================================================================
// ���_�f�[�^�ݒ�
//
//in
// �J�n���W, �I����, �J���[
//
//=============================================================================
void SetVertexCircle(D3DXVECTOR3 Position, float radius, int vertexN)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
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