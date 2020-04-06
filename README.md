# GoTimerPlus

This is a homebrew Nintendo DS application designed to be used as a timer for playing games such as Go, Chess and Shogi. Features of the application that are hoped to be supported in the future:

- Multiple Pre-set timing modes, to allow you to easily setup a timer in no time.
  - Blitz
  - Absolute
    - Able to use Japanese or Canadian Byoyomi
  - Also includes NHK cup rules:
    - 30 seconds per move, with 10x1 minute (Spilling system)
- Custom timer save slots; You can create a timer using the setup utility, then save those to a custom slot to be used later.

## How the Timer System Works
### Base Level:

The way that the timer system tracks time in this application (so far) is based on the VBlank period of the screen. libNDS supplies the ability to detect the VBlank, which occurs once every 1/60th of a second. This gives each VBlank period the equivalent of taking 16.66r ms. Using this, we can estimate down to a ms level how much time should've passed, and keep track of time this way.

In the future, I will look into a more accurate way of tracking time down to the indiviual millisecond level, but for now, this seems to work well; and as
1. this isn't a tournament legal timer and
2. humans generally can't push a button fast enough for it to matter much in the long run
I feel this will work fine.


## Things that are in current development:

What would be a shorter list?
1. Pretty much everything at this point.
   1. So far this app only displays a graphic to the background layer of the top screen, and the debug console on the bottom where I'm tracking the timer states.
   2. Graphics are being developed continually, but the basic sprites for the top display have been designed and are in the graphics folder.
   3. Beyond that, there isn't much yet in this application. This will be a slow process, as I'm still learning all this.

## Build Instructions

I use VSCode for all my development in this app; Graphics were created in GIMP. Built in Ubuntu. If you'd like to build it for yourself, make sure you have devkitPro setup with libNDS installed. Once done, simply run `make` in the directory to generate the NDS file.


## Included Tasks
Included is the `.vscode` file where my setup is stored. Included are a few tasks that I run, that you are free to configure to your needs:
1) Make task
2) Clean task
3) Test task: runs NDS file in Desmume
4) Copy to SD task.
   1) This works on Linux; will need setup for other OS environments.
   2) Change the name of the SD card in the copy_to_sd_linux.sh file to the name of your SD card (if on linux.) This will make it easy to send the file to your ROM folder. This copy script has been designed with the default directory setup of TWLMenu++ in mind.

## Thanks For Checking this Out.
This is a hobby/passion project. As such, development is mostly handled by myself. I don't know much about NDS Programming, let alone C++ programming. My background is in C#, so I'm not used to this kind of low level code. But, I'm using this as a learning experience with something I enjoy (Go/Baduk/Weiqi)

If you'd like to contribute, please feel free to branch and submit merge requests as necessary. I'm going to update this README file with an image to describe the vision that I'm seeking to create, so if you have ideas how to get it where it needs to be, I'm more than happy for the contributions. Help is not expected however.