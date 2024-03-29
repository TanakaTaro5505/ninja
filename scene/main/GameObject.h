#pragma once
#include "DxLib.h"
#include "PadUtil.h"
#include "Vec2.h"

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
	void setPos(Vec2 pos) { m_pos = pos; }
	Vec2 getPos() { return m_pos; }
	// 速度設定
	void setVec(Vec2 vec) { m_vec = vec; }
	Vec2 getVec() { return m_vec; }
	// スケール
	void setScale(float scale) { m_scale = scale; }
	float getScale() { return m_scale; }

	// 回転設定
	void addAngle(float add) { m_angle += add; }	// 一定速度で回転する物体に使用する
protected:
	bool m_isExist;
	int m_graphicHandle;
	unsigned int m_color;
	float m_radius;

	Vec2 m_pos;
	Vec2 m_vec;

	float m_scale;
	float m_angle;

	int m_graphicSizeX;
	int m_graphicSizeY;
};