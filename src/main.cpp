#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ==========================================
// CONFIGURATION
// ==========================================
const char* ssid = "iPhone";
const char* password = "aassddff";

// Pins
const int LATCH_PIN = 2;  
const int CLOCK_PIN = 4;  
const int DATA_PIN  = 15; 

WebServer server(80);

// ==========================================
// BITMAP LIBRARY (50 Shapes)
// ==========================================
const uint8_t SHAPES[][8] = {
    // --- 0-9: Geometric ---
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0: OFF
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, // 1: FULL ON
    {0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C}, // 2: Circle
    {0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF}, // 3: Square
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 4: Diamond
    {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81}, // 5: X Shape
    {0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18}, // 6: Plus
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}, // 7: Diagonal 1
    {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01}, // 8: Diagonal 2
    {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}, // 9: Checkerboard

    // --- 10-19: Icons ---
    {0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00}, // 10: Heart
    {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C}, // 11: Smile
    {0x3C, 0x42, 0xA5, 0x81, 0x99, 0xA5, 0x42, 0x3C}, // 12: Sad
    {0x00, 0x01, 0x03, 0x16, 0x8C, 0xD8, 0x70, 0x20}, // 13: Checkmark
    {0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18}, // 14: Arrow Up
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18}, // 15: Arrow Down
    {0x10, 0x30, 0x70, 0xFF, 0xFF, 0x70, 0x30, 0x10}, // 16: Arrow Left
    {0x08, 0x0C, 0x0E, 0xFF, 0xFF, 0x0E, 0x0C, 0x08}, // 17: Arrow Right
    {0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18}, // 18: Hollow Diamond
    {0x7E, 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x81}, // 19: Letter A box

    // --- 20-29: Nature/Weather ---
    {0x00, 0x42, 0x3C, 0x42, 0x00, 0x42, 0x3C, 0x42}, // 20: Flowers
    {0x24, 0x5A, 0x24, 0x00, 0x42, 0x3C, 0x00, 0x00}, // 21: Sun Small
    {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81}, // 22: Star
    {0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0xDB, 0x81, 0x00}, // 23: Mushroom
    {0x08, 0x1C, 0x3E, 0x7F, 0x1C, 0x1C, 0x1C, 0x1C}, // 24: Tree
    {0x0C, 0x1E, 0x3E, 0xFE, 0xFE, 0x00, 0x00, 0x00}, // 25: Cloud
    {0x00, 0x00, 0x6C, 0xFE, 0xFE, 0x7C, 0x38, 0x10}, // 26: Heart Inverse
    {0x10, 0x38, 0x54, 0x10, 0x10, 0x54, 0x38, 0x10}, // 27: Snowflake
    {0x08, 0x14, 0x22, 0x41, 0x22, 0x14, 0x08, 0x00}, // 28: Diamond outline
    {0x3C, 0x42, 0x99, 0xBD, 0xBD, 0x99, 0x42, 0x3C}, // 29: Face Neutral

    // --- 30-39: Game/Fun ---
    {0x3C, 0x7E, 0xDB, 0xFF, 0xFF, 0xDB, 0x42, 0x3C}, // 30: Alien/Invader
    {0x00, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x3C, 0x00}, // 31: Coin
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 32: Jewel
    {0x00, 0x66, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00}, // 33: Heart Filled
    {0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C}, // 34: Target
    {0x00, 0x18, 0x3C, 0x5A, 0x99, 0x18, 0x18, 0x18}, // 35: Sword
    {0x18, 0x3C, 0x7E, 0xDB, 0xFF, 0x24, 0x5A, 0xA5}, // 36: Ghost
    {0x3C, 0x7E, 0xFF, 0xFF, 0xE7, 0xC3, 0x81, 0x00}, // 37: Pacman Open
    {0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C}, // 38: Pacman Closed
    {0x81, 0xC3, 0xE7, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 39: Shield

    // --- 40-49: Islamic/Abstract ---
    {0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18}, // 40: Rub El Hizb
    {0x3C, 0x66, 0x42, 0x42, 0x42, 0x42, 0x66, 0x3C}, // 41: Mosque Dome
    {0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00}, // 42: Chevron Left
    {0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x00}, // 43: Chevron Right
    {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00}, // 44: Stripes Horz
    {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}, // 45: Mesh
    {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00}, // 46: Box
    {0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00}, // 47: Diamond Filled
    {0x10, 0x10, 0x10, 0xFF, 0x10, 0x10, 0x10, 0x00}, // 48: Cross Thin
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}  // 49: Dot
};

