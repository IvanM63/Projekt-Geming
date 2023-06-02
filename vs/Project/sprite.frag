#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

// Texture samplers
uniform sampler2D ourTexture;
uniform vec3 colorAdjustment;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f) * vec4(0.00784314f, 0.203922f, 0.211765f,0.9f);
    texColor.rgb *= colorAdjustment ;
    gl_FragColor = texColor;
}