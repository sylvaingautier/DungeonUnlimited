#pragma once
#include "Dungeon_map.h"
namespace raylib {
#include "raylib.h"
	}
#include <vector>

class Monstre
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------


	raylib::Image m_Set;
	raylib::Image m_Set_Flip_Horizontal;
	int m_Size;
	int m_SizeSet_x;
	int m_SizeSet_y;
	raylib::Rectangle m_Rec{};
	raylib::Rectangle m_CollBox{};
	int m_Dir = 0; //0=IDLE
	int m_ActionCourante = 0; //0=Aucune action
	int m_SpeedWalk = 3;

	float m_TimeWait = 0.100f;
	raylib::Vector2 m_MicroMvt{};
	raylib::Vector2 m_PosMapCurr{};
	raylib::Vector2 m_PosMapDest{};
	raylib::Vector2 m_PosScreenCurr{};
	raylib::Vector2 m_DirDest{};
	struct s_Monstre
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
	double previousTime_Walk;
	struct s_Monstre m_Walk;
	struct s_Monstre m_Attack;
	struct s_Monstre m_Idle;
	struct s_Monstre m_Chute;

public:
	void Init();
	void Idle();
	void Walk(int dir);
	int Attack(int dir);
	int Chute(int dir);


};

