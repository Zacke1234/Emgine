#version 330 core
in vec3 viewPos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 LightPos;
in vec3 ourColor;
in vec3 FragPos;

out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform sampler2D ourTexture;
uniform vec3 lightPosition;

void main()
{
    vec3 ambient = ambientStrength * lightColor;    
    
     // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    
    vec3 result = (ambient + diffuse + specular);
    

    
    //color and image
    FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0);  
    //FragColor = vec4(norm, 1.0);
} 
