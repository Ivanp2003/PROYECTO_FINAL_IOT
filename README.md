# 🏠 Casa Inteligente 

Proyecto académico de automatización residencial desarrollado por el Equipo Rocket 
para la asignatura Desarrollo de IoT - Escuela Politécnica Nacional.

## 📖 Descripción

Sistema domótico basado en Arduino Uno que automatiza tres funciones principales 
del hogar mediante sensores y actuadores conectados a la plataforma IoT ThingSpeak.

### Funcionalidades Implementadas

1. **🚗 Garaje Automatizado**
   - Apertura automática al detectar vehículos
   - Sensor ultrasónico HC-SR04 (rango 10-17 cm)
   - Servomotor SG90 para el mecanismo de apertura

2. **💡 Control de Iluminación por sonido**
   - Activación mediante aplausos
   - Sensor de sonido KY-038
   - LEDs indicadores controlados

3. **🌧️ Tendedero Inteligente**
   - Recogida automática ante lluvia
   - Sensor de lluvia FC-37
   - Servomotor SG90 para el mecanismo de tendedero

## 🔧 Componentes Utilizados

### Hardware Principal
- **Microcontrolador**: Arduino Uno (ATmega328P)
- **Conectividad**: Módulo WiFi ESP8266 ESP-01
- **Sensores**:
  - HC-SR04: Sensor ultrasónico de distancia
  - KY-038: Sensor de sonido
  - FC-37: Sensor de lluvia
- **Actuadores**:
  - 2x Servomotor SG90
  - LEDs con resistencias 220Ω
- **Otros**: Protoboard, cables jumper, resistencias (1kΩ, 2kΩ, 220Ω)

### Software
- **IDE**: Arduino IDE 1.8+
- **Plataforma IoT**: ThingSpeak
- **Lenguaje**: C/C++ para Arduino
- **Bibliotecas**:
  - Servo.h (control de servomotores)
  - SoftwareSerial.h (comunicación con ESP8266)

## 📊 Arquitectura del Sistema

## 📊 Arquitectura del Sistema

![Arquitectura del Sistema](https://raw.githubusercontent.com/Ivanp2003/PROYECTO_FINAL_IOT/main/diagramaBloques.png)


## 📡 Conexiones de Pines

| Componente | Pin Arduino | Función |
|------------|------------|---------|
| HC-SR04 TRIG | PIN 2 | Disparo ultrasónico |
| HC-SR04 ECHO | PIN 3 | Eco ultrasónico |
| Servo Garaje | PIN 8 | Control PWM |
| Servo Tendedero | PIN 10 | Control PWM |
| Sensor Lluvia DO | PIN 9 | Salida digital |
| Sensor Lluvia AO | A0 | Salida analógica |
| Sensor Sonido DO | PIN 6 | Salida digital |
| LEDs Sonido | PIN 7 | Control (con R 220Ω) |
| LEDs Garaje | PIN 13 | Control (con R 220Ω) |
| ESP8266 TX | PIN 11 | Transmisión serial |
| ESP8266 RX | PIN 12 | Recepción (vía divisor de voltaje) |

## 🚀 Instalación y Configuración

### Requisitos Previos
- Arduino IDE instalado
- Cuenta en ThingSpeak
- Red WiFi disponible

### Pasos de Instalación

1. **Clonar el repositorio**
```bash
   git clone https://github.com/Ivanp2003/PROYECTO_FINAL_IOT.git
   cd PROYECTO_FINAL_IOT
```

2. **Configurar credenciales WiFi**
   Editar en el código:
```cpp
   const char* ssid = "TU_RED_WIFI";
   const char* password = "TU_CONTRASEÑA";
```

3. **Configurar ThingSpeak**
   Obtener API Key de tu canal y actualizar:
```cpp
   String apiKey = "TU_API_KEY_THINGSPEAK";
```

4. **Cargar el código**
   - Conectar Arduino Uno al PC
   - Abrir el archivo .ino en Arduino IDE
   - Seleccionar placa: Tools > Board > Arduino Uno
   - Seleccionar puerto COM correcto
   - Compilar y subir el código

5. **Verificar funcionamiento**
   - Abrir Monitor Serial (9600 baudios)
   - Verificar conexión WiFi
   - Comprobar envío de datos a ThingSpeak

## 📈 Análisis de Datos

El sistema envía datos cada **5 segundos** a ThingSpeak con las siguientes variables:

- **Campo 1**: Distancia medida (cm)
- **Campo 2**: Nivel de humedad/lluvia (0-1023)
- **Campo 3**: Contador de aplausos detectados
- **Campo 4**: Estados de actuadores



## 👥 Equipo de Desarrollo

**Equipo Rocket - EPN**
- Odaliz Balseca
- Alejandro Guanoluisa
- Andrew Paillacho
- Andrés Panchi

**Asignatura**: Desarrollo de IoT / GR1  
**Institución**: Escuela Politécnica Nacional  
**Fecha**: Enero 2026

## 📝 Documentación Técnica

Para información detallada sobre:
- Justificación de componentes
- Metodología de desarrollo
- Análisis estadístico de resultados
- Diagramas y esquemas

Consultar el documento técnico completo en la carpeta `https://epnecuador-my.sharepoint.com/personal/juan_gonzalez02_epn_edu_ec/_layouts/15/onedrive.aspx?id=%2Fpersonal%2Fjuan%5Fgonzalez02%5Fepn%5Fedu%5Fec%2FDocuments%2F2025B%2FDesarrollo%20IOT%2FExamen%202%20%2D%20IOT%2FBalseca%5FGuanoluisa%5FPaillacho%5FPanchi&viewid=fffdf2f4%2D3f44%2D4b90%2D86b5%2D1638c381a109`.



## 🛠️ Solución de Problemas

### El ESP8266 no se conecta al WiFi
- Verificar credenciales de red
- Comprobar alimentación de 3.3V estable
- Revisar divisor de voltaje (1kΩ + 2kΩ)

### Los servomotores no responden
- Verificar alimentación externa (5V suficiente)
- Comprobar conexiones PWM
- Revisar código de control

### Datos no llegan a ThingSpeak
- Verificar API Key
- Comprobar conexión a internet
- Revisar intervalo de envío (mínimo 15 segundos)


Este proyecto es de carácter académico desarrollado para la Escuela Politécnica 
Nacional. 

## 🔗 Enlaces

- **Código fuente**: https://github.com/Ivanp2003/PROYECTO_FINAL_IOT.git
- **Video demostración**: https://vt.tiktok.com/ZSa9D4sKb/
---

**Desarrollado con ❤️ por Equipo Rocket - EPN 2026**
