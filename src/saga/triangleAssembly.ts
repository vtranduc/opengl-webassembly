import { all, takeEvery, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import {
  lookAt,
  positionCamera,
  scale,
  translate,
} from "../reducer/triangleAssembly";
import { PayloadAction } from "@reduxjs/toolkit";
import { Vector3 } from "../types";

export function* triangleAssemblySaga(handle: EngineHandle) {
  initialSetUp(handle);
  yield all([
    takeEvery(translate.type, translateSaga(handle)),
    takeEvery(scale.type, scaleSaga(handle)),
    takeLatest(positionCamera.type, positionCameraSaga(handle)),
    takeLatest(lookAt.type, lookAtSaga(handle)),
  ]);
}

function initialSetUp(handle: EngineHandle) {
  handle.positionCameraTriangleAssembly([0, 0, 0.3]);
  handle.lookAtTriangleAssembly([0, 0, 0]);
}

function translateSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Vector3>) {
    handle.translateTriangleAssembly(payload);
  };
}

function scaleSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Vector3>) {
    handle.scaleTriangleAssembly(payload);
  };
}

function positionCameraSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Vector3>) {
    handle.positionCameraTriangleAssembly(payload);
  };
}

function lookAtSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Vector3>) {
    handle.lookAtTriangleAssembly(payload);
  };
}
