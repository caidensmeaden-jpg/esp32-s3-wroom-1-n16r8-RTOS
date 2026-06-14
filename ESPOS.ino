#include <Arduino.h>
#include <WiFi.h>
#include "esp_sleep.h"

bool commandLineActive = true;
float peakTemp = 0.0;

void initTempSensor();
float getTemperature();
void runCpuStress(int minutes);
void scanWifi();
void launchGames();
void playTicTacToe();
void playTetris();
void runHeatFunction();
void runColdFunction();
void runFramesTest();

void setup() {
  Serial.begin(115200);
  delay(1500);
  initTempSensor();
  
  Serial.println("\r\n========================================================");
  Serial.println("  ███████╗███████╗██████╗  ██████╗ ███████╗   ██╗   ██╗ ");
  Serial.println("  ██╔════╝██╔════╝██╔══██╗██╔═══██╗██╔════╝   ██║   ██║ ");
  Serial.println("  █████╗  ███████╗██████╔╝██║   ██║███████╗   ██║   ██║ ");
  Serial.println("  ██╔══╝  ╚════██║██╔═══╝ ██║   ██║╚════██║   ╚██╗ ██╔╝ ");
  Serial.println("  ███████╗███████║██║     ╚██████╔╝███████║    ╚████╔╝  ");
  Serial.println("  ╚══════╝╚══════╝╚═╝      ╚═════╝ ╚══════╝     ╚═══╝   ");
  Serial.println("========================================================");
  Serial.println("            OPERATING SYSTEM ARCHITECTURE               ");
  Serial.println("         VERSION: V0.1 | HARDWARE: ESP32-S3             ");
  Serial.println("   Input 'help' into the terminal to begin operations. ");
  Serial.println("========================================================\r\n");
  Serial.print("espos> ");
}

void loop() {
  if (!commandLineActive) {
    if (Serial.available()) {
      Serial.read();
    }
    return;
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.length() > 0) {
      Serial.println(command);

      if (command.equalsIgnoreCase("help")) {
        Serial.println("\r\n+------------------ ESPOS V0.1 MASTER COMMAND REGISTER ------------------+");
        Serial.printf("| %-12s : %-53s |\n", "help", "Displays this comprehensive command directory index.");
        Serial.printf("| %-12s : %-53s |\n", "specs", "Extracts engine configurations and Silicon specifications.");
        Serial.printf("| %-12s : %-53s |\n", "temps", "Queries current, active thermal metrics and history peaks.");
        Serial.printf("| %-12s : %-53s |\n", "stress", "Initiates 4-minute continuous cycle processing core stress.");
        Serial.printf("| %-12s : %-53s |\n", "wifi", "Triggers RF environment matrix scanning (Connection locked).");
        Serial.printf("| %-12s : %-53s |\n", "game", "Launches the localized text-based game subsystem engine.");
        Serial.printf("| %-12s : %-53s |\n", "heat", "Forces 100% load saturation on all matrices for 3 minutes.");
        Serial.printf("| %-12s : %-53s |\n", "cold", "Drops operating frequency states to baseline for 3 minutes.");
        Serial.printf("| %-12s : %-53s |\n", "frames", "Performs a 60-second high-density pipeline throughput test.");
        Serial.printf("| %-12s : %-53s |\n", "shut down", "Terminals standard I/O pipelines and enters zero-draw state.");
        Serial.printf("| %-12s : %-53s |\n", "reboot", "Triggers a software-controlled warm reset sequence.");
        Serial.println("+------------------------------------------------------------------------+\r\n");
      } 
      else if (command.equalsIgnoreCase("specs")) {
        Serial.println("\r\n================= SILICON SPECIFICATION MATRIX =================");
        Serial.printf("  CPU Execution Clock Speed : %d MHz\n", ESP.getCpuFreqMHz());
        Serial.printf("  System Internal ROM Size  : %d Bytes\n", ESP.getFlashChipSize());
        Serial.printf("  Allocated Heap Footprint  : %d Bytes\n", ESP.getHeapSize());
        Serial.printf("  Available Memory Space    : %d Bytes\n", ESP.getFreeHeap());
        Serial.printf("  Minimum Ever Free Heap    : %d Bytes\n", ESP.getMinFreeHeap());
        Serial.printf("  Silicon Chip Revision ID  : %d\n", ESP.getChipRevision());
        Serial.printf("  Espressif SDK Framework   : %s\n", ESP.getSdkVersion());
        Serial.println("================================================================\r\n");
      } 
      else if (command.equalsIgnoreCase("temps")) {
        float current = getTemperature();
        Serial.println("\r\n================ THERMAL MONITORING ================");
        Serial.printf("  Active Core Temperature     : %.2f °C / %.2f °F\n", current, (current * 9.0 / 5.0) + 32.0);
        Serial.printf("  Historical Boundary Peak    : %.2f °C / %.2f °F\n", peakTemp, (peakTemp * 9.0 / 5.0) + 32.0);
        Serial.println("====================================================\r\n");
      } 
      else if (command.equalsIgnoreCase("stress")) {
        runCpuStress(4);
      } 
      else if (command.equalsIgnoreCase("wifi")) {
        scanWifi();
      } 
      else if (command.equalsIgnoreCase("game")) {
        launchGames();
      } 
      else if (command.equalsIgnoreCase("heat")) {
        runHeatFunction();
      } 
      else if (command.equalsIgnoreCase("cold")) {
        runColdFunction();
      } 
      else if (command.equalsIgnoreCase("frames")) {
        runFramesTest();
      } 
      else if (command.equalsIgnoreCase("shut down")) {
        Serial.println("\r\n[SYSTEM] Terminating operational runtime environments...");
        Serial.println("[SYSTEM] Severing downstream standard I/O channels...");
        Serial.println("[SYSTEM] Issuing physical deep sleep sequence. System offline.");
        Serial.flush();
        
        commandLineActive = false;
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        esp_deep_sleep_start();
      } 
      else if (command.equalsIgnoreCase("reboot")) {
        Serial.println("\r\n[SYSTEM] Dispatching warm boot flag...");
        Serial.flush();
        delay(800);
        ESP.restart();
      } 
      else {
        Serial.println("[ERROR] Unrecognized syntax structure. Input 'help' for proper structural syntax.");
      }

      if (commandLineActive) {
        Serial.print("\nespos> ");
      }
    }
  }
}

