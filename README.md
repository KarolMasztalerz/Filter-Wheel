# Filter Wheel
This is folder that contains firmware for Backyard Space Program filter wheel. This firmware is meant to be installed on Arduino board found inside the filter wheel.

Current COM protocol:

Messaging is realised via standard arduino USB COM Port, Baud rate 9600. Filter wheel will attempt to open port upon connection.

Currently supported commands are strings/chars of:

0-request firmware information and state from filter wheel, will be sent as a string to COM.
1-move by 1 filter to left.
2-move by 1 filter to right.
3-input the number of filter slots in filter wheel carousel. This depends on model of carousel. Next input is the number of filter slots.

Expected returns from wheel:
0: command performed succsefully
-1: unknown command.
