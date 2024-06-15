#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

typedef struct {
  unsigned int ID;
} Shader;

// Function to initialize the shader (constructor equivalent)
Shader createShader(const char *vertexPath, const char *fragmentPath);

// Function to use / activate the shader
void useShader(const Shader *shader);

// Utility uniform functions
void setShaderBool(const Shader *shader, const char *name, int value);
void setShaderInt(const Shader *shader, const char *name, int value);
void setShaderFloat(const Shader *shader, const char *name, float value);

#endif // SHADER_H
