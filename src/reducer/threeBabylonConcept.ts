import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { ThreeBabylonConcept } from "../types";

const threeBabylonConcept = createSlice({
  name: "threeBabylonConcept",
  initialState: {} as ThreeBabylonConcept,
  reducers: {
    togglePostProcessing(state, action: PayloadAction<void>) {},
  },
});

export default threeBabylonConcept.reducer;

export const { togglePostProcessing } = threeBabylonConcept.actions;
