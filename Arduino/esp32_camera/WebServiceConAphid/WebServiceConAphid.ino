#include <Limones-lite_inferencing.h>
#include <WiFi.h>
#include "esp_camera.h"
#include <WebServer.h>


// Configuración de tu red WiFi
//const char* ssid = "Totalplay-2.4G-f2e0";
//const char* password = "EHtagDtxYAdWh5k7";

const char* ssid = "QwQ";
const char* password = "qwquwuunu";

WebServer server(80);  // El servidor web en el puerto 80

// Configuración de los pines de la ESP32-CAM (dependiendo del modelo)
#define CAMERA_MODEL_AI_THINKER

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#endif

String detection_result = "No detection yet";  // Inicializamos el resultado de detección

void startCameraServer();
void handleRoot();
void handleCapture();
void handleInference();
void startCamera();

// Inicialización de la cámara y WiFi
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  startCamera();

  // Definir rutas para el servidor web
  server.on("/", handleRoot);
  server.on("/capture", handleCapture);
  server.on("/inference", handleInference);  // Ruta para el resultado de inferencia
  server.begin();
}

// Configuración de la cámara
void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // Inicializar cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Error inicializando cámara: 0x%x", err);
    return;
  }
}

// Función para la página principal
void handleRoot() {
  String html = "<html><body><h1>ESP32-CAM</h1><p>Prediccion en tiempo real: <span id='result'>" + detection_result + "</span></p>";
  html += "<img src='/capture' id='stream'><script>";
  html += "setInterval(function(){ fetch('/inference').then(response => response.text()).then(data => { document.getElementById('result').innerHTML = data; }); }, 1000);";  // Actualizar predicciones cada 1 segundo
  html += "</script></body></html>";
  server.send(200, "text/html", html);
}

// Función para capturar y mostrar la imagen
void handleCapture() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Error capturando la imagen");
    server.send(500, "text/plain", "Error capturando la imagen");
    return;
  }

  server.send_P(200, "image/jpeg", (const char *)fb->buf, fb->len);
  esp_camera_fb_return(fb);
}
// Función para manejar las inferencias
void handleInference() {
  camera_fb_t *fb = esp_camera_fb_get();  // Capturamos una imagen
  if (!fb) {
    Serial.println("Error capturando la imagen para inferencia");
    server.send(500, "text/plain", "Error capturando la imagen para inferencia");
    return;
  }

  // Declaración local de ei_camera_get_data()
  auto ei_camera_get_data = [&](size_t offset, size_t length, float *out_ptr) -> int {
    size_t pixel_ix = offset * 3;  // La señal es RGB888, cada pixel son 3 bytes
    size_t pixels_left = length;
    size_t out_ptr_ix = 0;

    while (pixels_left != 0) {
      // Convertimos de BGR a RGB
      out_ptr[out_ptr_ix] = (fb->buf[pixel_ix + 2] << 16) + (fb->buf[pixel_ix + 1] << 8) + fb->buf[pixel_ix];
      out_ptr_ix++;
      pixel_ix += 3;
      pixels_left--;
    }
    return 0;  // Devuelve 0 si la conversión es exitosa
  };

  ei_impulse_result_t result = {0};
  ei::signal_t signal;
  signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
  signal.get_data = ei_camera_get_data;  // Asignamos la función

  // Corremos el clasificador
  if (run_classifier(&signal, &result, false) == EI_IMPULSE_OK) {
    
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
    ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
    if (bb.value == 0) {
      continue;
    }
    ei_printf(" %s (%f)\r\n",
              bb.label,
              bb.value);
    detection_result = String(bb.label)+"("+String(float(bb.value))+") \n";
  }
    

  } else {
    detection_result = "Error en la inferencia";
  }

  esp_camera_fb_return(fb);  // Devolvemos el framebuffer
  server.send(200, "text/plain", detection_result);  // Enviamos el resultado al cliente
}



void loop() {
  server.handleClient();
}
