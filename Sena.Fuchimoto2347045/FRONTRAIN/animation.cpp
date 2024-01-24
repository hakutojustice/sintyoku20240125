//#include "animation.h"
//
//Animation SkyEnemy;    //SkyEnemy�̃A�j���[�V����
//
////�ǂݍ��݁E�n���h������
//BOOL Animation_Init(VOID)
//{
//	//SkyEnemy�̃A�j���[�V����
//	SkyEnemy = LoadAnimation(
//		GraphicPathSkyEnemy,
//		AnimSkyEnemyDivX,                 //�A�j���[�V������������
//		AnimSkyEnemyDivY                  //�A�j���[�V�����c������
//	); if (AnimSkyEnemy.Handle[0] == -1) { return FALSE; }
//
//	return TRUE;
//}
//
////��n��
//VOID Animation_End(VOID)
//{
//	DeleteAnimation(AnimSkyEnemy);
//
//	return;
//}
//
////�ǂݍ��݃G���[���b�Z�[�W
//VOID AnimationLoadErrMessage(const char* path)
//{
//	//�G���[�p������
//	char ErrStr[AnimationPathStrMax];
//
//	//�G���[�p������̓��e����ɂ���
//	for (int i = 0; i < AnimationPathStrMax; i++) { ErrStr[i] = '\0'; }
//
//	//�G���[���e��A�����Đ���
//	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);
//
//	//�p�X���Ԉ���Ă���ȂǂŃC���X�g�[���ł��Ȃ��ꍇ�̓G���[
//	MessageBox(
//		GetMainWindowHandle(),
//		ErrStr,
//		AnimationLoadErrTitle,
//		MB_OK);
//
//	return;
//}
//
////�A�j���[�V�����ǂݍ���
//Animation LoadAnimation(Graphic graphic, int XNum, int YNum)
//{
//	Animation animation;
//
//	//�ǂݍ��񂾉摜�̏��������p��
//	animation.g = graphic;
//
//	//�摜�̕�������ݒ�
//	animation.a.DivX = XNum;
//	animation.a.DivY = YNum;
//
//	//�摜�̕��ƍ������Čv�Z
//	animation.g.c.Width = animation.g.c.Width / XNum;
//	animation.g.c.Height = animation.g.c.Height / YNum;
//
//	//�����蔻����Čv�Z
//	ReMakeCollRect(&animation.g);
//
//	//�A�j���[�V�����̃n���h���z��𓮓I�m��
//	animation.Handle = (int*)calloc(XNum * YNum, sizeof(int));
//
//	//int�^�̃|�C���^�Ɍ^�ϊ�
//	//�������𓮓I�m�ۂ��Ēl���[���ŏ�����
//	//�m�ۂ���v�f�̌�
//	//�m�ۂ���v�f�̃f�[�^�^
//
//	//�A�j���[�V�����𕪊����ă������ɓǂݍ���
//	LoadDivGraph(
//		graphic.c.Path,          //�A�j���[�V�����̃p�X
//		(XNum * YNum),        //��������
//		XNum, YNum,            //(��)������ - (�c)������
//		animation.g.c.Width,    //��������1���̕�
//		animation.g.c.Height,   //��������1���̍���
//		animation.Handle       //�A�������n���h���z��̐擪
//	);
//
//	//�ǂݍ��݃G���[
//	if (animation.Handle == NULL || animation.Handle[0] == -1)
//	{
//		AnimationLoadErrMessage(graphic.c.Path);
//	}
//
//	//�������ɓǂݍ��񂾉摜�̓T�C�Y��m�肽������������p�ς�
//	DeleteGraphic(graphic);
//
//	//�n���h���̗v�f����������
//	animation.a.NowHandleIndex = 0;
//
//	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
//	animation.g.Handle = animation.Handle[animation.a.NowHandleIndex];
//
//	return animation;
//
//}
//
////�`��
//VOID DrawAnimation(Animation* animation)
//{
//	//�摜�`��
//	DrawGraphic(&animation->g);
//
//	//�A�j���[�V�������Ȃ�R�}��i�߂�
//	if (animation->a.IsAnimStartFlg == TRUE)
//	{
//		if (animation->a.FrameByFrameCnt < animation->a.FrameByFrameMax)
//		{
//			animation->a.FrameByFrameCnt++;
//		}
//		else
//		{
//			//�R�}��i�߂Ă��镔��
//			if (animation->a.NowHandleIndex < animation->a.DivX * animation->a.DivY - 1)
//			{
//				animation->a.NowHandleIndex++;
//			}
//			else
//			{
//				animation->a.NowHandleIndex = 0;
//			}
//
//			//�A�j���[�V�����̗v�f�����Z�b�g
//			animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];
//
//			//�R�}���菉����
//			animation->a.FrameCnt++;
//		}
//
//		//�A�j���[�V�����������p���ł͂Ȃ��Ƃ�
//		if (animation->a.FrameMax != AnimationInfinity)
//		{
//			//�A�j���[�V������1��݂̂Ȃ�A�j���[�V�������Ԃ𖳎�
//			if (animation->a.FrameMax != AnimationOnce)
//			{
//				//�A�j���[�V�������Ԃ��I���Ȃ�΃A�j���[�V�����I��
//				if (animation->a.FrameCnt > animation->a.FrameMax)
//				{
//					animation->a.IsAnimStartFlg = FALSE;    //�A�j���[�V�����J�n�t���OOFF
//					animation->g.c.IsDraw = FALSE;          //�A�j���[�V�����J�n�t���OOFF
//				}
//			}
//
//			//�A�j���[�V�����̃R�}�̍Ō�Ȃ�΃A�j���[�V�����I��
//			if (animation->a.NowHandleIndex >= animation->a.DivX * animation->a.DivY - 1)
//			{
//				animation->a.IsAnimStartFlg = FALSE;    //�A�j���[�V�����J�n�t���OOFF
//				animation->g.c.IsDraw = FALSE;          //�A�j���[�V�����J�n�t���OOFF
//			}
//		}
//			
//	}
//
//	return;
//}
//
////���
//VOID DeleteAnimation(Animation animation)
//{
//	//����ɓǂݍ��݂��ł��Ă����
//	if (animation.Handle != NULL && animation.Handle[0] != -1)
//	{
//		//������������
//		for (int i = 0; i < animation.a.DivX * animation.a.DivY; i++)
//		{
//			DeleteGraph(animation.Handle[i]);
//		}
//
//		//���I�m�ۂ��������������
//		free(animation.Handle);
//	}
//
//	//2��ȏ��free��h���v���O�����̃N���b�V���h�~
//	animation.Handle = NULL;
//
//	return;
//}
//
////�A�j���[�V�����J�n
//void AnimationStart(Animation* animation, int MillTime, int MillInterval)
//{
//	//�A�j���[�V�����̕b����������
//	animation->a.FrameCnt = 0;
//
//	//�A�j���[�V�����̌p�����Ԃ��v�Z
//	if (MillTime == AnimationInfinity)
//	{
//		//�����A�j���[�V�����������p���Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
//		animation->a.FrameMax = AnimationInfinity;
//	}
//	else if (MillTime == AnimationOnce)
//	{
//		//�����A�j���[�V������1��݂̂Ȃ�A���ۂ�MAX���Ԃ��v�Z�����Ȃ�
//		animation->a.FrameMax = AnimationOnce;
//	}
//	else
//	{
//		animation->a.FrameMax = (MillTime / 1000.0f);
//	}
//
//	//�A�j���[�V�����̊Ԋu��������
//	animation->a.FrameByFrameCnt = 0;
//	animation->a.FrameByFrameMax = (MillInterval / 1000.0f);
//
//	//�n���h���̗v�f����������
//	animation->a.NowHandleIndex = 0;
//
//	//�ŏ��̃A�j���[�V�����̗v�f�����Z�b�g
//	animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];
//
//	//�A�j���[�V�����J�n�t���OON
//	animation->a.IsAnimStartFlg = TRUE;
//
//	//�A�j���[�V�����`��t���OON
//	animation->g.c.IsDraw = TRUE;
//
//	return;
//}