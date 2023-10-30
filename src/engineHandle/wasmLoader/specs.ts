enum WasmCommunicationDataType {
  String = "string",
  Number = "number",
}

interface wasmExportedFunctionData {
  name: string;
  return: WasmCommunicationDataType;
  params: WasmCommunicationDataType[];
}

export enum WasmCallbackType {
  vi = "vi",
}

type WasmCallback<T extends WasmCallbackType> = T extends WasmCallbackType.vi
  ? (param1: number) => void
  : never;

interface EngineCallback {
  name: string;
  type: WasmCallbackType;
}

// Modify accordingly to CMakeLists.txt and build.sh

const id = "engine";

const path = "/build/engine.js";

const timeoutInSeconds = 5;

// The following are to be modified accordingly to WebAssembly codes manually

// Engine commands

const exportedFunctions: wasmExportedFunctionData[] = [
  {
    name: "sayHello",
    return: WasmCommunicationDataType.String,
    params: [
      WasmCommunicationDataType.String,
      WasmCommunicationDataType.Number,
    ],
  },
  {
    name: "initialize",
    return: WasmCommunicationDataType.Number,
    params: [
      WasmCommunicationDataType.String,
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
    ],
  },
  {
    name: "usePreset",
    return: WasmCommunicationDataType.Number,
    params: [WasmCommunicationDataType.Number],
  },
  {
    name: "setClearColor",
    return: WasmCommunicationDataType.Number,
    params: [WasmCommunicationDataType.Number],
  },
  {
    name: "setColorTriangleColor",
    return: WasmCommunicationDataType.Number,
    params: [WasmCommunicationDataType.Number],
  },
  {
    name: "translateTriangleAssembly",
    return: WasmCommunicationDataType.Number,
    params: [
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
    ],
  },
  {
    name: "scaleTriangleAssembly",
    return: WasmCommunicationDataType.Number,
    params: [
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
    ],
  },
  {
    name: "positionCameraTriangleAssembly",
    return: WasmCommunicationDataType.Number,
    params: [
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
    ],
  },
  {
    name: "lookAtTriangleAssembly",
    return: WasmCommunicationDataType.Number,
    params: [
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
      WasmCommunicationDataType.Number,
    ],
  },
];

export { id, path, timeoutInSeconds, exportedFunctions };

export type Commands = {
  sayHello: (name: string, repeat: number) => string;
  initialize: (
    canvasId: string,
    clearColor: number,
    startingPreset: number
  ) => number;
  setClearColor: (color: number) => number;
  usePreset: (presetCode: number) => number;
  setColorTriangleColor: (color: number) => number;
  translateTriangleAssembly: (x: number, y: number, z: number) => number;
  scaleTriangleAssembly: (x: number, y: number, z: number) => number;
  positionCameraTriangleAssembly: (x: number, y: number, z: number) => number;
  lookAtTriangleAssembly: (x: number, y: number, z: number) => number;
};

// Callbacks from the engine

export const engineCallbacks: EngineCallback[] = [
  {
    name: "onClearColorChange",
    type: WasmCallbackType.vi,
  },
  {
    name: "onColorTriangleUpdated",
    type: WasmCallbackType.vi,
  },
];

export type CallbackSetters = {
  onClearColorChange: (callback: WasmCallback<WasmCallbackType.vi>) => number;
  onColorTriangleUpdated: (
    callback: WasmCallback<WasmCallbackType.vi>
  ) => number;
};

export interface ModuleControl {
  commands: Commands;
  callbackSetters: CallbackSetters;
}
