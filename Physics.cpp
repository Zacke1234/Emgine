#define GLM_ENABLE_EXPERIMENTAL
#include "Physics.h"
#include "glm.hpp"
#include <ext/quaternion_trigonometric.hpp>
#include <gtc/quaternion.hpp>
#include "VirtualObject.h"



float Restitution;
float LinearDrag;

Physics::Physics()
{
	/*CheckIntersect(Collider * c1, Collider * c2);*/
}

void Physics::Simulate(const float& aDeltaTime)
{
	colliders = UpdatePhysicsScene();
	std::vector<Collision> collisions = CheckIntersections(colliders);
	
	// gotta update this
	
	// Just setting the positions of the colliders to match the visual
	std::vector<Collider*> cols = UpdatePhysicsScene();

	// checking for any intersections and storing their data in a vector of collisions
	//std::vector<Collision> collisions = CheckIntersections(cols);

	ApplyGravity(colliders, aDeltaTime);

	//As a result of those collisions what should happen?
	HandleCollisions(collisions);

	//at the moment this only applying gravity to my colliders since I have no calculations for linear and angular velocity based on collisions.
	//This should ideally be in HandleCollisions
	ApplyVelocity(cols, aDeltaTime);

	//Making sure that the visuals of the colliders aligned with the colliders
	UpdateVisuals();
}

void Physics::UpdateVisuals()
{
	for (auto& o : VirtualObject::Entities)
	{
		o->Position += o->myCollider->position;
		
		//o->myCollider->position = o->Position;
		//o->trans += o->myCollider->transform;
	}
}

void Physics::ApplyVelocity(std::vector<Collider*> colliders, const float& dt)
{
	for (Collider* c : colliders)
	{
		if (c->hasGravity && !c->isKinematic)
		{
			//std::cout << "apply velocity";
			c->velocity += glm::vec3(0, 0.96f, 0) * dt;
			c->transform[3] = glm::vec4(c->position, 1.0f);

			float maxAngularVelocity = 3;
			if (glm::length(c->angularVelocity) > maxAngularVelocity)
			{
				c->angularVelocity = glm::normalize(c->angularVelocity) * maxAngularVelocity;
			}
			if (glm::length(c->angularVelocity) > 0.0001f)
			{
				glm::vec3 angularVelocityNorm = glm::normalize(c->angularVelocity);
				glm::quat angularRotation = glm::angleAxis(glm::length(c->angularVelocity) * dt, angularVelocityNorm);
				
				glm::mat3 rotationDelta = glm::mat3_cast(angularRotation);
				c->transform = glm::mat4(rotationDelta) * c->transform;
			}

			if (c->mass > 0)
			{ 
				c->velocity *= glm::pow(1.0f - LinearDrag, dt);
			}
		}
		 
	}


}

void Physics::ApplyGravity(std::vector<Collider*> colliders, const float& dt)
{
	for (Collider* c : colliders)
	{
		if (!c->isKinematic)
		{
			//std::cout << "apply gravity";
			glm::vec3 position = glm::vec3(c->transform[3]);
			// 9.84
			c->velocity.y -= 0.001f * dt;
			position += c->velocity * dt;
			c->position = position;
			c->transform[3] = glm::vec4(position, 1.0f);
		}
	}
}

void Physics::HandleCollisions(std::vector<Collision> collisions)
{
	for (Collision c : collisions)
	{
		std::cout << "handle Collision";
		if (!c.col1->isKinematic)
		{
			c.col1->velocity *= -1;
		}
		
		if (!c.col2->isKinematic)
		{
			c.col2->velocity *= -1;
		}
		if (!c.col1->isKinematic || !c.col2->isKinematic)
		{
			
			glm::vec3 normal = glm::normalize(c.col2->position - c.col1->position);

			//relative velocity
			glm::vec3 relativeVelocity = c.col2->velocity - c.col1->velocity;
			float velocityAlongNormal = glm::dot(relativeVelocity, normal);

			// < 0 means they are moving towards each other
			if (velocityAlongNormal < 0)
			{
				// Coefficient of restitution (bounciness) and calculating impulse
				float restitution = 0.2f;
				float impulse = (1 + restitution) * velocityAlongNormal;

				if (!c.col1->isKinematic)
				{
					glm::vec3 impulseVector = impulse * normal;
					c.col1->velocity += impulseVector;
				}

				if (!c.col2->isKinematic)
				{
					glm::vec3 impulseVector = impulse * normal;
					c.col2->velocity -= impulseVector;
				}
			}
		}
	}
}

