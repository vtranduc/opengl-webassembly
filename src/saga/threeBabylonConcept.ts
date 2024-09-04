import { all, takeEvery } from "redux-saga/effects";
import { EngineHandle } from "../engineHandle";
import { PayloadAction } from "@reduxjs/toolkit";
import { togglePostProcessing } from "../reducer/threeBabylonConcept";

export function* threeBabylonConceptSaga(handle: EngineHandle) {
  yield all([
    takeEvery(togglePostProcessing.type, togglePostProcessingSaga(handle)),
  ]);
}

function togglePostProcessingSaga(handle: EngineHandle) {
  return function (action: PayloadAction<void>) {
    handle.togglePostProcessingThreeBabylonConcept();
  };
}
