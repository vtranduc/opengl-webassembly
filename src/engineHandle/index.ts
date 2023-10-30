import { onClearColorUpdated } from "../reducer";
import { onColorUpdate } from "../reducer/colorTriangle";
import { store } from "../store";
import { Vector3 } from "../types";
import { CallbackSetters, Commands, ModuleControl } from "./wasmLoader/specs";

export class EngineHandle {
  private commands: Commands;

  constructor({ commands, callbackSetters }: ModuleControl) {
    this.commands = commands;
    this.setEngineCallbacks(callbackSetters);
  }

  private setEngineCallbacks(callbackSetters: CallbackSetters) {
    callbackSetters.onClearColorChange((color: number) =>
      store.dispatch(onClearColorUpdated(color))
    );
    callbackSetters.onColorTriangleUpdated((color: number) =>
      store.dispatch(onColorUpdate(color))
    );
  }

  public sayHello(name: string, repeat: number) {
    return this.commands.sayHello(name, repeat);
  }

  public initialize(
    canvasId: string,
    clearColor: number,
    startingPreset: number
  ) {
    return this.commands.initialize(canvasId, clearColor, startingPreset);
  }

  public setClearColor(color: number) {
    return this.commands.setClearColor(color);
  }

  public usePreset(presetCode: number) {
    return this.commands.usePreset(presetCode);
  }

  public setColorTriangleColor(color: number) {
    return this.commands.setColorTriangleColor(color);
  }

  public translateTriangleAssembly(displacement: Vector3) {
    return this.commands.translateTriangleAssembly(
      displacement[0],
      displacement[1],
      displacement[2]
    );
  }

  public scaleTriangleAssembly(scale: Vector3) {
    return this.commands.scaleTriangleAssembly(scale[0], scale[1], scale[2]);
  }

  public positionCameraTriangleAssembly(position: Vector3) {
    return this.commands.positionCameraTriangleAssembly(
      position[0],
      position[1],
      position[2]
    );
  }

  public lookAtTriangleAssembly(target: Vector3) {
    return this.commands.lookAtTriangleAssembly(
      target[0],
      target[1],
      target[2]
    );
  }
}
