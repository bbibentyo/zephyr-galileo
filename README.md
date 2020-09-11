# zephyr-galileo
Zephyr [reel board](https://github.com/zephyrproject-rtos/zephyr/wiki/reel-Board) programming adventure.

## Installing Prerequisites
Follow the instructions available on [zephyr website](https://docs.zephyrproject.org/latest/guides/west/install.html).

## Environment setup
I am testing my code on Ubuntu 20.04 using _Zephyr reel board._ I learnt the hard way that there are two versions of reel board. I am using the latest, remember to append `v2` to the name when setting the environment variable.

There are a couple of **Environment Variables** to setup before compiling your own code. If you are using `bash`, you can add the lines below to your `~/.bashrc` file for persistence across user sessions.

1. `export ZEPHYR_BASE=/path/to/zephyr/project` # in my case it is `~/zephyrproject/zephyr`
2. `export BOARD=reel_board_v2` # name of the board that you are using. Be careful with the name.
3. `export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr/sdk` # in my case it is `~/zephyr-sdk-0.11.3`

reload the session by running `source ~/.bashrc`

## Connecting board to PC
After installing west and zephyr sdk, connect your reel board to your computer using **MICRO-USB** cable. There are two usb slots on the board. One is nRF & the other is debug. You can read the [board label](https://github.com/zephyrproject-rtos/zephyr/wiki/reel-Board) to know which is slot is which. If there are no labels, face the front of the board (where there is a small disaplay screen), on your right, there will be two USB slots, the top slot is the debug slot.

After connecting the board, flip the switch on the back of the board to **USB**. The switch is located between the two USB ports.

On Ubuntu, you should see a USB connection alert if the connection was successful. If not, check your cable.

## Building sample code
Make sure that you have loaded the environment variables specified above. Navigate to the `$ZEPHYR_BASE` directory and execute:
1. `west build -p samples/basic/blinky`  # to build the code.
2. `west flash`  # to upload the code to the board.

You should see the led light in the middle of the board blink, if all was successful.

You can repeat the process with another sample project. If you want to try writing something to board display, try *samples/display/cfb_custom_font* sample project.

## Connecting to reel board using your android device.
Using my android device (Galaxy S10),  I was able to connect to zephyr reel board via *Bluetooth*

1. Download **nRF Connect** from the *Play Store*
2. Turn on the board (either to USB if plugged in or battery if not plugged in)
3. On your mobile device, open **nRF Connect** and grant it the necessary permissions (Yes, it requests location permission for proximity)
4. Using the app on your mobile device, scan available devices and look for the *reel board*
5. Once selected from the list of available devices, *reel board* will generate a password which you will enter on your mobile device when prompted for code.


# Writing your own code

Follow the official instructions on zephyr website or clone this repository and delete everything in `src` create a new `src/main.c` and start from there.
If `west` complains the first time you try to build your own code, try running  `west config build.generator "Unix Makefiles"` from within the cloned directory.


# Issues that I have encountered.

1. *west build* complained that `lvgl.h` couldn't be found. Make sure that Zephyr project modules and includes folder are accessible and are located in `$ZEPHYR_BASE` directory.
2. Don't use the example is `samples/display/lvgl` for writing to board display... it doesn't work on reel_board_v2. instead use `samples/display/cfb` or `samples/display/cfb_custom_font`
3. Multiple Python versions installed on the host. This could be an issue if you are using *conda/miniconda*... I got around the problem by removing miniconda entries from `~/.bashrc`
