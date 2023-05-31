enum WasmCommunicationDataType {
  String = "string",
  Number = "number",
}

interface wasmExportedFunctionData {
  name: string;
  return: WasmCommunicationDataType;
  params: WasmCommunicationDataType[];
}

// Modify accordingly to CMakeLists.txt and build.sh

const id = "engine";

const path = "/build/engine.js";

const timeoutInSeconds = 5;

// The following are to be modified accordingly to WebAssembly codes manually

const exportedFunctions: wasmExportedFunctionData[] = [
  {
    name: "sayHello",
    return: WasmCommunicationDataType.String,
    params: [
      WasmCommunicationDataType.String,
      WasmCommunicationDataType.Number,
    ],
  },
];

export { id, path, timeoutInSeconds, exportedFunctions };

export type Commands = {
  sayHello: (name: string, repeat: number) => string;
};
