#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>

// WiFi Credentials
const char *ssid = "Mukuldhy";
const char *password = "12345678";

// Web server endpoint
const char *serverURL = "https://mindapp-simulation.onrender.com/update"; // Change this

TFT_eSPI tft = TFT_eSPI(); // TFT display instance

// Function Prototypes
void connectToWiFi();
void reconnectWiFi();
void displayWiFiStatus(String status, int rssi, String color);
String getColorForSignal(int rssi);
void sendDataToServer(String status, int rssi, String color);

void setup()
{
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_RED);
    tft.setTextSize(2);

    connectToWiFi();
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        int rssi = WiFi.RSSI(); // Get signal strength
        String statusColor = getColorForSignal(rssi);

        displayWiFiStatus("Connected", rssi, statusColor);
        sendDataToServer("Connected", rssi, statusColor);
    }
    else
    {
        displayWiFiStatus("Disconnected", 0, "Gray");
        reconnectWiFi();
    }

    delay(1000);
}

void connectToWiFi()
{
    tft.println("Connecting...");
    Serial.println("Connecting to WiFi...");

    WiFi.begin(ssid, password);
    int retries = 0;

    while (WiFi.status() != WL_CONNECTED && retries < 10)
    {
        delay(1000);
        Serial.print(".");
        tft.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nConnected!");
        tft.println("\nConnected!");
    }
    else
    {
        Serial.println("\nFailed!");
        tft.println("\nFailed!");
    }
}

void reconnectWiFi()
{
    for (int attempt = 1; attempt <= 2; attempt++)
    {
        Serial.println("Reconnecting... Attempt " + String(attempt));
        WiFi.disconnect();
        WiFi.reconnect();
        delay(5000);

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Reconnected!");
            return;
        }
    }

    Serial.println("Failed to reconnect.");
}

void displayWiFiStatus(String status, int rssi, String color)
{
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 20);
    tft.print("WiFi: ");
    tft.print(status);
    tft.setCursor(20, 50);

    if (status == "Connected")
    {
        tft.print("Signal: ");
        tft.print(rssi);
        tft.print(" dBm");
    }

    tft.setCursor(20, 80);
    tft.print("Color: ");
    tft.print(color);
}

String getColorForSignal(int rssi)
{
    if (rssi > -50)
        return "Green"; // Excellent
    if (rssi > -70)
        return "Yellow"; // Good
    return "Red";        // Weak
}

