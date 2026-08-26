# human-fatigue-digital-twin
A C++ simulation worker alertness and fatigue-related safety risk in hazardous work environments , based on three process model of Alertness.
This project implements a digital twin prototype for estimating real-time fatigue risk among workers in dangerous work environments - such as off shore oil rigs -
where a single laps in alertness from an exhausted worker can lead to serious safety consequence.
 HOW IT WORKS :
 first we need explain that what a three process model actually models.
three process model simply combines two separate calculations to predict one output and that is a worker Alertness level , those two calculations are defined in the following manner :
Process S(Homeostatic): Models "Sleep Pressure" , which builds the longer a workers stays awake and dissipates while they sleep.
Process C(Circadian) : Models the body's internal 24-hour clock , which naturally raises and lowers alertness at certain times of day regardless of how long someone has been awake.
These two processes are combined and converted onto the real , standardized Karolinska Sleepiness Scale(KSS) , a 1-9 scale used in actual sleep research (1=very alert , 9=very sleepy).
Where possible , the specific constants used in these formula are taken from peer-reviewed research. In a few cases , the original papers exact values were not accessible to us , in those cases , we derived our own reasonable values using known boundary conditions , and we noted this explicitly where ever it applies , both in code comments and later on this README.
