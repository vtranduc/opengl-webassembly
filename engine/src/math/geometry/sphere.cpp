#include "../../../headers/math/geometry/sphere.h"

Sphere::Sphere() { generateVertices(); };

Sphere::~Sphere() { delete[] mesh.vertices; }

GLfloat* Sphere::getVertices() const { return mesh.vertices; }

 GLsizeiptr Sphere::getSize() const { return mesh.size; }

GLsizei Sphere::getCount() const { return mesh.count; }

void Sphere::generateVertices(int nTheta, int nPhi) {
    #if ASSERT_VALID_ARGUMENTS
    assert(nTheta >= 8 && nTheta <= 128 && nPhi >= 8 && nPhi <= 128);
    #endif

    delete[] mesh.vertices;

    Vector3 v0, v1, v2, v3;

    int nTriangles = (nTheta + (nPhi - 2) * nTheta) * 2;

    mesh.vertices = new GLfloat[nTriangles * 9];

    float deltaTheta = 2.0f * M_PI / float(nTheta);
    float deltaPhi = M_PI / float(nPhi);

    v1.copy(Vector3::sphericalToCartesian(r, 0.0f, deltaPhi, &v0));

    int i = 0;

    for (int iTheta = 1; iTheta < nTheta; iTheta++) {
        mesh.vertices[i++] = 0.0f;
        mesh.vertices[i++] = 0.0f;
        mesh.vertices[i++] = r;
        for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
        Vector3::sphericalToCartesian(r, float(iTheta) * deltaTheta, deltaPhi, &v1);
        for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
    }
    mesh.vertices[i++] = 0.0f;
    mesh.vertices[i++] = 0.0f;
    mesh.vertices[i++] = r;
    for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
    for (int j = 0; j < 3; j++) mesh.vertices[i++] = v0[j];

    for (int j = 0; j < nTheta * 9; j++) mesh.vertices[i++] = j % 3 == 2 ? -mesh.vertices[j] : mesh.vertices[j];

    for (int iPhi = 1; iPhi < nPhi - 1; iPhi++) {
        for (int iTheta = 0; iTheta < nTheta; iTheta++) {
            Vector3::sphericalToCartesian(r, float(iTheta) * deltaTheta, float(iPhi) * deltaPhi, &v0);
            Vector3::sphericalToCartesian(r, float(iTheta + 1) * deltaTheta, float(iPhi) * deltaPhi, &v1);
            Vector3::sphericalToCartesian(r, float(iTheta) * deltaTheta, float(iPhi + 1) * deltaPhi, &v2);
            Vector3::sphericalToCartesian(r, float(iTheta + 1) * deltaTheta, float(iPhi + 1) * deltaPhi, &v3);

            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v0[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v2[j];

            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v2[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v3[j];
        }
    }

    mesh.size = nTriangles * 9 * sizeof(GLfloat);
    mesh.count = nTriangles * 3;
}