# DialogTestBench
A test platform to test popup dialog, which should be compiled as static libray.
And following steps also must be taken to make it working: 
1. Add static library to "link -> input -> additional dependences"
2. Add lib_rsc.res to "link -> input -> additional dependences"
3. Set path of additional library for both library and lib_rsc.res;
4. Set path of include for head files to include the path of resource.h of library;
5. Compile the project.

A simple way to add to be tested dialog is implement as following:
Add a propery sheet for the to be tested project in the folder PropertySheets.
The followings are defined in the sheet:
LibDir: folder including the static library compiled from the tested dialog of release version
LibDBDir: folder including the static library compiled from the tested dialog of debug version
LibIncDir: folder including the head files of the tested dialog

Arguments for the application:
DialogTestBench [-h] [-p] [-c|-i] [-d DEV_IDS]
-h: show help
-c: start detecting com-port devices, default value
-i: start detecting network devices
-p: show percentage in the progress, default show number
-d: specify to be searched device ids
