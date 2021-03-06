# Kobuki FTDI

![Kobuki Logo](resources/kobuki.png)

----

This package provides tools for flashing the [FT232R](https://www.ftdichip.com/Products/ICs/FT232R.htm) usb-to-serial
converter from [FTDI](https://www.ftdichip.com/) on a Kobuki. 

**It is not a necessary dependency for the Kobuki runtime.**

For user information on troubleshooting a USB connection, refer to [Kobuki Documentation/Troubleshooting](https://kobuki.readthedocs.io/en/devel/troubleshooting.html).

----

## Dev Notes

### How it Works

Kobuki's FTDI chip is flashed with a special identifier that allows programs
to uniquely identify the device as a kobuki. This in turn allows for udev rules
that conveniently establish it's presence in a *nix filesystem under `/dev/kobuki`.

To test:

```
# copy across udev rules
> sudo cp 60-kobuki.rules /etc/udev/rules.d
> sudo service udev reload
> sudo service udev restart
```

### Is it Working?

Does kobuki appear as USB device?

```
> lsusb
0403:6001 Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC
```

Do you see it in `dmesg` when you insert the usb cable?

```
> dmesg
[  118.984126] usb 3-1: new full-speed USB device number 5 using xhci_hcd
[  119.139253] usb 3-1: New USB device found, idVendor=0403, idProduct=6001
[  119.139257] usb 3-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[  119.139259] usb 3-1: Product: iClebo Kobuki
[  119.139261] usb 3-1: Manufacturer: Yujin Robot
[  119.139263] usb 3-1: SerialNumber: kobuki_A505QO28
[  119.150240] usbcore: registered new interface driver usbserial_generic
[  119.150249] usbserial: USB Serial support registered for generic
[  119.152383] usbcore: registered new interface driver ftdi_sio
[  119.152403] usbserial: USB Serial support registered for FTDI USB Serial Device
[  119.152505] ftdi_sio 3-1:1.0: FTDI USB Serial Device converter detected
[  119.152530] usb 3-1: Detected FT232RL
[  119.152665] usb 3-1: FTDI USB Serial Device converter now attached to ttyUSB0
```

and when you remove it?

```
[  184.386124] usb 3-1: USB disconnect, device number 5
[  184.386507] ftdi_sio ttyUSB0: FTDI USB Serial Device converter now disconnected from ttyUSB0
[  184.386547] ftdi_sio 3-1:1.0: device disconnected
```

Get the serial number:

```
> sudo <install_path>/lib/kobuki_ftdi/get_serial_number
1 device(s) found.

Device #0
  Manufacturer : Yujin Robot
  Product      : iClebo Kobuki
  Serial Number: kobuki_A505QO28
```

### Flashing the Device

Only do this if you are at the factory or you are very certain it is necessary.
This should rarely need to be done outside of the factory.

```
# Flash
> sudo <install_location>/lib/kobuki_ftdi/flasher
# Check the serial number again
> sudo <install_path>/lib/kobuki_ftdi/get_serial_number
1 device(s) found.

Device #0
  Manufacturer : Yujin Robot
  Product      : iClebo Kobuki
  Serial Number: kobuki_A505QO28
```
