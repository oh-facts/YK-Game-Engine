#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
    vec4 textureColor = texture(tex0, texCoord);
    FragColor = mix(textureColor, vec4(ourColor, 1.0), 0.5);
}
