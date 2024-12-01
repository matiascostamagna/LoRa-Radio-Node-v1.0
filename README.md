Teoría de las Comunicaciones
Actividad de Laboratorio 4
Implementación de módulos de radio frecuencia con soporte de sistemas embebidos.

Objetivo
Implementar, evaluar y documentar para diversas arquitecturas de comunicación, las características de los dispositivos de comunicación de corto alcance y bajo consumo (IoT).

Requerimientos de Implementación
Los requerimientos principales indicados como requerimientos funcionales (RA) se encuentran en el documento de guía “PresentacionPBL”

Desarrollo
Se realizará el enlace de comunicación en nodos según la arquitectura de punto a punto y multipunto (topología estrella)
Los datos a intercambiar pueden ser entregados por un sensor externo con entrada a GPIO del sistema embebido o mensaje preconfigurado
Como adicional, en arquitectura multipunto, desarrollar un nodo en modo Gateway para recepción de datos de diversos nodos y publicación a internet.
Los módulos de radio son de libre elección, pero con el acuerdo de ser común por lo menos a otro grupo para lograr enlaces entre estos.
Para la elección del sistema embebido son recomendables los basados en hardware libre y código abierto como Arduino (en sus versiones y modelos) o ESP32; compatibles con IDE Arduino como plataforma de desarrollo de
aplicación.
En la arquitectura general los sistemas embebidos manejan el protocolo SPI y pueden gobernar y enviar datos a módulos compatibles con SPI.