void Physics::HandleDynamicDynamic(std::vector<Collision> collisions)
{
	for (Collision c : collisions)
	{
		std::cout << "handle dynamic dynamic";
		glm::vec3 normal = c.normal1; // might need to change that to just normal without the 1

		glm::vec3 relativeVelocity = c.col2->velocity - c.col1->velocity;
		float velocityAlongNormal = glm::dot(relativeVelocity, normal);

		if (velocityAlongNormal > 0) continue;

		float impulse = (1 + Restitution) * velocityAlongNormal;

		glm::vec3 impulseVector = impulse * normal;

		c.col1->velocity += impulseVector;
		c.col2->velocity += impulseVector;

		glm::vec3 r1 = c.point - c.col1->position;
		glm::vec3 r2 = c.point - c.col2->position;

		glm::vec3 torque1 = glm::cross(r1, impulseVector);
		glm::vec3 torque2 = glm::cross(r2, impulseVector);

		c.col1->angularVelocity += c.col1->inverseMomentOfInertia * torque1 * 100000000.0f;
		c.col2->angularVelocity += c.col2->inverseMomentOfInertia * torque2 * 100000000.0f;
		
	}
}

void Physics::HandleStaticDynamic(std::vector<Collision> collisions)
{
	const float SlidingFriction = 0.5f;
	for (Collision c : collisions)
	{
		std::cout << "handle static dynamic";
		Collider* A = c.col1;
		Collider* B = c.col2;

		bool A_isDynamic = !A->isKinematic;
		bool B_isDynamic = !B->isKinematic;

		if (!A_isDynamic && !B_isDynamic) continue;

		Collider* dynamicCollider = A_isDynamic ? A : B;
		Collider* staticCollider = A_isDynamic ? B : A;

		glm::vec3 n = glm::normalize(c.normal1);
		glm::vec3 r = c.point - dynamicCollider->position;

		glm::vec3 v = dynamicCollider->velocity + glm::cross(dynamicCollider->angularVelocity, r);
		float vRelDotN = glm::dot(v, n);

		if (vRelDotN > 0) continue;

		float invMass = (dynamicCollider->mass > 0) ? 1.0f / dynamicCollider->mass : 0;
		glm::vec3 r_cross_n = glm::cross(r, n);
		float angularEffect = glm::dot(r_cross_n, dynamicCollider->inverseMomentOfInertia * r_cross_n);

		float impulseMagnitude = -(1 + Restitution) * vRelDotN / (invMass * angularEffect);
		glm::vec3 impulse = impulseMagnitude * n;

		//apply impulse to linear velocity
		dynamicCollider->velocity += impulse * invMass;

		//angular velocity (considering moment of inertia 
		dynamicCollider->angularVelocity += dynamicCollider->inverseMomentOfInertia * glm::cross(r, impulse);

		glm::vec3 tangentVelocity = v - (n * glm::dot(v, n));
		if (glm::length(tangentVelocity) > 0.0001f)
		{
			glm::vec3 frictionDirection = -glm::normalize(tangentVelocity);
			glm::vec3 frictionImpulse = frictionDirection * SlidingFriction * glm::length(tangentVelocity);

			dynamicCollider->velocity += frictionImpulse * invMass;
			dynamicCollider->angularVelocity += dynamicCollider->inverseMomentOfInertia * glm::cross(r, frictionImpulse);
		}

	}
}

