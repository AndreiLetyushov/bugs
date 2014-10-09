
attribute highp vec4 vertex;
attribute mediump vec3 aTexCoords;
uniform mediump mat4 matrix;
uniform mediump mat4 projection;
uniform mediump mat3 textureTransformation;
varying mediump vec2 vTexCoords;
void main(void)
{
    vec3 tex = aTexCoords * textureTransformation;
    vTexCoords = vec2(tex.x, tex.y);
    gl_Position = projection * matrix * vertex;
}
