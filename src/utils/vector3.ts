import { Vector3 } from "../types";

export function cartesianToSpherical(xyz: Vector3): Vector3 {
  const r = getVector3Length(xyz);
  const phi = Math.atan2(xyz[0], xyz[2]);
  const theta = Math.atan2(
    Math.sqrt(xyz[0] * xyz[0] + xyz[2] * xyz[2]),
    xyz[1]
  );
  return [r, phi, theta];
}

export function sphericalToCartesian(rPhiTheta: Vector3): Vector3 {
  const sz = Math.sin(rPhiTheta[2]);
  const x = rPhiTheta[0] * sz * Math.sin(rPhiTheta[1]);
  const y = rPhiTheta[0] * Math.cos(rPhiTheta[2]);
  const z = rPhiTheta[0] * sz * Math.cos(rPhiTheta[1]);
  return [x, y, z];
}

export function rotatePoint(
  point: Vector3,
  pivot: Vector3,
  displacement: Vector3
): Vector3 {
  const arm = point.map((comp, i) => comp - pivot[i]) as Vector3;
  const spherical = cartesianToSpherical(arm);
  const displacedSpherical = spherical.map(
    (comp, i) => comp + displacement[i]
  ) as Vector3;
  const res = sphericalToCartesian(displacedSpherical).map(
    (comp, i) => comp + pivot[i]
  ) as Vector3;
  return res;
}

export function getVector3Length(vector: Vector3) {
  return Math.sqrt(vector.reduce((acc, val) => acc + val * val, 0));
}
