#include "texture.h"
//============================
//�}�N����`
//============================
#define MAX_TEXTURE_NUM 100		//���[�h���E��


//===============================
//�O���[�o���ϐ�
//===============================
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];	//�e�N�X�`�����̃|�C���^�̔z��

static UINT g_TextureIndex;		//���[�h�ς݂̃e�N�X�`���[��

static char g_TextureName[MAX_TEXTURE_NUM][256];	//�e�N�X�`���t�@�C�����̃o�b�t�@�@�t�@�C����255�����܂�



int TextureNo = 0;

void InitTexture()
{
	TextureNo = 0;
	if (TextureNo == -1)
	{
		exit(999);	//�����I��
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



//�e�N�X�`���֘A

//______________________________________________________________
//|�w��̃e�N�X�`�������擾									|
//|In�F�g�p�������e�N�X�`���n���h��								|
//|Out�F�e�N�X�`�����̃|�C���^�̓������|�C���^�ϐ��̃|�C���^__|
ID3D11ShaderResourceView ** GetTexture(int index)
{
	//�G���[�`�F�b�N
	if (index < 0 || index >= g_TextureIndex)//0�����@�b�b�@���[�h���I�[�o�[
	{
		return NULL;
	}

	return &g_pTexture[index];
}

//_______________________________________________
//|In�F�e�N�X�`���t�@�C�����̐擪�|�C���^	     |
//|Out�F���[�h�����e�N�X�`���n���h��_____________|
int LoadTexture(char * filename)
{
	//���łɓǂݍ��܂ꂽ�e�N�X�`�����𒲂ׂē����̃e�N�X�`�������ۑ������ꍇ�́A�e�N�X�`�����̊i�[���ꂽ�z��̔ԍ���Ԃ�
	for (int i = 0; i < g_TextureIndex; i++)
	{//�e�N�X�`�������r
		if (strcmp(&g_TextureName[i][0], filename) == 0)	//&g_TextureName[i][0] �� g_TextureName[i]
		{
			return i;
		}
	}
	//�ǂݍ��ݐ������E�𒴂��Ă��Ȃ����H
	if (g_TextureIndex >= MAX_TEXTURE_NUM)
	{
		return -1;	//�G���[�R�[�h��Ԃ�
	}

	//�e�N�X�`���̃��[�h
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(GetDevice(), filename, NULL, NULL, &g_pTexture[g_TextureIndex], NULL);
	if (hr != S_OK)
	{
		return -1;			
	}

	//���[�h�����e�N�X�`�����̓o�^
	strcpy_s(g_TextureName[g_TextureIndex], 256, filename);
	g_TextureIndex++;

	return (g_TextureIndex - 1);

	return g_TextureIndex;
}