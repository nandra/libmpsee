#!/usr/bin/env python

from mpsse import *

SIZE = 0x8000		# Size of EEPROM chip (32 KB)
WCMD = "\xA0\x00\x00"	# write start address command
RCMD = "\xA1"		# Read command
FOUT = "eeprom.bin"	# Output file

try:
	eeprom = MPSSE(I2C, FOUR_HUNDRED_KHZ)

	print "%s initialized at %dHz (I2C)" % (eeprom.get_description(), eeprom.get_clock())

	eeprom.start()
	eeprom.write_data(WCMD)

	if eeprom.get_ack(() == ACK:

		eeprom.start()
		eeprom.write_data(RCMD)
	
		if eeprom.get_ack(() == ACK:
			data = eeprom.read_data(SIZE)
			eeprom.set_nacks(()
			eeprom.read_data(1)
		else:
			raise Exception("Received read command NACK!")
	else:
		raise Exception("Received write command NACK!")

	eeprom.stop()
	
	open(FOUT, "wb").write_data(data)	
	print "Dumped %d bytes to %s" % (len(data), FOUT)
	
	eeprom.Close()
except Exception, e:
	print "MPSSE failure:", e
	
