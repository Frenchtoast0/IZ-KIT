# IZ Language #

### Sample Code ###
```js
pushButton == high causes ledLight = high;

pushButton == high and lightSensor >= 0.5 causes ledLight = high and ledLight2 = high;

Timer == high causes ledLight = low;

pushButton == high causes start Timer 50;

pushButton == low causes Timer = low; //clears timer

lcdOutput == "Hello, world!"; //standalone command

pushButton == high causes lcdOutput = "Hello, World";

discordBot == "bonjour" causes ledLight = high;

```

### Explanation ###
Code lines are split into two parts, the events and
the listeners.  These two pieces are split on the "causes" keyword.  Every statement before "causes" (split by an "and") will be encapsulated into an event.  Every statement (split by an "and") after the "causes" will be encapsulated into a listener. Statements can be standalone or inside events

### Keywords ###

Keyword       | Function
------------- | -------------
causes        | Creates an event listener
and           | Splits state conditions of an event
high          | Same thing as 1 (for binary I/O)
low           | Same thing as 0 (for binary I/O)
start         | Sets a timer to low and runs it

### Commands ###
Start [TimerName] [tenth seconds] - sets timer to become
high after the specified time period ends (tenths of seconds)

### Complex Outputs ###
LCD's, RGB leds, led matrixes, and other complex 
inputs will require some special work on the 
backend to allow string outputs.