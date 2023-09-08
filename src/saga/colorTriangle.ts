import { all, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { setColor } from "../reducer/colorTriangle";
import { PayloadAction } from "@reduxjs/toolkit";

export function* colorTriangleSaga(handle: EngineHandle) {
  yield all([takeLatest(setColor.type, setColorSaga(handle))]);
}

function setColorSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<number>) {
    handle.setColorTriangleColor(payload);
  };
}
