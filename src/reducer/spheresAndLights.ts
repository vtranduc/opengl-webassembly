import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { Cardinal, SpheresAndLights } from "../types";

const spheresAndLights = createSlice({
  name: "spheresAndLights",
  initialState: {} as SpheresAndLights,
  reducers: {
    rotateCamera(state, action: PayloadAction<Cardinal>) {},

    rotateObject(state, action: PayloadAction<Cardinal>) {},

    toggleSelection(state, action: PayloadAction<void>) {},
  },
});

export default spheresAndLights.reducer;

export const { rotateCamera, rotateObject, toggleSelection } =
  spheresAndLights.actions;
