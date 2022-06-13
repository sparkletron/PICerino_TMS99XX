# PICerino TMS99XX

Test Board and Software Library for TI TMS99XX video chips.  

author: Jay Convertino  

date: 2022.04.23  

license: MIT (software), None (hardware)  

<div class="panel panel-warning">
**Warning**
{: .panel-heading}
<div class="panel-body">

This system is not fully tested and is full of bugs. Plenty of issues to fix. Please wait till version 1 is released for daily use or feedback.

</div>
</div>

## Release Versions
### Current
  - none

### Past
  - none
  
## Requirements
### Hardware
  - KiCad
  
### Software
  - xc8 compiler
  
## Information

Directory Listing:  

  - docs - Data documents for various ICs.
  - schematic - KiCad schematic of TMS99XX test board. See readme.md in dir for details.
  - src - Any source code for the project.
    - lib_picTMS99XX- library with test program for picerino. See readme.md in dir for details. 

### Video Output
  This video circuit is based on a few ideas. Mostly TI's application document, and TMS-RGB for the use of the LM1881. Main issue with TMS-RGB is the goal of this project was to output component to the retro tink x2. The RGB would of made the unit have to use surface mount parts. This was something I wanted to avoid since I want anyone to be able to solder and build this. Everything else is from application datasheets and just trial and error. TI's application data sheet was keying out the Yr/Yb color bursts with a decoulping cap passing the signal to a 4066 that just went to ground during sync. This in theory should work fine, but in practice you'll still see a bit of the burst. Plus then its AC coupled and the regular op amps hated it even with a DC path added. TMS-RGB used a sample and hold method, which worked great to the converter chip. Problem came when passing that signal to a 6db gain opamp directly. Small differences would result in the new sampled part that was the color burst being offset and cause an over green issue. Plus it was more complicated. I wanted this down to 3 IC's at most. Realizing I could just use the switch to change to a new DC level I worked on the resulting circuit. The resulting circuit, on color burst, will switch from the video to the DC level set circuit and back when done. The typical level seemed to be 2.78 volts, which is perfect for a zener diode application since its a standard voltage. A pot is added for small adjustment of about 100mv (2.7 to 2.8) to clean up the black level. A 1k resistor is added as a pullup to the output of the LM1881 burst pin. This was needed due to an odd video artifact. The left hand side of the screen would have a horizontal color strip on the very edge. The LM1881 puts out a terrible edge so this could be added noise, or the fact it wasn't working quick enough. Its very odd since the resistor (adding current in this manner) was the only way that fixed it. Using a schmitt trigger buffer with plenty of current output did not fix it. Just going with it at this point. 
