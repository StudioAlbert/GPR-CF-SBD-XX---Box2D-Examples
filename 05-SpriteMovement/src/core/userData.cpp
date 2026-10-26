#include "core/userData.h"

std::string UserData::ToString(const UserDataType type)
{
	switch (type)
	{
		case UserDataType::Ship: return "SHIP";
		case UserDataType::Limit: return "LIMIT";
		case UserDataType::Asteroid: return "ASTEROID";
		case UserDataType::Missile: return "MISSILE";
		case UserDataType::None: break;
	}
	return "NONE";
}
