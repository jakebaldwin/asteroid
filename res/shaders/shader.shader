#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uMVP;
uniform vec3 uColor;

out vec3 fragColor;
out vec3 normal;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
    fragColor = uColor;
    normal = aNormal;  // You can use this later for lighting
}

#shader fragment
#version 330 core

in vec3 fragColor;
in vec3 normal;

out vec4 color;

void main()
{
    // Simple solid color for now
    // You can add basic lighting later if you want
    float lightIntensity = dot(normalize(normal), normalize(vec3(1.0, 1.0, 1.0))) * 0.5 + 0.5;
    color = vec4(fragColor * lightIntensity, 1.0);
}
