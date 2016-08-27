#version 330
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
layout(location=0) in vec2 vertexPosition;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = vertexPosition;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}