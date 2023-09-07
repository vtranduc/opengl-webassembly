import { RGBColor } from "react-color";

export function rgbToHex({ r, g, b }: RGBColor) {
  return (r << 16) | (g << 8) | b;
}

export function hexToRgb(hex: number): RGBColor {
  return {
    r: (hex >> 16) & 0xff,
    g: (hex >> 8) & 0xff,
    b: hex & 0xff,
  };
}
