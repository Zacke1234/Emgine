#include "Physics.h"

Physics::Physics()
{
}

void Physics::Simulate(const float& aDeltaTime)
{
	// Just setting the positions of the colliders to match the visual
	std::vector<Collider*> cols = UpdatePhysicsScene();

	// checking for any intersections and storing their data in a vector of collisions
	std::vector<Collision> collisions = CheckIntersections(cols);

	//As a result of those collisions what should happen?
	HandleCollisions(collisions);

	//at the moment this only applying gravity to my colliders since I have no calculations for linear and angular velocity based on collisions.
	//This should ideally be in HandleCollisions
	ApplyVelocity(cols, aDeltaTime);

	//Making sure that the visuals of the colliders aligned with the colliders
	//Update visuals
}

void Physics::ApplyVelocity(std::vector<Collider*> colliders, const float& dt)
{

}

void Physics::HandleCollisions(std::vector<Collision> collisions)
{
}

std::vector<Collider*> Physics::UpdatePhysicsScene()
{
	return std::vector<Collider*>();
}

std::vector<Collision> Physics::CheckIntersections(std::vector<Collider*> colliders)
{
	return std::vector<Collision>();
}
