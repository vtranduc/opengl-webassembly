import { PayloadAction, createSlice } from "@reduxjs/toolkit";
import { ColorTriangleState } from "../types";

const colorTriangleSlice = createSlice({
  name: "colorTriangle",
  initialState: {
    color: 0xff00ff,
  } as ColorTriangleState,
  reducers: {
    setColor(state, action: PayloadAction<number>) {},

    onColorUpdate(state, { payload }: PayloadAction<number>) {
      state.color = payload;
    },
  },
});

export default colorTriangleSlice.reducer;

export const { setColor, onColorUpdate } = colorTriangleSlice.actions;
