# Links and guides that helped me find this stuff out
- [david bowie kept me sain](https://genius.com/David-bowie-space-oddity-lyrics);

## what helped with the board
- [helped with the figureing out how the hell to use WiFiClient.read()](https://forum.arduino.cc/index.php?topic=91348.0)
- [one of the worst docs ive ever read but it helped](https://www.arduino.cc/en/Reference/WiFi)
- so i had wifi connection issues they were fixed by 
  - using the right board envoriment *wemos d1*
  - in the end i found alot of online sources were not giving alot of helpful info excpet [esp doc](https://arduino-esp8266.readthedocs.io/en/latest/)
- [followed this to the letter for wifi](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
   - i tried other methods but they all did not at all work
   - alot of my problems werent actually with the code on the doc 
   they were with the dam serial monitor not displaying in the terminal
    - it got so bad i tried [the blink test](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide)
    which didnt work for some ungodly reason so i went back to the unreliable serial monitor
- [the serial moniter kept not working](https://github.com/arduino/arduino-pro-ide/issues/127) [or this one](https://forums.losant.com/t/nothing-showing-up-on-the-serial-monitor/708/2)
  - this isnt helpful but im throwing it in here so i dont forget essentally 
  i found out that the serial communcation on these things is very picky at least in atom so i kept getting no output
  from the device only to see on the sevrer end it says it can see it, it looks like a very common issue
- [when dealing with client class this helped ALOT](https://www.arduino.cc/en/Reference/WiFiClient)
  - [this helped a bit and was how i found the top one but yeah](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-class.html)

## what helped the server
- [this was the final guide that actually did the trick hot dam](https://www.binarytides.com/php-socket-programming-tutorial/comment-page-1/)
- [1000000% better docs then arduino](https://www.php.net/manual/en/book.sockets.php)

# this is a quick right down/info dump will come back and document