void initTempSensor() {
  peakTemp = getTemperature();
}

float getTemperature() {
  float tsens_out = temperatureRead();
  if (tsens_out > peakTemp) {
    peakTemp = tsens_out;
  }
  return tsens_out;
}

void runCpuStress(int minutes) {
  Serial.printf("\r\n[COMPUTE] Spawning mathematical load saturation matrix for %d minutes...\n", minutes);
  unsigned long duration = minutes * 60 * 1000;
  unsigned long start = millis();
  unsigned long cycles = 0;
  
  while (millis() - start < duration) {
    volatile double targetValue = 42.42;
    for (int i = 0; i < 80000; i++) {
      targetValue = sqrt(targetValue) * sin(targetValue) * exp(cos(targetValue));
    }
    cycles++;
    if (cycles % 100 == 0) {
      getTemperature();
    }
    yield();
  }
  Serial.printf("[COMPUTE] Cycle phase terminated. Aggregated peaks logged at %.2f °C\n", peakTemp);
}

void scanWifi() {
  Serial.println("\r\n[RF_ENGINE] Activating 2.4GHz physical layer transceiver scan...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(250);
  
  int networkCount = WiFi.scanNetworks();
  if (networkCount == 0) {
    Serial.println("[RF_ENGINE] Vector complete: No broadcast nodes detected.");
  } else {
    Serial.printf("[RF_ENGINE] Scan complete. %d distinct terminal links intercepted:\n", networkCount);
    Serial.println("+-----+----------------------------------+----------+----------+");
    Serial.printf("| %-3s | %-32s | %-8s | %-8s |\n", "CH", "SSID VECTOR", "RSSI", "SECURE");
    Serial.println("+-----+----------------------------------+----------+----------+");
    for (int i = 0; i < networkCount; ++i) {
      String encryptionType = "";
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN: encryptionType = "OPEN"; break;
        case WIFI_AUTH_WEP: encryptionType = "WEP"; break;
        case WIFI_AUTH_WPA_PSK: encryptionType = "WPA"; break;
        case WIFI_AUTH_WPA2_PSK: encryptionType = "WPA2"; break;
        case WIFI_AUTH_WPA_WPA2_PSK: encryptionType = "WPA/WPA2"; break;
        default: encryptionType = "UNKN"; break;
      }
      Serial.printf("| %-3d | %-32.32s | %-6d dBm | %-8s |\n", WiFi.channel(i), WiFi.SSID(i).c_str(), WiFi.RSSI(i), encryptionType.c_str());
      delay(15);
    }
    Serial.println("+-----+----------------------------------+----------+----------+");
  }
  Serial.println("[SECURITY] Protocol error: Network validation keys are restricted in 'ESPOS V0.1'.");
}

