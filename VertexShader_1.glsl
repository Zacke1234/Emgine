#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aTexCoords;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBitangent;  

//layout (location = 3) in vec3 aColor;

out vec3 viewPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 LightPos;
out vec3 ourColor;
out vec3 FragPos;
out vec4 FragPosLightSpace;


uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;



// mip mapping
out VS_OUT {
    vec3 FragPos;
    vec2 TexCoord;
    mat3 TBN;
} vs_out;  
     

void main()
{ 
// mip map
   vec3 T = normalize(vec3(transform * vec4(aTangent,   0.0)));
   vec3 B = normalize(vec3(transform * vec4(aBitangent, 0.0)));
   vec3 N = normalize(vec3(transform * vec4(aNormal,    0.0)));
   mat3 TBN = mat3(T, B, N);

   //mip mapping
     // obtain normal from normal map in range [0,1]
    //normal = texture(normalMap, fs_in.TexCoords).rgb;
    // transform normal vector to range [-1,1]
    //normal = normalize(normal * 2.0 - 1.0); 

    vs_out.TBN = mat3(T, B, N);
    FragPos = vec3(transform * vec4(aPos, 1.0));

    // lightSpaceMatrix
    gl_Position = projection * view  * transform * vec4(FragPos, 1.0); 
    viewPos = vec3(view * transform * vec4(aPos, 1.0));
   
    //Normal = mat3(transpose(inverse(transform))) * aNormal;
   
    LightPos = lightPos;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    TexCoord = aTexCoord;
}









