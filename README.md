# 🟢 ESP32 8×8 LED Matrix — Shape Gallery

This project uses an **ESP32** and **74HC595 shift registers** to drive a **single 8×8 LED matrix** and display a gallery of **clear, high-contrast pixel shapes**.

Included categories:

* 💡 Cute / emoji faces
* 🧭 Geometric symbols
* ⚙ Mechanical designs
* 🎮 Retro-game sprites
* ❤️ Islamic art patterns
* 🧠 Math / fractal-style graphics

The display uses high-speed multiplexing so shapes appear **stable (no visible flicker)**.

---

## ✅ Features

* ESP32 compatible
* 1× 8×8 LED matrix
* Uses 74HC595 shift registers
* Dozens of premade shapes
* Smooth continuous slideshow
* Beginner-friendly code and wiring
* Easy to add your own pixel art

---

## 🧩 Hardware Required

| Item                   | Qty     | Notes                   |
| ---------------------- | ------- | ----------------------- |
| ESP32 Dev Board        | 1       | Any common ESP32        |
| 8×8 LED Matrix         | 1       | Common anode or cathode |
| 74HC595 shift register | 2       | Daisy-chained           |
| Resistors 220–1kΩ      | 8       | Current limiting        |
| Breadboard             | 1       |                         |
| Jumper wires           | several |                         |
| USB cable              | 1       | Programming             |

---

## 🔌 Wiring Overview

This project assumes:

* two **74HC595** shift registers
* one controls **rows**
* one controls **columns**
* columns are **active LOW**

### ESP32 Pins Used

| ESP32 GPIO | 74HC595       |
| ---------- | ------------- |
| GPIO 15    | DS (Data)     |
| GPIO 4     | SH_CP (Clock) |
| GPIO 2     | ST_CP (Latch) |
| 3.3V or 5V | VCC           |
| GND        | GND           |

> If shapes appear flipped or rotated, just swap matrix orientation or reverse wiring direction. The code logic is universal.

---

## 🖼️ Adding images to this README (wiring/photo)

1. Create a folder named:

```
images
```

2. Place your image files inside, for example:

```
images/wiring.png
images/project_photo.jpg
```

3. Reference them in README like this:

```markdown
![Wiring Diagram](images/wiring.png)
![Project Photo](images/project_photo.jpg)
```

GitHub will automatically display them.

---

## ▶️ Uploading the code

### Arduino IDE

1. Install Arduino IDE
2. Install **ESP32 Boards** support via Boards Manager
3. Select:

```
Tools → Board → ESP32 Dev Module
```

4. Select COM port
5. Paste project code
6. Upload

### PlatformIO (VS Code)

1. Install VS Code
2. Install PlatformIO extension
3. Create new project → board: `esp32dev`
4. Replace `src/main.cpp` with project code
5. Upload

---

## 🎨 Shapes Included

### 💡 Emoji

🙂 smile
😉 wink
😄 happy
☹ sad
😮 surprised

### 🧭 Geometric

⭕ circle
⬜ hollow square
⬛ solid square
❌ X-shape
◆ diamond
→ ← arrows

### ⚙ Mechanical

⚙ gear
🔩 hex nut
🌀 fan/turbine
⇅ piston actuator

### 🎮 Retro Game

👾 space invader
🚀 ship
❤️ pixel heart
👽 alien sprite

### ❤️ Islamic Art

✴ 8-point star
▣ framed star
▒ tile pattern
░ kufic grid style

### 🧠 Math / Fractal

▦ checkerboard
△ sierpinski-style
╲ diagonal slope
▇ equalizer bars

---

## ➕ Adding your own shapes

Each shape is 8 bytes, 1 byte per column, 1 bit per LED:

```cpp
const uint8_t MY_CUSTOM_SHAPE[8] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};
```

Then add to the shape list in code.

Upload again and it appears in the slideshow.

---

## 🛠 Troubleshooting

### Nothing lights

* check GND common
* check VCC
* verify COM port
* bad breadboard connections

### Shapes are mirrored / upside down

* rotate matrix
* swap row/column drivers
* reverse bit order in pattern

### Display flickers

* reduce multiplex delay
* check loose wires
* ensure good 5V supply if used

---

## 🚀 Future Improvements

* Button to change modes
* Wi-Fi app control (ESP32 web server)
* Bluetooth remote
* Sound-reactive equalizer
* Scrolling text
* Animation frames (bouncing ball, rotating gear)

---

## 📜 License

This project is free to use for:

* education
* hobby projects
* research
* commercial applications

MIT License recommended.

---

## 🙌 About This Project

This project is designed for:

* learning matrix multiplexing
* working with shift registers
* ESP32 GPIO practice
* pixel-art display creation
* embedded graphics experimentation

Have fun building and modifying it!
