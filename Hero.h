#pragma once
namespace raylib {
#include "raylib.h"
}

class Hero
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------

	raylib::Image m_HeroSet;
	raylib::Image m_HeroSet_Flip_Horizontal;
	int m_HeroSize;
	int m_SizeHeroSet_x;
	int m_SizeHeroSet_y;
	raylib::Rectangle m_RecHero{};
	int m_HeroDir=0; //0=IDLE
	int m_HeroActionCourante = 0; //0=Aucune action
	int m_SpeedWalk=3;

	int m_IdelIndex=0;
	int m_IdelInc = 1;
	float m_IdleTime = 0.640f;

	int m_WalkIndex = 0;
	int m_AttackIndex = 0;
	int m_Inc = 1;

	float m_Time = 0.100f;

	raylib::Vector2 m_HeroPos{};

public:
	void Init();
	void Idle();
	void Walk(int dir);
	int Attack(int dir);
};

