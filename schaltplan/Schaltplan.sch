EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ZTPROJ"
Date "2020-06-17"
Rev "1.0"
Comp ""
Comment1 "KT"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 5EEA462B
P 4650 3200
F 0 "A?" H 4650 4381 50  0001 C CNN
F 1 "Arduino_UNO_R3" H 4650 4289 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 4650 3200 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 4650 3200 50  0001 C CNN
	1    4650 3200
	1    0    0    -1  
$EndComp
$Comp
L Timer_RTC:DS3231MZ U?
U 1 1 5EEAE01F
P 7050 4700
F 0 "U?" H 7050 4211 50  0001 C CNN
F 1 "RTC DS3231" H 7365 4290 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7050 4200 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231M.pdf" H 7050 4100 50  0001 C CNN
	1    7050 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4500 6050 4500
Wire Wire Line
	6050 4500 6050 4000
Wire Wire Line
	6050 4000 5150 4000
Wire Wire Line
	6550 4600 6350 4600
Wire Wire Line
	6350 4600 6350 3900
Wire Wire Line
	6350 3900 5150 3900
$Comp
L Sensor:DHT11 U?
U 1 1 5EEB1BB2
P 6850 2400
F 0 "U?" H 6607 2446 50  0001 R CNN
F 1 "DHT22_1" H 6607 2400 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 6850 2000 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 7000 2650 50  0001 C CNN
	1    6850 2400
	1    0    0    -1  
$EndComp
$Comp
L Sensor:DHT11 U?
U 1 1 5EEB2EC0
P 6850 3300
F 0 "U?" H 6607 3346 50  0001 R CIN
F 1 "DHT22_2" H 6607 3300 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 6850 2900 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 7000 3550 50  0001 C CNN
	1    6850 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2200 4850 2000
Wire Wire Line
	4850 2000 6250 2000
Wire Wire Line
	6250 2000 6250 2900
Wire Wire Line
	6250 2900 6850 2900
Wire Wire Line
	6850 2900 6850 3000
Connection ~ 6250 2000
Wire Wire Line
	6250 2000 6850 2000
Wire Wire Line
	6850 2000 6850 2100
Wire Wire Line
	4750 4300 4750 4500
Wire Wire Line
	4750 4500 5750 4500
Wire Wire Line
	5750 4500 5750 3700
Wire Wire Line
	5750 3700 6850 3700
Wire Wire Line
	6850 3700 6850 3600
Wire Wire Line
	6850 2700 7450 2700
Wire Wire Line
	7450 2700 7450 3700
Wire Wire Line
	7450 3700 6850 3700
Connection ~ 6850 3700
Wire Wire Line
	6850 2900 7750 2900
Wire Wire Line
	7750 4000 7050 4000
Wire Wire Line
	7050 4000 7050 4300
Connection ~ 6850 2900
Wire Wire Line
	7050 5100 7050 5200
Wire Wire Line
	7050 5200 8050 5200
Wire Wire Line
	8050 5200 8050 4150
Wire Wire Line
	8050 3700 7450 3700
Connection ~ 7450 3700
$Comp
L Device:BFS U?
U 1 1 5EECF3A7
P 8550 3550
F 0 "U?" V 8325 3550 50  0001 C CNN
F 1 "BFS_1" H 8462 3550 50  0000 R CNN
F 2 "" H 8550 3550 50  0001 C CNN
F 3 "~" H 8550 3550 50  0001 C CNN
	1    8550 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:BFS U?
U 1 1 5EECFCA2
P 8550 4000
F 0 "U?" V 8325 4000 50  0001 C CNN
F 1 "BFS_2" H 8462 4000 50  0000 R CNN
F 2 "" H 8550 4000 50  0001 C CNN
F 3 "~" H 8550 4000 50  0001 C CNN
	1    8550 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3850 7750 3850
Connection ~ 7750 3850
Wire Wire Line
	7750 3850 7750 4000
Wire Wire Line
	8550 3400 7750 3400
Wire Wire Line
	8550 4150 8050 4150
Connection ~ 8050 4150
Wire Wire Line
	8050 4150 8050 3700
Wire Wire Line
	8550 3700 8050 3700
Connection ~ 8050 3700
Connection ~ 7750 3400
Wire Wire Line
	7750 3400 7750 3850
Wire Wire Line
	7750 2900 7750 3400
Wire Wire Line
	5150 3300 5600 3300
Wire Wire Line
	5600 3300 5600 5500
Wire Wire Line
	5600 5500 9000 5500
Wire Wire Line
	9000 5500 9000 3550
Wire Wire Line
	9000 3550 8700 3550
Wire Wire Line
	8700 4000 8850 4000
Wire Wire Line
	8850 4000 8850 5400
Wire Wire Line
	8850 5400 5850 5400
Wire Wire Line
	5850 5400 5850 3400
Wire Wire Line
	5850 3400 5150 3400
Text GLabel 9000 3550 2    50   Input ~ 0
A1
Text GLabel 8850 4000 1    50   Input ~ 0
A2
$Comp
L Device:SD_Card U?
U 1 1 5EF06957
P 2800 2950
F 0 "U?" H 2750 3541 50  0001 C CNN
F 1 "SD_Card" H 2833 3423 50  0000 C CNN
F 2 "" H 2750 2950 50  0001 C CNN
F 3 "" H 2750 2950 50  0001 C CNN
	1    2800 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2850 3800 2850
Wire Wire Line
	3800 2850 3800 3700
Wire Wire Line
	3800 3700 4150 3700
Wire Wire Line
	3400 2950 3750 2950
Wire Wire Line
	3750 2950 3750 3800
Wire Wire Line
	3750 3800 4150 3800
Wire Wire Line
	3400 2750 3650 2750
Wire Wire Line
	3650 2750 3650 3900
Wire Wire Line
	3650 3900 4150 3900
Wire Wire Line
	3400 2650 3950 2650
Wire Wire Line
	3950 2650 3950 3600
Wire Wire Line
	3950 3600 4150 3600
Wire Wire Line
	3400 3050 3550 3050
Wire Wire Line
	3550 3050 3550 2000
Wire Wire Line
	3550 2000 4850 2000
Connection ~ 4850 2000
Wire Wire Line
	3400 3150 3550 3150
Wire Wire Line
	3550 3150 3550 5200
Wire Wire Line
	3550 5200 7050 5200
Connection ~ 7050 5200
Text Notes 1900 1900 0    79   ~ 0
D5 auf 5VDC (VCC) setzen,\num BFS zu kalibrieren.\n(Beim Booten)
Wire Wire Line
	7150 2400 7350 2400
Wire Wire Line
	7350 2400 7350 1700
Wire Wire Line
	7350 1700 4100 1700
Wire Wire Line
	4100 1700 4100 2800
Wire Wire Line
	4100 2800 4150 2800
Wire Wire Line
	7150 3300 7600 3300
Wire Wire Line
	7600 3300 7600 1600
Wire Wire Line
	7600 1600 4050 1600
Wire Wire Line
	4050 1600 4050 2900
Wire Wire Line
	4050 2900 4150 2900
Text GLabel 7350 2150 0    50   Input ~ 0
D2
Text GLabel 7600 3300 3    50   Input ~ 0
D3
$EndSCHEMATC