// Alphabet (A-Z)
const uint8_t ALPHABET[][8] = {
  {0x18, 0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, // A
  {0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00}, // B
  {0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, // C
  {0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00}, // D
  {0x7E, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00, 0x00}, // E
  {0x7E, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00, 0x00}, // F
  {0x3C, 0x66, 0x60, 0x6E, 0x66, 0x66, 0x3C, 0x00}, // G
  {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, // H
  {0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, // I
  {0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00}, // J
  {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, // K
  {0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00, 0x00}, // L
  {0xC3, 0xE7, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3, 0x00}, // M
  {0xC3, 0xE3, 0xF3, 0xDB, 0xCF, 0xC7, 0xC3, 0x00}, // N
  {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // O
  {0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, // P
  {0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x0E, 0x00}, // Q
  {0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x00}, // R
  {0x3C, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x3C, 0x00}, // S
  {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, // T
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, // U
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, // V
  {0xC3, 0xC3, 0xC3, 0xDB, 0xFF, 0xE7, 0xC3, 0x00}, // W
  {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}, // X
  {0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, // Y
  {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00}  // Z
};

// ==========================================
// SYSTEM STATE
// ==========================================
// 999 = Global Demo Mode (Cycles everything)
// 888 = Animation Only Loop
// 777 = Shapes Only Loop
int activeMode = 999; 

uint8_t frameBuffer[8] = {0};
unsigned long lastUpdate = 0;
int step = 0;
int demoIndex = 0;

// ==========================================
// CORE FUNCTIONS
// ==========================================

void applyMode8(const uint8_t input[8]) {
    memset(frameBuffer, 0, 8);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (input[i] & (1 << j)) frameBuffer[7 - j] |= (1 << (7 - i));
        }
    }
}

void sendData(uint8_t r, uint8_t c) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, r);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, ~c);
    digitalWrite(LATCH_PIN, HIGH);
}

void render() {
    for (int c = 0; c < 8; c++) {
        sendData(frameBuffer[c], (1 << c));
        delayMicroseconds(250);
        sendData(0, 0);
    }
}

// ==========================================
// ANIMATION LOGIC
// ==========================================

void runAnimations() {
    unsigned long now = millis();

    // --- GLOBAL DEMO MODE (999) ---
    if (activeMode == 999) {
        if (now - lastUpdate > 1000) { // Change every 1 second
            if (demoIndex < 50) {
                applyMode8(SHAPES[demoIndex]); // Show static shapes
            } else if (demoIndex == 50) {
                activeMode = 101; step = 0; // Trigger Gear
                lastUpdate = now; return;
            }
            demoIndex++;
            if (demoIndex > 50) demoIndex = 2; // Loop back to shapes
            lastUpdate = now;
        }
    }

    // --- AUTO SHAPES LOOP (777) ---
    else if (activeMode == 777) {
        if (now - lastUpdate > 800) {
            if (step < 2) step = 2;
            applyMode8(SHAPES[step]);
            step++;
            if (step > 49) step = 2;
            lastUpdate = now;
        }
    }

    // --- AUTO ANIMATION LOOP (888) ---
    else if (activeMode == 888) {
        if (step == 0) activeMode = 101; // Start Gear
        else if (step == 1) activeMode = 102; // Start Pacman
        else if (step == 2) activeMode = 103; // Start Musashi
        // Logic handles switching back to 888 after anim finishes
    }

    // --- SPECIFIC ANIMATIONS ---
    
    // Gear (101)
    else if (activeMode == 101) {
        if (now - lastUpdate > 150) {
            if (step % 2 == 0) { uint8_t g1[8]={0x3C,0x42,0x99,0xA5,0xA5,0x99,0x42,0x3C}; applyMode8(g1); }
            else { uint8_t g2[8]={0x3C,0x52,0x89,0xBD,0xBD,0x91,0x4A,0x3C}; applyMode8(g2); }
            step++;
            lastUpdate = now;
            // Return to Demo if running
            if (step > 20 && demoIndex > 0) { activeMode=999; demoIndex=51; step=0; } 
        }
    }
    // Pacman (102)
    else if (activeMode == 102) {
        if (now - lastUpdate > 200) {
            if (step % 2 == 0) applyMode8(SHAPES[37]); else applyMode8(SHAPES[38]);
            step++;
            lastUpdate = now;
        }
    }
    // Musashi (103)
    else if (activeMode == 103) {
        if (now - lastUpdate > 500) {
            int seq[] = {12, 20, 18, 0, 18, 7, 8}; int len = 7;
            if (step >= len) step = 0;
            applyMode8(ALPHABET[seq[step]]);
            step++;
            lastUpdate = now;
        }
    }
    // Rahman (104)
    else if (activeMode == 104) {
        if (now - lastUpdate > 500) {
            int seq[] = {17, 0, 7, 12, 0, 13}; int len = 6;
            if (step >= len) step = 0;
            applyMode8(ALPHABET[seq[step]]);
            step++;
            lastUpdate = now;
        }
    }
}

// ==========================================
// WEB DASHBOARD
// ==========================================

void handleRoot() {
    String h = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    h += "<style>";
    h += "body{background:#121212;color:#e0e0e0;font-family:'Segoe UI',sans-serif;text-align:center;margin:0;padding:0;}";
    h += "h1{background:#1f1f1f;padding:20px;margin:0;border-bottom:2px solid #00e676;color:#00e676;}";
    h += ".sec{padding:10px;text-align:left;color:#03dac6;font-weight:bold;text-transform:uppercase;border-bottom:1px solid #333;margin-top:10px;}";
    h += ".grid{display:grid;grid-template-columns:repeat(auto-fill, minmax(100px, 1fr));gap:8px;padding:10px;}";
    h += "button{background:#333;color:white;border:none;padding:12px;border-radius:6px;font-size:13px;cursor:pointer;transition:0.2s;}";
    h += "button:active{background:#00e676;color:black;}";
    h += ".auto{background:#6200ea;color:white;}";
    h += ".stop{background:#cf6679;color:black;font-weight:bold;width:90%;margin:20px;padding:15px;font-size:16px;}";
    h += "</style><script>function s(id){fetch('/set?id='+id);}</script></head><body>";
    
    h += "<h1>MUSASHI STUDIO</h1>";

    // Auto Modes
    h += "<div class='sec'>Auto Modes</div><div class='grid'>";
    h += "<button class='auto' onclick='s(999)'>FULL DEMO</button>";
    h += "<button class='auto' onclick='s(777)'>ALL SHAPES</button>";
    h += "</div>";

    // Animations
    h += "<div class='sec'>Animations</div><div class='grid'>";
    h += "<button onclick='s(101)'>GEAR</button>";
    h += "<button onclick='s(102)'>PACMAN</button>";
    h += "<button onclick='s(103)'>MUSASHI</button>";
    h += "<button onclick='s(104)'>RAHMAN</button>";
    h += "</div>";

    // Geometric
    h += "<div class='sec'>Geometric</div><div class='grid'>";
    h += "<button onclick='s(2)'>Circle</button><button onclick='s(3)'>Square</button>";
    h += "<button onclick='s(4)'>Diamond</button><button onclick='s(5)'>X-Cross</button>";
    h += "<button onclick='s(6)'>Plus</button><button onclick='s(9)'>Checker</button>";
    h += "</div>";

    // Icons
    h += "<div class='sec'>Icons</div><div class='grid'>";
    h += "<button onclick='s(10)'>Heart</button><button onclick='s(11)'>Smile</button>";
    h += "<button onclick='s(12)'>Sad</button><button onclick='s(13)'>Check</button>";
    h += "<button onclick='s(14)'>Arrow Up</button><button onclick='s(15)'>Arrow Dn</button>";
    h += "</div>";

    // Fun
    h += "<div class='sec'>Games & Fun</div><div class='grid'>";
    h += "<button onclick='s(30)'>Invader</button><button onclick='s(31)'>Coin</button>";
    h += "<button onclick='s(35)'>Sword</button><button onclick='s(36)'>Ghost</button>";
    h += "<button onclick='s(39)'>Shield</button><button onclick='s(20)'>Flower</button>";
    h += "</div>";

    // Islamic
    h += "<div class='sec'>Islamic Art</div><div class='grid'>";
    h += "<button onclick='s(40)'>Rub El Hizb</button><button onclick='s(41)'>Mosque</button>";
    h += "<button onclick='s(44)'>Stripes</button><button onclick='s(45)'>Mesh</button>";
    h += "</div>";

    h += "<button class='stop' onclick='s(0)'>STOP DISPLAY</button>";
    h += "</body></html>";
    server.send(200, "text/html", h);
}

void setup() {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(100);
    MDNS.begin("musashi");

    server.on("/", handleRoot);
    server.on("/set", [](){
        activeMode = server.arg("id").toInt();
        step = 0; // Reset animation step
        demoIndex = 0; // Reset demo state
        if (activeMode < 100 && activeMode > 0) {
            applyMode8(SHAPES[activeMode]);
        }
        if (activeMode == 0) memset(frameBuffer, 0, 8);
        server.send(200, "text/plain", "OK");
    });
    server.begin();
    
    // Start with Full Demo Mode
    activeMode = 999;
    Serial.println(WiFi.localIP());
}

void loop() {
    server.handleClient();
    runAnimations();
    render();
}
