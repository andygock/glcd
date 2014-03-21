#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../controllers/PCD8544.c ../../devices/PIC32.c ../../glcd.c ../../graphics.c ../../graphs.c ../../text.c ../../text_tiny.c ../../unit_tests.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/86698313/PCD8544.o ${OBJECTDIR}/_ext/1941839043/PIC32.o ${OBJECTDIR}/_ext/43898991/glcd.o ${OBJECTDIR}/_ext/43898991/graphics.o ${OBJECTDIR}/_ext/43898991/graphs.o ${OBJECTDIR}/_ext/43898991/text.o ${OBJECTDIR}/_ext/43898991/text_tiny.o ${OBJECTDIR}/_ext/43898991/unit_tests.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/86698313/PCD8544.o.d ${OBJECTDIR}/_ext/1941839043/PIC32.o.d ${OBJECTDIR}/_ext/43898991/glcd.o.d ${OBJECTDIR}/_ext/43898991/graphics.o.d ${OBJECTDIR}/_ext/43898991/graphs.o.d ${OBJECTDIR}/_ext/43898991/text.o.d ${OBJECTDIR}/_ext/43898991/text_tiny.o.d ${OBJECTDIR}/_ext/43898991/unit_tests.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/86698313/PCD8544.o ${OBJECTDIR}/_ext/1941839043/PIC32.o ${OBJECTDIR}/_ext/43898991/glcd.o ${OBJECTDIR}/_ext/43898991/graphics.o ${OBJECTDIR}/_ext/43898991/graphs.o ${OBJECTDIR}/_ext/43898991/text.o ${OBJECTDIR}/_ext/43898991/text_tiny.o ${OBJECTDIR}/_ext/43898991/unit_tests.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=../../controllers/PCD8544.c ../../devices/PIC32.c ../../glcd.c ../../graphics.c ../../graphs.c ../../text.c ../../text_tiny.c ../../unit_tests.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F256H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/86698313/PCD8544.o: ../../controllers/PCD8544.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/86698313 
	@${RM} ${OBJECTDIR}/_ext/86698313/PCD8544.o.d 
	@${RM} ${OBJECTDIR}/_ext/86698313/PCD8544.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/86698313/PCD8544.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/86698313/PCD8544.o.d" -o ${OBJECTDIR}/_ext/86698313/PCD8544.o ../../controllers/PCD8544.c   
	
${OBJECTDIR}/_ext/1941839043/PIC32.o: ../../devices/PIC32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1941839043 
	@${RM} ${OBJECTDIR}/_ext/1941839043/PIC32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1941839043/PIC32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1941839043/PIC32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/1941839043/PIC32.o.d" -o ${OBJECTDIR}/_ext/1941839043/PIC32.o ../../devices/PIC32.c   
	
${OBJECTDIR}/_ext/43898991/glcd.o: ../../glcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/glcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/glcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/glcd.o.d" -o ${OBJECTDIR}/_ext/43898991/glcd.o ../../glcd.c   
	
${OBJECTDIR}/_ext/43898991/graphics.o: ../../graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/graphics.o.d" -o ${OBJECTDIR}/_ext/43898991/graphics.o ../../graphics.c   
	
${OBJECTDIR}/_ext/43898991/graphs.o: ../../graphs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphs.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/graphs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/graphs.o.d" -o ${OBJECTDIR}/_ext/43898991/graphs.o ../../graphs.c   
	
${OBJECTDIR}/_ext/43898991/text.o: ../../text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/text.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/text.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/text.o.d" -o ${OBJECTDIR}/_ext/43898991/text.o ../../text.c   
	
${OBJECTDIR}/_ext/43898991/text_tiny.o: ../../text_tiny.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/text_tiny.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/text_tiny.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/text_tiny.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/text_tiny.o.d" -o ${OBJECTDIR}/_ext/43898991/text_tiny.o ../../text_tiny.c   
	
${OBJECTDIR}/_ext/43898991/unit_tests.o: ../../unit_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/unit_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/unit_tests.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/unit_tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/unit_tests.o.d" -o ${OBJECTDIR}/_ext/43898991/unit_tests.o ../../unit_tests.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
else
${OBJECTDIR}/_ext/86698313/PCD8544.o: ../../controllers/PCD8544.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/86698313 
	@${RM} ${OBJECTDIR}/_ext/86698313/PCD8544.o.d 
	@${RM} ${OBJECTDIR}/_ext/86698313/PCD8544.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/86698313/PCD8544.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/86698313/PCD8544.o.d" -o ${OBJECTDIR}/_ext/86698313/PCD8544.o ../../controllers/PCD8544.c   
	
${OBJECTDIR}/_ext/1941839043/PIC32.o: ../../devices/PIC32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1941839043 
	@${RM} ${OBJECTDIR}/_ext/1941839043/PIC32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1941839043/PIC32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1941839043/PIC32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/1941839043/PIC32.o.d" -o ${OBJECTDIR}/_ext/1941839043/PIC32.o ../../devices/PIC32.c   
	
${OBJECTDIR}/_ext/43898991/glcd.o: ../../glcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/glcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/glcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/glcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/glcd.o.d" -o ${OBJECTDIR}/_ext/43898991/glcd.o ../../glcd.c   
	
${OBJECTDIR}/_ext/43898991/graphics.o: ../../graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphics.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/graphics.o.d" -o ${OBJECTDIR}/_ext/43898991/graphics.o ../../graphics.c   
	
${OBJECTDIR}/_ext/43898991/graphs.o: ../../graphs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphs.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/graphs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/graphs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/graphs.o.d" -o ${OBJECTDIR}/_ext/43898991/graphs.o ../../graphs.c   
	
${OBJECTDIR}/_ext/43898991/text.o: ../../text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/text.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/text.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/text.o.d" -o ${OBJECTDIR}/_ext/43898991/text.o ../../text.c   
	
${OBJECTDIR}/_ext/43898991/text_tiny.o: ../../text_tiny.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/text_tiny.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/text_tiny.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/text_tiny.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/text_tiny.o.d" -o ${OBJECTDIR}/_ext/43898991/text_tiny.o ../../text_tiny.c   
	
${OBJECTDIR}/_ext/43898991/unit_tests.o: ../../unit_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/43898991 
	@${RM} ${OBJECTDIR}/_ext/43898991/unit_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/43898991/unit_tests.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/43898991/unit_tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/_ext/43898991/unit_tests.o.d" -o ${OBJECTDIR}/_ext/43898991/unit_tests.o ../../unit_tests.c   
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DGLCD_DEVICE_PIC32 -DGLCD_CONTROLLER_PCD8544 -DGLCD_USE_SPI -I"../../" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC32_PINGUINO_OTG_AND_NOKIA_5110.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
