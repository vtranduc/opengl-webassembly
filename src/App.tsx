import "./App.css";
import { useDispatch } from "react-redux";
import { sayHello } from "./reducer";

function App() {
  const dispatch = useDispatch();
  return (
    <div>
      <button
        onClick={() => dispatch(sayHello({ name: "Tanjiro", repeat: 7 }))}
      >
        Say Hello
      </button>
      <canvas id="glCanvas" />
    </div>
  );
}

export default App;
