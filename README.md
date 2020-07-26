# Fortune Machine Computer 机器电脑
# Yoe Yat System Design 如日系统设计

Email 电邮: FortuneMachineComputer@gmail.com
Blog 博客: http://yoeyat.blogspot.com
Website网页 : http://www.facebook.com/fortunemachinecomputer
Google 谷歌 : https://fortune-machine-computer.business.site/
YouTube 优管 : https://www.youtube.com/playlist?list=PLF6c98ucvwdJrBeHWzdXoPVAzHv2a3_lZ

# fast_body_temperature_meter component

TJC3224T022_011 Screen / 屏幕 

GY-906 BCC or DCC Temperature Sensor / 红外线传感器

Cytron Macker Uno or Arduino Uno with extra buzzer mainboard /主板

Box 盒子

Some jumper wire / 一些跳线

Micro usb cable / 线


#Component I buy from here / 元件我在这里买

https://item.taobao.com/item.htm?id=561727164788
https://item.taobao.com/item.htm?id=615285502789

https://my.cytron.io/p-maker-uno-simplifying-arduino-for-education
https://my.cytron.io/p-plastic-box-120x80x40mm-grey
https://my.cytron.io/p-usb-micro-b-cable
https://my.cytron.io/p-40-ways-male-to-female-jumper-wire
https://my.cytron.io/p-40-ways-male-to-male-jumper-wire

#Software library used
https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library
https://www.arduino.cc/en/main/software
http://wiki.tjc1688.com/doku.php
http://tjcfile.iicp.net:885/USARTHMI/hmi.rar

#Wiring
TJC3224T022_011 
VCC to Uno 5v
GND to Uno GND
TX	to Uno Rx (pin 4 software serial)
RX	to Uno Tx (pin 3 software serial)

GY-906 BCC
VCC to Uno 3.3v
GND to Uno GND
SDA to Uno Analog Pin 4
SCL to Uno Analog PIn 5

