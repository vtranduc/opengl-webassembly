import { all, takeEvery } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { translate } from "../reducer/triangleAssembly";
import { PayloadAction } from "@reduxjs/toolkit";
import { Vector3 } from "../types";

export function* triangleAssemblySaga(handle: EngineHandle) {
  yield all([takeEvery(translate.type, translateSaga(handle))]);
}

function translateSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Vector3>) {
    handle.translateTriangleAssembly(payload);
  };
}
