import { all, select, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { setColor } from "../reducer/colorTriangle";
import { PayloadAction } from "@reduxjs/toolkit";
import { ColorTriangleState, State } from "../types";

export function* colorTriangleSaga(handle: EngineHandle) {
  yield applyCurrent(handle);
  yield all([takeLatest(setColor.type, setColorSaga(handle))]);
}

function* applyCurrent(handle: EngineHandle) {
  const state: ColorTriangleState = yield select(
    (state: State) => state.colorTriangle
  );
  handle.setColorTriangleColor(state.color);
}

function setColorSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<number>) {
    handle.setColorTriangleColor(payload);
  };
}
