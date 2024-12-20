# Repositorio de Tesis

A continuación se mencionará información importante de lo último que se ha trabajado en los últimos cuatrimestres, divididos entre los diversos secciones y archivos que se encuentran en el repositorio:

## Limones


### Arduino
Es un fichero que contiene todos los archivos de Arduino de la posible implementación del modelo de limones para un servidor web, siendo **CameraWebServer** y **esp32_camera**.
Aparte se encuentran las librerías utilizadas de Arduino y un archivo .ZIP del modelo más reciente con el que se obtuvo el mejor rendimiento.

### Imagenes Generales
Contienen diversas imágenes que se utilizaron para el primer borrador del artículo y algunas pruebas. En general, en el archivo se encuentran:

1. Pruebas de diferentes hiperparámetros del modelo: **Pruebas-Clasificacion.png**, **TEST2.png**, **TEST3.png**.
2. Imágenes de stock para pruebas: **aphid.jfif** y **hojasana.jpg**.
3. Prueba de cómo se implementa el modelo:  **Implementacion del modelo.png**.
4. Pruebas de detección de la ESP-CAM32: **Deteccion en ESPCAM32.png** y **Deteccion en ESPCAM32-2.png**.
5. Testeo del Web Server (Sin resultados relevantes): **TEST-ProgArduino.png**.

---

## Tomates

### PlantVillage-Tomato-3Clases_inferencing
Fichero que cuenta con ejemplos de diversas placas para la implementación del modelo de 3 clases del dataset de PlantVillage de tomates.

### Tomato-Tests
En este fichero se encuentran todas las pruebas que se realizaron con el dataset de tomates de PlantVillage:

- **N.º Clase**: Son ficheros enumerados del 3 al 8 con los resultados de diversas pruebas realizadas a un modelo donde se aumentaban las épocas de entrenamiento de 2 en 2 hasta que dejara de funcionar la versión gratuita de EdgeImpulse. Todos son resultados del entrenamiento.

- **Validación**: Fichero que cuenta con diversos archivos parecidos a los mencionados anteriormente, solo que ahora enfocado solamente a la validación del modelo.

- **Pruebas.txt**: Archivo con los datos utilizados para las diversas pruebas del modelo  en EdgeImpulse.

- **ei-plantvillage.ZIP**: Archivo .ZIP con el modelo de 3 clases del dataset, no se ha implementado aún.

- **Rendimiento del modelo.PDF**: PDF que cuenta con el rendimiento del modelo en dos tablas, una siendo la del entrenamiento y otra la de validación. A continuacion un adelanto de lo que se puede encontrar en el PDF


### Entrenamiento ( Learnig Rate: 0,0005)
|    Epocas  | 8          | 10         | 12         | 14         | 16         | 18         | 20         |
|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| 3 Clases   | -          | 96,70%     | 96,90%     | 97,20%     | 97,20%     | 97,30%     | **97,30%** |
| 4 Clases   | -          | 91,00%     | 91,90%     | 91,90%     |**92,0%(15)**| -          | -          |
| 5 Clases   | -          | 88,90%     | 89,40%     | 90,90%     |**91,8%(15)**| -          | -          |
| 6 Clases   | -          | 88,40%     | **88,40%** | -          | -          | -          | -          |
| 7 Clases   | -          | **86,40%** | -          | -          | -          | -          | -          |
| 8 Clases   | **84,40%** | -          | -          | -          | -          | -          | -          |


### Validación ( Learnig Rate: 0,0005)
|    Epocas  | 8          | 10         | 12         | 14         | 16         | 18         | 20         |
|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| 3 Clases   | -          | 93,83%     | 93,83%     | 93,98%     | 95,63%     | 95,55%     | **96,02%** |
| 4 Clases   | -          | 86,16%     | 87,41%     | 87,41%     |**88,99%(15)**| -          | -          |
| 5 Clases   | -          | 84,05%     | 85,43%     | 87,72%     |**88,85%(15)**| -          | -          |
| 6 Clases   | -          | 81,05%     | **81,05%** | -          | -          | -          | -          |
| 7 Clases   | -          | **82,32%** | -          | -          | -          | -          | -          |
| 8 Clases   | **78,63%** | -          | -          | -          | -          | -          | -          |

En negritas se encuentran los mejores resultados de cada clase

---
   

   


    