EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 61ECBE52
P 3325 2875
F 0 "A1" H 3325 4056 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 3325 3965 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 3325 2875 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 3325 2875 50  0001 C CNN
	1    3325 2875
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A3
U 1 1 61ECC8B3
P 7150 3850
F 0 "A3" H 7200 4731 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 7200 4640 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 7425 3100 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 7250 3550 50  0001 C CNN
	1    7150 3850
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A2
U 1 1 61ECDC3A
P 5425 3850
F 0 "A2" H 5475 4731 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 5475 4640 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 5700 3100 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 5525 3550 50  0001 C CNN
	1    5425 3850
	1    0    0    -1  
$EndComp
$Comp
L PJ-037A:PJ-037A J1
U 1 1 61ED222D
P 4500 2550
F 0 "J1" H 4495 2890 50  0000 C CNN
F 1 "PJ-037A" H 4495 2799 50  0000 C CNN
F 2 "PJ-037A_Connector:CUI_PJ-037A" H 4500 2550 50  0001 L BNN
F 3 "" H 4500 2550 50  0001 L BNN
F 4 "Manufacturer recommendations" H 4500 2550 50  0001 L BNN "STANDARD"
F 5 "CUI INC" H 4500 2550 50  0001 L BNN "MANUFACTURER"
	1    4500 2550
	1    0    0    -1  
$EndComp
Text GLabel 5275 4950 0    50   Input ~ 0
GND_Barrel
Text GLabel 7000 4950 0    50   Input ~ 0
GND_Barrel
Text GLabel 4850 2650 2    50   Input ~ 0
GND_Barrel
Text GLabel 3275 4375 0    50   Input ~ 0
GND_Uno
Wire Wire Line
	3425 3975 3425 4375
Wire Wire Line
	3425 4375 3275 4375
Text GLabel 5275 4800 0    50   Input ~ 0
GND_Uno
Text GLabel 7000 4800 0    50   Input ~ 0
GND_Uno
Wire Wire Line
	5425 4650 5425 4800
Wire Wire Line
	5425 4800 5275 4800
Wire Wire Line
	5275 4950 5625 4950
Wire Wire Line
	5625 4650 5625 4950
Wire Wire Line
	7000 4800 7150 4800
Wire Wire Line
	7150 4800 7150 4650
Wire Wire Line
	7000 4950 7350 4950
Wire Wire Line
	7350 4650 7350 4950
$Comp
L Device:C_Small C1
U 1 1 61ECECEC
P 6150 2550
F 0 "C1" H 6242 2596 50  0000 L CNN
F 1 "100uF" H 6242 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6150 2550 50  0001 C CNN
F 3 "~" H 6150 2550 50  0001 C CNN
	1    6150 2550
	1    0    0    -1  
$EndComp
Text GLabel 3450 1550 0    50   Input ~ 0
Uno_5V
Wire Wire Line
	3525 1875 3525 1550
Wire Wire Line
	3525 1550 3450 1550
Wire Wire Line
	5025 3450 4975 3450
Wire Wire Line
	4975 3450 4975 3550
Wire Wire Line
	4975 3550 5025 3550
Wire Wire Line
	6750 3450 6700 3450
Wire Wire Line
	6700 3450 6700 3550
Wire Wire Line
	6700 3550 6750 3550
Text GLabel 2675 2475 0    50   Input ~ 0
D2
Text GLabel 2675 2575 0    50   Input ~ 0
D3
Text GLabel 2675 2675 0    50   Input ~ 0
D4
Text GLabel 2675 2775 0    50   Input ~ 0
D5
Wire Wire Line
	2675 2475 2825 2475
Wire Wire Line
	2675 2575 2825 2575
Wire Wire Line
	2675 2675 2825 2675
Wire Wire Line
	2675 2775 2825 2775
Text GLabel 4875 3950 0    50   Input ~ 0
D2
Wire Wire Line
	4875 3950 5025 3950
Text GLabel 4875 3850 0    50   Input ~ 0
D3
Wire Wire Line
	4875 3850 5025 3850
Text GLabel 6600 3950 0    50   Input ~ 0
D4
Wire Wire Line
	6600 3950 6750 3950
Text GLabel 6600 3850 0    50   Input ~ 0
D5
Wire Wire Line
	6600 3850 6750 3850
Text GLabel 5025 3150 0    50   Input ~ 0
Uno_5V
Wire Wire Line
	5025 3150 5425 3150
