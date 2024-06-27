import "./App.css";
import { useDispatch, useSelector } from "react-redux";
import { initialize, sayHello, setClearColor, setPreset } from "./reducer";
import { useEffect, useRef, useState } from "react";
import { SketchPicker } from "react-color";
import { hexToRgb, rgbToHex } from "./utils";
import { CameraRotation, Preset, Projection, State } from "./types";
import { setColor } from "./reducer/colorTriangle";
import {
  rotateCamera,
  scale,
  setProjectionType,
  translate,
} from "./reducer/triangleAssembly";
import {
  rotateCamera as rotateCameraSpheresAndLights,
  toggleSelection,
} from "./reducer/spheresAndLights";

const presets: { type: Preset; name: string }[] = [
  { type: Preset.ColorTriangle, name: "Color Triangle" },
  { type: Preset.TriangleAssembly, name: "Triangle Assembly" },
  { type: Preset.SpheresAndLights, name: "Spheres and Lights" },
];

function App() {
  const dispatch = useDispatch();
  const ref = useRef<HTMLCanvasElement>(null);

  const preset = useSelector((state: State) => state.test.preset);

  const [isClearColorPickerOpen, setIsClearColorPickerOpen] =
    useState<boolean>(false);

  const clearColor = useSelector((state: State) => state.test.clearColor);

  useEffect(() => {
    const canvas = ref.current;
    if (!canvas) return;
    canvas.width = 800;
    canvas.height = 800;
    dispatch(initialize());
  }, [ref, dispatch]);

  function getPanel() {
    switch (preset) {
      case Preset.ColorTriangle:
        return <ColorTrianglePanel />;
      case Preset.TriangleAssembly:
        return <TriangleAssemblyPanel />;
      case Preset.SpheresAndLights:
        return <SpheresAndLightsPanel />;
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
          dispatch(rotateCamera([0, -0.05, 0]));
          break;
        case "6":
          dispatch(rotateCamera([0, 0.05, 0]));

          break;
        case "8":
          dispatch(rotateCamera([0, 0, -0.05]));

          break;
        case "2":
          dispatch(rotateCamera([0, 0, 0.05]));
          break;
        case "o":
          dispatch(setProjectionType(Projection.Orthographic));
          break;
        case "p":
          dispatch(setProjectionType(Projection.Perspective));
          break;
        case "+":
          dispatch(rotateCamera([-0.05, 0, 0]));
          break;
        case "-":
          dispatch(rotateCamera([0.05, 0, 0]));
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

function SpheresAndLightsPanel() {
  const dispatch = useDispatch();

  useEffect(() => {
    document.addEventListener("keydown", onKeyDown);
    function onKeyDown(e: KeyboardEvent) {
      e.preventDefault();
      e.stopPropagation();
      switch (e.key) {
        case "4":
          dispatch(rotateCameraSpheresAndLights(CameraRotation.Left));
          break;
        case "6":
          dispatch(rotateCameraSpheresAndLights(CameraRotation.Right));
          break;
        case "8":
          dispatch(rotateCameraSpheresAndLights(CameraRotation.Up));
          break;
        case "2":
          dispatch(rotateCameraSpheresAndLights(CameraRotation.Down));
          break;
        case " ":
          dispatch(toggleSelection());
          break;
        default:
          break;
      }
    }
    return () => {
      document.removeEventListener("keydown", onKeyDown);
    };
  }, [dispatch]);

  return null;
}
