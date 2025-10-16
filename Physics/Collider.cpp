#include "Collider.h"
#include "Physics.h"
#include <Object.h>


glm::mat3 ComputeMomentOfInertiaCube(float mass, glm::vec3 extents)
{
    //float inertiaScalar = (2.0f / 3.0f) * mass * (extents * extents);
    return glm::mat3(NULL);
}

glm::mat3 ComputeMomentOfInertiaSphere(float mass, float radius)
{
    float inertiaScalar = (2.0f / 3.0f) * mass * (radius * radius);
    return glm::mat3(inertiaScalar);
}

//void Collider::UpdateCollider(SphereCollider* sphere, CubeCollider* cube)
//{
//
//}

Collider::Collider() 
{
	angularVelocity = glm::vec3(0, 0, 0);
	center = glm::vec3(0, 0, 0);
	hasGravity = true;
	inverseMomentOfInertia = Math::identity3;
	isKinematic = false;
	mass = 0; 
	momentOfInertia = Math::identity3;
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	velocity = glm::vec3(0, 0, 0);
	transform = Math::identity4;
	//std::cout << "test";

}

void Collider::SetTheCollision()
{
	Cube* cube = new Cube();
	Mesh* mesh = new Mesh();
	LightData* light = new LightData();

	
	//CubeCollider* cubeColl = new CubeCollider(center, extents, pos);
	for (auto& o : Object::Entities)
	{
		if (&cube) // ?
		{
			ColliderType::Cube;
			//o->Scale = CubeCollider::extents;
		}
		if(&mesh)
		{
			ColliderType::Sphere;
			//o->Scale = SphereCollider::center;
		}
		if (&light)
		{
			ColliderType::Null;
		}
		
		
	}
	//std::cout << "set the collision" << std::endl;
}