Text GLabel 6750 3150 0    50   Input ~ 0
Uno_5V
Wire Wire Line
	6750 3150 7150 3150
$Comp
L 796949-4:796949-4 J2
U 1 1 61EE0DC2
P 6200 4450
F 0 "J2" V 6304 4222 50  0000 R CNN
F 1 "796949-4" V 6213 4222 50  0000 R CNN
F 2 "TE_Terminal_Block:TE_796949-4" H 6200 4450 50  0001 L BNN
F 3 "" H 6200 4450 50  0001 L BNN
F 4 "796949-4" H 6200 4450 50  0001 L BNN "Comment"
	1    6200 4450
	0    -1   -1   0   
$EndComp
$Comp
L 796949-4:796949-4 J3
U 1 1 61EF4A90
P 7925 4450
F 0 "J3" H 7797 4454 50  0000 R CNN
F 1 "796949-4" H 7797 4545 50  0000 R CNN
F 2 "TE_Terminal_Block:TE_796949-4" H 7925 4450 50  0001 L BNN
F 3 "" H 7925 4450 50  0001 L BNN
F 4 "796949-4" H 7925 4450 50  0001 L BNN "Comment"
	1    7925 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5925 3750 6000 3750
Wire Wire Line
	6000 3750 6000 4250
Wire Wire Line
	5925 3850 6100 3850
Wire Wire Line
	6100 3850 6100 4250
Wire Wire Line
	5925 3950 6200 3950
Wire Wire Line
	6200 3950 6200 4250
Wire Wire Line
	5925 4050 6300 4050
Wire Wire Line
	6300 4050 6300 4250
Wire Wire Line
	7650 3750 7725 3750
Wire Wire Line
	7725 3750 7725 4250
Wire Wire Line
	7650 3850 7825 3850
Wire Wire Line
	7825 3850 7825 4250
Wire Wire Line
	7650 3950 7925 3950
Wire Wire Line
	7925 3950 7925 4250
Wire Wire Line
	7650 4050 8025 4050
Wire Wire Line
	8025 4050 8025 4250
Text GLabel 4850 2450 2    50   Input ~ 0
12V
Wire Wire Line
	4850 2450 4700 2450
Wire Wire Line
	4850 2650 4700 2650
Text GLabel 5625 3000 1    50   Input ~ 0
12V
Wire Wire Line
	5625 3000 5625 3150
Text GLabel 7350 3000 1    50   Input ~ 0
12V
Wire Wire Line
	7350 3000 7350 3150
Text GLabel 6075 2375 0    50   Input ~ 0
12V
$Comp
L Device:C_Small C3
U 1 1 61F2EB46
P 6600 2550
F 0 "C3" H 6692 2596 50  0000 L CNN
F 1 "100uF" H 6692 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6600 2550 50  0001 C CNN
F 3 "~" H 6600 2550 50  0001 C CNN
	1    6600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6075 2375 6150 2375
Wire Wire Line
	6150 2375 6150 2450
Wire Wire Line
	6150 2450 6600 2450
Connection ~ 6150 2450
Wire Wire Line
	6150 2650 6600 2650
Text GLabel 6075 2650 0    50   Input ~ 0
GND_Barrel
Wire Wire Line
	6075 2650 6150 2650
Connection ~ 6150 2650
$Comp
L Device:C_Small C4
U 1 1 61F3818E
P 7525 2550
F 0 "C4" H 7617 2596 50  0000 L CNN
F 1 "100uF" H 7617 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7525 2550 50  0001 C CNN
F 3 "~" H 7525 2550 50  0001 C CNN
	1    7525 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 61F38195
P 7975 2550
F 0 "C5" H 8067 2596 50  0000 L CNN
F 1 "100uF" H 8067 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7975 2550 50  0001 C CNN
F 3 "~" H 7975 2550 50  0001 C CNN
	1    7975 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2375 7525 2375
Wire Wire Line
	7525 2375 7525 2450
Wire Wire Line
	7525 2450 7975 2450
Connection ~ 7525 2450
Wire Wire Line
	7525 2650 7975 2650
Wire Wire Line
	7450 2650 7525 2650
Connection ~ 7525 2650
Text GLabel 7450 2375 0    50   Input ~ 0
Uno_5V
Text GLabel 7450 2650 0    50   Input ~ 0
GND_Uno
$EndSCHEMATC
