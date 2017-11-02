Controlador de dos semáforos con funciones de:

    * Colores rojo, ámbar y verde en los dos semáforos.
    * Modo automático desactivable: en el modo automático los dos semáforos cambian a verde alternativamente.
    * Duración personalizable del periodo en verde. Aunque igual para los dos semáforos.
    * Duración personalizable de la transición de verde a rojo (= duración del ámbar).
    * Botón manual para forzar el cambio de verde a rojo. Uno para los dos semáforos.

Componentes:

    Arduino UNO o equivalente
    Placa de relés, mínimo 6
        Placa de relés activa en bajo
        Tiene un jumper de 3 posiciones [GND - VCC - JD-VCC] que se pone en [VCC - JD-VCC]
    Un potenciómetro R1, para controlar la velocidad de cambio (referencia = duración del ámbar)
    Un potenciómetro R2, para controlar la duración del verde (número de iteraciones de velocidad de cambio)
        Los potenciómetros da igual el valor, se han usado 100K
    Un jumper, para desactivar el modo automático (el jumper abierto es automático, cerrado es manual)
    Un pulsador, para solicitar el cambio del semáforo
        
Conexiones:

    5V de la Arduino se pone en un bus al que van:
        VCC de la tarjeta de relés
        Un extremo del potenciómetro de R1
        Un extremo del potenciómetro de R2

    GND de la Arduino va a un bus en el que están
        GND de la tarjeta de relés
        El otro extremo del potenciómetro R1
        El otro extremo del potenciómetro R2
        Una de las patillas del jumper (será activo en baja cuando se cierre)
        Un extremo del pulsador (el pulsador será activo en baja)
        
    De la placa Arduino:
        A0 al jumper. Si no se conecta a GND (jumper cerrado) el pin está configurado con un pullup resistor que activa el modo automático.
        A1 al otro extremo del pulsador. Se configura este pin con un pullup resistor interno.
        A2 al valor del potenciómetro R1 de control de velocidad de cambio.
        A3 al valor del potenciómetro R2 de control de duración del verde.
        D0 a D5 a las entradas de la placa de relés para los 6 relés individuales.