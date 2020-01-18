#!/usr/bin/env python

from mpsse import *
from time import sleep

# Open mpsse in GPIO mode
io = MPSSE(GPIO)

# Toggle the first GPIO pin on/off 10 times
for i in range(0, 10):

	io.set_pin_high(GPIOL0)
	print "GPIOL0 State:", io.pin_state(GPIOL0)
	sleep(1)

	io.set_pin_low(GPIOL0)
	print "GPIOL0 State:", io.pin_state(GPIOL0)
	sleep(1)

io.Close()
