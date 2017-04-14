# 1188 Final Project

Kyle Monto, Mike Mortensen, Matt Damiani, Beth Shenck

The **PubSubClient** folder contains a sample project that Dickerson linked to. If you download Energia, and place the **PubSubClient** folder inside of `Energia/libraries` folder you will be able to open and run the project.

The **MQTT_Milk_Sensor_Publisher** folder contains a modified version of the main file from the **PubSubClient** project.

To run -
1. Load the Arduino code from **MQTT_Milk_Sensor_Publisher** onto your MSP432 with CC3100 wifi module.
2. Write you MSP432 following the schematic in the `schematic` folder
3. Import the NODE-RED JSON (in `nodered/milkReadingsNodeRed.JSON`) file into a new NODE-RED project (May need to configure project to have cloudant database)
4. Add the index to the cloudant DB found in the `cloudant` folder and go to *Permissions* for the created database and check the box for *reader* from *Unauthorized Connections* this will allow you to access the data with a request generated from NODE-RED
5. Deploy the NODE-RED project and start the MSP432 with the Arduino code


* There may be other configurations that may I may not have thought of so be sure to follow exceptions to resolve these errors

* Explore some of the other folders on for more information or examples on the code for the MSP432 or NODE-RED

* This project was largely based off of this project:
http://energia.nu/creating-an-iot-connected-sensor-with-energia-mqtt/

* Consult the link above if you need more information
