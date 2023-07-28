#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkVBO(VBO &VBO, GLuint layout, GLuint numComponents)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}