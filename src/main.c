#include "../include/shader.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
// test
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw: window creation
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "STUPID TRIANGLES", NULL, NULL);

  if (window == NULL) {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initalize GLAD");
    return -1;
  }

  Shader shader = createShader("/Users/craigsau/Documents/Programming/"
                               "LearnOpenGL/src/shaders/triangleVertex.glsl",
                               "/Users/craigsau/Documents/Programming/"
                               "LearnOpenGL/src/shaders/triangleFragment.glsl");
  if (shader.ID == 0) {
    fprintf(stderr, "Failed to create shader program\n");
    return -1;
  }

  // set up the vertex data (and buffer(s)) and configure vertex attributes
  float firstTriangle[] = {
      // first triangle
      // positions         // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(
      2,
      VAOs); // we can also generate multiple VAOs or buffers at the same time
  glGenBuffers(2, VBOs);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attribute(s). first triangle
  glBindVertexArray(VAOs[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidently
  // modify this VAO, but this rarely happens. Modifying other VAO's requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  // glBindVertexArray(0); // not really necessary as well, but beware of calls
  // that could affect VAOs while this one is bound (like binding element buffer
  // objects, or enabling/disabling vertex attributes)

  // uncomment this call to draw in wirefram polygons
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // render loop
  while (!glfwWindowShouldClose(window)) {
    // input
    processInput(window);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    useShader(&shader);
    // glUseProgram(shaderProgram);

    // draw our first triangle
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved, etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // (I would argue this isn't REAALLY optional but yanno what do i know)
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);

  // glfw: terminate, clearing all previously allocated GLFW resources
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
