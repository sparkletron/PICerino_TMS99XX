# PICerino TMS VDP

Test Board and Software Library for TI TMS992X and TMS9118 video display processors.

author: Jay Convertino  

date: 2022.04.23  

license: MIT (software/Hardware)

## Release Versions
### Current
  - v2.1.0 - Improved video circuit for the TMS9118.

### Past
  - v2.0.0 - Improved video circuit that actually works.
  - v1.0.0 - Improved video circuit and TMS9118 schematic added.
  - v0.5.0 - First version with old video circuit.
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
    - TMS9118 - Contains a schematic for a TMS9118 board with video circuit (v2).
    - TMS992X - Contains a schematic for a TMS992X board with video circuit (v2).
  - src - Any source code for the project.
    - lib_picTMS99XX folder contains a library with test program for picerino. See readme.md in this directory for details.

### Usage
  This is made to be used with the picerino development board. This uses the standard DRAM since there are plenty of them around from various venders. The idea is the test program with put the card through its paces. This is done by putting the VDP into all modes and testing all of its functions. Currently this is incomplete. GFX II, various sprite sizes and edge cases need testing. The other idea with this was to create a simple video circuit for YrYbY output to go to an upscaler and then to HDMI. The retrotink 2x works well with the output of this unit.

### Build
  Through hole components were selected for everything, except for the video circuit of the TMS9118. This something I had on hand. Production uses a double sided board.

### Video Output
  This video circuit is based on a few ideas. Mostly TMS-RGB for the use of the LM1881. All other design choices are from application datasheets and just trial and error. Main issue with TMS-RGB being used whole sale is it has all surface mount components and it isn't universal for TMS9918. The goal of this project was to output component or composite to the retro tink x2. TI's application data sheet is keying out the Yr/Yb color bursts with a decoulping cap passing the signal to a 4066 that just went to ground during sync. This in theory should work fine, but in practice you'll still see a bit of the burst. TMS-RGB used a sample and hold method, which worked great to the converter chip. Taking the TMS RGB and just using a quad switch to sample the Yb signal, then pass it to the other inputs that then use that sample when needed (see lm1881 connections). This method of using a quad switch eliminates the too much blue issue. It also results in a circuit that is only 3 ic's. A MAX394, ADG813, and LM1881. The opamp is setup to rebalance the colors per the TMS RGB Y+Yr+Yb findings. Again big thanks to them for spending the time to document how and what they did. Saved me a lot of work on this project.

### Issues
  N/A
