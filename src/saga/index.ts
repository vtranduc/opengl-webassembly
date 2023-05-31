import { all, takeLatest } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { sayHello } from "../reducer";
import { PayloadAction } from "@reduxjs/toolkit";

export default function* saga() {
  const handle = new EngineHandle();
  yield handle.initialize();
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
