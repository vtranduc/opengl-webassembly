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
  vfff = "vfff",
}

export type WasmCallback<T extends WasmCallbackType> =
  T extends WasmCallbackType.vi
    ? (param0: number) => void
    : T extends WasmCallbackType.vfff
    ? (param0: number, param1: number, param2: number) => void
    : never;

interface EngineCallback {
  name: string;
  types: WasmCallbackType[];
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
  {
    name: "setProjectionTypeTriangleAssembly",
    return: WasmCommunicationDataType.Number,
    params: [WasmCommunicationDataType.Number],
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
  setProjectionTypeTriangleAssembly: (type: number) => number;
};

// Callbacks from the engine

export const engineCallbacks: EngineCallback[] = [
  {
    name: "onClearColorChange",
    types: [WasmCallbackType.vi],
  },
  {
    name: "onColorTriangleUpdated",
    types: [WasmCallbackType.vi],
  },
  {
    name: "onTriangleAssemblyUpdated",
    types: [
      WasmCallbackType.vi,
      WasmCallbackType.vfff,
      WasmCallbackType.vfff,
      WasmCallbackType.vfff,
      WasmCallbackType.vfff,
    ],
  },
];

export type CallbackSetters = {
  onClearColorChange: (
    callbacks: [WasmCallback<WasmCallbackType.vi>]
  ) => number;
  onColorTriangleUpdated: (
    callbacks: [WasmCallback<WasmCallbackType.vi>]
  ) => number;
  onTriangleAssemblyUpdated: (
    callbacks: [
      WasmCallback<WasmCallbackType.vi>,
      WasmCallback<WasmCallbackType.vfff>,
      WasmCallback<WasmCallbackType.vfff>,
      WasmCallback<WasmCallbackType.vfff>,
      WasmCallback<WasmCallbackType.vfff>
    ]
  ) => number;
};

export interface ModuleControl {
  commands: Commands;
  callbackSetters: CallbackSetters;
}
