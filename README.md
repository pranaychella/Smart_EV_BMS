# Smart_EV_BMS
smart ev battery management system using arduino and components in proteus
# Smart EV Battery Management System (BMS) using Arduino & Proteus

## Overview

This project is a Smart Electric Vehicle Battery Management System (BMS) designed using Arduino UNO and simulated in Proteus.

The system continuously monitors battery voltage, current, temperature, and battery percentage while protecting the battery against unsafe operating conditions.

---

## Features

- Battery Voltage Monitoring
- Battery Percentage (State of Charge)
- Current Monitoring using ACS712
- Temperature Monitoring using LM35
- Automatic LCD Dashboard
- Low Battery Warning
- Over Temperature Protection
- Cooling Fan Control
- Relay Based Battery Disconnect
- Buzzer Alarm
- Green, Yellow and Red Status LEDs
- Automatic Screen Switching
- Startup Self-Test Animation

---

## Hardware Used

- Arduino UNO
- 16x2 LCD
- ACS712 Current Sensor
- LM35 Temperature Sensor
- Relay
- BC547 Transistor
- 1N4007 Diode
- Cooling Fan (DC Motor)
- Active Buzzer
- Green LED
- Yellow LED
- Red LED
- Potentiometer
- Resistors
- Battery

---

## Software Used

- Arduino IDE
- Proteus 8 Professional

---

## System Operation

### Normal Mode

- Green LED ON
- Relay ON
- Fan OFF
- LCD displays battery information

### Low Battery

- Battery below 20%
- Red LED ON
- Buzzer ON
- LCD displays:

LOW BATTERY

CHARGE NOW

### High Temperature

Temperature above 45°C

- Fan ON
- Yellow LED ON

### Critical Temperature

Temperature above 60°C

- Relay OFF
- Fan ON
- Red LED ON
- Buzzer ON
- LCD displays:

OVER TEMP

SYSTEM OFF

### Over Current

Current exceeds threshold

- Relay OFF
- Red LED ON
- Buzzer ON

---

## Proteus Simulation

The complete system has been simulated using Proteus.

Simulation includes

- Voltage monitoring
- Current monitoring
- Temperature monitoring
- Automatic protection logic
- Relay control
- Cooling fan control

---

## Project Structure

```
Smart_EV_BMS
│
├── Arduino_Code
│     Smart_EV_BMS.ino
│
├── Proteus
│     Smart_EV_BMS.pdsprj
│     Smart_EV_BMS.dsn
│
├── Images
│     Circuit.png
│     Dashboard.png
│
├── README.md
│
└── Report.pdf
```

---

## Future Improvements

- CAN Bus Communication
- Bluetooth Monitoring
- IoT Dashboard
- Mobile App
- Cell Balancing
- State of Health (SOH)
- Data Logging
- Cloud Monitoring

---

## Author

Pranay Kumar

B.Tech Electronics and Communication Engineering

GitHub:
https://github.com/pranaychella

LinkedIn:
https://www.linkedin.com/in/pranay-kumar-485794239

---

## License

This project is developed for educational and academic purposes.