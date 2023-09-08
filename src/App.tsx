import "./App.css";
import { useDispatch, useSelector } from "react-redux";
import {
  initialize,
  sayHello,
  setClearColor,
  setUniform,
  setPreset,
} from "./reducer";
import { useEffect, useRef, useState } from "react";
import { SketchPicker } from "react-color";
import { hexToRgb, rgbToHex } from "./utils";
import { State } from "./types";
import { setColor } from "./reducer/colorTriangle";

function App() {
  const dispatch = useDispatch();
  const ref = useRef<HTMLCanvasElement>(null);

  const color = useSelector((state: State) => state.colorTriangle.color);

  const [isClearColorPickerOpen, setIsClearColorPickerOpen] =
    useState<boolean>(false);

  const clearColor = useSelector((state: State) => state.test.clearColor);

  useEffect(() => {
    if (!ref.current) return;
    dispatch(initialize());
  }, [ref, dispatch]);

  return (
    <div>
      <div>
        <button
          onClick={() => dispatch(sayHello({ name: "Tanjiro", repeat: 7 }))}
        >
          Say Hello
        </button>
        <button onClick={() => dispatch(setClearColor(0xff00ff))}>
          Purple
        </button>
        <button onClick={() => dispatch(setClearColor(0xffff00))}>
          Yellow
        </button>
        <button onClick={() => dispatch(setClearColor(0xc5d3eb))}>
          Soft blue
        </button>
        <button
          onClick={() => dispatch(setUniform({ type: 0, data: 0x0000ff }))}
        >
          Blue Triangle
        </button>
        <button
          onClick={() => dispatch(setUniform({ type: 0, data: 0xffff00 }))}
        >
          Yellow triangle
        </button>
        <button onClick={() => dispatch(setPreset(0))}>Preset 0</button>
        <button onClick={() => dispatch(setPreset(1))}>Preset 1</button>
      </div>
      <div style={{ display: "flex" }}>
        <canvas ref={ref} id="canvas" />
        <div>
          <button
            onClick={() => setIsClearColorPickerOpen(!isClearColorPickerOpen)}
          >
            {isClearColorPickerOpen
              ? "⬆ Hide Clear Color Picker"
              : "⬇ Show Clear Color Picker"}
          </button>
          {isClearColorPickerOpen && (
            <SketchPicker
              color={hexToRgb(clearColor)}
              onChange={({ rgb }) => dispatch(setClearColor(rgbToHex(rgb)))}
            />
          )}
          <SketchPicker
            color={hexToRgb(color)}
            onChange={({ rgb }) => dispatch(setColor(rgbToHex(rgb)))}
          />
        </div>
      </div>
    </div>
  );
}

export default App;
