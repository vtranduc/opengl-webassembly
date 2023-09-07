import {
  PayloadAction,
  Reducer,
  createAction,
  createSlice,
} from "@reduxjs/toolkit";
import { State, TestState, UniformData } from "../types";

// Placeholder slice, to be removed

const testSlice = createSlice({
  name: "empty",
  initialState: {
    clearColor: 0x0000,
  } as TestState,
  reducers: {
    sayHello(state, action: PayloadAction<{ name: string; repeat: number }>) {},
    setClearColor(state, action: PayloadAction<number>) {},
    setUniform(state, action: PayloadAction<UniformData>) {},
    setPreset(state, action: PayloadAction<number>) {},
    onClearColorUpdated(state, { payload }: PayloadAction<number>) {
      state.clearColor = payload;
    },
  },
});

const rootReducer: Record<keyof State, Reducer> = {
  test: testSlice.reducer,
};

export const initialize = createAction("initialize");

export default rootReducer;

export const {
  sayHello,
  setClearColor,
  setUniform,
  setPreset,
  onClearColorUpdated,
} = testSlice.actions;
