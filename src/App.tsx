import "./App.css";
import { useDispatch } from "react-redux";
import { initialize, sayHello, setClearColor } from "./reducer";
import { useEffect, useRef } from "react";

function App() {
  const dispatch = useDispatch();
  const ref = useRef<HTMLCanvasElement>(null);

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
      </div>
      <canvas ref={ref} id="canvas" />
    </div>
  );
}

export default App;
