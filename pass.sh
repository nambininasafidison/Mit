#!/bin/bash
ip a add 192.168.76.12/24 dev wlan0 label wlan0:1
ip a add 192.168.75.13/24 dev wlan0 label wlan0:2
echo "net.ipv4.ip_forward = 1" > /etc/sysctl.conf
sysctl -p
#iptables -t Nat -A POSTROUTING -o wlan0 -j MASQUARADE
#ip r add 192.168.75.14/24 via  192.168.76.12 dev wlan0:1
