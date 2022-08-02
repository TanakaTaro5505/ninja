#pragma once
#include "DxLib.h"
#include "PadUtil.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

	// �I�u�W�F�N�g�̐���
	void create(float x, float y, float radius, unsigned int color);
	// �摜���w�肵�ăI�u�W�F�N�g����
	void createGraphic(float x, float y, int handle);

	void update();
	void draw();

	// ���̃I�u�W�F�N�g�Ƃ̏Փ˔���
	bool isCol(GameObject* target);

	bool isExist() { return m_isExist; }

	void setColor(unsigned int color) { m_color = color; }

	void setRadius(float radius) { m_radius = radius; }
	float getRadius() { return m_radius; }
	// �ʒu�ݒ�
	void setPos(VECTOR pos) { m_pos = pos; }
	VECTOR getPos() { return m_pos; }
	// ���x�ݒ�
	void setVec(VECTOR vec) { m_vec = vec; }
	VECTOR getVec() { return m_vec; }
	// �X�P�[��
	void setScale(float scale) { m_scale = scale; }
	float getScale() { return m_scale; }

	// ��]�ݒ�
	void addAngle(float add) { m_angle += add; }	// ��葬�x�ŉ�]���镨�̂Ɏg�p����
protected:
	bool m_isExist;
	int m_graphicHandle;
	unsigned int m_color;
	float m_radius;

	VECTOR m_pos;
	VECTOR m_vec;

	float m_scale;
	float m_angle;

	int m_graphicSizeX;
	int m_graphicSizeY;
};