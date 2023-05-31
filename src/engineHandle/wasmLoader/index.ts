import {
  Commands,
  exportedFunctions,
  id,
  path,
  timeoutInSeconds,
} from "./specs";

export async function loadWasm(): Promise<Commands> {
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => {
      reject("Timeout: Loading WASM has failed!");
    }, timeoutInSeconds * 1000);

    (window as any).Module = {
      arguments: ["strawberry"],
      preRun: [],
      postRun: [],
      onExit: function (a: any) {
        alert("EXIT: " + a);
      },
      onAbort: function (a: any) {
        alert("ABORTED: " + a);
      },
      print: function (text: any) {
        console.log("Engine : " + text);
      },
      printErr: function (text: any) {
        console.log("Module : Error : " + text);
      },
      setStatus: function (e: any) {
        console.log("Module : Status: " + e);
      },
      monitorRunDependencies: function (e: any) {
        console.log("Module : Dependencies: " + e);
      },
      onRuntimeInitialized: () => {
        clearTimeout(timer);
        const module = (window as any).Module;
        const commands = exportedFunctions.reduce((acc, data) => {
          return {
            ...acc,
            [data.name]: module.cwrap(data.name, data.return, data.params),
          };
        }, {}) as Commands;
        resolve(commands);
      },
    };

    const script = document.createElement("script");
    script.id = id;
    script.src = path;

    document.body.appendChild(script);
  });
}
