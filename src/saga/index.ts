import { all, select, take, takeEvery, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { initialize, sayHello, setClearColor, setPreset } from "../reducer";
import { PayloadAction } from "@reduxjs/toolkit";
import { loadWasm } from "../engineHandle/wasmLoader";
import { ModuleControl } from "../engineHandle/wasmLoader/specs";
import { colorTriangleSaga } from "./colorTriangle";
import { Preset, State } from "../types";

export default function* saga() {
  yield take(initialize.type);
  yield engineSaga();
}

function* engineSaga() {
  const control: ModuleControl = yield loadWasm();
  const handle = new EngineHandle(control);
  const currentPreset: Preset = yield select(
    (state: State) => state.test.preset
  );
  const clearColor: number = yield select(
    (state: State) => state.test.clearColor
  );
  const result = handle.initialize("canvas", clearColor, currentPreset);
  if (!result) throw new Error("Failed to initialize the engine!");
  yield all([
    colorTriangleSaga(handle),
    takeLatest(sayHello.type, sayHelloSaga(handle)),
    takeLatest(setClearColor.type, setClearColorSaga(handle)),
    takeEvery(setPreset.type, setPresetSaga(handle)),
  ]);
}

function sayHelloSaga(handle: EngineHandle) {
  return function ({
    payload: { name, repeat },
  }: PayloadAction<{ name: string; repeat: number }>) {
    const str = handle.sayHello(name, repeat);
    console.log("Engine response: ", str);
  };
}

function setClearColorSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<number>) {
    handle.setClearColor(payload);
  };
}

function setPresetSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<number>) {
    handle.usePreset(payload);
  };
}
