#pragma once
#include "Shot.h"

class ColllisionMaster;

class Laser :
    public Shot
{
public:
    Laser();
    
    virtual ~Laser();


    virtual void Update();

    virtual void Draw();

    virtual void ShotProgram(Vec2 Spos, Vec2 DirVec);

    bool GetVisible()const { return m_isVisible; }

    bool LineCollider(float x1,float y1,float x2,float y2);

    Vec2 GetLaserPos() { return m_laserHead; };
    
    bool OnLaserCollision(Rect rect);

    float toEquation(float& pos1X,float& pos1Y, float& pos2X,float& pos2Y);//�ꎟ�����������ĐؕЂ�Ԃ�


private:
    Rect m_rect;

    Vec2 m_laserHead;//���[�U�[�̐擪
    Vec2 m_laserTail;//���[�U�[�̔�

    Vec2 m_dirVec;//���[�U�[�̐擪
    Vec2 m_startPos;//���[�U�[�̔�

    Vec2 m_expLine;//���[�U�[��1���֐�
    int b = 0;//�ؕ�

    bool m_isVisible;

    int m_limitTime;
};