void sendDataToServer(String status, int rssi, String color)
{
    if (WiFi.status() != WL_CONNECTED)
        return;

    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{";
    payload += "\"status\": \"" + status + "\",";
    payload += "\"rssi\": " + String(rssi) + ",";
    payload += "\"color\": \"" + color + "\"";
    payload += "}";

    int httpResponseCode = http.POST(payload);
    Serial.println("HTTP Response: " + String(httpResponseCode));

    http.end();
}



// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <TFT_eSPI.h>
// #include <lvgl.h>

// // WiFi Credentials
// const char* ssid = "Mukuldhy";
// const char* password = "12345678";

// // Web server endpoints
// const char* serverURL = "http://192.168.1.199:5000/update";  // WiFi status
// const char* recordTriggerURL = "https://maker.ifttt.com/trigger/record_audio/with/key/XYZ123";  // Recording
// const char* speakerResultURL = "http://192.168.1.199:5000/speaker_result";  // Speaker AI result

// TFT_eSPI tft = TFT_eSPI();
// lv_disp_draw_buf_t disp_buf;
// lv_obj_t *wifi_label, *record_button, *speaker_label;

// // Function Prototypes
// void connectToWiFi();
// void updateWiFiStatus();
// void triggerVoiceRecording(lv_event_t *e);
// void checkSpeakerResult();
// void createUI();
// static void lv_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

// void setup() {
//     Serial.begin(115200);
//     tft.init();
//     tft.setRotation(1);
//     lv_init();
    
//     static lv_color_t buf[TFT_WIDTH * 10];
//     lv_disp_draw_buf_init(&disp_buf, buf, NULL, TFT_WIDTH * 10);
    
//     lv_disp_drv_t disp_drv;
//     lv_disp_drv_init(&disp_drv);
//     disp_drv.draw_buf = &disp_buf;
//     disp_drv.flush_cb = lv_flush_cb;
//     lv_disp_drv_register(&disp_drv);
    
//     createUI();
//     connectToWiFi();
// }

// void loop() {
//     lv_task_handler();
//     delay(500);
//     updateWiFiStatus();
// }

// void connectToWiFi() {
//     lv_label_set_text(wifi_label, "Connecting to WiFi...");
//     WiFi.begin(ssid, password);
//     int retries = 0;
//     while (WiFi.status() != WL_CONNECTED && retries < 10) {
//         delay(1000);
//         retries++;
//     }
    
//     if (WiFi.status() == WL_CONNECTED) {
//         lv_label_set_text(wifi_label, "WiFi: Connected ✅");
//     } else {
//         lv_label_set_text(wifi_label, "WiFi: Failed ❌");
//     }
// }

// void updateWiFiStatus() {
//     if (WiFi.status() == WL_CONNECTED) {
//         int rssi = WiFi.RSSI();
//         String statusText = "WiFi: Connected ✅\nSignal: " + String(rssi) + " dBm";
//         lv_label_set_text(wifi_label, statusText.c_str());
        
//         HTTPClient http;
//         http.begin(serverURL);
//         http.addHeader("Content-Type", "application/json");
//         String payload = "{ \"status\": \"Connected\", \"rssi\": " + String(rssi) + " }";
//         http.POST(payload);
//         http.end();
//     } else {
//         lv_label_set_text(wifi_label, "WiFi: Disconnected ❌");
//         WiFi.reconnect();
//     }
// }

// void triggerVoiceRecording(lv_event_t *e) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin(recordTriggerURL);
//         http.GET();
//         http.end();
//         lv_label_set_text(speaker_label, "Recording... 🎤");
//         delay(6000);
//         checkSpeakerResult();
//     } else {
//         lv_label_set_text(speaker_label, "WiFi not connected! ❌");
//     }
// }

// void checkSpeakerResult() {
//     HTTPClient http;
//     http.begin(speakerResultURL);
//     int httpResponseCode = http.GET();
    
//     if (httpResponseCode > 0) {
//         String response = http.getString();
//         lv_label_set_text(speaker_label, ("Speaker: " + response).c_str());
//     } else {
//         lv_label_set_text(speaker_label, "Error in AI response ❌");
//     }
//     http.end();
// }

// void createUI() {
//     wifi_label = lv_label_create(lv_scr_act());
//     lv_label_set_text(wifi_label, "WiFi: Connecting...");
//     lv_obj_align(wifi_label, LV_ALIGN_TOP_MID, 0, 10);
    
//     record_button = lv_btn_create(lv_scr_act());
//     lv_obj_set_size(record_button, 120, 50);
//     lv_obj_align(record_button, LV_ALIGN_CENTER, 0, -30);
//     lv_obj_t *btn_label = lv_label_create(record_button);
//     lv_label_set_text(btn_label, "Record 🎙️");
//     lv_obj_add_event_cb(record_button, triggerVoiceRecording, LV_EVENT_CLICKED, NULL);
    
//     speaker_label = lv_label_create(lv_scr_act());
//     lv_label_set_text(speaker_label, "Speaker: Unknown ❓");
//     lv_obj_align(speaker_label, LV_ALIGN_CENTER, 0, 30);
// }

// static void lv_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
//     tft.startWrite();
//     for (int y = area->y1; y <= area->y2; y++) {
//         tft.setAddrWindow(area->x1, y, area->x2 - area->x1 + 1, 1);
//         tft.pushColors((uint16_t*)&color_p[(y - area->y1) * (area->x2 - area->x1 + 1)], area->x2 - area->x1 + 1, true);
//     }
//     tft.endWrite();
//     lv_disp_flush_ready(disp_drv);
// }













// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <TFT_eSPI.h>
// #include <lvgl.h>

// // WiFi Credentials
// const char* ssid = "Mukuldhy";
// const char* password = "12345678";

// // Web server endpoints
// const char* serverURL = "http://192.168.1.199:5000/update";  // WiFi status
// const char* recordTriggerURL = "https://maker.ifttt.com/trigger/record_audio/with/key/XYZ123";  // Recording
// const char* speakerResultURL = "http://192.168.1.199:5000/speaker_result";  // Speaker AI result

// TFT_eSPI tft = TFT_eSPI();
// lv_obj_t *wifi_label, *record_button, *speaker_label;

// // Function Prototypes
// void connectToWiFi();
// void reconnectWiFi();
// void updateWiFiStatus();
// void triggerVoiceRecording();
// void checkSpeakerResult();
// void createUI();

// void setup() {
//     Serial.begin(115200);
//     tft.init();
//     tft.setRotation(1);
//     lv_init();

//     tft.fillScreen(TFT_BLACK);
//     lv_disp_buf_t disp_buf;
//     static lv_color_t buf[LV_HOR_RES_MAX * 10];
//     lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
//     lv_disp_drv_t disp_drv;
//     lv_disp_drv_init(&disp_drv);
//     disp_drv.buffer = &disp_buf;
//     lv_disp_drv_register(&disp_drv);

//     createUI();
//     connectToWiFi();
// }

// void loop() {
//     lv_task_handler();
//     delay(500);
//     updateWiFiStatus();
// }

// // Connect to WiFi
// void connectToWiFi() {
//     lv_label_set_text(wifi_label, "Connecting to WiFi...");
//     Serial.println("Connecting to WiFi...");

//     WiFi.begin(ssid, password);
//     int retries = 0;
//     while (WiFi.status() != WL_CONNECTED && retries < 10) {
//         delay(1000);
//         Serial.print(".");
//         retries++;
//     }

//     if (WiFi.status() == WL_CONNECTED) {
//         Serial.println("\nConnected!");
//         lv_label_set_text(wifi_label, "WiFi: Connected ✅");
//     } else {
//         Serial.println("\nFailed!");
//         lv_label_set_text(wifi_label, "WiFi: Failed ❌");
//     }
// }

// // Reconnect WiFi
// void reconnectWiFi() {
//     Serial.println("Reconnecting...");
//     WiFi.disconnect();
//     WiFi.reconnect();
//     delay(5000);
// }

// // Update WiFi Status
// void updateWiFiStatus() {
//     if (WiFi.status() == WL_CONNECTED) {
//         int rssi = WiFi.RSSI();
//         String statusText = "WiFi: Connected ✅\nSignal: " + String(rssi) + " dBm";
//         lv_label_set_text(wifi_label, statusText.c_str());

//         // Send data to server
//         HTTPClient http;
//         http.begin(serverURL);
//         http.addHeader("Content-Type", "application/json");

//         String payload = "{ \"status\": \"Connected\", \"rssi\": " + String(rssi) + " }";
//         http.POST(payload);
//         http.end();
//     } else {
//         lv_label_set_text(wifi_label, "WiFi: Disconnected ❌");
//         reconnectWiFi();
//     }
// }

// // Trigger Voice Recording on Phone
// void triggerVoiceRecording() {
//     if (WiFi.status() == WL_CONNECTED) {
//         Serial.println("Triggering voice recording...");

//         HTTPClient http;
//         http.begin(recordTriggerURL);
//         int httpResponseCode = http.GET();
//         http.end();

//         lv_label_set_text(speaker_label, "Recording... 🎤");
//         delay(6000);  // Wait for recording to complete
//         checkSpeakerResult();
//     } else {
//         lv_label_set_text(speaker_label, "WiFi not connected! ❌");
//     }
// }

// // Check Speaker Identification Result
// void checkSpeakerResult() {
//     HTTPClient http;
//     http.begin(speakerResultURL);
//     int httpResponseCode = http.GET();

//     if (httpResponseCode > 0) {
//         String response = http.getString();
//         lv_label_set_text(speaker_label, ("Speaker: " + response).c_str());
//     } else {
//         lv_label_set_text(speaker_label, "Error in AI response ❌");
//     }

//     http.end();
// }

// // Create UI with LVGL
// void createUI() {
//     // WiFi Status Label
//     wifi_label = lv_label_create(lv_scr_act(), NULL);
//     lv_label_set_text(wifi_label, "WiFi: Connecting...");
//     lv_obj_align(wifi_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

//     // Record Button
//     record_button = lv_btn_create(lv_scr_act(), NULL);
//     lv_obj_set_size(record_button, 120, 50);
//     lv_obj_align(record_button, NULL, LV_ALIGN_CENTER, 0, -30);
//     lv_obj_t *btn_label = lv_label_create(record_button, NULL);
//     lv_label_set_text(btn_label, "Record 🎙️");
//     lv_btn_set_action(record_button, LV_BTN_ACTION_CLICK, triggerVoiceRecording);

//     // Speaker Result Label
//     speaker_label = lv_label_create(lv_scr_act(), NULL);
//     lv_label_set_text(speaker_label, "Speaker: Unknown ❓");
//     lv_obj_align(speaker_label, NULL, LV_ALIGN_CENTER, 0, 30);

//     // Re-identify Button
//     lv_obj_t *identify_button = lv_btn_create(lv_scr_act(), NULL);
//     lv_obj_set_size(identify_button, 120, 50);
//     lv_obj_align(identify_button, NULL, LV_ALIGN_CENTER, 0, 80);
//     lv_obj_t *id_label = lv_label_create(identify_button, NULL);
//     lv_label_set_text(id_label, "Identify Again 🔄");
//     lv_btn_set_action(identify_button, LV_BTN_ACTION_CLICK, triggerVoiceRecording);
// }
