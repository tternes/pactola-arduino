#Pactola Arduino Demo

This respository contains a [Pactola API](http://pactola.io) demo sketch for the [Arduino](http://arduino.cc) project platform.



# Setup
You'll need to modify a few variables in the sketch in order to deliver notifications to your device:

	String device = "deviceIdHere"; // use your personal Device ID

Customize the contents of the notification by modifying the `json` variable in the sketch source. See the [Pactola API Documentation](http://pactola.io/api) for more details.

	String json = "{ \"title\" : \"Arduino Test\", \"message\" : \"It Works :)\" }";


# Usage
The sketch automatically delivers a notification the Pactola API if a network connection is available when the board boots up.