###########################################################################
## Makefile generated for component 'unit_conversion'. 
## 
## Makefile     : unit_conversion_rtw.mk
## Generated on : Mon Dec 13 00:36:55 2021
## Final product: ./unit_conversion.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = unit_conversion
MAKEFILE                  = unit_conversion_rtw.mk
MATLAB_ROOT               = $(MATLAB_WORKSPACE)/C/Program_Files/MATLAB/R2021a
MATLAB_BIN                = $(MATLAB_WORKSPACE)/C/Program_Files/MATLAB/R2021a/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = $(MATLAB_WORKSPACE)/C/Users/AVEES/Documents/MATLAB/codegen/lib/unit_conversion
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
MODELLIB                  = unit_conversion.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU GCC for NVIDIA Embedded Processors
# Supported Version(s):    
# ToolchainInfo Version:   2021a
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

CCOUTPUTFLAG  = --output_file=
LDOUTPUTFLAG  = --output_file=
XCOMPILERFLAG =  

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = -lm -lm -lstdc++

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: GNU GCC for NVIDIA Embedded Processors Assembler
AS = as

# C Compiler: GNU GCC for NVIDIA Embedded Processors C Compiler
CC = gcc

# Linker: GNU GCC for NVIDIA Embedded Processors Linker
LD = gcc

# C++ Compiler: GNU GCC for NVIDIA Embedded Processors C++ Compiler
CPP = g++

# C++ Linker: GNU GCC for NVIDIA Embedded Processors C++ Linker
CPP_LD = g++

# Archiver: GNU GCC for NVIDIA Embedded Processors Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: Make Tool
MAKE = make


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = -o
CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  =
ECHO                = echo
MV                  =
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = -r
ASFLAGS              = -c \
                       $(ASFLAGS_ADDITIONAL) \
                       $(INCLUDES)
CFLAGS               = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -O2
CPPFLAGS             = -c \
                       -MMD -MP -MF"$(@:%.o=%.dep)" -MT"$@"  \
                       -fpermissive  \
                       -O2
CPP_LDFLAGS          = -lrt -pthread -ldl
CPP_SHAREDLIB_LDFLAGS  = -shared  \
                         -lrt -pthread -ldl
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -lrt -pthread -ldl
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared  \
                       -lrt -pthread -ldl



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./unit_conversion.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(MATLAB_WORKSPACE)/C/Users/AVEES/Documents/MATLAB -I$(MATLAB_WORKSPACE)/C/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/nvidia/include -I$(MATLAB_WORKSPACE)/C/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/nvidia/sources/utils -I$(MATLAB_ROOT)/toolbox/coder/rtiostream/src/utils -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DMW_DL_DATA_PATH="$(START_DIR)" -DMW_SCHED_OTHER=1
DEFINES_CUSTOM = 
DEFINES_SKIPFORSIL = -D__linux__ -DARM_PROJECT -D_USE_TARGET_UDP_ -D_RUNONTARGETHARDWARE_BUILD_ -DSTACK_SIZE=200000
DEFINES_STANDARD = -DMODEL=unit_conversion

DEFINES = $(DEFINES_) $(DEFINES_CUSTOM) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/unit_conversion_data.cpp $(START_DIR)/rt_nonfinite.cpp $(START_DIR)/rtGetNaN.cpp $(START_DIR)/rtGetInf.cpp $(START_DIR)/unit_conversion_initialize.cpp $(START_DIR)/unit_conversion_terminate.cpp $(START_DIR)/unit_conversion.cpp $(START_DIR)/unit_conversion_in_vehicle_sensor.cpp $(START_DIR)/unit_conversion_front_vision_track.cpp $(START_DIR)/unit_conversion_front_vision_lane.cpp $(START_DIR)/unit_conversion_front_radar_track.cpp $(START_DIR)/coordinate.cpp $(START_DIR)/coordinate_transformation_front_vision_track.cpp $(START_DIR)/coordinate_transformation_front_vision_lane.cpp $(START_DIR)/road_curvature.cpp $(START_DIR)/motion_attribute.cpp $(START_DIR)/gating.cpp $(START_DIR)/shape_attribute.cpp $(START_DIR)/tracking.cpp $(START_DIR)/prediction.cpp $(START_DIR)/correction.cpp $(START_DIR)/inv.cpp $(START_DIR)/track_management.cpp $(START_DIR)/vehicle_recognition.cpp $(START_DIR)/pedestrian_recognition.cpp $(START_DIR)/filter_in_vehicle_sensor.cpp $(START_DIR)/coordinate_transformation_front_radar_track.cpp $(START_DIR)/sort.cpp $(START_DIR)/sortIdx.cpp $(MATLAB_WORKSPACE)/C/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/nvidia/sources/utils/MW_nvidia_init.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = unit_conversion_data.cpp.o rt_nonfinite.cpp.o rtGetNaN.cpp.o rtGetInf.cpp.o unit_conversion_initialize.cpp.o unit_conversion_terminate.cpp.o unit_conversion.cpp.o unit_conversion_in_vehicle_sensor.cpp.o unit_conversion_front_vision_track.cpp.o unit_conversion_front_vision_lane.cpp.o unit_conversion_front_radar_track.cpp.o coordinate.cpp.o coordinate_transformation_front_vision_track.cpp.o coordinate_transformation_front_vision_lane.cpp.o road_curvature.cpp.o motion_attribute.cpp.o gating.cpp.o shape_attribute.cpp.o tracking.cpp.o prediction.cpp.o correction.cpp.o inv.cpp.o track_management.cpp.o vehicle_recognition.cpp.o pedestrian_recognition.cpp.o filter_in_vehicle_sensor.cpp.o coordinate_transformation_front_radar_track.cpp.o sort.cpp.o sortIdx.cpp.o MW_nvidia_init.c.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = $(LDFLAGS_CUSTOMLIBFLAGS) -lm -lstdc++

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


