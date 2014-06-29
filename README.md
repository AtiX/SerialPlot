SerialPlot
==========

A program that plots incoming data from a serial connection like an arduino.

![Main Window](https://raw.github.com/AtiX/SerialPlot/media/screenshot0.jpg)

The program reads full lines from the serial connection and parses lines beginning with `PLOT `;
the screenshot was created with data like
```
PLOT current:107 movingAvg:66.28
```