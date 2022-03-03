import serial
import time
import sys

if __name__ == '__main__':
'''
    arg = np.array(sys.argv)
    arg = arg[1:]
    sys.stdout.write(str(np.random.random(arg.astype(int))))
	serport = input("\n Type in serial port: ")
	'''

	# ser = serial.Serial(serport, 9600)
	# If you are using a windows, uncomment below
	#ser = serial.Serial('/dev/tty.usbmodem1411401', 9600)
	# scan_status = 0
	'''
	def scan_ctl():
		# b for begin and s for stop, r for reset
		user_input = input("\n Type b/s/r: ")
		if user_input == "b":
			print("Scan begins")
			# time.sleep(0.1)
			# ser.write(b'H')
			# scan_status = 1 
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
	'''
	def start_scan():
		return 'start'

	def stop_scan():
		return 'stop'

	def puase():
		return 'puase'

	def reset():
		return 'reset'

	'''
	time.sleep(2)
	f = open("LiDAR.txt",'w')

	if scan_status == 0:
		scan_status = scan_ctl()
		if scan_status == 1:
			with open("LiDAR.txt", 'w', encoding = 'utf-8') as f:
				f.write("LiDAR scanning data\n")
				for i in range(0,10):
					data = ser.readline()
					data = data.decode('utf-8')
					print(data)
				
					f.write(data + "\n")
				#f.close()
			print ("File closed")
		elif scan_status == 2:
			print("Not scanning")


	'''




