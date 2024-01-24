//#pragma once
////�A�j���[�V���������̃w�b�_�t�@�C��
//
////�w�b�_�t�@�C���ǂݍ���
//#include "DxLib.h"
//#include "graphic.h"
//#include "SkyEnemy.h"
//#include "DistanceEnemy.h"
//
////�G���[
//#define AnimationLoadErrCap   "���ǂݍ��ߖ�������"
//#define AnimationLoadErrTitle  "�A�j���[�V�����G���["
//
////������̒���
//#define AnimationPathStrMax 256
//#define AnimationErrStrMax 512
//
////�A�j���[�V�����t�@�C���̃p�X
//#define GraphicPathSkyEnemy  ".\\date\\SkyEnemy.png"
//#define AnimSkyEnemyDivX      15               //SkyEnemy�̉�������
//#define AnimSkyEnemyDivY      20               //SkyEnemy�̏c������
//
//#define GraphicPathBomb      ".\\date\\����Down.png"
//#define AnimBombDivX          30
//#define AnimBombDivY          30
//
////�A�j���[�V���������p��
//#define AnimationInfinity     -99999
//
////�A�j���[�V����1��̂�
//#define AnimationOnce         -11111
//
////�A�j���[�V�����\���̂̃R�A����
//typedef struct _AnimationCore
//{
//	int NowHandleIndex = -1;  //���݂̃n���h���̗v�f��
//
//	int DivX = 0;     //�摜�̉�������
//	int DivY = 0;     //�摜�̏c������
//
//	int FrameCnt = 0;      //�A�j���[�V�����̃R�}����
//	int FrameMax = 0;      //�A�j���[�V�����̃R�}����MAX
//
//	int FrameByFrameCnt = 0;   //�A�j���[�V�����̃R�}���莞��
//	int FrameByFrameMax = 0;   //�A�j���[�V�����̃R�}���莞��MAX
//
//	BOOL IsAnimStartFlg = FALSE;  //�A�j���[�V�����J�n�t���O
//}AnimationCore;
//
////�A�j���[�V�����\����
//typedef struct _Animation
//{
//	Graphic     g;  //�摜
//	AnimationCore     a; //�A�j���[�V�����R�A
//	int* Handle;    //�n���h��(�������𓮓I�m��)
//}Animation;
//
////�O���O���[�o���ϐ�
//extern Animation AnimSkyEnemy;  //Skyenemy�̃A�j���[�V����
//
////�O���v���g�^�C�v�錾
//extern BOOL Animation_Init(VOID);               //�ǂݍ��݁E�n���h������
//extern VOID Animation_End(VOID);                //��n��
//extern VOID AnimationLoadErrMessage(const char* path);   //�ǂݍ��݃G���[���b�Z�[�W
//
//extern Animation LoadAnimation(const char* path, int XNum, int YNum);   //�A�j���[�V�����ǂݍ���
//extern VOID DrawAnimation(Animation* animation);                       //�`��
//extern VOID DeleteAnimation(Animation animation);                      //���
//
//extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);  //�A�j���[�V�����J�n
