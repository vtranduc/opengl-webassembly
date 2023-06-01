import "./App.css";
import { useDispatch } from "react-redux";
import { sayHello, setClearColor } from "./reducer";

function App() {
  const dispatch = useDispatch();
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
      <canvas id="canvas" />
    </div>
  );
}

export default App;
