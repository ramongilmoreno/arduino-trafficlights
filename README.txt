Componentes:

    Arduino UNO o equivalente
    Placa de rel�s, m�nimo 6
        Placa de rel�s activa en bajo
        Tiene un jumper de 3 posiciones [GND - VCC - JD-VCC] que se pone en [VCC - JD-VCC]
    Un potenci�metro de 100K
    Un pulsador
        
Conexiones:

    5V de la Arduino se pone en un bus al que van:
        VCC de la tarjeta de rel�s
        Un extremo de un potenci�metro de 100K

    GND de la Arduino va a un bus en el que est�n
        GND de la tarjeta de rel�s
        El otro extremo del potenci�metro de 100K
        Un extremo del pulsador (el pulsador ser� activo en baja)
        
    De la placar Arduino
        A0 al valor del potenci�metro
        A1 al otro extremo del pulsador (se configura este pin con uno pullup resistor interno)
        D0 a D5 a las entradas de la placa de rel�s para los 6 rel�s individuales