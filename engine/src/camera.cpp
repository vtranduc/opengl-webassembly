#include "../headers/camera.h"

const GLfloat* Camera::getProjectionValue() { return projection.value(); }

const GLfloat* Camera::getViewValue() { return view.value(); }

void Camera::setPosition(const float* position) { view.setPosition(position[0], position[1], position[2]); };

void Camera::lookAt(const float* target) { view.lookAt(target[0], target[1], target[2]); };