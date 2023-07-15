#ifndef GRAPHICSENGINE_FRAME_H
#define GRAPHICSENGINE_FRAME_H

static void error_callback(int err_code, const char *description);

static void frame_resize_callback(GLFWwindow *window, int width, int height);

void start_frame();

void set_window_hints();

void handle_window_resize(GLFWwindow *window);

int main();

#endif