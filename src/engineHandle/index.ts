import { Commands } from "./wasmLoader/specs";

export class EngineHandle {
  private commands: Commands;

  constructor(commands: Commands) {
    this.commands = commands;
  }

  public sayHello(name: string, repeat: number) {
    return this.commands.sayHello(name, repeat);
  }

  public initialize(canvasId: string, clearColor: number) {
    return this.commands.initialize(canvasId, clearColor);
  }

  public setClearColor(color: number) {
    return this.commands.setClearColor(color);
  }
}
