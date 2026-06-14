# ESPOS (Operating System Architecture) - V0.1

An interactive, text-based command-line operating system simulation built entirely for the **Espressif ESP32-S3** microcontroller platform. ESPOS exposes silicon diagnostic controls, RF layer observation tools, active thermal load saturation testing engines, and interactive terminal games via standard asynchronous serial pipelines.

============================================
  ███████╗███████╗██████╗  ██████╗ ███████╗
  ██╔════╝██╔════╝██╔══██╗██╔═══██╗██╔════╝
  █████╗  ███████╗██████╔╝██║   ██║███████╗
  ██╔══╝  ╚════██║██╔═══╝ ██║   ██║╚════██║
  ███████╗███████║██║     ╚██████╔╝███████║ 
  ╚══════╝╚══════╝╚═╝      ╚═════╝ ╚══════╝  
============================================

---

## 🛠️ Hardware Requirements & Identification

This source configuration is optimized specifically for the following hardware stack:
* **Microcontroller:** Espressif ESP32-S3-WROOM-1
* **Flash Memory Configuration:** 16MB (Quad SPI / DIO)
* **PSRAM Configuration:** 8MB Octal SPI (OPI PSRAM)

---

## ⚙️ Arduino IDE Board Manager Compilation Settings

To correctly map the internal flash partitions and register the high-density memory buffers, you **must configure your Arduino IDE exactly** as shown below before compiling and flashing the sketch:

| Configuration Setting | Required Target Value |
| :--- | :--- |
| **Board** | `ESP32S3 Dev Module` |
| **USB CDC On Boot** | `"Enabled"` *(Required for native USB serial feedback)* |
| **CPU Frequency** | `"240MHz (WiFi)"` |
| **Core Debug Level** | `"None"` |
| **USB DFU On Boot** | `"Disabled"` |
| **Erase All Flash Before Sketch Upload** | `"Disabled"` |
| **Events Run On** | `"Core 1"` |
| **Flash Mode** | `"DIO 80MHz"` |
| **Flash Size** | `"16MB (128Mb)"` |
| **JTAG Adapter** | `"Disabled"` |
| **Arduino Runs On** | `"Core 1"` |
| **USB Firmware MSC On Boot** | `"Disabled"` |
| **Partition Scheme** | `"16M Flash (3MB APP/9.9MB FATFS)"` |
| **PSRAM** | `"OPI PSRAM"` *(Matches the 8MB R8 chip profile)* |
| **Upload Mode** | `"UART0 / Hardware CDC"` |
| **Upload Speed** | `"921600"` |
| **USB Mode** | `"Hardware CDC and JTAG"` |
| **Zigbee Mode** | `"Disabled"` |

---

## 🚀 Deployment & Connection Instructions

### 1. Flashing the Application (Code Upload)
* Connect your ESP32-S3 development board to your computer using the **COM/UART Port** (typically labeled *UART* or connected via a standard USB-to-Serial onboard bridge chip like the CP210x or CH340).
* Select the corresponding active COM Port in the Arduino IDE (`Tools` -> `Port`).
* Click **Upload** to write the binary image onto the flash memory layer.

### 2. Operating the Terminal (Runtime Interface)
* Once flashing is completed successfully, disconnect the cable from the UART port and connect your data cable into the **Native USB Port** on the module.
* Open your chosen Serial Terminal Monitor (Arduino Serial Monitor, PuTTY, or TeraTerm).
* Select the native USB COM port and assign the baseline transmission rate: **`115200 Baud`**.
* Ensure your terminal software configuration splits line endings with a newline character (`\n` or `NL`).
* Press `Enter` or input `help` inside the terminal interface to populate the primary system index register.

---

## 📑 Core Master Command Directory

* `help` - Displays the comprehensive terminal interface directory index.
* `specs` - Extracts engine clock variables, flash boundaries, and available heap space metrics.
* `temps` - Queries the internal silicon physical layer thermal sensors to log active and historical peak bounds.
* `stress` - Spawns a 4-minute continuous core processing math saturation stress cycle.
* `wifi` - Triggers an RF environment matrix scan across the 2.4GHz spectrum channels.
* `game` - Diverts standard execution priority to the text-based retro game subsystem engine.
* `heat` - Forces a 3-minute burst array load test. Contains safety traps that trigger a complete hardware sleep state if core temperature exceeds 75°C.
* `cold` - Constrains system frequency parameters down to a baseline 80MHz for 3 minutes to achieve thermal reduction.
* `frames` - Executes an asynchronous high-density text rendering pipeline pipeline throughput assessment.
* `reboot` - Dispatches a software-controlled warm boot reset sequence.
* `shut down` - Terminates standard runtime I/O lines and commands the module into deep zero-draw sleep.
