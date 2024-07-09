import { all, takeEvery } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import {
  rotateCamera,
  rotateObject,
  toggleSelection,
} from "../reducer/spheresAndLights";
import { PayloadAction } from "@reduxjs/toolkit";
import { Cardinal } from "../types";

export function* spheresAndLightsSaga(handle: EngineHandle) {
  yield all([
    takeEvery(rotateCamera.type, rotateCameraSaga(handle)),
    takeEvery(rotateObject, rotateObjectSaga(handle)),
    takeEvery(toggleSelection.type, toggleSelectionSaga(handle)),
  ]);
}

function rotateCameraSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Cardinal>) {
    handle.rotateCameraSpheresAndLights(payload);
  };
}

function rotateObjectSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<Cardinal>) {
    handle.rotateObjectSpheresAndLights(payload);
  };
}

function toggleSelectionSaga(handle: EngineHandle) {
  return function (action: PayloadAction<void>) {
    handle.toggleSelectionCameraSpheresAndLights();
  };
}
