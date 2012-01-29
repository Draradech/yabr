
//  ENTRY(ID,  var,                  rightshift,  resolution,    unit,    name,                                  minvalue,   maxvalue  )

    ENTRY('0', rawSensorData.battery,    0,       0.021076,      "V",     "Raw Batteriespannung",                0.0,        20.0      )
    ENTRY('1', rawSensorData.sonar1,     0,       1.0,           "",      "Raw Sonar 1",                         0.0,       200.0      )
    ENTRY('2', rawSensorData.sonar2,     0,       1.0,           "",      "Raw Sonar 2",                         0.0,       200.0      )
    ENTRY('3', lastLoopTicks,            0,       1.0,           "%",     "Prozessorauslastung",                 0.0,       100.0      )
	
//  ENTRY('0', attitude.longAcc,         0,       0.001,         "m/ss",  "Längsbeschleunigung",                 -25.0,      25.0      )
//  ENTRY('1', attitude.latAcc,          0,       0.001,         "m/ss",  "Querbeschleunigung",                  -25.0,      25.0      )
//  ENTRY('2', attitude.elevAcc,         0,       0.001,         "m/ss",  "Vertikalbeschleunigung",              -25.0,      25.0      )
//  ENTRY('3', attitude.angleRate,       7,       0.0001,        "°/s",   "Winkelgeschwindigkeit",               -75.0,      75.0      )

//  ENTRY('4', attitude.speed,           0,       0.0001,        "m/s",   "Geschwindigkeit",                     -1.25,      1.25      )
//  ENTRY('5', attitude.position,        6,       0.0001,        "m",     "Position",                            -5.0,       5.0       )
//  ENTRY('6', attitude.diffSide,        3,       0.0001,        "m",     "Positionsdiff R/L",                   -0.5,       0.5       )

//  ENTRY('7', attitude.angleAcc,        6,       0.0001,        "°",     "Winkel Beschlunigungssensor",         -25.0,      25.0      )
//  ENTRY('8', attitude.angleGyro,       6,       0.0001,        "°",     "Winkel Gyro",                         -25.0,      25.0      )
//  ENTRY('9', attitude.angleFused,      6,       0.0001,        "°",     "Winkel Fusioniert",                   -25.0,      25.0      )
    
//  ENTRY('a', actuator.powerRight,      0,       1.0,           "",      "PWM Motor Rechts",                    -250.0,     250.0     )
//  ENTRY('b', actuator.powerLeft,       0,       1.0,           "",      "PWM Motor Links",                     -250.0,     250.0     )

//  ENTRY('c', attitude.voltage,         0,       0.001,         "V",     "Batteriespannung",                    0.0,        15.0      )
//  ENTRY('d', lastLoopTicks,            0,       1.0,           "%",     "CPU Auslastung",                      0.0,        100.0     )

//  ENTRY('e', rawSensorData.longAcc,    0,       0.007359339,   "m/ss",  "Raw Längsbeschleunigung",             -25.0,      25.0      )
//  ENTRY('f', rawSensorData.latAcc,     0,       0.007359339,   "m/ss",  "Raw Querbeschleunigung",              -25.0,      25.0      )
//  ENTRY('g', rawSensorData.elevAcc,    0,       0.007359339,   "m/ss",  "Raw Vertikalbeschleunigung",          -25.0,      25.0      )
//  ENTRY('h', rawSensorData.angleRate,  0,       0.07324219,    "°/s",   "Raw Winkelgeschwindigkeit",           -75.0,      75.0      )

//  ENTRY('i', rawSensorData.wssWheelRight, 0,    0.500,         "m/s",   "Raw Geschwindigkeit Rechts",          -1.25,      1.25      )
//  ENTRY('j', rawSensorData.wssWheelLeft, 0,     0.500,         "m/s",   "Raw Geschwindigkeit Links",           -1.25,      1.25      )
//  ENTRY('k', rawSensorData.position,   4,       0.0005,        "m",     "Raw Position",                        -2.5,       2.5       )
//  ENTRY('l', rawSensorData.diffSide,   3,       0.001,         "m",     "Raw Positionsdiff R/L",               -0.25,      0.25      )

//  ENTRY('m', rawSensorData.voltage,    0,       0.06161719,    "V",     "Raw Batteriespannung",                0.0,        15.0      )

    ENTRY(0,   0,                        0,       0.0,           "-",     "Ende der Tabelle",                    0.0,        0.0       )
