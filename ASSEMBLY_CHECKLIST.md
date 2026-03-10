# 🎯 Fingerbot Assembly Checklist

Use this checklist to track your assembly progress and ensure nothing is missed.

---

## ✅ Pre-Assembly Phase (Do This First!)

### Components Verification
- [ ] ESP32 DevKitC V4 on hand
- [ ] MT3608 boost converter module
- [ ] IRLZ44N MOSFET (N-channel, logic-level)
- [ ] 1N4007 Diode (general purpose rectifier)
- [ ] 100Ω resistor (for gate series)
- [ ] 100kΩ resistor (for gate pull-down)
- [ ] Solenoid (7.4V rated, 250mA)
- [ ] USB 5V power supply/charger (2A minimum recommended)
- [ ] Micro-USB cable (for ESP32 programming)
- [ ] Breadboard or PCB for assembly
- [ ] Jumper wires (various gauge for secure connections)
- [ ] Multimeter (for voltage verification)

### Documentation Review
- [ ] Read [WIRING.md](WIRING.md) completely
- [ ] Understand the three main circuit sections:
  1. Power & MT3608 boost circuit
  2. Solenoid control path (diode & MOSFET)
  3. ESP32 gate control with resistors
- [ ] Review safety warnings in WIRING.md
- [ ] Understand why 1N4007 diode is critical (flyback protection)
- [ ] Understand why 100kΩ pull-down is critical (prevents unwanted activation)

---

## ⚙️ Physical Assembly Phase

### MT3608 Boost Converter Setup
- [ ] Place MT3608 module on breadboard/PCB
- [ ] Locate the trimmer potentiometer (small screw on module)
- [ ] Connect USB 5V to MT3608 VIN+
- [ ] Connect USB GND to MT3608 VIN-
- [ ] **DO NOT CONNECT SOLENOID YET**

### Calibrate MT3608 Voltage
- [ ] Set multimeter to DC voltage measurement
- [ ] Connect multimeter + probe to MT3608 VOUT+
- [ ] Connect multimeter - probe to MT3608 VOUT-
- [ ] Read the voltage (should show ~5V initially)
- [ ] Using a small flathead screwdriver, slowly turn MT3608 trimmer potentiometer
- [ ] Target voltage: **7.4V - 8.0V**
- [ ] Once achieved, note "MT3608 calibrated to ___ V" (write down exact value)
- [ ] **WITHOUT LOAD** - do not connect solenoid during this adjustment!

### Power Distribution (Primary Rails)
- [ ] Run wire from USB 5V to ESP32 Micro-USB 5V in (via breadboard)
- [ ] Run wire from USB GND to ESP32 GND
- [ ] Run wire from USB 5V to MT3608 VIN+ (if not already done)
- [ ] Run wire from USB GND to MT3608 VIN-
- [ ] Create a **COMMON GND node** on breadboard where these wires meet:
  - [ ] USB charger GND wire
  - [ ] ESP32 GND wire
  - [ ] MT3608 VOUT- (return) wire
  - [ ] IRLZ44N SOURCE pin (drain return)
- [ ] Double-check: **All 4+ ground references physically touch at one breadboard node**

### Mount MOSFET (IRLZ44N)
- [ ] Position IRLZ44N on breadboard with 3 pins visible:
  - Gate (usually pin 1, leftmost)
  - Drain (usually pin 2, middle)
  - Source (usually pin 3, rightmost)
- [ ] **Verify pin orientation** using component datasheet or label on package
- [ ] Gate pin will connect to ESP32 GPIO 17 (via 100Ω resistor)
- [ ] Drain pin will connect to solenoid negative
- [ ] Source pin will connect to COMMON GND

### Install Flyback Diode (1N4007)
- [ ] Locate 1N4007 diode (black component with stripe on one end)
- [ ] **Cathode (stripe end)** must connect to MT3608 VOUT+
- [ ] **Anode (plain end)** must connect to the node where solenoid negative and MOSFET drain meet
- [ ] Do NOT reverse the polarity - this is critical!
- [ ] Route the diode so it's easily identifiable in final assembly

