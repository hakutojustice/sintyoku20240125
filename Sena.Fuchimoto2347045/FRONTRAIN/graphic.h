#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include "DxLib.h"

#define GraFxInfinity    -99999 //�����p��

//�G���[
#define ImageLoadErrCap   "���ǂݍ��݂܂���ł���"
#define ImageLoadErrTitle  "�摜�ǂݍ��݃G���["

//������̒���
#define ImagePathStrMax 256
#define ImageErrStrMax 512

//�摜�t�@�C���̃p�X
#define GraphicPathTitleButton

//�񋓌^
enum Graphic_Align
{
	GraAlignTopL,   //�摜�̊�_�ŏ㍶����
	GraAlitnTopC,   //�摜�̊�_�ŏ㒆������
	GraAlignTopR,   //�摜�̊�_�ŏ�E����

	GraAlignBottomL,  //�摜�̊�_�ŉ�������
	GraAlignBottomC,  //�摜�̊�_�ŉ���������
	GraAlignBottomR,  //�摜�̊�_�ŉ��E����

	GraAlignAllCenter,  //�摜�̊�_�ŏ㉺�����E����������
};

//�`��̌���
enum Graphic_Fx
{
	GraFxBlink,  //�_��
	GraFxFadeIn,  //�����`�s����
	GraFxFadeOut,   //�s����������
	GraFxFadeInOut,   //�s������������
	GraFxNone   //�ʏ�`��
};

//�摜�\���̂̃R�A����
typedef struct _GraphicCore
{
	char Path[ImagePathStrMax];   //�p�X

	POINT pos;    //�摜�̊�_(�ʏ�͍���)
	int Width = 0;   //��
	int Height = 0;  //����

	RECT Coll;      //��`�̓����蔻��
	RECT CollMargin;  //��`�̓����蔻������߂�

	Graphic_Align Align = GraAlignTopL; //��������

	float Rate = 1.0f;      //�g�嗦
	float Angle = 0.0f;     //�p�x

	BOOL IsDraw = FALSE;    //�`�悷�邩?

	BOOL IsFxStartFlg = FALSE;  //�`��G�t�F�N�g�t���O
	Graphic_Fx Fx = GraFxNone;   //�`��G�t�F�N�g�̎��
	int FxMillTime = 0;    //�G�t�F�N�g���ԃJ�E���g
	int FxMillTimeMax = 0;   //�G�t�F�N�g���ԃJ�E���gMAX
	int FxInterMillTime = 0;  //�G�t�F�N�g���ԃJ�E���g
	int FxInterMillTimeMax = 0;  //�G�t�F�N�g���ԃJ�E���gMAX
	float Alpha = 0.0f;   //�����x(0.0�`1.0�����邱��)
}GraphicCore;

//�摜�\����
typedef struct _Graphic
{
	GraphicCore c;     //�R�A
	int Handle = -1;   //�n���h��
}Graphic;

//�O���O���[�o���ϐ�
extern Graphic TitleButton;  //�^�C�g���{�^��

//�O���v���g�^�C�v�錾
extern BOOL Graphic_Init(VOID);     //�ǂݍ��݁E�n���h������
extern VOID Graphic_End(VOID);     //��n��
extern VOID GraphicLoadErrMessage(const char* path);   //�ǂݍ��݃G���[���b�Z�[�W

extern Graphic LoadGraphic(const char* path, POINT point, RECT margin, Graphic_Align align);  //�ǂݍ���
extern VOID DrawGraphic(Graphic* graphic);       //�`��
extern VOID DeleteGraphic(Graphic graphic);      //���

extern VOID ReMakeCollRect(Graphic* graphic);    //�����蔻��̋�`���Đ���

extern VOID GraphicFxStart(Graphic* graphic, Graphic_Fx Fx, int MillTime, int MillInterval);   //�G�t�F�N�g�J�n
