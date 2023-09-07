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

function App() {
  const dispatch = useDispatch();
  const ref = useRef<HTMLCanvasElement>(null);

  const [test, setTest] = useState<number>(0x000000);

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
          <SketchPicker
            color={hexToRgb(test)}
            onChange={(color) => setTest(rgbToHex(color.rgb))}
          />
          <SketchPicker
            color={hexToRgb(clearColor)}
            onChange={({ rgb }) => dispatch(setClearColor(rgbToHex(rgb)))}
          />
        </div>
      </div>
    </div>
  );
}

export default App;
