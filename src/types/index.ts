export interface TestState {
  clearColor: number;
}

export interface ColorTriangleState {
  color: number;
}

export interface State {
  test: TestState;
  colorTriangle: ColorTriangleState;
}

export interface UniformData {
  type: number;
  data: number;
}
