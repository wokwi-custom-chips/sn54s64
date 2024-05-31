# Wokwi sn54s64 Chip

This is a custom chip for [Wokwi](https://wokwi.com/). It implements the sn54s64 IC.

## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
  "dependencies": {
    "chip-sn54s64": "github:wokwi-custom-chips/sn54s64@0.1.0"
  }
```

Then, add the chip to your circuit by adding a `chip-sn54s64` item to the `parts` section of diagram.json:

```json
  "parts": {
    ...,
    { "type": "chip-sn54s64", "id": "chip1" }
  },
```

For a complete example, see [The sn54s64 chip test project](https://wokwi.com/projects/399439793994800129).
