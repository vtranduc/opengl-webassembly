#include "../../headers/geometries/sphere.h"

Sphere::Sphere() : Sphere::Sphere(1.0f, 64, 64) {}

Sphere::Sphere(float radius_, int nTheta, int nPhi)
    : Geometry(getNumOfTriangles(nTheta, nPhi)), radius(radius_) {
    generateVertices(nTheta, nPhi);    
}

void Sphere::generateVertices(int nTheta, int nPhi) {
    #if ASSERT_VALID_ARGUMENTS
    assert(nTheta >= 8 && nTheta <= 256 && nPhi >= 8 && nPhi <= 256);
    #endif

    Vector3 v0, v1, v2, v3;
    int nTriangles = getNumOfTriangles(nTheta, nPhi);
    float deltaTheta = M_2PI / float(nTheta);
    float deltaPhi = M_PI / float(nPhi);
    v1.copy(Vector3::sphericalToCartesian(radius, 0.0f, deltaPhi, &v0));

    int i = 0;
    for (int iTheta = 1; iTheta <= nTheta; iTheta++) {
        setVertexValue(0.0f, i++);
        setVertexValue(0.0f, i++);
        setVertexValue(radius, i++);
        for (int j = 0; j < 3; j++) setVertexValue(v1[j], i++);
        Vector3::sphericalToCartesian(radius, float(iTheta) * deltaTheta, deltaPhi, &v1);
        for (int j = 0; j < 3; j++) setVertexValue(v1[j], i++);
    }

    for (int iPhi = 1; iPhi < nPhi - 1; iPhi++) {
        for (int iTheta = 0; iTheta < nTheta; iTheta++) {
            Vector3::sphericalToCartesian(radius, float(iTheta) * deltaTheta, float(iPhi) * deltaPhi, &v0);
            Vector3::sphericalToCartesian(radius, float(iTheta + 1) * deltaTheta, float(iPhi) * deltaPhi, &v1);
            Vector3::sphericalToCartesian(radius, float(iTheta) * deltaTheta, float(iPhi + 1) * deltaPhi, &v2);
            Vector3::sphericalToCartesian(radius, float(iTheta + 1) * deltaTheta, float(iPhi + 1) * deltaPhi, &v3);

            for (int j = 0; j < 3; j++) setVertexValue(v0[j], i++);
            for (int j = 0; j < 3; j++) setVertexValue(v2[j], i++);
            for (int j = 0; j < 3; j++) setVertexValue(v1[j], i++);

            for (int j = 0; j < 3; j++) setVertexValue(v1[j], i++);
            for (int j = 0; j < 3; j++) setVertexValue(v2[j], i++);
            for (int j = 0; j < 3; j++) setVertexValue(v3[j], i++);
        }
    }

    for (int j = 0; j < nTheta; j++) {
        int k = j * 9;

        setVertexValue(0.0f, i++);
        setVertexValue(0.0f, i++);
        setVertexValue(-radius, i++);

        setVertexValue(getVertexValue(k + 6), i++);
        setVertexValue(getVertexValue(k + 7), i++);
        setVertexValue(-getVertexValue(k + 8), i++);

        setVertexValue(getVertexValue(k + 3), i++);
        setVertexValue(getVertexValue(k + 4), i++);
        setVertexValue(-getVertexValue(k + 5), i++);
    }

    for (int iVertex = 0; iVertex < nTriangles * 3; iVertex++) {
        int index = iVertex * 3;
        v0.set(getVertexValue(index), getVertexValue(index + 1), getVertexValue(index + 2)).normalize();
        for (int j = 0; j < 3; j++) setNormalValue(v0[j], index + j);
    }
}

int Sphere::getNumOfTriangles(int nTheta, int nPhi) { return (nTheta + (nPhi - 2) * nTheta) * 2; };