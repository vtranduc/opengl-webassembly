import {
  PayloadAction,
  Reducer,
  createAction,
  createSlice,
} from "@reduxjs/toolkit";
import { State, TestState } from "../types";

// Placeholder slice, to be removed

const testSlice = createSlice({
  name: "empty",
  initialState: {} as TestState,
  reducers: {
    sayHello(state, action: PayloadAction<{ name: string; repeat: number }>) {},
    setClearColor(state, action: PayloadAction<number>) {},
  },
});

const rootReducer: Record<keyof State, Reducer> = {
  test: testSlice.reducer,
};

const initialize = createAction("initialize");

export default rootReducer;

const { sayHello, setClearColor } = testSlice.actions;

export { sayHello, setClearColor, initialize };
