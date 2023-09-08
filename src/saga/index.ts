import { all, take, takeEvery, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { initialize, sayHello, setClearColor, setPreset } from "../reducer";
import { PayloadAction } from "@reduxjs/toolkit";
import { loadWasm } from "../engineHandle/wasmLoader";
import { ModuleControl } from "../engineHandle/wasmLoader/specs";
import { colorTriangleSaga } from "./colorTriangle";

export default function* saga() {
  yield take(initialize.type);
  yield engineSaga();
}

function* engineSaga() {
  const control: ModuleControl = yield loadWasm();
  const handle = new EngineHandle(control);
  const result = handle.initialize("canvas", 0xc5d3eb);
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
