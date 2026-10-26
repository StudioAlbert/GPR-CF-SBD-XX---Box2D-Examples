#pragma once

#include <optional>

#include <SFML/Graphics.hpp>

#include "core/box2DEntity.h"

constexpr float kMaxAngularVelocity = 2.0f;
constexpr float kMaxLinearVelocity = 5.0f;

class Ship : public Box2DEntity
{
public:
	explicit Ship(b2WorldId world);

	void Init(sf::Vector2u window_size);
	void Update();

	void SpeedUp(float force);
	void SpeedDown(float damping);
	void RotateLeft(float torque);
	void RotateRight(float torque);
	void SetAngularDamping(float damping);

	float Life() const { return life_; }
	void SetDamages(float damages) { life_ -= damages; }
	static constexpr float LifeMax() { return 100.0f; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void ApplyLocalForce(float force);
	void ApplyTorque(float torque);

	std::optional<sf::Sprite> sprite_;
	float life_ = 100.0f;
};
