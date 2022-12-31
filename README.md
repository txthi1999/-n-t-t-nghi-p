# STEM
# Overview
Git này hướng dẫn sử dụng boar của đề tài "Thiết kế board hỗ trợ giáo dục STEM"

## Power 
- Input: 12VDC 
- Output: 
    + M1, M2: 12VDC
    + Servor x6: 5VDC
    + I2C: 3.3V 
    + Analog line: 3.3VDC QTR-5RC(link: https://www.thegioiic.com/qtr-5rc-cam-bien-do-line-khoang-cach-7mm-ngo-ra-ttl)
    + Ultra sound: 5VDC HC-SR04(link: https://www.thegioiic.com/hc-sr04-cam-bien-sieu-am)
## Onboard Peripheral 
|Block                                  |Component  |
|---------------------------------------|-----------|
|Buzzer                                 |KLJ-7525   |
|Output PWM expander,I2C conmunicate    |PCA9685    |
|H-Bridge                               |TB6612     |
|USB to UART                            |CP1202     |

## ESP32 pin assignment
|GPIO       |Function       |
|-----------|---------------|
|IO23       |PWMA - TB6612  |
|IO22       |PWMB - TB6612  |
|IO4        |AIN1 - TB6612  |
|IO2        |AIN2 - TB6612  |
|IO17       |BIN1 - TB6612  |
|IO5        |BIN2 - TB6612  |
|IO21       |BUZZER         |
|IO27       |USER BUTTON    |
|SENSOR_VP  |ADC1           |
|SENSOR_VN  |ADC2           |
|IO34       |ADC3           |
|IO35       |ADC4           |
|IO18       |SDA            |
|IO19       |SCL            |
|IO13       |MOSI           |
|IO15       |CS             |
|IO14       |SCK            |
|IO32       |TRIG           |
|IO33       |ECHO           |

## PCA pin assignment 
I2C address pin A0A1A2A3A4A5 = 000000
|PIN        |Connected      |
|-----------|---------------|
|LED0       |Servo 1        |
|LED1       |Servo 2        |
|LED2       |Servo 3        |
|LED3       |Servo 4        |
|LED4       |Servo 5        |
|LED5       |Servo 6        |


## Connector 
|Type       |Function                               |Decription                     |
|-----------|---------------------------------------|-----------                    |
|RJ11 6P6   |ANA_line                               |1:GND; 2-5:ANA4-ANA1; 6:5VDC   |
|RJ11 6P4 x6|Servo                                  |1:GND; 2:5VDC; 3:PWM;  4:NC    |
|RJ11 6P4   |I2C                                    |1:GND; 2:SDA;  3:SCL;  4:3.3V  |
|RJ11 6P4   |Ultra sound                            |1:GND; 2:ECHO; 3:TRIG; 4:5V    |
|Domino     |Output Supply power anh control Motor  |2.54mm 2pin                    |
|jack DC    |Input Supply power board and Peripheral|12VDC                          |
|USB type-C |USB code                               |                               |

