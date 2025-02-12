#pragma once
#include <glm.hpp>
#include <iostream>

class Collider
{
public: 
	virtual ~Collider() {}

	template<typename T>
	bool isOf() { return (dynamic_cast<T>(this) != NULL); }

	glm::mat4 transform;
	glm::vec3 center;
	// move to dynamic body
	bool hasGravity;
	glm::vec3 velocity;
	float mass;
	
};

struct Collision {
	Collider* col1;
	Collider* col2;
	glm::vec3 point;
	glm::vec3 normal1;
	glm::vec3 normal2;
};

class SphereCollider : public Collider{

public:

	float radius;
	
	SphereCollider(const glm::vec3& aCenter, const float& aRadius)
	{
		velocity = glm::vec3(0, 0, 0);
		hasGravity = false;
		center = aCenter;
		radius = aRadius;
		mass = 1;
	}

};