void launchGames() {
  Serial.println("\r\n┌────────────────────────────────────────────────────────┐");
  Serial.println("│              ESPOS SYSTEM SUBSURFACE GAME ENGINE       │");
  Serial.println("└────────────────────────────────────────────────────────┘");
  Serial.println("  1. Tactical Matrix Engine (Tic Tac Toe vs Logic AI)     ");
  Serial.println("  2. Linear Solid-State Geometric Engine (1x4 Tetris)     ");
  Serial.println("  To escape back to standard workspace prompt, write 'exit'");
  Serial.println("──────────────────────────────────────────────────────────");
  Serial.print("game-engine> ");
  
  while (true) {
    if (Serial.available() > 0) {
      String choice = Serial.readStringUntil('\n');
      choice.trim();
      if (choice == "1") {
        playTicTacToe();
        break;
      } else if (choice == "2") {
        playTetris();
        break;
      } else if (choice.equalsIgnoreCase("exit")) {
        Serial.println("[GAME] Suspending engine state cycles.");
        break;
      } else {
        Serial.print("Invalid vector option. Input '1', '2', or 'exit': ");
      }
    }
    yield();
  }
}

void playTicTacToe() {
  Serial.println("\r\n[ENG_3x3] Initializing Tic Tac Toe instance against Core AI logic.");
  char gridArray[9] = {'1','2','3','4','5','6','7','8','9'};
  
  auto renderCanvas = [&gridArray]() {
    Serial.println("\r\n         ┌───┬───┬───┐");
    Serial.printf("         │ %c │ %c │ %c │\n", gridArray[0], gridArray[1], gridArray[2]);
    Serial.println("         ├───┼───┼───┤");
    Serial.printf("         │ %c │ %c │ %c │\n", gridArray[3], gridArray[4], gridArray[5]);
    Serial.println("         ├───┼───┼───┤");
    Serial.printf("         │ %c │ %c │ %c │\n", gridArray[6], gridArray[7], gridArray[8]);
    Serial.println("         └───┴───┴───┘");
  };

  renderCanvas();
  Serial.print("Target vector node placement identifier (1-9): ");
  
  int cycleIndex = 0;
  while(cycleIndex < 5) {
    if (Serial.available() > 0) {
      String userResponse = Serial.readStringUntil('\n');
      userResponse.trim();
      int selectedIndex = userResponse.toInt() - 1;
      
      if(selectedIndex >= 0 && selectedIndex < 9 && gridArray[selectedIndex] != 'X' && gridArray[selectedIndex] != 'O') {
        gridArray[selectedIndex] = 'X';
        cycleIndex++;
        
        if(cycleIndex < 5) {
          for(int i = 0; i < 9; i++) {
            if(gridArray[i] != 'X' && gridArray[i] != 'O') {
              gridArray[i] = 'O';
              Serial.printf("\n[AI] Computer pipeline claimed vector mapping target %d\n", i + 1);
              break;
            }
          }
        }
        renderCanvas();
        if(cycleIndex < 5) {
          Serial.print("Target vector node placement identifier (1-9): ");
        }
      } else {
        Serial.print("[ERROR] Node coordinates blocked or invalid. Re-input target (1-9): ");
      }
    }
    yield();
  }
  Serial.println("[ENG_3x3] Execution cycle completed. Matrix populated.");
}

