import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { Projection, Vector3 } from "../types";

const triangleAssembly = createSlice({
  name: "triangleAssembly",
  initialState: {},
  reducers: {
    translate(state, action: PayloadAction<Vector3>) {},

    scale(state, action: PayloadAction<Vector3>) {},

    positionCamera(state, action: PayloadAction<Vector3>) {},

    lookAt(state, action: PayloadAction<Vector3>) {},

    setProjectionType(state, action: PayloadAction<Projection>) {},
  },
});

export default triangleAssembly.reducer;

export const { translate, scale, positionCamera, lookAt, setProjectionType } =
  triangleAssembly.actions;
