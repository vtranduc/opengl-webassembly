#include "../../../headers/math/matrix/transformation.h"

TransformationMatrix::TransformationMatrix() : Matrix4() { identity(); };

TransformationMatrix& TransformationMatrix::translate(float x, float y, float z) {
    float coord[3] = {x, y, z};
    return translate(coord);
};

TransformationMatrix& TransformationMatrix::translate(float *coord) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 3; j++)  *(*this)[i][j] += coord[j] * *(*this)[i][3];
    return *this;
};

TransformationMatrix& TransformationMatrix::scale(float scalar) { return scale(scalar, scalar, scalar); };

TransformationMatrix& TransformationMatrix::scale(float x, float y, float z) {
    float scaleXYZ[3] = {x, y, z};
    return scale(scaleXYZ);
};

TransformationMatrix& TransformationMatrix::scale(float* scaleXYZ) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 3; j++) *(*this)[i][j] *= scaleXYZ[j];
    return *this;
};
