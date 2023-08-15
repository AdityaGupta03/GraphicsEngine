#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 view; // Add the view matrix uniform
uniform float scale = 0.0;

void main() {

    vec4 transformedPos = view * vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    gl_Position = transformedPos;
    color = aColor;
	
}