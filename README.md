# PICerino TMS99XX

Test Board and Software Library for TI TMS99XX video chips.  

author: Jay Convertino  

date: 2022.04.23  

license: MIT (software/Hardware)

## Release Versions
### Current
  - v0.5

### Past
  - none
  
## Requirements
### Hardware
  - KiCad
  
### Software
  - xc8 compiler
  
## Information

### Directory Listing:

  - docs - Data documents for various ICs.
  - schematic - KiCad schematic of TMS99XX test board. See readme.md in dir for details.
  - src - Any source code for the project.
    - lib_picTMS99XX folder contains a library with test program for picerino. See readme.md in this directory for details.

### Usage
  This is made to be used with the picerino development board. This uses the standard DRAM since there are plenty of them around from various venders. The idea is the test program with put the card through its paces. This is done by putting the VDP into all modes and testing all of its functions. Currently this is incomplete. GFX II, various sprite sizes and edge cases need testing. The other idea with this was to create a simple video circuit for YrYbY output to go to an upscaler and then to HDMI. The retrotink 2x works well with the output of this unit.

### Build
  Through hole components were selected for everything, including the video circuit regardless of expense or being the best for easy construction. I used an T-Tech Quick Circuit 5000 to mill out a single sided board. A BOM will in the schematic directory should point you towards components to use.

### Video Output
  This video circuit is based on a few ideas. Mostly TI's application document, and TMS-RGB for the use of the LM1881. All other design choices are from application datasheets and just trial and error. Main issue with TMS-RGB being used whole sale is it has all surface mount components and it isn't universal for TMS9918. The goal of this project was to output component or composite to the retro tink x2. TI's application data sheet is keying out the Yr/Yb color bursts with a decoulping cap passing the signal to a 4066 that just went to ground during sync. This in theory should work fine, but in practice you'll still see a bit of the burst. TMS-RGB used a sample and hold method, which worked great to the converter chip. Problem came when passing that signal to a 6db gain opamp directly. Small differences would result in the new sampled part that was inserted during the color burst being offset and cause an over green issue. Plus it was more complicated then the TI grounding method. I wanted this down to 3 IC's at most. Realizing I could just use the switch to change to a new DC level I worked on the resulting circuit. The resulting circuit, on color burst, will switch from the video to the DC level set circuit and back and repeat. The typical level seemed to be 2.78 volts for DC, which is perfect for a zener diode application since its a standard voltage. A pot is added for small adjustment of about 100mv (2.7 to 2.8) to adjust the black level.

### Issues
  The socket to picerino does not provide the best ground path which causes issue with the video black level circuit. A 1k resistor is added as a pullup to the output of the LM1881 burst pin. This was needed due to an odd video artifact. The left hand side of the screen would have a horizontal color strip on the very edge. The LM1881 puts out a terrible edge so this could be added noise, or the fact it wasn't working quick enough. Its very odd since the resistor (adding current in this manner) was the only way that fixed it. Using a schmitt trigger buffer with plenty of current output did not fix it. Just going with it at this point.
