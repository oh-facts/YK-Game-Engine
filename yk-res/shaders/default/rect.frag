#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex0;
uniform vec4 color;

void main()
{
    vec4 textureColor = texture(tex0, texCoord);

    if(textureColor.a < 0.1)
    {
        discard;
    }

    FragColor =  color * textureColor;
}
