
#include "Logger.h"
#include "Monstre.h"


void Monstre::Init()
{

	m_Set = raylib::LoadImage("Resources/personnages/chara_troll_48x48.png");     // Loaded in CPU memory (RAM)

	if (m_Set.height == 0)
	{
		//erreur
		Logger::GetInstance()->Log(__FILE__, __LINE__, "Erreur de chargement du TileSet : monstre", LogLevel::ERROR);
		return;
	}
	m_Set_Flip_Horizontal = raylib::ImageCopy(m_Set);
	raylib::ImageFlipHorizontal(&m_Set_Flip_Horizontal);
	m_Size = 144;
	m_SizeSet_x = 4;
	m_SizeSet_y = 14;
	m_Rec.height = m_Size;
	m_Rec.width = m_Size;
	m_CollBox.height = 40;
	m_CollBox.width = 22;

	// Initialisation des Structures pour le IDLE du 
	m_Idle.IndexFrame = 0;
	m_Idle.NbFrame = 4;
	m_Idle.Frame = { 0,1,2,1 };
	m_Idle.Frame_Inv = { 0,1,2,1 }; // Pas d'inverse, ce n'est pas util
	m_Idle.TimeWait = { 0.640,0.080,0.640,0.080 };
	m_Idle.Pos = { 0,0,0,0 };

	// Initialisation des Structures pour le mouvement du 
	m_Walk.IndexFrame = 0;
	m_Walk.NbFrame = 4;
	m_Walk.Frame = { 0,1,2,3 };
	m_Walk.Frame_Inv = { 3,2,1,0 };
	m_Walk.TimeWait = { 0.100,0.100,0.100,0.100 };
	m_Walk.Pos = { 0,0,0,0 };


	// Initialisation des Structures pour l'attack du 
	m_Attack.IndexFrame = 0;
	m_Attack.NbFrame = 6;
	m_Attack.Frame = { 0,1,2,3,3,0 };
	m_Attack.Frame_Inv = { 3,2,1,0,0,3 };
	m_Attack.TimeWait = { 0.300,0.100,0.100,0.300,0.080,0 };
	m_Attack.Pos = { -2,+3,+3,+3,-1,0 };

	// Initialisation des Structures pour la chute
	m_Chute.IndexFrame = 0;
	m_Chute.NbFrame = 4;
	m_Chute.Frame = { 0,1,2,3 };
	m_Chute.Frame_Inv = { 3,2,1,0 };
	m_Chute.TimeWait = { 0.100,0.080,0.060,0.010 };
	m_Chute.Pos = { 10,15,20,30 };



}
void Monstre::Idle()
{
	m_Rec.x = m_Idle.GetFrame(false) * m_Size;
	m_Rec.y = 0;
	m_TimeWait = m_Idle.GetTimeWait();
	m_MicroMvt = m_Idle.GetMicroMvtPos(0);
	m_Idle.IncIndexFrame();
}
void Monstre::Walk(int dir)
{
	switch (dir)
	{
	case 1: //Haut
		m_Rec.x = m_Walk.GetFrame(false) * m_Size;
		m_Rec.y = 4 * m_Size;
		break;
	case 2: //Bas
		m_Rec.x = m_Walk.GetFrame(false) * m_Size;
		m_Rec.y = 2 * m_Size;
		break;
	case 3: //Droite
		m_Rec.x = m_Walk.GetFrame(false) * m_Size;
		m_Rec.y = 3 * m_Size;
		break;
	case 4: //Gauche
		m_Rec.x = m_Walk.GetFrame(true) * m_Size;
		m_Rec.y = 3 * m_Size;
		break;
	}
	m_TimeWait = m_Walk.GetTimeWait();
	m_MicroMvt = m_Walk.GetMicroMvtPos(dir);
	m_Walk.IncIndexFrame();
}
int Monstre::Attack(int dir)
{
	switch (dir)
	{
	case 1: //Haut
		m_Rec.x = m_Attack.GetFrame(false) * m_Size;
		m_Rec.y = 7 * m_Size;
		break;
	case 2: //Bas
		m_Rec.x = m_Attack.GetFrame(false) * m_Size;
		m_Rec.y = 5 * m_Size;
		break;
	case 3: //Droite
		m_Rec.x = m_Attack.GetFrame(false) * m_Size;
		m_Rec.y = 6 * m_Size;
		break;
	case 4: //Gauche
		m_Rec.x = m_Attack.GetFrame(true) * m_Size;
		m_Rec.y = 6 * m_Size;
		break;
	}
	m_TimeWait = m_Attack.GetTimeWait();
	m_MicroMvt = m_Attack.GetMicroMvtPos(dir);
	m_Attack.IncIndexFrame();
	if (m_Attack.IndexFrame != 0)
	{
		//Attack en cours
		return 2;
	}
	else
	{
		//Attack termin�e
		return 0;
	}
}

int Monstre::Chute(int dir)
{
	switch (dir)
	{
	case 1: //Haut
		m_Rec.x = m_Chute.GetFrame(false) * m_Size;
		m_Rec.y = 11 * m_Size;
		break;
	case 2: //Bas
		m_Rec.x = m_Chute.GetFrame(false) * m_Size;
		m_Rec.y = 12 * m_Size;
		break;
	case 3: //Droite
		m_Rec.x = m_Chute.GetFrame(false) * m_Size;
		m_Rec.y = 13 * m_Size;
		break;
	case 4: //Gauche
		m_Rec.x = m_Chute.GetFrame(true) * m_Size;
		m_Rec.y = 13 * m_Size;
		break;
	}

	m_TimeWait = m_Chute.GetTimeWait();
	m_MicroMvt = m_Chute.GetMicroMvtPos(dir);
	m_Chute.IncIndexFrame();
	if (m_Chute.IndexFrame == 0)
	{
		return 4;
	}
	return 3;
}
