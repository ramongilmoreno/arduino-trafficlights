Controlador de dos semáforos con funciones de:

    * Colores rojo, ámbar y verde en los dos semáforos.
        * Semáforo de peatones: "Peatón pulse" y "Espere verde"
    * Modo automático desactivable: en el modo automático los dos semáforos cambian a verde alternativamente.
    * Duración personalizable del periodo en verde. Aunque igual para los dos semáforos.
    * Duración personalizable de la transición de verde a rojo (= duración del ámbar).
    * Botón manual para forzar el cambio de verde a rojo. Uno para los dos semáforos.
   
Componentes:

    Arduino UNO o equivalente
    Placa de relés x8
        Placa de relés activa en bajo
    Un potenciómetro R1, para controlar la velocidad de cambio (referencia = duración del ámbar)
    Un potenciómetro R2, para controlar la duración del verde (número de iteraciones de velocidad de cambio)
        Los potenciómetros da igual el valor, se han usado 100K
    Un interruptor, para desactivar el modo automático (el interruptor abierto es automático, cerrado es manual)
    Un pulsador, para solicitar el cambio del semáforo
        No se distingue uno u otro semáforo
    
Alimentación:

    Se puede alimentar separadamente la placa Arduino de la de relés.
        Aunque el conexionado aquí presentado no lo implementa, el aislamiento de las dos placas es sencillo alimentando por separado GND y JD-VCC de la placa de relés.
    
    La placa de relés tiene un jumper de 3 posiciones [GND - VCC - JD-VCC] que se quita.
        Al pin GND y JD-VCC conectaremos 0 y 5V directamente de una fuente (puede ser un cargador USB) para que el relé funcione de forma aislada.
        
    En las conexiones debajo se va a conectar una fuente de 5V a un bus. Y de ahí se alimentan:
        La placa Arduino 5V y GND
        La placa de relés, en los 3 [GND - VCC - JD-VCC] pines a GNC y JD-VCC (sin el jumper, aunque si vamos a conectar todo esto da igual)
        
Conexiones:

    5V de la Arduino se pone en un bus al que van:
        Un extremo del potenciómetro de R1
        Un extremo del potenciómetro de R2
        A la entrada de alimentación 5V de la placa Arduino
        A la entrada VCC de la placa de relés junto a las señales de entrada
        A la entrada JD-VCC de la placa de relés

    GND de la Arduino va a un bus en el que están
        GND (de los pines [GND - VCC - JD-VCC]) de la tarjeta de relés 
        El otro extremo del potenciómetro R1
        El otro extremo del potenciómetro R2
        Una de las patillas del interruptor (será activo en baja cuando se cierre)
        Un extremo del pulsador (el pulsador será activo en baja)
        
    De la placa Arduino:
        A0 al interruptor. Si no se conecta a GND (= si el interruptor no está cerrado) el pin está configurado con un pullup resistor que activa el modo automático.
        A1 al otro extremo del pulsador. Se configura este pin con un pullup resistor interno.
        A2 al valor del potenciómetro R1 de control de velocidad de cambio.
        A3 al valor del potenciómetro R2 de control de duración del verde.
        D0 a D7 a las entradas de la placa de relés para los 6 relés individuales:
            D0 Semáforo 1 Rojo
            D1 Semáforo 1 Ámbar
            D2 Semáforo 1 Verde
            D3 Semáforo 1 Peatón pulse/Espere verde
            D4 Semáforo 2 Rojo
            D5 Semáforo 2 Ámbar
            D6 Semáforo 2 Verde
            D7 Semáforo 2 Peatón pulse/Espere verde
