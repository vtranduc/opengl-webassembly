import { all, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { sayHello } from "../reducer";
import { PayloadAction } from "@reduxjs/toolkit";
import { loadWasm } from "../engineHandle/wasmLoader";
import { Commands } from "../engineHandle/wasmLoader/specs";

export default function* saga() {
  yield engineSaga();
}

function* engineSaga() {
  const commands: Commands = yield loadWasm();
  const handle = new EngineHandle(commands);
  yield all([takeLatest(sayHello.type, sayHelloSaga(handle))]);
}

function sayHelloSaga(handle: EngineHandle) {
  return function ({
    payload: { name, repeat },
  }: PayloadAction<{ name: string; repeat: number }>) {
    const str = handle.sayHello(name, repeat);
    console.log("Engine response: ", str);
  };
}
