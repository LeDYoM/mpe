#version 330
//precision highp;
//in vec4 fPosition;
in vec4 fColor;
//in vec2 fTextCoord0;
out vec4 rColorOut0;
//uniform sampler2D texture;
void main(void) {
    //rColorOut0 = texture2D(texture, fTextCoord0.st);
    //rColorOut0.a = 0.5;
    rColorOut0 = fColor;
}

/*
#version 330
in vec4 col;
in vec4 vPosition;
out vec4 colorOut;
void main() {
    colorOut = col;
}
*/
