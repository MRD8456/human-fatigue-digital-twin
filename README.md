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

Custom KSS model :

While we decided to use C-S as our core equation , we faced another problem while we were testing the actual equation and that was the resulted number exceeded from the normal KSS model max which was 9.

So to address this issue, we decided to change the value of a and b in the original KSS model and replace them with our own calculated number since our equations are different from the equations that resulted the fixed values of a and b.

the final formula resulted as : 9-[(C-S)-(-16.8)/(0.1-(-16.8))]*(9-1) 


Deciding a 12% break bonus :

While we were trying to finalize a formula for break bonus so that we could add it to our core C-S formula so that we could include energy boost from taking a break, to add this break bonus we had choice of using a percentage between 10%-15% of model's total range which makes it around (1.5-2.5)  and to accurately choose the number , we used a simple example in order to find out which number would make more common sense in the real world and represents a better safety flagging if included in our equation.

For the example we considered a worker that has been awake for 10 hours (Alertness-level=-3.501).At break bonus=15% which almost equals 2.54 bonus, that worker's score would jump to nearly neutral(-0.96) right after the break which is suggesting that the break erased all signs of tiredness signals but if we fix the break bonus on 12%  and redo the calculations we realize that it only produces a -1.5 after bonus which is more realistic and better in case of safety flagging. So we decided to use 12% of the whole model's alertness range as our break bonus.
