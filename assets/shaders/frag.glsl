#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D Tex0;
// uniform sampler2D Tex1;

void main() {
       // FragColor = vec4(vecColor, 1.0);
       // FragColor = vec4(0.5, 0.0, 0.0, 1.0);
       FragColor = texture(Tex0, texCoord);
        // FragColor = mix(texture(Tex0, texCoord), texture(Tex1, texCoord), 0.2);
}
