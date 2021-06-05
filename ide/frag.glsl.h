R"(
#version 430

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform vec4 inColor;

void main(void)
{
    //color = inColor;
    color = vec4(1.0f,0.0f,0.0f,1.0f);
}
)"
