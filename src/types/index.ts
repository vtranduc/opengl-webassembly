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