void playTetris() {
  Serial.println("\r\n[ENG_4x8] Initializing Linear Stick Tetris engine matrix.");
  Serial.println("[INPUT] Mechanics: Transmit 'A' for West translation, 'D' for East translation.");
  
  int internalColumnValue = 2;
  
  for (int stepIndex = 0; stepIndex < 8; stepIndex++) {
    if (Serial.available() > 0) {
      char readByte = Serial.read();
      if ((readByte == 'a' || readByte == 'A') && internalColumnValue > 0) {
        internalColumnValue--;
      }
      if ((readByte == 'd' || readByte == 'D') && internalColumnValue < 3) {
        internalColumnValue++;
      }
    }

    Serial.println("     ║════════════════════║");
    for (int yCoord = 0; yCoord < 8; yCoord++) {
      Serial.print("     ║ ");
      for (int xCoord = 0; xCoord < 4; xCoord++) {
        if (yCoord == stepIndex && xCoord == internalColumnValue) {
          Serial.print("████ ");
        } else {
          Serial.print("  .  ");
        }
      }
      Serial.println("║");
    }
    Serial.println("     ║════════════════════║");
    delay(1200);
  }
  Serial.println("[ENG_4x8] Object transformation sequence finalized. Object locked.");
}

void runHeatFunction() {
  Serial.println("\r\n[THERM_BURST] Warning: Saturating physical layers to 100% maximum operations.");
  WiFi.mode(WIFI_AP_STA);
  WiFi.scanNetworks(true);
  
  unsigned long executionBoundary = millis();
  float maximumAllowedTemperatureLimit = 75.0;
  float trackedBestThermalPoint = getTemperature();

  while (millis() - executionBoundary < 180000) {
    unsigned long internalIntervalTime = millis();
    
    while(millis() - internalIntervalTime < 1000) {
      volatile double intensiveMathValue = 1974.23;
      for(int k=0; k<2500; k++) {
        intensiveMathValue = sin(intensiveMathValue) * cos(intensiveMathValue) * sqrt(intensiveMathValue);
      }
      yield();
    }
    
    float measuredThermalMetric = getTemperature();
    if(measuredThermalMetric > trackedBestThermalPoint) {
      trackedBestThermalPoint = measuredThermalMetric;
    }

    Serial.printf("best temp: %.2f, current temp: %.2f\n", trackedBestThermalPoint, measuredThermalMetric);

    if (measuredThermalMetric >= maximumAllowedTemperatureLimit) {
      Serial.println("heat inbound, emergency shut down activated");
      Serial.flush();
      delay(200);
      esp_deep_sleep_start();
    }
  }
  
  WiFi.mode(WIFI_OFF);
  Serial.println("[THERM_BURST] Thermal saturation run cycle completed safely.");
}

void runColdFunction() {
  Serial.println("\r\n[THERM_DROP] Dropping downstream processing systems to sub-operational limits.");
  
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  setCpuFrequencyMhz(80);
  
  unsigned long sequenceStartTimeMarker = millis();
  float trackedLowestThermalPoint = getTemperature();

  while (millis() - sequenceStartTimeMarker < 180000) {
    delay(1000);
    
    float measuredThermalMetric = getTemperature();
    if (measuredThermalMetric < trackedLowestThermalPoint) {
      trackedLowestThermalPoint = measuredThermalMetric;
    }

    Serial.printf("best temp: %.2f, current temp: %.2f\n", trackedLowestThermalPoint, measuredThermalMetric);
  }
  
  setCpuFrequencyMhz(240);
  Serial.println("[THERM_DROP] Thermal sub-operational state expired. Main clock speed restored.");
}

void runFramesTest() {
  Serial.println("\r\n[PIPELINE] Initializing 60-second high-density async burst test...");
  unsigned long timingThresholdLimit = millis();
  unsigned long aggregateFrameCalculations = 0;
  
  while (millis() - timingThresholdLimit < 60000) {
    Serial.printf("[METRIC] Active Throughput Vector Sequence ID Target: %lu \r", aggregateFrameCalculations);
    aggregateFrameCalculations++;
  }
  Serial.printf("\n[PIPELINE] Test completed. Handled %lu high-density structural text vectors.\n", aggregateFrameCalculations);
}