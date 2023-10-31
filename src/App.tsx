import "./App.css";
import { useDispatch, useSelector } from "react-redux";
import { initialize, sayHello, setClearColor, setPreset } from "./reducer";
import { useEffect, useRef, useState } from "react";
import { SketchPicker } from "react-color";
import { hexToRgb, rgbToHex } from "./utils";
import { Preset, Projection, State } from "./types";
import { setColor } from "./reducer/colorTriangle";
import {
  positionCamera,
  scale,
  setProjectionType,
  translate,
} from "./reducer/triangleAssembly";

const presets: { type: Preset; name: string }[] = [
  { type: Preset.ColorTriangle, name: "Color Triangle" },
  { type: Preset.TriangleAssembly, name: "Triangle Assembly" },
];

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
        {presets.map((data, i) => (
          <button
            key={i}
            onClick={() => dispatch(setPreset(data.type))}
            disabled={preset === data.type}
          >
            {data.name}
          </button>
        ))}
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
  const dispatch = useDispatch();
  const [radius, setRadius] = useState<number>(1.8);
  const [phi, setPhi] = useState<number>(0);
  const [theta, setTheta] = useState<number>(Math.PI / 2);

  useEffect(() => {
    const sz = Math.sin(theta);
    const x = radius * sz * Math.sin(phi);
    const y = radius * Math.cos(theta);
    const z = radius * sz * Math.cos(phi);
    dispatch(positionCamera([x, y, z]));
  }, [radius, phi, theta, dispatch]);

  useEffect(() => {
    document.addEventListener("keydown", onKeyDown);

    function onKeyDown(e: KeyboardEvent) {
      e.preventDefault();
      e.stopPropagation();

      switch (e.key) {
        case "w":
          dispatch(translate([0.0, 0.0, -0.1]));
          break;
        case "s":
          dispatch(translate([0.0, 0.0, 0.1]));
          break;
        case "e":
          dispatch(translate([0.0, 0.1, 0.0]));
          break;
        case "q":
          dispatch(translate([0.0, -0.1, 0.0]));
          break;
        case "d":
          dispatch(translate([0.1, 0.0, 0.0]));
          break;
        case "a":
          dispatch(translate([-0.1, 0.0, 0.0]));
          break;
        case "ArrowRight":
          dispatch(scale([1.1, 1.0, 1.0]));
          break;
        case "ArrowLeft":
          dispatch(scale([0.9, 1.0, 1.0]));
          break;
        case "ArrowUp":
          dispatch(scale([1.0, 1.1, 1.0]));
          break;
        case "ArrowDown":
          dispatch(scale([1.0, 0.9, 1.0]));
          break;
        case "4":
          setPhi((oldPhi) => (oldPhi - 0.05) % (2 * Math.PI));
          break;
        case "6":
          setPhi((oldPhi) => (oldPhi + 0.05) % (2 * Math.PI));
          break;
        case "8":
          setTheta((oldTheta) => Math.max(0, oldTheta - 0.05));
          break;
        case "2":
          setTheta((oldTheta) => Math.min(Math.PI, oldTheta + 0.05));
          break;
        case "o":
          dispatch(setProjectionType(Projection.Orthographic));
          break;
        case "p":
          dispatch(setProjectionType(Projection.Perspective));
          break;
        case "+":
          setRadius((oldRadius) => Math.max(0, oldRadius - 0.05));
          break;
        case "-":
          setRadius((oldRadius) => oldRadius + 0.05);
          break;
        default:
          break;
      }
    }
    return () => {
      document.removeEventListener("keydown", onKeyDown);
    };
  }, [dispatch]);

  return <h3>Triangle Aseembly</h3>;
}
