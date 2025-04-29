#pragma once
#include <glm.hpp>
#include <iostream>
#include <glm.hpp>


glm::mat3 ComputeMomentOfInertiaCube(float mass, glm::vec3 extents);
glm::mat3 ComputeMomentOfInertiaSphere(float mass, float radius);

class Collider
{
public: 
	Collider();
	virtual ~Collider() {};

	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != NULL); }; // do i need multiple of these in the structs?

	

	//void UpdateCollider(SphereCollider* sphere, CubeCollider* cube);
	enum class Type{
		Null, Sphere, Cube, Raycast
	};
	glm::mat4 transform;
	
	glm::vec3 center;
	// move to dynamic body
	bool hasGravity;
	glm::vec3 velocity;
	float mass;
	glm::vec3 position;
	bool isKinematic;
	Type type = Type::Null;
	glm::vec3 angularVelocity;
	glm::vec3 scale;

	glm::mat3 momentOfInertia;
	glm::mat3 inverseMomentOfInertia;

	void SetTheCollision();
	
	
	
};

struct Collision {
	Collider* col1;
	Collider* col2;
	glm::vec3 point;
	glm::vec3 normal1;
	glm::vec3 normal2;
	float restitution; // I think it goes here
	glm::mat3 LinearDrag; // maybe
};



class SphereCollider : public Collider{

public:

	float radius;
	
	
	SphereCollider(const glm::vec3& aCenter, const float& aRadius, glm::vec3 Apos) : Collider()
	{
		type = Type::Sphere;
		velocity = glm::vec3(0, 0, 0);
		hasGravity = false;
		center = aCenter;
		radius = aRadius;
		mass = 1;
		position = Apos;
		
	}

};

class CubeCollider : public Collider
{
public:
	// glm::vec3 aScale
	CubeCollider(const glm::vec3& aCenter, const glm::vec3& someExtents, glm::vec3 Apos)  : Collider()
	{
		type = Type::Cube;
		velocity = glm::vec3(0, 0, 0);
		hasGravity = false;
		center = aCenter;
		extents = someExtents;
		position = Apos;
		//scale = aScale;
	}
	glm::vec3 extents;
};

class Ray {
public:
	Ray(const glm::vec3& anOrigin, const glm::vec3& aDirection)
	{
		origin = anOrigin;
		direction = aDirection;
	}
	glm::vec3 origin;
	glm::vec3 direction;
};

class RayHit {
public:
	RayHit(glm::vec3 aPoint, Collider* aCollider, float aDistance) {
		point = aPoint;
		collider = aCollider;
		distance = aDistance;
	};

	glm::vec3 point;
	Collider* collider;
	float distance;
};