### Gate Control Resistor Network
- [ ] Take the 100Ω resistor
  - [ ] Connect one end to ESP32 GPIO 17 outpad
  - [ ] Connect other end to to IRLZ44N GATE pin
  - [ ] This resistor protects the gate from noise and ringing
  
- [ ] Take the 100kΩ resistor
  - [ ] Connect one end to IRLZ44N GATE pin (same node as 100Ω)
  - [ ] Connect other end to COMMON GND
  - [ ] This resistor pulls the gate LOW during ESP32 reset

- [ ] **Result**: Gate node should have 3 connections:
  1. From 100Ω resistor (toward GPIO 17)
  2. From 100kΩ resistor (toward GND)
  3. From MOSFET gate pin itself

### Connect Solenoid
- [ ] Identify solenoid positive and negative leads
- [ ] Take positive lead:
  - [ ] Connect through the 1N4007 diode (anode end)
  - [ ] Route to MT3608 VOUT+ rail
  
- [ ] Take negative lead:
  - [ ] Connect directly to IRLZ44N DRAIN pin
  - [ ] *This is the return path from solenoid through MOSFET to GND*

---

## 🔍 Pre-Power Verification

### Visual Inspection (NOT powered yet!)
- [ ] Scan entire breadboard for loose wires or cold connections
- [ ] Verify no wires are crossed or touching unintended nodes
- [ ] Check 1N4007 diode orientation one more time (stripe toward +)
- [ ] Confirm 100Ω and 100kΩ resistors are in place at gate node
- [ ] Trace path from ESP32 GPIO 17 → 100Ω → GATE → 100kΩ → GND
- [ ] Trace power path: USB 5V → ESP32, USB 5V → MT3608 → 7.4V out
- [ ] Trace ground path: All GND connections converge at one node

### Multimeter Continuity/Short Check (Component level)
Using your multimeter set to continuity/resistance mode:
- [ ] VOUT+ to GND: Should show **HIGH resistance** (>100kΩ) - NO SHORT
- [ ] MT3608 VOUT+ to MT3608 VOUT-: Should show **HIGH resistance** - NO SHORT
- [ ] Solenoid between its leads: Should show **1-5Ω resistance** (DC coil resistance)
- [ ] Gate pin to GND (with 100kΩ in place): Should show approximately 100kΩ

---

## 🔌 First Power-Up Phase

### Pre-Power Checklist
- [ ] All connections verified above
- [ ] USB power supply connected (but not to ESP32 yet)
- [ ] Solenoid NOT in any weird position (not strained)
- [ ] Multimeter standing by for measurements

### Apply Power (Step 1: MT3608 Only)
- [ ] Plug USB charger into wall/power source
- [ ] DO NOT plug ESP32 in yet
- [ ] Using multimeter, verify MT3608 VOUT = 7.4V (as calibrated before)
- [ ] If voltage is wrong, adjust trimmer back to 7.4V
- [ ] If voltage still wrong after adjustment, attempt recalibration from scratch

### Apply Power (Step 2: ESP32 Connected)
- [ ] Connect ESP32 Micro-USB cable to powered USB charger
- [ ] Listen carefully - solenoid should NOT click (gate pull-down should hold it LOW)
- [ ] Watch for LED lights on ESP32 (boot sequence)
- [ ] Open serial monitor:
  ```bash
  platformio device monitor --baud 115200
  ```
- [ ] You should see boot messages (see [QUICK_START.md](QUICK_START.md))
- [ ] If solenoid unexpectedly clicked: **Power off immediately**
  - Likely cause: Pull-down resistor not installed, or gate floating

---

## 💻 Software Configuration & Upload

### Configure WiFi (MANDATORY before upload)
- [ ] Open file: `include/config.h`
- [ ] Find these lines:
  ```cpp
  #define WiFi_SSID "YOUR_SSID"
  #define WiFi_PASSWORD "YOUR_PASSWORD"
  ```
- [ ] Replace `YOUR_SSID` with your actual WiFi network name in quotes
- [ ] Replace `YOUR_PASSWORD` with your actual WiFi password in quotes
- [ ] Examples:
  ```cpp
  #define WiFi_SSID "MyHomeWiFi"
  #define WiFi_PASSWORD "correct-horse-battery-staple"
  ```
- [ ] Save the file (Ctrl+S)