bool Physics::BoolCheckIntersect(Collider* c1, Collider* c2) 
{
	//CheckIntersect(c1, c2);
	if (c1->isOf<SphereCollider>() && c2->isOf<SphereCollider>())
	{
		std::cout << "check intersect";
		SphereCollider* sphere1 = dynamic_cast<SphereCollider*>(c1);
		SphereCollider* sphere2 = dynamic_cast<SphereCollider*>(c2);
		return SphereSphereIntersect(*sphere1, *sphere2);
	}
}

std::vector<Collider*> Physics::UpdatePhysicsScene()
{
	std::vector<Collider*> returnColliders;
	for (auto& o : VirtualObject::Entities)
	{
		//std::cout << "apply velocity";
		returnColliders.push_back(o->myCollider);

	}
	return returnColliders;
}

std::vector<Collision> Physics::CheckIntersections(std::vector<Collider*> colliders)
{
	
	std::vector<Collision> collisions;

	int count = colliders.size();

	//for (int i = 0; i < count; i++)
	//{
	//	for (int j = i + 1; j < count; j++)
	//	{
	//		Collision c = CheckIntersect(colliders[i], colliders[j]); // cannot convert from bool to collision? 
	//		if (c.col1 != nullptr && c.col2 != nullptr)
	//		{
	//			collisions.push_back(c);
	//		}
	//	}
	//}

	// 
	for (Collider* c1 : colliders)
	{
		
		for (Collider* c2 : colliders)
		{
			if (c1 != c2)
			{
				
				if (BoolCheckIntersect(c1, c2))
				{
					std::cout << "check Intersection";
					Collision collision;
					collision.col1 = c1;
					collision.col2 = c2;
					collisions.push_back(collision);

				}
			}
		}
	}
	return collisions;
}

glm::mat3 Physics::ComputeMomentOfInertiaSPhere(float mass, float radius) // omw to return a float that is a glm
{
	float inertiaScalar = (2.0f / 3.0f) * mass * (radius * radius);
	return glm::mat3(inertiaScalar);
}

