#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform float scale;

void main() {
    gl_Position = view * projection * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
}
