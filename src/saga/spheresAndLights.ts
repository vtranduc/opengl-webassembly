import { all, takeEvery } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { rotateCamera } from "../reducer/spheresAndLights";
import { PayloadAction } from "@reduxjs/toolkit";
import { CameraRotation } from "../types";

export function* spheresAndLightsSaga(handle: EngineHandle) {
  yield all([takeEvery(rotateCamera.type, rotateCameraSaga(handle))]);
}

function rotateCameraSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<CameraRotation>) {
    handle.rotateCameraSpheresAndLights(payload);
  };
}
