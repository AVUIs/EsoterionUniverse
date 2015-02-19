Esoterion Universe
==================

A deep and colourful generative 3D AV project.

Main features:
- Infinite 3D space
- Infinite number of planet-like dynamic objects
- Single screen for interface and output

What you need
-------------

- The most recent version of openFrameworks, download here: https://github.com/openframeworks/openFrameworks/archive/master.zip
- Max 7, download trial here: https://cycling74.com/products/max/
- FTM library for Max 7, download here: http://ftm.ircam.fr/index.php/Download

Installation
------------

- Unzip openFrameworks to a convenient place in your system
- Clone this repository to `apps/myApps/EsoterionUniverse/` inside openFrameworks folder
- Download sound source from http://wirelesscowboy.org/esoterionuniverse/balayage444.wav and place in `EsoterionUniverse/bin/max/` folder
- Install Max 7
- Install FTM library: if needed add it manually to `Max 7/Packages` folder inside your user's `Documents` folder

Running
-------

- Open `max/MainPatch.maxpat` in Max 7, when loaded click Audio On/Off (beware of a glitch first time)
- Open and run XCode project `esoterionUniverse.xcodeproj`
- Add an object with `a` key and try changing the parameters
- If there`s no sound, first turn volume up, then click Audio On/Off twice in Max patch
- Show instructions with `h` key
- Play around and have fun

Known issue
-----------

Due to either a compabitility issue between poly~ and gbr.ola objects, or cpu consumption issues between video/osc/synthesis on the same computer, the granular synthesis is affected by glitches. A new version should see these problems solved hopefully.

Disclaimer
----------

This software is provided here on an “as is” basis, without warranty of any kind, either expressed, implied, or statutory, including, without limitation, warranties that it is free of defects, merchantable, fit for a particular purpose or non-infringing. The entire risk as to the quality and performance of the software is with you.

Credits
---------------------

[Coralie Diatkine](http://coraliediatkine.eu)

[Matthias Moos](http://matthiasmoos.tumblr.com)

[Will Gallia](http://willgallia.com)

[Borut Kumperscak](http://wirelesscowboy.org)