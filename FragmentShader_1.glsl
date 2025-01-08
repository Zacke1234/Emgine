#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{   //color and image
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);  

    //color
    //FragColor = vertexColor;

    //image
    //FragColor = texture(ourTexture, TexCoord);

    //image on another image
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    //FragColor = vec4(1, 0, 0, 1);

    //FragColor = vec4(lightColor * objectColor, 1.0);
} 
