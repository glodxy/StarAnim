#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

void main()
{
    int i;
    for(i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
        gl_Position = gl_in[i].gl_Position + vec4(gs_in[i].normal, 0.0)*0.1;
        EmitVertex();
        EndPrimitive();
    }

}