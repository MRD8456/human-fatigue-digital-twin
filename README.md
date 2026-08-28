# human-fatigue-digital-twin
A C++ simulation modeling worker's alertness level and tiredness-level related safety risks in dangerous work environments , based on the three process model of Alertness.

This project implements a digital twin prototype for estimating real life fatigue-risk among workers in dangerous work environments such as offshore oil rigs
where a lapse in alertness from an exhausted worker can lead to serious safety consequences.

 HOW IT WORKS :
 
 first we need explain that what a three process model actually models.
three process model simply combines two separate calculations to predict one output and that is a worker Alertness level , and the two calculations  definitions are :

Process S(Homeostatic): Models "Sleep Pressure" , which builds the longer a workers stays awake and dissipates while they sleep.

Process C(Circadian) : Models the body's internal 24-hour clock , which naturally raises and lowers alertness at certain times of day regardless of how long someone has been awake.

These two processes are combined and converted onto the real , standardized Karolinska Sleepiness Scale(KSS) , a 1-9 scale used in actual sleep research (1=very alert , 9=very sleepy).
Where possible , the specific constants used in these formula are taken from peer-reviewed research. In a few cases , the original papers exact values were not accessible to us , in those cases , we derived our own reasonable values using known boundary conditions , and we noted this explicitly where ever it applies , both in code comments and later on this README.

INSTRUCTIONS :

In order to be able to run this file you would need to have the C++ compiler installed on you device  either MSYS2 or MinGW  , secondly you would need a terminal to actually run the 
so our recommendation would be VS code or VS studio.
Next step is to actually compile all 5 files and to do that you would need to type in this prompt into your terminal window on VS code :
g++ main.cpp worker.cpp simulation.cpp -o digitaltwin

After compiling it , you need to actually run it in order to get the actual output : .\digitaltwin.exe 
Then you should be able to see the output in your terminal window.
