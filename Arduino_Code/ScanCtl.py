import serial
import time


serport = input("\n Type in serial port: ")
ser = serial.Serial(serport, 9600)
# If you are using a windows, uncomment below
#ser = serial.Serial('/dev/tty.usbmodem1411401', 9600)
scan_status = 0
def scan_ctl():
	# b for begin and s for stop, r for reset
	user_input = input("\n Type b/s/r: ")
	if user_input == "b":
		print("Scan begins")
		time.sleep(0.1)
		ser.write(b'H')
		scan_status = 1 
		#scan_ctl()
	elif user_input == "s":
		print("Scan stops")
		time.sleep(0.1)
		ser.write(b'L')
		scan_status = 2
		#scan_ctl()
	# elif user_input == "r":
	# 	print("Reseting scanning")
	# 	time.sleep(0.1)
	# 	ser.write(b'L')
	# 	ser.close()
	else:
		print("invalid input")
	
	return scan_status

scanCount = 0

time.sleep(2)
f = open("LiDAR.txt",'w')

while scan_status == 0:
	scan_status = scan_ctl()

	if scan_status == 1:
		dataSize = input("\n Type in number of data points (int): ")
		dataSize = int(dataSize)
		if scanCount == 0:
			with open("LiDAR.txt", 'w', encoding = 'utf-8') as f:
				f.write("LiDAR scanning data\n")
				for i in range(0,dataSize):
					data = ser.readline()
					data = data.decode('utf-8')
					#print(data)
				
					f.write(data + "\n")
				#f.close()
				scanCount += 1
		
		# append new scanned data if not first round of scanning
		else:
			with open("LiDAR.txt", 'a', encoding = 'utf-8') as f:
				
				for i in range(0,dataSize):
					data = ser.readline()
					data = data.decode('utf-8')
					#print(data)
				
					f.write(data + "\n")
				#f.close()
				scanCount += 1
					
		print ("File closed")
		print ("{} time(s) scanned so far".format(scanCount))
		scan_status = 0
	
	elif scan_status == 2:
		print("Not scanning")








