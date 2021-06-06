R"(
#version 430

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec4 inColor;
in vec4 varyingColor;

void main(void)
{
    //color = inColor;
    color = varyingColor;
}
)"
