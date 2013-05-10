Server Monitor
==============

Tool to keep an eye on a list of servers and services, developed on QT (under Linux but may be compiled for windows too); The tool will send a notification when a server is found down.

The whole idea is:

  * Read the destination list from a json configuration file. (done)
    - Multithreaded connections are not implemented yet, but still is planned.
  * Open a connection to each of the servers given in the list. (done)
  * If a connection fails sends a notification event to the DWM so it may be attended. (done)
  * A graphic GUI is being designed. (In Process)
    - Start / Stop button is needed. (TODO)
    - Both last cases should save a basic statistic table. (TODO)
    - If a connection success provide different statistics depending on the lag. (TODO)
  * QT5 migration will help in the process to cover more platforms (TODO)

The Motivation
==============

This project is done because I'm currently a sysadmin with a constantly changing set of servers and QT development is fun.


Instalation
===========

There is no such automated method to install this application but you can compile and use it running:

 * cmake .
 * make

And then run using ./ServerMonitor

There is a configuration sample which you should rename to config.json instead of config-sample.json; edit it and set valid IP addresses or hostnames.

Enjoy!!
=======
