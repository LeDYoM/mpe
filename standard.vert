#version 330
in vec4 posAttr;
in vec4 colAttr;
//in vec2 vTextCoord0;
out vec4 fPosition;
out vec4 fColor;
//out vec2 fTextCoord0;
uniform mat4 matrix;

void main(void) {
    fPosition = matrix * posAttr;
    gl_Position = fPosition;
    fColor = colAttr;
}

/*
#version 330
in vec4 posAttr;
in vec4 colAttr;
//out vec4 vPosition;
out vec4 col;
uniform mat4 matrix;

void main() {
    col = colAttr;
    gl_Position = matrix * posAttr;
}
*/
