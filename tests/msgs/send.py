#!/usr/bin/python

# Send UDP broadcast packets

MYPORT = 67

import sys, time
from socket import *

if len(sys.argv) < 2:
	print("Please specify intput file from which the data will be read and sent")
	sys.exit(1)

s = socket(AF_INET, SOCK_DGRAM)
s.bind(('', 0))
s.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

data = open(sys.argv[1]).read()
print(data)
s.sendto(data, ('<broadcast>', MYPORT))
