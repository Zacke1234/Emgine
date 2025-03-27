#include "Collider.h"


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

