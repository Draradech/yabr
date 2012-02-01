
//  ENTRY(ID,  var,                  rightshift,  resolution,    unit,    name,                                  minvalue,   maxvalue  )

    ENTRY('0', actuator.powerRight,      0,       1,             "PWM",   "Stellwert Rechts",                    -255,       255       )
    ENTRY('1', actuator.powerLeft,       0,       1,             "PWM",   "Stellwert Links",                     -255,       255       )

//  ENTRY('0', sensorOffsets.longAcc,    0,       0.007359339,   "m/ss",  "Offset Längsbeschleunigung",          -5.0,       5.0       )
//  ENTRY('1', sensorOffsets.latAcc,     0,       0.007359339,   "m/ss",  "Offset Querbeschleunigung",           -5.0,       5.0       )
//  ENTRY('2', sensorOffsets.elevAcc,    0,       0.007359339,   "m/ss",  "Offset Vertikalbeschleunigung",       -5.0,       5.0       )

//  ENTRY('3', controlPara.angleP,       0,       1.0,      "PWM / °",    "P-Anteil Winkelregler",               -50.0,      50.0      )
//  ENTRY('4', controlPara.angleD,       0,       1.0,      "PWM / °/s",  "D-Anteil Winkelregler",               -50.0,      50.0      )

    ENTRY(0,   lastLoopTicks,              0,       0.0,           "-",     "Ende der Tabelle",                  0.0,        0.0       )
