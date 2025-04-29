#pragma once
#include <vector>
#include "Collider.h"
#include "VirtualObject.h"

namespace Math {
	extern const glm::mat4 identity4;
	extern const glm::mat3 identity3;

}

class Physics
{
public:
	Physics();
	void Simulate(const float& aDeltaTime);

	void ApplyVelocity(std::vector<Collider*> colliders, const float& dt);
	void ApplyGravity(std::vector<Collider*> colliders, const float& dt);

	void HandleCollisions(std::vector<Collision> collisions);
	void HandleDynamicDynamic(std::vector<Collision> collisions);
	void HandleStaticDynamic(std::vector <Collision> collisions);
	void UpdateVisuals();

	void ApplyCollision(const float& dt, std::vector<Collision> collisions);

	glm::vec3 SafeNormalise(glm::vec3 vector);
	
	bool BoolCheckIntersect(Collider* c1, Collider* c2);
	std::vector<Collider*> UpdatePhysicsScene();
	std::vector<Collision> CheckIntersections(std::vector<Collider*> colliders);
	glm::mat3 ComputeMomentOfInertiaSPhere(float mass, float radius);
	bool SphereSphereIntersect(const SphereCollider& c1, const SphereCollider& c2);
	bool CubeSphereIntersect(const CubeCollider& aCube1, const SphereCollider& aSpher2);
	bool CubeCubeIntersect(const CubeCollider& aCube1, const CubeCollider& aCube2);

	bool RayCast(const Ray& aRay, RayHit& aHit);

	bool CheckRayIntersect(const Ray& aRay, Collider* aCollider);

	bool RayCubeIntersect(const Ray& aRay, CubeCollider aCube);
	bool RaySphereIntersect(const Ray& aRay, SphereCollider aSphere);

	bool RayOBBIntersect(const Ray& aRay, const CubeCollider& aCube);
	
	bool Testgravity = true;

	bool TimeTicking = true;
private:
	std::vector<Collider*> colliders;

	std::vector<Collision*> collisions;

	std::vector<VirtualObject*> m_virtualObjects;
};

