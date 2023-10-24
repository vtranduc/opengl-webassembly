import { useDispatch, useSelector } from "react-redux";
import { Preset, State } from "../types";
import { useEffect } from "react";
import { translate } from "../reducer/triangleAssembly";

export function useInputs() {
  const preset = useSelector((state: State) => state.test.preset);

  const dispatch = useDispatch();

  useEffect(() => {
    switch (preset) {
      case Preset.TriangleAssembly:
        return triangleAssemblyListeners();
      default:
        return;
    }

    function triangleAssemblyListeners() {
      document.addEventListener("keydown", onKeyDown);

      function onKeyDown(e: KeyboardEvent) {
        e.preventDefault();
        e.stopPropagation();

        switch (e.key) {
          case "w":
            dispatch(translate([0.0, 0.1, 0.0]));
            break;
          case "s":
            dispatch(translate([0.0, -0.1, 0.0]));
            break;
          case "d":
            dispatch(translate([0.1, 0.0, 0.0]));
            break;
          case "a":
            dispatch(translate([-0.1, 0.0, 0.0]));
            break;
          default:
            break;
        }
      }
      return () => {
        document.removeEventListener("keydown", onKeyDown);
      };
    }
  }, [preset, dispatch]);
}
