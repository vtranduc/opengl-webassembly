export enum Preset {
  ColorTriangle = 0,
  TriangleAssembly = 1,
}

export interface TestState {
  preset: Preset;
  clearColor: number;
}

export interface ColorTriangleState {
  color: number;
}

export interface TriangleAssemblyState {
  projection: Projection;
  position: Vector3;
  scale: Vector3;
  camera: Vector3;
  target: Vector3;
}

export type Vector3 = [number, number, number];

export interface TriangleAssemblyState {
  position: Vector3;
  scale: Vector3;
}

export interface State {
  test: TestState;
  colorTriangle: ColorTriangleState;
  triangleAssembly: TriangleAssemblyState;
}

export enum Projection {
  Orthographic = 0,
  Perspective = 1,
}