### Build & Upload Firmware
- [ ] In VS Code, connect the ESP32 via Micro-USB
- [ ] Open the PlatformIO terminal/sidebar
- [ ] Click "Build" (checkmark icon) - this compiles the code
- [ ] Wait for build to complete (should see "success" message)
- [ ] Click "Upload" (arrow icon) - this flashes the ESP32
- [ ] Wait for upload to complete (may take 30-60 seconds)
- [ ] You should see messages like:
  ```
  esptool.py write_flash ...
  Flash written successfully
  ```

- [ ] **If upload fails**, retry with a different USB cable or different USB port

---

## 🧪 Functional Testing

### Test 1: Serial Monitor Check
- [ ] Open serial monitor (PlatformIO plug icon or `platformio device monitor`)
- [ ] You should see the startup banner:
  ```
  ╔════════════════════════════════════════╗
  ║     FINGERBOT v1.0 - INITIALIZING      ║
  ╚════════════════════════════════════════╝
  ```
- [ ] Check for WiFi connection success:
  ```
  [WIFI] Connected!
  [WIFI] IP Address: 192.168.x.x
  ```
- [ ] Note the IP address (you'll need it for web access)
- [ ] Final message should show:
  ```
  [SETUP] Web server started on port 80
  ```

### Test 2: Web Interface Access
- [ ] Open a web browser on your computer
- [ ] Navigate to: `http://192.168.x.x/` (replace with your ESP32's IP)
- [ ] You should see a control panel with:
  - [ ] Large green "PRESS BUTTON"
  - [ ] Refresh Status button
  - [ ] Status box showing press count and WiFi connection
- [ ] If page doesn't load, check:
  - [ ] IP address is correct (verify in serial monitor)
  - [ ] ESP32 and computer are on same WiFi network
  - [ ] No firewall blocking port 80

### Test 3: First Solenoid Activation
- [ ] Watch solenoid (listen for click)
- [ ] Click "PRESS BUTTON" on web interface
- [ ] Expected result:
  - [ ] Audible **click** or **buzz** sound from solenoid
  - [ ] Duration: ~100ms (very brief)
  - [ ] Button becomes temporarily disabled
  - [ ] Serial monitor shows: `[SOLENOID] Pulse requested: 100ms`
  - [ ] Serial monitor shows: `[SOLENOID] Pulse complete. Total presses: 1`
  - [ ] Status page updates to show "Presses: 1"

### Test 4: Multiple Activations
- [ ] Click "PRESS BUTTON" 5 more times quickly
- [ ] Each click should:
  - [ ] Produce an audible response
  - [ ] Increment the press counter
  - [ ] Show in serial monitor
- [ ] Refresh status page: Should show "Presses: 6"
- [ ] If counter isn't incrementing, check NVS storage (probably OK, still learning)

### Final Hardware Test
- [ ] Weak/no click:
  - [ ] Verify MT3608 VOUT with multimeter: Should be 7.4V
  - [ ] Probe Gate pin with multimeter during press (should jump from 0V to ~3.3V)
  - [ ] Check solenoid leads aren't reversed
  
- [ ] Unexpected repeated clicks:
  - [ ] Check 100Ω/100kΩ resistors are installed correctly
  - [ ] Verify gate isn't floating (touching other wires)
  - [ ] Check for breadboard connection issues

---

## ✨ Success Criteria - Assembly Complete When:

- [ ] System boots without errors
- [ ] WiFi connects on first attempt
- [ ] Web interface loads
- [ ] Solenoid produces clear audible click
- [ ] Press counter increments
- [ ] Multiple activations work consistently
- [ ] No errors in serial monitor
- [ ] No resets or unexpected restarts

---

## 📝 Final Notes

**Assembly Date**: _______________

**MT3608 Calibration Voltage**: ________ V

**ESP32 IP Address**: 192.168.____.____

**WiFi Network Used**: _______________________

**First Test Result**: ✓ Success / □ Needs troubleshooting

**Notes/Observations**: 
_________________________________________________________________________
_________________________________________________________________________

---

**🎉 Congratulations!** If you've checked everything above, your Fingerbot is ready to use!

See [QUICK_START.md](QUICK_START.md) for advanced configurations and troubleshooting.
