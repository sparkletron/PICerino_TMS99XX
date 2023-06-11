# PICerino TMS VDP

Test Board and Software Library for TI TMS992X and TMS9118 video display processors.

author: Jay Convertino  

date: 2022.04.23  

license: MIT (software/Hardware)

## Release Versions
### Current
  - v1.0 - Improved video circuit and TMS9118 schematic added.

### Past
  - v0.5 - First version with old video circuit.
  - none
  
## Requirements
### Hardware
  - KiCad
  
### Software
  - xc8 compiler
  
## Information

### Directory Listing:

  - docs - Data documents for various ICs.
  - schematic - KiCad schematic
    - TMS9118 - Contains a schematic for a TMS9118 board with video circuit.
    - TMS992X - Contains a schematic for a TMS992X board with video circuit.
  - src - Any source code for the project.
    - lib_picTMS99XX folder contains a library with test program for picerino. See readme.md in this directory for details.

### Usage
  This is made to be used with the picerino development board. This uses the standard DRAM since there are plenty of them around from various venders. The idea is the test program with put the card through its paces. This is done by putting the VDP into all modes and testing all of its functions. Currently this is incomplete. GFX II, various sprite sizes and edge cases need testing. The other idea with this was to create a simple video circuit for YrYbY output to go to an upscaler and then to HDMI. The retrotink 2x works well with the output of this unit.

### Build
  Through hole components were selected for everything, except for the video circuit of the TMS9118. This something I had on hand. Production uses a double sided board.

### Video Output
  This video circuit is based on a few ideas. Mostly TI's application document, and TMS-RGB for the use of the LM1881. All other design choices are from application datasheets and just trial and error. Main issue with TMS-RGB being used whole sale is it has all surface mount components and it isn't universal for TMS9918. The goal of this project was to output component or composite to the retro tink x2. TI's application data sheet is keying out the Yr/Yb color bursts with a decoulping cap passing the signal to a 4066 that just went to ground during sync. This in theory should work fine, but in practice you'll still see a bit of the burst. TMS-RGB used a sample and hold method, which worked great to the converter chip. Problem came when passing that signal to a 6db gain opamp directly. Small differences would result in the new sampled part that was inserted during the color burst being offset and cause an over green issue. Plus it was more complicated then the TI grounding method. I wanted this down to 3 IC's at most. Realizing I could just use the switch to change to a new DC level I worked on the resulting circuit. The resulting circuit, on color burst, will switch from the video to the DC level set circuit and back and repeat. Originaly this was done with a zener and a pot, this turned out of be a source of contant pain if the voltage changed at all. The method came up with after was a slow op amp used to filter out anything over 15 khz and provide the DC offset from the Yb on its output. Also the jail bars were bad, which turned out to be switching noise from the LM1881. This is helped by isolating the CBURST line from the analog switch, a transistor will suffice. Though in this circuit a op amp is used due to one half used for the DC signal already.

### Issues
  N/A
