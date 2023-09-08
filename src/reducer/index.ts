import {
  PayloadAction,
  Reducer,
  createAction,
  createSlice,
} from "@reduxjs/toolkit";
import { State, TestState } from "../types";
import colorTriangleReducer from "./colorTriangle";

// Placeholder slice, to be removed

const testSlice = createSlice({
  name: "empty",
  initialState: {
    clearColor: 0x0000,
  } as TestState,
  reducers: {
    sayHello(state, action: PayloadAction<{ name: string; repeat: number }>) {},
    setClearColor(state, action: PayloadAction<number>) {},
    setPreset(state, action: PayloadAction<number>) {},
    onClearColorUpdated(state, { payload }: PayloadAction<number>) {
      state.clearColor = payload;
    },
  },
});

const rootReducer: Record<keyof State, Reducer> = {
  test: testSlice.reducer,
  colorTriangle: colorTriangleReducer,
};

export const initialize = createAction("initialize");

export default rootReducer;

export const { sayHello, setClearColor, setPreset, onClearColorUpdated } =
  testSlice.actions;
