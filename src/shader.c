#include "../include/shader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *readShaderSource(const char *filePath) {
  FILE *file = fopen(filePath, "r");
  if (!file) {
    fprintf(stderr, "Could not open file: %s\n", filePath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *source = (char *)malloc(length + 1);
  if (!source) {
    fprintf(stderr, "Could not allocate memory for shader source\n");
    fclose(file);
    return NULL;
  }

  fread(source, 1, length, file);
  source[length] = '\0';

  fclose(file);
  return source;
}

void checkCompileErrors(GLuint shader, const char *type) {
  GLint success;
  GLchar infoLog[1024];
  if (strcmp(type, "PROGRAM") == 0) {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type,
              infoLog);
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type,
              infoLog);
    }
  }
}

// Helper function to compile a shader
static GLuint compileShader(const char *source, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  checkCompileErrors(shader,
                     shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");

  // this is less logging than the chechCompileErrors function above, keeping
  // around for now
  // GLint compileStatus;
  // glGetShaderiv(shader, GL_COMPUTE_SHADER, &compileStatus);
  // if (compileStatus != GL_TRUE) {
  //     char buffer[512];
  //     glGetShaderInfoLog(shader, 512, NULL, buffer);
  //     fprintf(stderr, "Shader compile error: %s\n", buffer);
  //     glDeleteShader(shader);
  //     return 0;
  // }

  return shader;
}

// Function to initialize the shader (constructor equivalent)
Shader createShader(const char *vertexPath, const char *fragmentPath) {
  Shader shader;
  shader.ID = 0;

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("Version: %s\n", version);

  char *vertexSource = readShaderSource(vertexPath);
  char *fragmentSource = readShaderSource(fragmentPath);

  if (!vertexSource || !fragmentSource) {
    free(vertexSource);
    free(fragmentSource);
    return shader;
  }

  printf("Attempting to compile the vertex shader!\n");
  GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
  printf("Compiled the vertex shader!\n");
  printf("Attempting to compile the fragment shader!\n");
  GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
  printf("Compiled the fragment shader!\n");

  free(vertexSource);
  free(fragmentSource);

  if (!vertexShader || !fragmentShader) {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shader;
  }

  shader.ID = glCreateProgram();
  glAttachShader(shader.ID, vertexShader);
  glAttachShader(shader.ID, fragmentShader);
  glLinkProgram(shader.ID);

  GLint linkStatus;
  glGetProgramiv(shader.ID, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE) {
    char buffer[512];
    glGetProgramInfoLog(shader.ID, 512, NULL, buffer);
    fprintf(stderr, "Program link error: %s\n", buffer);
    glDeleteProgram(shader.ID);
    shader.ID = 0;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shader;
}

// Function to use / activate the shader
void useShader(const Shader *shader) { glUseProgram(shader->ID); }

// Utility uniform functions
void setShaderBool(const Shader *shader, const char *name, int value) {
  glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void setShaderInt(const Shader *shader, const char *name, int value) {
  glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void setShaderFloat(const Shader *shader, const char *name, float value) {
  glUniform1f(glGetUniformLocation(shader->ID, name), value);
}
