Name: Shota Tonari
CruzID: 1828506

Summary: In this lab we were required to combine our knowledge from our last Lab6 which was our introduction to use our PICKIT3 for the first time. Using our knowledge of coding and testing onto our actual PICKIT, we are asked to create a Toaster/Broil/Bake Oven using out potentiometer/buttons. 

Approach: The first approach I took to complete this lab was to start with adding a helper function called UPDATELED which was to SET the LEDS that we will be using for the lab. After creating that function, I was able to start working on UpdateOvenLED. While creating my UpdateOvenLED I encountered multiple issues such as many overflow errors because when I initialized my variables I used a 16 unsigned byte instead of a 8 unsigned byte. By fixing errors, I was able to write my two ISR functions for my timers as well as my main function.

Describe Results: I think it turned out better than expected, as I was able to physically see my Oven work in real time which was an almost euphoric feeling. By allowing myself to visualize my oven I was able to debug each function and test out using my main file. I ended up with an error that I couldn't fix but I still was able to compile and build successfully. Overall, I enjoyed doing this lab as much as Lab6 because of how you can really see your code run physically.

Extra Credit Approach: For the extra credit approach, I was able to call the function OledSetDisplayInverted which inverted the display and then bring back the display back to a normal state using OledSetDisplayNormal.