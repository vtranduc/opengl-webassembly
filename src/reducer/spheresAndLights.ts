import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { CameraRotation, SpheresAndLights } from "../types";

const spheresAndLights = createSlice({
  name: "spheresAndLights",
  initialState: {} as SpheresAndLights,
  reducers: {
    rotateCamera(state, action: PayloadAction<CameraRotation>) {},

    toggleSelection(state, action: PayloadAction<void>) {},
  },
});

export default spheresAndLights.reducer;

export const { rotateCamera, toggleSelection } = spheresAndLights.actions;