DERIVED_SRCS = $(subst .o,.dep,$(OBJS))

build:

%.dep:



-include codertarget_assembly_flags.mk
-include *.dep


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.c.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : %.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(START_DIR)/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.c.o : $(MATLAB_WORKSPACE)/C/Users/AVEES/Documents/MATLAB/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.s.o : $(MATLAB_WORKSPACE)/C/Users/AVEES/Documents/MATLAB/%.s
	$(AS) $(ASFLAGS) -o "$@" "$<"


%.cpp.o : $(MATLAB_WORKSPACE)/C/Users/AVEES/Documents/MATLAB/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_data.cpp.o : $(START_DIR)/unit_conversion_data.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.cpp.o : $(START_DIR)/rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetNaN.cpp.o : $(START_DIR)/rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rtGetInf.cpp.o : $(START_DIR)/rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_initialize.cpp.o : $(START_DIR)/unit_conversion_initialize.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_terminate.cpp.o : $(START_DIR)/unit_conversion_terminate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion.cpp.o : $(START_DIR)/unit_conversion.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_in_vehicle_sensor.cpp.o : $(START_DIR)/unit_conversion_in_vehicle_sensor.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_front_vision_track.cpp.o : $(START_DIR)/unit_conversion_front_vision_track.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_front_vision_lane.cpp.o : $(START_DIR)/unit_conversion_front_vision_lane.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


unit_conversion_front_radar_track.cpp.o : $(START_DIR)/unit_conversion_front_radar_track.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coordinate.cpp.o : $(START_DIR)/coordinate.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coordinate_transformation_front_vision_track.cpp.o : $(START_DIR)/coordinate_transformation_front_vision_track.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coordinate_transformation_front_vision_lane.cpp.o : $(START_DIR)/coordinate_transformation_front_vision_lane.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


road_curvature.cpp.o : $(START_DIR)/road_curvature.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


motion_attribute.cpp.o : $(START_DIR)/motion_attribute.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


gating.cpp.o : $(START_DIR)/gating.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


shape_attribute.cpp.o : $(START_DIR)/shape_attribute.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


tracking.cpp.o : $(START_DIR)/tracking.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


prediction.cpp.o : $(START_DIR)/prediction.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


correction.cpp.o : $(START_DIR)/correction.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


inv.cpp.o : $(START_DIR)/inv.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


track_management.cpp.o : $(START_DIR)/track_management.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


vehicle_recognition.cpp.o : $(START_DIR)/vehicle_recognition.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


pedestrian_recognition.cpp.o : $(START_DIR)/pedestrian_recognition.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


filter_in_vehicle_sensor.cpp.o : $(START_DIR)/filter_in_vehicle_sensor.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


coordinate_transformation_front_radar_track.cpp.o : $(START_DIR)/coordinate_transformation_front_radar_track.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sort.cpp.o : $(START_DIR)/sort.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


sortIdx.cpp.o : $(START_DIR)/sortIdx.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


MW_nvidia_init.c.o : $(MATLAB_WORKSPACE)/C/ProgramData/MATLAB/SupportPackages/R2021a/toolbox/target/supportpackages/nvidia/sources/utils/MW_nvidia_init.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	echo "### PRODUCT = $(PRODUCT)"
	echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	echo "### BUILD_TYPE = $(BUILD_TYPE)"
	echo "### INCLUDES = $(INCLUDES)"
	echo "### DEFINES = $(DEFINES)"
	echo "### ALL_SRCS = $(ALL_SRCS)"
	echo "### ALL_OBJS = $(ALL_OBJS)"
	echo "### LIBS = $(LIBS)"
	echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	echo "### ASFLAGS = $(ASFLAGS)"
	echo "### CFLAGS = $(CFLAGS)"
	echo "### LDFLAGS = $(LDFLAGS)"
	echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	echo "### CPPFLAGS = $(CPPFLAGS)"
	echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	echo "### ARFLAGS = $(ARFLAGS)"
	echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(RM) *.c.dep
	$(RM) *.cpp.dep
	$(ECHO) "### Deleted all derived files."