bool Physics::SphereSphereIntersect(const SphereCollider& c1, const SphereCollider& c2)
{
	float dist = glm::distance(c1.position, c2.position);

	if (dist < c1.radius + c2.radius)
	{
		std::cout << "Spheres are intersecting!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool Physics::CubeSphereIntersect(const CubeCollider& aCube1, const SphereCollider& aSphere2)
{
	glm::vec3 sphereCenter = glm::vec3(aSphere2.transform[3]);
	glm::vec3 localSphereCenter = glm::inverse(aCube1.transform) * glm::vec4(sphereCenter, 1.0f);
	glm::vec3 closestPoint = glm::clamp(localSphereCenter, -aCube1.extents, aCube1.extents);
	float dist2 = glm::length(localSphereCenter - closestPoint);
	return dist2 < aSphere2.radius * aSphere2.radius;
}

bool Physics::CubeCubeIntersect(const CubeCollider& aCube1, const CubeCollider& aCube2)
{
	// static_assert failed: ''abs' only accept floating-point and integer scalar or vector inputs'

	glm::mat3 rotation1 = glm::mat3(aCube1.transform);
	glm::mat3 rotation2 = glm::mat3(aCube2.transform);
	glm::vec3 translation = glm::vec3(aCube2.transform[3]) - glm::vec3(aCube1.transform[3]);
	translation = glm::transpose(rotation1) * translation;

	glm::mat3 rotation = glm::transpose(rotation1) * rotation2;
	glm::mat3 absRotation; /* glm::abs(rotation) + glm::mat3(0.0001f);*/

	for (int i = 0; i < 3; i++)
	{
		absRotation[i] = glm::abs(rotation[i]) + 0.00001f;
	} 
	glm::vec3 halfSize1 = aCube1.extents * 0.5f;
	glm::vec3 halfSize2 = aCube2.extents * 0.5f;

	// SAT (seperating axis theorem
	for (int i = 0; i < 3; ++i)
	{
		float ra = halfSize1[i];
		float rb = glm::dot(absRotation[i], halfSize2);
		if (glm::abs(translation[i]) > ra + rb) return false;
	}

	for (int i = 0; i < 3; ++i)
	{
		float ra = glm::dot(absRotation[i], halfSize1);
		float rb = halfSize2[i];
		if (glm::abs(glm::dot(rotation[i], translation)) > ra + rb) return false;
	}

	return true;

}

bool Physics::RayCast(const Ray& aRay, RayHit& aHit)
{
	
	for (Collider* c : colliders)
	{
		/*if (c->mass > 0)
		{
			c->velocity *= glm::pow(1.0f, Lineardrag)
		}*/
		if (CheckRayIntersect(aRay, c))
		{
			aHit.collider = c;
			aHit.point = glm::vec3(0, 0, 0);
			aHit.distance = 10;
			return true;
		}
	}
	return false;
}

bool Physics::CheckRayIntersect(const Ray& aRay, Collider* aCollider)
{
	if (aCollider->isOf<SphereCollider>())
	{
		SphereCollider* sphere = dynamic_cast<SphereCollider*>(aCollider);
		return RaySphereIntersect(aRay, *sphere);
	}
	else if (aCollider->isOf<CubeCollider>())
	{
		CubeCollider* cube = dynamic_cast<CubeCollider*>(aCollider);
		return RayCubeIntersect(aRay, *cube);
	}
}

bool Physics::RayCubeIntersect(const Ray& aRay, CubeCollider aCube)
{
	glm::vec3 min = glm::vec3(aCube.transform[3]) - aCube.extents;
	glm::vec3 max = glm::vec3(aCube.transform[3]) + aCube.extents;

	glm::vec3 invDir = 1.0f / aRay.direction;

	float t1 = (min.x - aRay.origin.x) * invDir.x;
	float t2 = (max.x - aRay.origin.x) * invDir.x;
	float t3 = (min.y - aRay.origin.y) * invDir.y;
	float t4 = (max.y - aRay.origin.y) * invDir.y;
	float t5 = (min.z - aRay.origin.z) * invDir.z;
	float t6 = (max.z - aRay.origin.z) * invDir.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::min(t5, t6));

	return tmax >= std::max(0.0f, tmin);
}

bool Physics::RaySphereIntersect(const Ray& aRay, SphereCollider aSphere)
{
	// Look at glm intersectRaySphere

	// vector from ray origin to sphere center
	glm::vec3 diff = aSphere.center - aRay.origin;

	// project diff onto ray direction
	float t0 = glm::dot(diff, aRay.direction);

	//perpendicular distance! .....? also dot on itself makse sense since diff is not normalized
	float dSquared = glm::dot(diff, diff) - t0 * t0;

	// distance is greater than the sphere's radius squared, no intersection
	float radiusSquared = aSphere.radius * aSphere.radius;
	if (dSquared > radiusSquared)
	{
		return false;
	}

	// distance from closest to intersection point 
	float t1 = glm::sqrt(radiusSquared - dSquared);

	float Epsilon = 0.000001f; // just a small number to help with tiny floating point errors
	float outIntersectionDistance = (t0 > t1 + Epsilon) ? t0 - t1 : t0 + t1; // could actually return this as the2 distance

	//return true if the intersection distance is positive
	return outIntersectionDistance > Epsilon;
}

bool Physics::RayOBBIntersect(const Ray& aRay, const CubeCollider& aCube)
{
	glm::vec3 center = glm::vec3(aCube.transform[3]);
	glm::mat3 rotation = glm::mat3(aCube.transform);

	glm::vec3 localOrigin = glm::transpose(rotation) * (aRay.origin - center);
	glm::vec3 localDirection = glm::transpose(rotation) * aRay.direction;

	CubeCollider localCube = CubeCollider(glm::vec3(0, 0, 0), aCube.extents);
	localCube.extents = aCube.extents;

	Ray localRay(localOrigin, localDirection);
	return RayCubeIntersect(localRay, localCube);
}
