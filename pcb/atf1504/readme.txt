This shield is based on https://github.com/hackup/ATF2FT232HQ

If CPLD is used and it needs JTAG erasing, connect a 12V PSU and run (OpenOCD version 0.10.0-rc2):

bin-x64\openocd.exe -f scripts\interface\ftdi\um232h.cfg -c "adapter_khz 400" -c "transport select jtag" -c "jtag newtap ATF1504AS tap -irlen 3 -expected-id 0x0150403f" -c init -c "svf atf1504as-erase.svf" -c "sleep 200" -c shutdown

