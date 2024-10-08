#include "../../../headers/math/geometry/sphere.h"

Sphere_::Sphere_(float radius, Vector3 surfaceColor) : r(radius), color(surfaceColor) { generateVertices(); };

Sphere_::~Sphere_() { delete[] mesh.vertices; delete[] mesh.normals; delete[] mesh.colors; }


void Sphere_::generateVertices(int nTheta, int nPhi) {
    #if ASSERT_VALID_ARGUMENTS
    assert(nTheta >= 8 && nTheta <= 256 && nPhi >= 8 && nPhi <= 256);
    #endif

    delete[] mesh.vertices; delete[] mesh.normals;

    Vector3 v0, v1, v2, v3;

    int nTriangles = (nTheta + (nPhi - 2) * nTheta) * 2;

    mesh.size = nTriangles * 9 * sizeof(GLfloat);
    mesh.count = nTriangles * 3;

    mesh.vertices = new GLfloat[nTriangles * 9];

    float deltaTheta = M_2PI / float(nTheta);
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

    for (int iPhi = 1; iPhi < nPhi - 1; iPhi++) {
        for (int iTheta = 0; iTheta < nTheta; iTheta++) {
            Vector3::sphericalToCartesian(r, float(iTheta) * deltaTheta, float(iPhi) * deltaPhi, &v0);
            Vector3::sphericalToCartesian(r, float(iTheta + 1) * deltaTheta, float(iPhi) * deltaPhi, &v1);
            Vector3::sphericalToCartesian(r, float(iTheta) * deltaTheta, float(iPhi + 1) * deltaPhi, &v2);
            Vector3::sphericalToCartesian(r, float(iTheta + 1) * deltaTheta, float(iPhi + 1) * deltaPhi, &v3);

            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v0[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v2[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];

            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v1[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v2[j];
            for (int j = 0; j < 3; j++) mesh.vertices[i++] = v3[j];
        }
    }

    for (int j = 0; j < nTheta; j++) {
        int k = j * 9;

        mesh.vertices[i++] = mesh.vertices[i++] = 0.0f;
        mesh.vertices[i++] = -r;

        mesh.vertices[i++] = mesh.vertices[k + 6];
        mesh.vertices[i++] = mesh.vertices[k + 7];
        mesh.vertices[i++] = -mesh.vertices[k + 8];

        mesh.vertices[i++] = mesh.vertices[k + 3];
        mesh.vertices[i++] = mesh.vertices[k + 4];
        mesh.vertices[i++] = -mesh.vertices[k + 5];
    }

    mesh.normals = new GLfloat[nTriangles * 9];

    for (int iVertex = 0; iVertex < nTriangles * 3; iVertex++) {
        int index = iVertex * 3;
        v0.set(mesh.vertices[index], mesh.vertices[index + 1], mesh.vertices[index + 2]).normalize();
        for (int j = 0; j < 3; j++) mesh.normals[index + j] = v0[j];
    }

    mesh.colors = new GLfloat[nTriangles * 9];

    for (int i = 0; i < nTriangles * 9; i += 3) {
        mesh.colors[i] = color[0];
        mesh.colors[i + 1] = color[1];
        mesh.colors[i + 2] = color[2];
    }
}
