import { PayloadAction, Reducer, createSlice } from "@reduxjs/toolkit";
import { State } from "../types";

// Placeholder slice, to be removed

const emptySlice = createSlice({
  name: "empty",
  initialState: {},
  reducers: {
    sayHello(state, action: PayloadAction<{ name: string; repeat: number }>) {},
  },
});

const rootReducer: Record<keyof State | "empty", Reducer> = {
  empty: emptySlice.reducer,
};

export default rootReducer;

const { sayHello } = emptySlice.actions;

export { sayHello };
