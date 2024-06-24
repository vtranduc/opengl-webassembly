import {
  PayloadAction,
  Reducer,
  createAction,
  createSlice,
} from "@reduxjs/toolkit";
import { Preset, State, TestState } from "../types";
import colorTriangleReducer from "./colorTriangle";
import triangleAssemblyReducer from "./triangleAssembly";
import spheresAndLightsReducer from "./spheresAndLights";

// Placeholder slice, to be removed

const testSlice = createSlice({
  name: "empty",
  initialState: {
    preset: Preset.SpheresAndLights,
    clearColor: 0xc5d3eb,
  } as TestState,
  reducers: {
    sayHello(state, action: PayloadAction<{ name: string; repeat: number }>) {},
    setClearColor(state, action: PayloadAction<number>) {},
    setPreset(state, { payload }: PayloadAction<Preset>) {
      state.preset = payload;
    },
    onClearColorUpdated(state, { payload }: PayloadAction<number>) {
      state.clearColor = payload;
    },
  },
});

const rootReducer: Record<keyof State, Reducer> = {
  test: testSlice.reducer,
  colorTriangle: colorTriangleReducer,
  triangleAssembly: triangleAssemblyReducer,
  spheresAndLights: spheresAndLightsReducer,
};

export const initialize = createAction("initialize");

export default rootReducer;

export const { sayHello, setClearColor, setPreset, onClearColorUpdated } =
  testSlice.actions;
