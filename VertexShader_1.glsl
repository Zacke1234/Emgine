#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 3) in vec3 aColor;

out vec3 viewPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 LightPos;
out vec3 ourColor;
out vec3 FragPos;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
    FragPos = vec3(transform * vec4(aPos, 1.0));
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    viewPos = vec3(view * transform * vec4(aPos, 1.0));
    //Normal = aNormal;
    Normal = mat3(transpose(inverse(transform))) * aNormal;
    //LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
    LightPos = lightPos;

    //ourColor = aColor;
    TexCoord = aTexCoord;
}









