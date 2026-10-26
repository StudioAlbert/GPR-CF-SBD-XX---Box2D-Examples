#pragma once

#include <string>

// Ce que Box2D rend quand on lui demande « a qui est cette forme ».
//
// En Box2D 3, `userData` est un simple `void*` : il n'y a plus de
// `b2BodyUserData` a deriver. On y range l'adresse de cette structure, que
// chaque entite possede PAR VALEUR — donc rien a liberer.
enum class UserDataType
{
	Ship,
	Limit,
	Asteroid,
	Missile,
	None
};

class UserData
{
public:
	UserData() = default;
	explicit UserData(const UserDataType type) : type_(type) {}

	UserDataType Type() const { return type_; }
	long LocalId() const { return local_id_; }

	void SetType(const UserDataType type) { type_ = type; }
	void SetLocalId(const long id) { local_id_ = id; }

	static std::string ToString(UserDataType type);

private:
	UserDataType type_ = UserDataType::None;
	long local_id_ = -1;
};
