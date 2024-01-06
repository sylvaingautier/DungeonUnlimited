#pragma once
namespace raylib {
#include "raylib.h"
}
#include <vector>
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
	raylib::Vector2 m_CollBoxHero{};
	int m_HeroDir=0; //0=IDLE
	int m_HeroActionCourante = 0; //0=Aucune action
	int m_SpeedWalk = 3; 

	float m_TimeWait = 0.100f;
	raylib::Vector2 m_MicroMvtHero{};
	raylib::Vector2 m_HeroPos{};

	struct s_Hero
	{
		int IndexFrame;
		int NbFrame;
		std::vector<int> Frame;
		std::vector<int> Frame_Inv;
		std::vector<float>  TimeWait;
		std::vector<int> Pos;

		void IncIndexFrame() {
			IndexFrame = (IndexFrame + 1) % NbFrame;
		};
		float GetTimeWait() {
			return TimeWait.at(IndexFrame);
		};
		int GetFrame(bool Inv) {
			if (Inv == false)
			{
				return Frame.at(IndexFrame);
			}
			else 
			{
				return Frame_Inv.at(IndexFrame);
			}

		};
		raylib::Vector2 GetMicroMvtPos(int Dir) {
			raylib::Vector2 RetourMicroMvtPos{};
			switch (Dir)
			{
				case 1://Haut
					RetourMicroMvtPos.x = 0;
					RetourMicroMvtPos.y = -Pos.at(IndexFrame);
					break;
				case 2://Bas
					RetourMicroMvtPos.x = 0;
					RetourMicroMvtPos.y = Pos.at(IndexFrame);
					break;
				case 3://Droite
					RetourMicroMvtPos.x = Pos.at(IndexFrame);
					RetourMicroMvtPos.y = 0;
					break;
				case 4://Gauche
					RetourMicroMvtPos.x = -Pos.at(IndexFrame);
					RetourMicroMvtPos.y = 0;
					break;


			}
			return RetourMicroMvtPos;
		};
	};

	struct s_Hero m_Walk;
	struct s_Hero m_Attack;
	struct s_Hero m_Idle;
	struct s_Hero m_Chute;

public:
	void Init();
	void Idle();
	void Walk(int dir);
	int Attack(int dir);
	int Chute(int dir);
};

