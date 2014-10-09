uniform sampler2D texture;
varying mediump vec2 vTexCoords;

void main(void)
{
    gl_FragColor = texture2D(texture, vTexCoords); //vec4(vTexCoords.x, vTexCoords.y, 0, 1);// texture2D(texture, vTexCoords);
}
