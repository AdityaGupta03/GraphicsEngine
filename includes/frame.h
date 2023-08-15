#ifndef GRAPHICSENGINE_FRAME_H
#define GRAPHICSENGINE_FRAME_H

#include "camera.h"

double lastX = 0.0;
double lastY = 0.0;
bool firstMouse = true;
bool mouseButtonPressed = false;

Camera camera(glm::vec3(0.0f, 0.0f, 1.0f));

static void error_callback(int err_code, const char *description);
static void frame_resize_callback(GLFWwindow *window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void start_frame();
void set_window_hints();
GLFWwindow *create_window();
int main();

#endif