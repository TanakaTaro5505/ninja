#pragma once
#include "DxLib.h"

class EffectManager
{
// define ----------------------------------
private:
	static const int cParticleMax = 1024;
	class Particle
	{
	public:
		Particle();
		virtual ~Particle()	{}

		bool create( float x, float y );

		bool isExist() { return (m_existFrame >= 0); }
		void update();
		void draw();
	private:
		int m_existFrame;
		unsigned int m_color;

		VECTOR m_pos;
		VECTOR m_vec;
	};
public:
	
//function ----------------------------------
public:
	EffectManager();
	virtual ~EffectManager();

	void create(float x, float y);
	void update();
	void draw();

//variable ----------------------------------
private:
	Particle m_particle[cParticleMax];
};
