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

export interface State {
  test: TestState;
  colorTriangle: ColorTriangleState;
}
