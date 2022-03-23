#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# tab-size: 4

from functools import reduce
import time, argparse
import serial, serial.tools.list_ports

BLOCK_SIZE	= 16
CMD_SOH		= b'\x01'	# [SOH] Start of Heading
CMD_STX		= b'\x02'	# [STX] Start of Text
CMD_ETX		= b'\x03'	# [ETX] End of Text
CMD_EOT		= b'\x04'	# [EOT] End of Transmission
CMD_ACK		= b'\x06'	# [ACK] Acknowledge
CMD_NACK	= b'\x15'	# [NAK] Negative Acknowledge
CMD_SUB		= b'\x1A'	# [SUB] Substitute
CMD_DEL		= b'\x7F'	# [DEL] Delete

class N76flash:
	def __init__(self, filename, port, baud, verbose, ntry=100):
		self.arg  = locals()
		try:
			self.s = serial.Serial(port, baudrate=baud)
			if (self.arg['verbose']): print(f'{port} used at {baud}')
		except serial.SerialException as e:
			print(e)
			if 'FileNotFoundError' in e.__str__():
				print(f'please select one from: {",".join([_.name for _ in list(serial.tools.list_ports.comports())])}')
				exit()
			raise
		self.data = open(filename, 'rb').read()
		print(f'read {len(self.data)} bytes from {filename}')

	def execute(self):
#		print (f'crc test: {self.crc(b"123456789")}')
		print('Connecting, please RESET the microcontroller...')
		for i in (self.ping, self.erase, self.write, self.reset):
			if not i():
				print('fail')
				exit()
		print('done')

	def crc(self, data):	#crc8 dallas/maxim
		def lfsr(crc, x):
			for i in range(8):
				crc = (crc>>1)^0x8C if (crc^(x>>i))&0x01 else (crc>>1)
			return crc
		return bytes([reduce(lfsr, data, 0)])	

	def tx(self, data):
		if (self.arg['verbose']): print(f'\t-> {data}')
		self.s.write(bytearray(data))

	def ack(self):
		ch = self.s.read(1)
		if (self.arg['verbose']): print(f'\t<- {ch}')
#		return True
		return ch == CMD_ACK

	def ping(self):
		print('ping')
		self.s.timeout=.2
		for i in range(self.arg['ntry']):
			self.s.flushInput()
			self.tx( CMD_SOH )
			if self.ack(): break
			time.sleep(.2)
			print(f'\rtry #{i}', end='')
		else:
#			print(' .. fail')
			return False
		print(' ok')
		return True

	def erase(self):
		print('erase')
		self.s.timeout=6.0	#max 6ms/page + overheads
		ts = time.time()
		self.tx( CMD_SUB + CMD_DEL )
		ack = self.ack();
		#if (self.arg['verbose']): 
		print(f'\t{time.time()-ts:f} sec')
		return ack

	def write(self):
		self.data += b'\xff' * ((BLOCK_SIZE-len(self.data)) % BLOCK_SIZE)	#FF-fill end of block
		self.s.timeout=1.	#11 us/byte + overheads
		ts = time.time()
		for i in range(0,len(self.data), BLOCK_SIZE):
			data = self.data[i:i+BLOCK_SIZE]
			crc  = self.crc(data)
			self.tx( CMD_STX + data + crc + CMD_ETX)
			if not self.ack(): return False
			print(f"write {((i+BLOCK_SIZE)*100)/len(self.data):.0f}%", end='\r');
		print('')
		#if (self.arg['verbose']): 
		print(f'\t{time.time()-ts:f} sec')
		return True

	def reset(self):
		print('reset')
		self.tx( CMD_EOT )
		return self.ack();


if __name__ == '__main__':
	parser = argparse.ArgumentParser(
		description='N76E003 Bootloader tool\nhttps://github.com/kimstik/N76E003',
		epilog='Copyright (C) kimstik, 2022.')
	parser.add_argument('filename',																		help='binary file to flash')
	parser.add_argument('-p', '--port'						,required=True	,							help='serial port')
	parser.add_argument('-b', '--baud',		default=19200	,required=False	,	type=int,				help='serial port baud rate')
	parser.add_argument('-v', '--verbose',	default=False	,required=False	,	action="store_true",	help='verbose output')
	args = parser.parse_args()

	N76flash(args.filename, args.port, args.baud, args.verbose).execute()
