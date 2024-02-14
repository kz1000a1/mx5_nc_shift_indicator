#pragma once

struct MX5_DATA_PARAM {
  uint8_t numExpectedBytes;
  uint8_t dataBytes;
  float scaleFactor;
  float bias;
};

//-------------------------------------------------------------------------------------//
// MAZDA 3rd GEN MX-5(mk3.5) SPEC
// https://www2.mazda.co.jp/cars/roadster/spec/pdf/roadster_specification.pdf
//-------------------------------------------------------------------------------------//

#define TYRE_OUTER_DIAMETER_16            191.9796    // 205/50R16       
#define TYRE_OUTER_DIAMETER_17            193.5182    // 205/45R17
#define GEAR_RATIO_1                         3.815
#define GEAR_RATIO_2                         2.260
#define GEAR_RATIO_3                         1.640
#define GEAR_RATIO_4                         1.177
#define GEAR_RATIO_5                         1.000
#define GEAR_RATIO_6                         0.787
#define FINAL_RATIO                          4.100

//-------------------------------------------------------------------------------------//
// CAN IDs
// https://github.com/timurrrr/RaceChronoDiyBleDevice/blob/master/can_db/mazda_mx5_nc.md
//-------------------------------------------------------------------------------------//
#define CAN_ID_STEERLING                  0x081
// 
// Update frequency: 100 times per second.
// 
// `0x081` contain data related to steering angle. This CAN ID is available only in
// cars with DSC module, so all cars from 2007 onwards.
// Only 4 bytes long.
// 
// Byte | Meaning
// ---- | -------
// 0 | unidentified
// 1 | on/off (EF/6F or 11101111/01101111)
// 2 & 3| signed values for the steering angle
// 
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Steering angle | `bytesToInt(raw, 2, 2)` | positive values are from centered position (0) to right, negative otherwise
// 
#define CAN_ID_BRAKE 0x085
// 
// Update frequency: 100 times per second.
// 
// `0x085` contain data related to braking. This CAN ID is available only in
// cars with DSC module, so all cars from 2007 onwards.
// 
// Byte | Meaning
// ---- | -------
// 0 & 1 | together with byte 1 represent the pressure of the braking system
// 2 | brake siwtch ON/OFF, information contained in bit 0 (MSB, from left)
// 3 | Not changing
// 4 | Not changing
// 5 | Not changing
// 6 | Not changing
// 7 | Not changing
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Brake pressure | `(3.4518689053*bytesToInt(raw, 0, 2)-327.27)/1000.00` | multipliers are obtained from data from Leisurehound user on miata.net, may be wrong. Unit is kPa
// Brake percentage | `min(0.2*(bytesToInt(raw, 0, 2)-102),100)` | this is an alternative to get brake percentage. When not pressed the value is 102, after braking and releasing it goes briefly down to 99 so you may see slightly negative percentage.
// Digital | `bitsToUint(raw,17,1)/2` | 0-1 value
// 
#define CAN_ID_ACCEL 0x090
// 
// Update frequency: 100 times per second.
// 
// `0x090` WIP. Probably related to accelerations. This CAN ID is available only in
// cars with DSC module, so all cars from 2007 onwards.
// 
// Byte | Meaning
// ---- | -------
// 0 | WIP
// 1 | WIP
// 2 | WIP
// 3 | WIP
// 4 | WIP
// 5 | WIP
// 6 | WIP
// 7 | WIP
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// ... | ... | ...
// 
#define CAN_ID_TORQUE 0x200
// 
// Update frequency: 100 times per second.
// 
// `0x200` WIP. Probably related to torque. Byte 7 contain
// Throttle Valve Position
// 
// Byte | Meaning
// ---- | -------
// 0 | WIP
// 1 | WIP
// 2 | WIP
// 3 | WIP
// 4 | WIP
// 5 | WIP
// 6 | WIP
// 7 | Throttle Valve Position (%)
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Throttle Position | `bytestouint(raw,7,1)*100/255.00` | Scale may need adjustment, doesn't take into account the offset for idle. Same value available in CAN ID 0x215 byte 6
// 
#define CAN_ID_ENGINE_SPEED 0x201
// 
// Update frequency: 100 times per second.
// 
// `0x201` This CAN ID is related to engine speed, vehicle speed
// and accelerator position.
// 
// Byte | Meaning
// ---- | -------
// 0 | With byte 1 represent engine speed
// 1 | With byte 0 represent engine speed
// 2 & 3| WIP: follows RPM
// 4 & 5 | represent vehicle speed
// 6 | Accelerator pedal position (%)
// 7 | Always FF
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Engine RPM | `bytestouint(raw,0,2)/4.00` | 
// Speed | `((bytestoint(raw,4,2)/100.00)-100)/3.6` | Raw speed data is given in km/h with a 100 km/h offset. The "3.6" at the end of the equation is needed to switch to m/s that is the unit used internally for calculation by RaceChrono. In the calculation RaceChrono will then multiply automatically for the correct value to transform the m/s to your choice of units (i.e. km/h or mph).
// Accelerator Position | `bytestoint(raw,6,1)*2.00` | This is a percentage, increments of 0.5%
// 
// ## CAN ID 0x215
// 
// Update frequency: 100 times per second.
// 
// `0x215` WIP. Mostly related to fault codes but
// byte 6 contain Throttle Valve Position
// 
// Byte | Meaning
// ---- | -------
// 0 | WIP
// 1 | WIP
// 2 | WIP
// 3 | WIP
// 4 | WIP
// 5 | WIP
// 6 | Throttle Valve Position (%)
// 7 | WIP
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Throttle Position | `bytestouint(raw,6,1)*100/255.00` | Scale may need adjustment, doesn't take into account the offset for idle. Same value available in CAN ID 0x200 byte 7
// 
#define CAN_ID_TRANSMISSION 0x231
// 
// Update frequency: 40 times per second.
// 
// `0x231` Is related to transmission, probably has
// more significative data for AT cars. On MT cars
// only interesting bit is the clutch switch
// 
// Byte | Meaning
// ---- | -------
// 0 | Always FF (on MT)
// 1 | bit 7 (MSB, counting from left) clutch switch; bit 6 (MSB) may be related to neutral/in gear?
// 2 | Always FF (on MT)
// 3 | Always FF (on MT)
// 4 | Always 00 (on MT)
// 5 | Always 00 (on MT)
// 6 | Always 00 (on MT)
// 7 | Always 00 (on MT)
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Digital | `(bitstouint(raw,15,1)-4)/2` | 0 - 1 value
// 
// 
#define CAN_ID_ENGINE 0x240
// 
// Update frequency: 10 times per second.
// 
// `0x240` Contains engine related data such as
// cooling water temperature, air intake temperature
// spark angle, calculated load, throttle valve position
// only interesting bit is the clutch switch
// 
// Byte | Meaning
// ---- | -------
// 0 | Calculated Load (%)
// 1 | Engine Coolant Temperature (属C)
// 2 | WIP: seems related to ignition timing (deg)
// 3 | Throttle Valve Position (%)
// 4 | Intake Air Temperature (属C)
// 5 | Always 00
// 6 | Always 00
// 7 | Always 00 (faults?)
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Percentage | `100*(bytestouint(raw,0,1)/255.00` | can't find Engine Load on RaceChrono list of channels
// Coolant temperature | `bytestouint(raw,1,1)-40` | RaceChrono does calculation in 属C then converts to your unit of choice. Same data availble in byte 0 of ID 420
// Throttle position | `100*bytestouint(raw,1,1)/255` | Scale may need adjustment. This ID should refer to absolute opening value, i.e. taking into account the opening at idle. Still, the value at idle for my measurements seems too high (11%...)
// Ignition advance
// Intake temperature | `bytestouint(raw,4,1)-40` | RaceChrono does calculation in 属C then converts to your unit of choice
// 
#define CAN_ID_WHEEL_SPEED 0x4b0
// 
// Update frequency: 100 times per second.
// 
// `0x4b0` is dedicated only to wheel speed representation
// 
// Byte | Meaning
// ---- | -------
// 0 & 1 | Front Left Wheel Speed
// 2 & 3 | Front Right Wheel Speed
// 4 & 5 | Rear Left Wheel Speed
// 6 & 7 | Rear Right Wheel Speed
// 
// Channel name | Equation | Notes
// ------------ | -------- | -----
// Vehicle Speed Front Left | `((bytestoint(raw,0,2)/100.00)-100)/3.6` | Raw speed data is given in km/h with a 100 km/h offset. The "3.6" at the end of the equation is needed to switch to m/s that is the unit used internally for calculation by RaceChrono. In the calculation RaceChrono will then multiply automatically for the correct value to transform the m/s to your choice of units (i.e. km/h or mph).
// Vehicle Speed Front Right | `((bytestoint(raw,2,2)/100.00)-100)/3.6` |
// Vehicle Speed Rear Left | `((bytestoint(raw,4,2)/100.00)-100)/3.6` |
// Vehicle Speed Rear Right | `((bytestoint(raw,6,2)/100.00)-100)/3.6` |
