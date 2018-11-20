This folder holds shared firmware for the vision system. Files are used by the vision firmware, as well as Master devices that communicate with vision hardware. 

The Delay.c/.h should replace the project's delay implementation
The project should include a header named Vision_HAL.h, which is similar to Vision_HAL_template.h

Please do not edit files directly under the 'VisionShared' folder; rather add new files under 'MasterInterface'. these are used in the vision project directly, so any changes made here will not be pulled back into the master branch. 