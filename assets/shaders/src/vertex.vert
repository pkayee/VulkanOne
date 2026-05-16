#version 450

layout (location = 0) in vec3 postion;
layout (location = 1) in vec3 colour;

layout (location = 0) out vec3 fragColour;

layout (push_constant) uniform Push {
    vec3 colour;
} push;

void main() {
    gl_Position = vec4(Position, 1.0);
    fragColour = colour;
}