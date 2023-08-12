import { CallbackSetters, Commands, ModuleControl } from "./wasmLoader/specs";

export class EngineHandle {
  private commands: Commands;

  constructor({ commands, callbackSetters }: ModuleControl) {
    this.commands = commands;
    this.setEngineCallbacks(callbackSetters);
  }

  private setEngineCallbacks(callbackSetters: CallbackSetters) {
    callbackSetters.onClearColorChange((color: number) =>
      console.log("Background color: ", color)
    );
  }

  public sayHello(name: string, repeat: number) {
    return this.commands.sayHello(name, repeat);
  }

  public initialize(canvasId: string, clearColor: number) {
    return this.commands.initialize(canvasId, clearColor);
  }

  public setUniform(type: number, color: number) {
    return this.commands.setUniform(type, color);
  }

  public setClearColor(color: number) {
    return this.commands.setClearColor(color);
  }
}
