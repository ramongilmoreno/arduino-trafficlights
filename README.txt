Traffic lights controller for two lights in an intersection with the following functions:

    * Red, yellow and green lights for each direction.
        * Pedestrian button lights (no pedestrian traffic light though): "Push" and "Wait".
    * Auto mode (each direction lights gets its share of green). Can be disabled.
    * Customizable duration of the transaction to red (that is: duration of the green light).
    * Customizable duration of the green light. Same time for both directions.
    * Input button to force traffic light change. Same switch for both directions.
   
Components:

    Arduino UNO or equivalent
    8x Relay board.
        5V.
        Enabled at low.
    R1 potentiometer, controls duration of transition/yellow light.
    R2 potentiometer, controls duration of green light (actually relative to the time of the transtion)
        Not of importance value of R1 and R2, though used 100K for both.
    Switch to disable auto mode.
        Open will be auto enabled (an internal pull up resistor will be used).
        Closed to ground will be manual mode.
    Push button to request traffic light change.
        Same input for both directions.

Power supply:

    Used a external 5V 1A mobile USB phone charger.
        This input was connected to:
            5V to the 5V pin in the Arduino board.
            5V to VCC and JD-VCC in relays board. Mine contained a jumper for it.
            GND to Arduino GND.
                And to the relays boards GND as well.
        Do not plug the USB cable to the Arduino board then the realys board to the Arduino.
            In this configuration Arduino board cannot supply enough current to the relay boards and voltage will drop.

Connections (includes power supply connections):

    The 5V from the power supply to:
        Arduino board 5V pin.
        Relays board VCC and JD-VCC (may use jumper).
        One side of R1 potentiomenter
        One side of R2 potentiomenter
        
    GND to:
        Arduino board GND pin.
        Relays board GND pin.
        Other side of R1 potentiomenter.
        Other side of R2 potentiomenter.
        One side of the auto mode switch.
        One side of the push button for traffic light change request.
        
    From Arduino board:
        A0 to the other side of the auto mode switch.
        A1 to the other side of the push button.
        A2 to the R1 potentiomenter value. To control transition speed.
        A3 to the R2 potentiomenter value. To control the duration of green light (same for both directions), relative to the transition duration.
        D0 to D7 to the 8 relays input:
            Traffic lights #1:
                D0 Red.
                D1 Yellow.
                D2 Green.
                D3 Pedestrian button indicator: push to change/please wait.
            Traffic lights #2:
                D4 Red.
                D5 Yellow.
                D6 Green.
                D7 Pedestrian button indicator: push to change/please wait.
