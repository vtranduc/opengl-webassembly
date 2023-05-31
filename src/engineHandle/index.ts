import { loadWasm } from "./wasmLoader";
import { Commands } from "./wasmLoader/specs";

export class EngineHandle {
  private commands?: Commands;

  public async initialize() {
    this.commands = await loadWasm();
  }

  public sayHello(name: string, repeat: number) {
    return this.commands!.sayHello(name, repeat);
  }
}
