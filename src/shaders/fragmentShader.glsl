#version 330 core

in vec3 vertexCoords;

void main() {
    gl_FragColor = vec4(abs(vertexCoords.x), abs(vertexCoords.y) , vertexCoords.z, 0.0);
}