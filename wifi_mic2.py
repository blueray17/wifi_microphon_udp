#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May 30 08:42:15 2022

@author: ipin
"""

import pyaudio
import socket

def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(0)
    try:
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

UDP_IP = get_ip()
UDP_PORT = 1234


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

p = pyaudio.PyAudio()

stream = p.open(format=32, channels=1, rate=11111, output=True)

try:
    while True:
        data, addr = sock.recvfrom(1024) # buffer de 1024 bytes
        stream.write(data)

except KeyboardInterrupt:  #precionar Crtl + C para salir
    print("Cerrando...")
    stream.stop_stream()
    stream.close()
    p.terminate()
