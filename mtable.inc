
//  ENTRY(ID,  var,                  rightshift,  resolution,    unit,    name,                                  minvalue,   maxvalue  )

    ENTRY('0', attitude.voltage,         0,       0.001,         "V",     "Batteriespannung",                      0.0,      20.0      )
    ENTRY('1', attitude.longAcc,         0,       0.001,         "m/ss",  "Längsbeschleunigung",                 -25.0,      25.0      )
    ENTRY('2', attitude.latAcc,          0,       0.001,         "m/ss",  "Querbeschleunigung",                  -25.0,      25.0      )
    ENTRY('3', attitude.vertAcc,         0,       0.001,         "m/ss",  "Vertikalbeschleunigung",              -25.0,      25.0      )
    ENTRY('4', attitude.angleRate,       7,       0.0001,        "°/s",   "Winkelgeschwindigkeit",              -300.0,     300.0      )
    ENTRY('5', attitude.speedRight,      0,       0.001,         "m/s",   "Radgeschwindigkeit Rechts",           -10,        10        )
    ENTRY('6', attitude.speedLeft,       0,       0.001,         "m/s",   "Radgeschwindigkeit Links",            -10,        10        )
    ENTRY('7', lastLoopTicks,            0,       1.0,           "",      "Prozessorauslastung",                   0.0,     100.0      )
    ENTRY('8', rawSensorData.voltage,    0,       1.0,           "",      "Raw Batteriespannung",                  0.0,    1000.0      )
    ENTRY('9', rawSensorData.angleRate,  0,       1.0,           "",      "Raw Winkelgeschwindigkeit",         -1024,      1024        )
    ENTRY('a', rawSensorData.longAcc,    0,       1.0,           "",      "Raw Längsbeschleunigung",           -3397,      3397        )
    ENTRY('b', rawSensorData.latAcc,     0,       1.0,           "",      "Raw Querbeschleunigung",            -3397,      3397        )
    ENTRY('c', rawSensorData.vertAcc,    0,       1.0,           "",      "Raw Vertikalbeschleunigung",        -3397,      3397        )
    ENTRY('d', rawSensorData.sonar1,     0,       1.0,           "",      "Raw Sonar 1",                           0.0,     200.0      )
    ENTRY('e', rawSensorData.sonar2,     0,       1.0,           "",      "Raw Sonar 2",                           0.0,     200.0      )
    ENTRY('f', rawSensorData.wssRight,   0,       1.0,           "",      "Raw Radgeschwindigkeit Rechts",       -75,        75        )
    ENTRY('g', rawSensorData.wssLeft,    0,       1.0,           "",      "Raw Radgeschwindigkeit Links",        -75,        75        )
    ENTRY('h', attitude.angleAcc,        6,       0.0001,        "°",     "Winkel Beschleunigungssensor",        -25.0,      25.0      )
    ENTRY('i', attitude.angleGyro,       6,       0.0001,        "°",     "Winkel Gyro",                         -25.0,      25.0      )
    ENTRY('j', attitude.angleFused,      6,       0.0001,        "°",     "Winkel Fusioniert",                   -25.0,      25.0      )
	

//  ENTRY('k', pos1,                     0,       1.0,           "",      "Pos 1",                             -1000.0,    1000.0      )
//  ENTRY('l', pos2,                     0,       1.0,           "",      "Pos 2",                             -1000.0,    1000.0      )
	

//  ENTRY('5', attitude.position,        6,       0.0001,        "m",     "Position",                            -5.0,       5.0       )
//  ENTRY('6', attitude.diffSide,        3,       0.0001,        "m",     "Positionsdiff R/L",                   -0.5,       0.5       )

    
//  ENTRY('a', actuator.powerRight,      0,       1.0,           "",      "PWM Motor Rechts",                    -250.0,     250.0     )
//  ENTRY('b', actuator.powerLeft,       0,       1.0,           "",      "PWM Motor Links",                     -250.0,     250.0     )

//  ENTRY('k', rawSensorData.position,   4,       0.0005,        "m",     "Raw Position",                        -2.5,       2.5       )
//  ENTRY('l', rawSensorData.diffSide,   3,       0.001,         "m",     "Raw Positionsdiff R/L",               -0.25,      0.25      )


    ENTRY(0,   lastLoopTicks,            0,       0.0,           "-",     "Ende der Tabelle",                    0.0,        0.0       )
