Componentes:

    Arduino UNO o equivalente
    Placa de relés, mínimo 6
        Placa de relés activa en bajo
        Tiene un jumper de 3 posiciones [GND - VCC - JD-VCC] que se pone en [VCC - JD-VCC]
    Un potenciómetro de 100K
    Un pulsador
        
Conexiones:

    5V de la Arduino se pone en un bus al que van:
        VCC de la tarjeta de relés
        Un extremo de un potenciómetro de 100K

    GND de la Arduino va a un bus en el que están
        GND de la tarjeta de relés
        El otro extremo del potenciómetro de 100K
        Un extremo del pulsador (el pulsador será activo en baja)
        
    De la placar Arduino
        A0 al valor del potenciómetro
        A1 al otro extremo del pulsador (se configura este pin con uno pullup resistor interno)
        D0 a D5 a las entradas de la placa de relés para los 6 relés individuales