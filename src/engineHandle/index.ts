import { onClearColorUpdated } from "../reducer";
import { onColorUpdate } from "../reducer/colorTriangle";
import { store } from "../store";
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

  public initialize(canvasId: string, clearColor: number) {
    return this.commands.initialize(canvasId, clearColor);
  }

  public setUniform(type: number, color: number) {
    return this.setColorTriangleColor(color);
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
}
