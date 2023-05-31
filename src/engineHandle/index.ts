import { Commands } from "./wasmLoader/specs";

export class EngineHandle {
  private commands: Commands;

  constructor(commands: Commands) {
    this.commands = commands;
  }

  public sayHello(name: string, repeat: number) {
    return this.commands.sayHello(name, repeat);
  }
}
