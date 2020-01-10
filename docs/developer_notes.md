# Developer Notes

## About

* Yujin flashes a serial id, 'kobuki_<unique identifier>' into the chip's eeprom at the factory.
* Users copy across a udev rule '60-kobuki.rules' to /etc/udev/rules.d directory.
* Users add themselves to the dialout group
* Restart services
* Plug in kobuki, it will appear on /dev/kobuki

## Programming the Eeprom

* Install kobuki_ftdi package
* Plug in the device
* Execute ftdi_kobuki

If it is the only FTDI device plugged in, simply

```
> sudo <install path>/lib/kobuki_ftdi/ftdi_koboki
```

will do the job, if not - optionally add an argument with the current serial id of the FTDI
chip you want to flash to the last command.

If things go bums up, then you will find an eeprom.backup saved in your current directory that you
can reflash back to the chip (using ftdi_write_eeprom).

```
> sudo <install path>/lib/kobuki_ftdi/ftdi_write_eeprom -f eeprom.req
```

## Preparing Udev

```
$ sudo addgroup $USER dialout
$ sudo cp 60-kobuki.rules /etc/udev/rules.d
$ sudo service udev reload
$ sudo service udev restart
```

Logout and log back in to make sure the dialout group permissions take affect.

## Issues

**WILL NOT WORK WITH libftdi 0.17!!!**

libftdi needs to be upgraded to work for TYPE_R (can see [FT232R](http://www.ftdichip.com/Products/ICs/FT232R.htm">FT232R)
on the iInterface variable in lsusb) FTDI chips. To workaround on lucid(Ubuntu 10.04), simply uninstall libftdi and 
ownload the sources for version 0.2/0.3 and above (might also work on 0.18 from emails I've read).

* http://www.intra2net.com/en/developer/libftdi/download.php

Might work out of the box on oneric(Ubuntu 11.10), but I haven't tried.

## Package Tree

* docs/specifications.md : Important specifications and data for our chip (mostly gathered from lsusb -v).
* src/ftdi_kobuki.cpp : Primary utility, reads the device eeprom, converts strings for kobuki, and reflashes.
* src/ftdi_read_eeprom.cpp : Reads and saves a device's eeprom to binary file on pc.
* src/ftdi_scan.cpp : Scans FTDI devices for the serial strings.
* src/ftdi_write_eeprom.cpp : Writes a backed up eeprom binary to the device.
* src/find_devices.cpp : Detect the presence of FTDI devices.
* src/get_serial_number.cpp : Print serial number of all the FTDI devices connected. with manufacture and product name.
* src/flasher.cpp : Flash FTDI chip's serial number with 'kobuki_' prefix.
* src/unflasher.cpp : Turn back FTDI chip's serial number to original.
* src/reset_device.cpp : Reset the all FTDI devices connected, to reload as standard FTDI device, after the flashing serial number.
* src/overwrite_serial_number.cpp : Overwrite serial number of FTDI device.

## System Utilities

### lsusb

Make sure you use sudo, if not, it will only retrieve part of the information.

```
> lsusb
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
 ...
Bus 002 Device 007: ID 0403:6001 Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC
// Get the two numbers to the left of the FTDI device (bus and device number) (e.g. 002, 007)
> sudo lsusb -v -s 002:007
```

### udevadm

Much more detailed information of a currently connected device.

```
> ls /dev/ttyUSB*
/dev/ttyUSB0
> sudo udevadm info -a -n /dev/ttyUSB0
```
