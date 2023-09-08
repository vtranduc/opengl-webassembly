import "./App.css";
import { useDispatch, useSelector } from "react-redux";
import { initialize, sayHello, setClearColor, setPreset } from "./reducer";
import { useEffect, useRef, useState } from "react";
import { SketchPicker } from "react-color";
import { hexToRgb, rgbToHex } from "./utils";
import { Preset, State } from "./types";
import { setColor } from "./reducer/colorTriangle";

function App() {
  const dispatch = useDispatch();
  const ref = useRef<HTMLCanvasElement>(null);

  const preset = useSelector((state: State) => state.test.preset);

  const [isClearColorPickerOpen, setIsClearColorPickerOpen] =
    useState<boolean>(false);

  const clearColor = useSelector((state: State) => state.test.clearColor);

  useEffect(() => {
    if (!ref.current) return;
    dispatch(initialize());
  }, [ref, dispatch]);

  function getPanel() {
    switch (preset) {
      case Preset.ColorTriangle:
        return <ColorTrianglePanel />;
      case Preset.TriangleAssembly:
        return <TriangleAssemblyPanel />;
      default:
        return null;
    }
  }

  return (
    <div>
      <div>
        <button
          onClick={() => dispatch(sayHello({ name: "Tanjiro", repeat: 7 }))}
        >
          Say Hello
        </button>
        <button onClick={() => dispatch(setPreset(Preset.ColorTriangle))}>
          Color Triangle
        </button>
        <button onClick={() => dispatch(setPreset(Preset.TriangleAssembly))}>
          Triangle Assembly
        </button>
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
          {getPanel()}
        </div>
      </div>
    </div>
  );
}

export default App;

function ColorTrianglePanel() {
  const dispatch = useDispatch();
  const color = useSelector((state: State) => state.colorTriangle.color);

  return (
    <>
      <h3>Color Triangle</h3>
      <SketchPicker
        color={hexToRgb(color)}
        onChange={({ rgb }) => dispatch(setColor(rgbToHex(rgb)))}
      />
    </>
  );
}

function TriangleAssemblyPanel() {
  return <h3>Triangle Aseembly</h3>;
}
