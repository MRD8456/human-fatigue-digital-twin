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

KEY DESIGN DESICISIONS:
S+C instead of full four process model :

We decided to use this equations instead of all the others that we had to include if we used the full four process model because based on an article from  Ingrid et al (2014)'s validation study , testing the model against a real airline crew sleep data, found that a simpler S+C performed as well as the fuller model once the circadian was properly calibrated the added ultradian (U) sleep-inertia (W) components did not meaningfully improved the predictive accuracy.
Turning S+C into C-S : 

While we were adjusting the new formula that we used as the core of our system it was obvious that both of the variables should represent the same thing in order to be able to do any calculations , so  we faced a problem which was that if we treated the S for sleepiness it would sense for the KSS scale because  it is an scale for alertness and if we change the value of S to alertness in order to match the C value , then we would be stating that the longer you stay awake , the more focused you would get.

So to address this issue we gave the S a negative value in our equation which resulted in the C-S formula, which is supported by a simple example where we calculated the following values using the related equations  S(taw=0)=2.4-just woke up , minimal sleep pressure- S(taw=24)=9.20-24 hours awake- this example shows that choosing the C-S as the core of our program is an accurate decision.
