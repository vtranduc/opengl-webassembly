import { createSlice } from "@reduxjs/toolkit";
import { SpheresAndLights } from "../types";

const spheresAndLights = createSlice({
  name: "spheresAndLights",
  initialState: {} as SpheresAndLights,
  reducers: {},
});

export default spheresAndLights.reducer;

export const {} = spheresAndLights.actions;
