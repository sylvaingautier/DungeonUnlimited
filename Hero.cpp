#include "Logger.h"
#include "Hero.h"

void Hero::Init()
{

	m_HeroSet = raylib::LoadImage("Resources/environnements/tilset_1/chara_hero_48x48.png");     // Loaded in CPU memory (RAM)

	if (m_HeroSet.height == 0)
	{
		//erreur
		Logger::GetInstance()->Log(__FILE__, __LINE__, "Erreur de chargement du TileSet : chara_hero_48x48.png", LogLevel::ERROR);
		return;
	}
	m_HeroSet_Flip_Horizontal = raylib::ImageCopy(m_HeroSet);
	raylib::ImageFlipHorizontal(&m_HeroSet_Flip_Horizontal);
	m_HeroSize = 144;
	m_SizeHeroSet_x = 4;
	m_SizeHeroSet_y = 11;
	m_RecHero.height = m_HeroSize;
	m_RecHero.width = m_HeroSize;
}
void Hero::Idle()
{
	m_IdelIndex = (m_IdelIndex + m_IdelInc);
	if (m_IdelIndex == 2)
	{
		m_IdelInc = -1;
	}
	if (m_IdelIndex == 0)
	{
		m_IdelInc = 1;
	}
	switch (m_IdelIndex)
	{
	case 0:
		m_IdleTime = 0.640f;
		break;
	case 1:
		m_IdleTime = 0.080f;
		break;
	case 2:
		m_IdleTime = 0.640f;
		break;
	}
	m_RecHero.x = m_IdelIndex *m_HeroSize;
	m_RecHero.y = 0;
}
void Hero::Walk(int dir)
{
	switch (dir)
	{
		case 1: //Haut
			m_Index = (m_Index + 1) % 3;
			m_RecHero.x = m_Index * m_HeroSize;
			m_RecHero.y = 4 * m_HeroSize;

			break;
		case 2: //Bas
			m_Index = (m_Index + 1) % 3;
			m_RecHero.x = m_Index * m_HeroSize;
			m_RecHero.y = 2 * m_HeroSize;
			break;
		case 3: //Gauche
		case 4: //Droite
			m_Index = (m_Index + 1) % 3;
			m_RecHero.x = m_Index * m_HeroSize;
			m_RecHero.y = 3 * m_HeroSize;
			break;
	}

}
int Hero::Attack(int dir)
{
	switch (dir)
	{
	case 1:
		m_Index = (m_Index + 1) % 4;
		m_RecHero.x = m_Index * m_HeroSize;
		m_RecHero.y = 7 * m_HeroSize;

		break;
	case 2:
		m_Index = (m_Index + 1) % 4;
		m_RecHero.x = m_Index * m_HeroSize;
		m_RecHero.y = 5 * m_HeroSize;
		break;
	case 3:
		m_Index = (m_Index + 1) % 4;
		m_RecHero.x = (4-m_Index) * m_HeroSize;
		m_RecHero.y = 6 * m_HeroSize;
		break;
	case 4:
		m_Index = (m_Index + 1) % 4;
		m_RecHero.x = m_Index * m_HeroSize;
		m_RecHero.y = 6 * m_HeroSize;
		break;
	}
	switch (m_Index)
	{
	case 0:
		m_Time = 0.300f;
		break;
	case 1:
		m_Time = 0.100f;
		break;
	case 2:
		m_Time = 0.100f;
		break;
	case 3:
		m_Time = 0.200f;
		return 0;
		break;
	}
	return 2;
}

