#include "../include/shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* readShaderSource(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = (char*)malloc(length + 1);
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

// Helper function to compile a shader
static GLuint compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPUTE_SHADER, &compileStatus);
    if (compileStatus != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        fprintf(stderr, "Shader compile error: %s\n", buffer);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Function to initialize the shader (constructor equivalent)
Shader createShader(const char *vertexPath, const char *fragmentPath) {
    Shader shader;
    shader.ID = 0;

    char* vertexSource = readShaderSource(vertexPath);
    char* fragmentSource = readShaderSource(fragmentPath);

    if (!vertexSource || !fragmentSource) {
        free(vertexSource);
        free(fragmentSource);
        return shader;
    }

    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

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
void useShader(const Shader* shader) {
    glUseProgram(shader->ID);
}

// Utility uniform functions
void setShaderBool(const Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value);
}

void setShaderInt(const Shader* shader, const char* name, int value) {
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void setShaderFloat(const Shader* shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}
