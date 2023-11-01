import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { Projection, TriangleAssemblyState, Vector3 } from "../types";

const triangleAssembly = createSlice({
  name: "triangleAssembly",
  initialState: {
    projection: Projection.Perspective,
    position: [0, 0, 0],
    scale: [1, 1, 1],
    camera: [0, 0, 1.8],
    target: [0, 0, 0],
  } as TriangleAssemblyState,
  reducers: {
    translate(state, action: PayloadAction<Vector3>) {},

    scale(state, action: PayloadAction<Vector3>) {},

    positionCamera(state, action: PayloadAction<Vector3>) {},

    rotateCamera(state, action: PayloadAction<Vector3>) {},

    lookAt(state, action: PayloadAction<Vector3>) {},

    setProjectionType(state, action: PayloadAction<Projection>) {},

    onProjectionUpdated(state, { payload }: PayloadAction<Projection>) {
      state.projection = payload;
    },

    onPositionChanged(state, { payload }: PayloadAction<Vector3>) {
      state.position = payload;
    },

    onScaleChanged(state, { payload }: PayloadAction<Vector3>) {
      state.scale = payload;
    },

    onCameraPositionChanged(state, { payload }: PayloadAction<Vector3>) {
      state.camera = payload;
    },

    onTargetChanged(state, { payload }: PayloadAction<Vector3>) {
      state.target = payload;
    },
  },
});

export default triangleAssembly.reducer;

export const {
  translate,
  scale,
  positionCamera,
  rotateCamera,
  lookAt,
  setProjectionType,
  onProjectionUpdated,
  onPositionChanged,
  onScaleChanged,
  onCameraPositionChanged,
  onTargetChanged,
} = triangleAssembly.actions;
