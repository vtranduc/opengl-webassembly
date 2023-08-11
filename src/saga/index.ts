import { all, take, takeEvery, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { initialize, sayHello, setClearColor, setUniform } from "../reducer";
import { PayloadAction } from "@reduxjs/toolkit";
import { loadWasm } from "../engineHandle/wasmLoader";
import { Commands } from "../engineHandle/wasmLoader/specs";
import { UniformData } from "../types";

export default function* saga() {
  yield take(initialize.type);
  yield engineSaga();
}

function* engineSaga() {
  const commands: Commands = yield loadWasm();
  const handle = new EngineHandle(commands);
  const result = handle.initialize("canvas", 0xc5d3eb);
  if (!result) throw new Error("Failed to initialize the engine!");
  yield all([
    takeLatest(sayHello.type, sayHelloSaga(handle)),
    takeLatest(setClearColor.type, setClearColorSaga(handle)),
    takeEvery(setUniform.type, setUniformSaga(handle)),
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

function setUniformSaga(handle: EngineHandle) {
  return function ({ payload }: PayloadAction<UniformData>) {
    handle.setUniform(payload.type, payload.data);
  };
}
