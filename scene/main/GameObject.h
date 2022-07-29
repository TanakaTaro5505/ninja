#pragma once
#include "DxLib.h"
#include "PadUtil.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

	// オブジェクトの生成
	void create(float x, float y, float radius, unsigned int color);
	// 画像を指定してオブジェクト生成
	void createGraphic(float x, float y, int handle);

	void update();
	void draw();

	// 他のオブジェクトとの衝突判定
	bool isCol(GameObject* target);

	bool isExist() { return m_isExist; }

	void setColor(unsigned int color) { m_color = color; }

	void setRadius(float radius) { m_radius = radius; }
	float getRadius() { return m_radius; }
	// 位置設定
	void setPos(VECTOR pos) { m_pos = pos; }
	VECTOR getPos() { return m_pos; }
	// 速度設定
	void setVec(VECTOR vec) { m_vec = vec; }
	VECTOR getVec() { return m_vec; }
protected:
	bool m_isExist;
	int m_graphicHandle;
	unsigned int m_color;
	float m_radius;

	VECTOR m_pos;
	VECTOR m_vec;

	int m_graphicSizeX;
	int m_graphicSizeY;
};