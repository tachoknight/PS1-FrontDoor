# PS1-FrontDoor
This is a project I put together to display something on the [BB-View](<https://www.element14.com/community/docs/DOC-55844/l/expansion-board-for-beaglebone-family-with-7-inch-lcd>) screen that is visible through the front door window of [Pumping Station: One](<http://pumpingstationone.org>). The computer driving the screen is a [BeagleBone Black](<https://beagleboard.org/black>) running Debian Linux attached to the screen via a ribbon cable.

As of April, 2016, it rolls through three screens:

* The PS:1 logo with the time of the open house displayed randomly on top
* The URL of PS:1's website (`pumpingstationone.org`) and the date and time of the open house
* The schedule of events taking place at PS:1 this week (currently it shows the first four in sooner-to-later order to fit on the screen because I haven't figured out how to make a nice marquee that shows everything)

There are two parts to the code base, the front-end [**PS1-FrontDoor application**](#ps1-frontdoor), and [**doorman**](#doorman), which is the back-end server.


## <a name="ps1-frontdoor"></a>PS1-FrontDoor (GUI application)
The PS1-FrontDoor application is a C++/QML application that uses the [Qt](<http://qt.io>) 5.6.1 framework. The Beaglebone Black has a native version of Qt compiled from Qt's git repository.

### Compiling Qt on the Beaglebone Black
The Qt library was downloaded from the Qt git repository (`https://code.qt.io`) and configured with:

	./configure -no-directfb -opensource

DirectFb is not properly supported on the BBB as Qt likes it and was causing the build to fail. As this is an open-source version of Qt, all code compiled with this version should be made publicly available (as this repository is doing).

#### Building
Running `./configure` will take, approximately half an hour to finish. Once you're ready to run `make`, make sure you've got some other things to do as you're gonna be waiting for awhile (I lost track, but Qt took anywhere between 48 and 60 hours to compile completely). Given the amount of time, I suggest running the build in a tmux session so that you don't have to keep your connection to the BBB going the whole time.	
### The GUI application
As this application does not handle any user input, it is written as a marquee app that cycles through a variety of screens, as handled by `carouseltimer.cpp`. The screens themselves are written using QML/QTQuick and have a `.qml` extension (the QTQuick-specific files have a `.ui.qml` extension). `main.qml` is the screen that contains the transition and state logic and sets the screen dimensions for the app to run full-screen on the BB-View (480x272 for the 4" screen).

Note that if you want to run the application on a machine that *isn't* the BBB, I recommend commenting out these lines in `main.qml`:
	
	flags: Qt.Splashscreen
	visibility: Qt.WindowFullScreen
so that it won't competely take over your display. 

#### Invoking the server (doorman)
The `scheduletimer.cpp` file contains a Qt timer object that is configured in its constructor to fire every half-hour and get the schedule in JSON format from the doorman server. 	

## <a name="doorman"></a>Doorman (Server application)
The doorman server (thanks to PS:1's member and CTO Doorman Dave for letting me use the name) is a Java-based application that is meant to run in Tomcat and serves the current PS:1 schedule for the next week from *right now* in JSON format. 

###Building
The code uses **Gradle** as its build tool. It does not include a `gradlew` command with its accompanying `.gradlew` directory, so it's assumed you have or can get gradle and invoke the build as:
	
	gradle war
and the war file will be found in `build/libs`. 

The server uses these libraries:

* Biweekly for iCal parsing
* FasterXML Jackson for json handling
* Servlet API 2.5

## TODO
This is specific to PS:1, but eventually we want to ressurect the [RFID system](<https://github.com/loansindi/ps1rfid>) so that folks can get in using their registered tags. The PS1-FrontDoor application should be updated to indicate that the tag has been successfully read and access granted.


