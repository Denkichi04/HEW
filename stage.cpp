#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "stage.h"
#include "player.h"
#include <time.h>
#include <stdlib.h>


#define BGNUM 5
#define UISIZE 270
#define MAXCOUNT 3	//���X�e�[�W�i�񂾂�S�[��

/*float x1;//�X�N���[���e�N�X�`��1�̈ʒu
float x2;//�X�N���[���e�N�X�`��2�̈ʒu
bool flg1;//�X�N���[���e�N�X�`��1�𓮂����t���O
bool flg2;//�X�N���[���e�N�X�`��2�𓮂����t���O
bool flg_bgchange1, flg_bgchange2;
int bgnum1, bgnum2;*/

int field1count;//�X�N���[�������������J�E���g
static bool StopScroll;
static int count;
static bool GetReady;

typedef struct
{
	D3DXVECTOR2 pos; //�X�N���[���e�N�X�`���̈ʒu
	float speed;
	int	  type;	//�t�B�[���h�̎�� 0:�ʏ� 1:�@2:��
	bool flg_move; // �X�N���[���e�N�X�`���𓮂����t���O
	bool flg_change;// �X�N���[���e�N�X�`����ϊ�����t���O

}FIELD_DATA;

FIELD_DATA field[2];

void Field1_Initialize(void)
{
	//�����ʒu��ݒ�
	field[0].pos.x = 0;
	field[1].pos.x = 0;
	field[0].pos.y = 0 - UISIZE;
	field[1].pos.y = -1080 - UISIZE;

	field[0].flg_move = 1;
	field[1].flg_move = 1;
	field[0].flg_change = 0;
	field[1].flg_change = 1;
	field[0].type = 0;
	field[1].type = (rand() % BGNUM - 2) + 1;
	field[0].speed = 5;
	field[1].speed = 5;

	srand((unsigned int)time(NULL));

	field1count = 0;
	StopScroll = 1;
	count = 0;
	GetReady = 0;
}


void Field1_Update(void)
{
	count++;

	if (count == 100)
	{
		StopScroll = 0;
	}

	if (field[0].flg_change == 1)
	{
		field[0].type = (rand() % (BGNUM - 2)) + 1;//BG1�������_�����I
		field[0].flg_change = 0;
		field1count++;
	}
	if (field[1].flg_change == 1)
	{
		field[1].type = (rand() % (BGNUM - 2)) + 1;//BG2�������_�����I
		field[1].flg_change = 0;
		field1count++;
	}

	if (field1count == MAXCOUNT)
	{
		field[1].type = 4;
	}


	//if (StopScroll == 0)
	//{
	//	field[0].speed = field[0].speed + GetPlayerSpeed();
	//	field[1].speed = field[1].speed + GetPlayerSpeed();
	//	/*MinuPlayerSpeed(GetPlayerSpeed());*/
	//}

}

void Field1_Finalize(void)
{

}

void Field1_Draw(void)
{
	if (field[0].flg_move == 1)
	{
		if (StopScroll == 0)
			field[0].pos.y = field[0].pos.y + field[0].speed;
		switch (field[0].type)
		{
		case 0:Sprite_Draw(TEXTURE_INDEX_STAGE_START, 0, field[0].pos.y);
			break;
		case 1:Sprite_Draw(TEXTURE_INDEX_STAGE1, 0, field[0].pos.y);
			break;
		case 2:Sprite_Draw(TEXTURE_INDEX_STAGE2, 0, field[0].pos.y);
			break;
		case 3:Sprite_Draw(TEXTURE_INDEX_STAGE3, 0, field[0].pos.y);
			break;
		case 4:Sprite_Draw(TEXTURE_INDEX_STAGE_END, 0, field[0].pos.y);
			break;
		}
		if (field[0].pos.y > 0 - UISIZE)
		{
			field[1].flg_move = 1;
		}
		if (field[0].pos.y > 1080 - UISIZE)
		{
			field[0].pos.y = -1080 + field[0].speed - UISIZE;
			field[0].flg_change = 1;
			field[0].flg_move = 0;
		}

		if (field[0].type == 4 && field[0].pos.y > 0)
		{
			field[0].pos.y = 0;
			StopScroll = 1;
		}
	}

	if (field[1].flg_move == 1)
	{
		if (StopScroll == 0)
			field[1].pos.y = field[1].pos.y + field[1].speed;
		switch (field[1].type)
		{
		case 0:Sprite_Draw(TEXTURE_INDEX_STAGE_START, 0, field[1].pos.y);
			break;
		case 1:Sprite_Draw(TEXTURE_INDEX_STAGE1, 0, field[1].pos.y);
			break;
		case 2:Sprite_Draw(TEXTURE_INDEX_STAGE2, 0, field[1].pos.y);
			break;
		case 3:Sprite_Draw(TEXTURE_INDEX_STAGE3, 0, field[1].pos.y);
			break;
		case 4:Sprite_Draw(TEXTURE_INDEX_STAGE_END, 0, field[1].pos.y);
			break;
		}
		if (field[1].pos.y > 0 - UISIZE)
		{
			field[0].flg_move = 1;
		}
		if (field[1].pos.y > 1080 - UISIZE)
		{
			field[1].pos.y = -1080;
			field[1].flg_change = 1;
			field[1].flg_move = 0;
		}

		if (field[1].type == 4 && field[1].pos.y > 0)
		{
			field[1].pos.y = 0;
			StopScroll = 1;
		}
	}
}

int GetField1Type1()
{
	return field[0].type;
}
int GetField2Type1()
{
	return field[1].type;
}
int GetField1X1()//�X�N���[�����̃t�B�[���h�̈ʒu(���W)���擾
{
	return field[0].pos.y;
}
int GetField2X1()
{
	return field[1].pos.y;
}
int Field1IsGoal()
{
	return StopScroll;
}