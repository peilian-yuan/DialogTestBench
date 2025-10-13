# DialogTestBench
A test platform to test popup dialog, which should be compiled as static libray.
And following steps also must be taken to make it working: 
1. Add static library to "link -> input -> additional dependences"
2. Add lib_rsc.res to "link -> input -> additional dependences"
3. Set path of additional library for both library and lib_rsc.res;
4. Set path of include for head files to include the path of resource.h of library;
5. Compile the project.

Arguments for the application:
DialogTestBench -c | -i [-p]
-c: start detecting com-port devices
-i: start detecting network devices
-p: show percentage in the progress
