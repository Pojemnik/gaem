#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor;

in vec2 iTexCoord0;

void main(void) {
	pixelColor = texture(textureMap0, iTexCoord0); 
}
