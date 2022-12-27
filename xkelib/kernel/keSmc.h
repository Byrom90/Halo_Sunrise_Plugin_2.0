#ifndef __KESMC_H
#define __KESMC_H

// for HalRegisterSMCNotification
// messageCode 0x83 notifies of PayloadAsUCHARs[0]
// 0x23 - IR event (priority 0 only?)
// 0x60/0x66 - tray events
// 0x70 thermal shutdown event

typedef struct _HAL_SMC_REGISTRATION { 
	void* NotificationRoutine; // 0x0 sz:0x4 function: void Notify(PHAL_SMC_REGISTRATION SMCRegistration, PSMC_MAILBOX_MESSAGE NotificationMessage);
	long Priority; // 0x4 sz:0x4
	LIST_ENTRY ListEntry; // 0x8 sz:0x8
} HAL_SMC_REGISTRATION, *PHAL_SMC_REGISTRATION; // size 16
C_ASSERT(sizeof(HAL_SMC_REGISTRATION) == 0x10);

typedef struct _SMC_MAILBOX_MESSAGE { 
	BYTE MessageCode; // 0x0 sz:0x1
	BYTE PayloadAsUCHARs[0xF]; // 0x1 sz:0xF
} SMC_MAILBOX_MESSAGE, *PSMC_MAILBOX_MESSAGE; // size 16
C_ASSERT(sizeof(SMC_MAILBOX_MESSAGE) == 0x10);

typedef VOID (*SMCNOTIFYROUTINE)(PHAL_SMC_REGISTRATION SMCRegistration, PSMC_MAILBOX_MESSAGE NotificationMessage);

// result from using smc_query_tray or HalRegisterSMCNotification's PayloadAsUCHARs[0]
typedef enum _SMC_TRAY_STATE {
	SMC_TRAY_OPEN = 0x60,
	SMC_TRAY_OPEN_REQUEST = 0x61,
	SMC_TRAY_CLOSE = 0x62,
	SMC_TRAY_OPENING = 0x63,
	SMC_TRAY_CLOSING = 0x64,
	SMC_TRAY_UNKNOWN = 0x65,
	SMC_TRAY_SPINUP = 0x66,
} SMC_TRAY_STATE;

typedef enum SMC_CMD{
	smc_poweron_type = 0x1,
	smc_query_rtc = 0x4,
	smc_query_sensor = 0x7,
	smc_query_tray = 0xA,
	smc_query_avpack = 0xF,
	smc_i2c_read_write = 0x11,
	smc_query_version = 0x12,
	smc_fifo_test = 0x13,
	smc_query_ir_address = 0x16,
	smc_query_tilt_sensor = 0x17,
	smc_read_82_interrupts = 0x1e,
	smc_read_8E_interrupts = 0x20,
	smc_set_standby = 0x82,
	smc_set_time = 0x85,
	smc_set_fan_algorithm = 0x88,
	smc_set_fan_speed_CPU = 0x89,
	smc_set_dvd_tray = 0x8b,
	smc_set_power_led = 0x8c,
	smc_set_audio_mute = 0x8d,
	smc_argon_related = 0x90,
	smc_set_fan_speed_GPU = 0x94, // not present on slim, not used/respected on newer fat
	smc_set_ir_address = 0x95,
	smc_set_dvd_tray_secure = 0x98,
	smc_set_leds = 0x99,
	smc_set_rtc_wake = 0x9a,
	smc_ana_related = 0x9b,
	smc_set_async_operation= 0x9c,
	smc_set_82_interrupts = 0x9d,
	smc_set_9F_interrupts = 0x9f,
};

typedef enum SMC_PWR_REAS{
	SMC_PWR_REAS_11_PWRBTN		= 0x11, // xss5 power button pushed
	SMC_PWR_REAS_12_EJECT		= 0x12, // xss6 eject button pushed
		SMC_PWR_REAS_15_ALARM		= 0x15, // xss guess ~ should be the wake alarm ~
	SMC_PWR_REAS_20_REMOPWR 	= 0x20, // xss2 power button on 3rd party remote/ xbox universal remote
		SMC_PWR_REAS_21_REMOEJC 	= 0x21, // eject button on xbox universal remote
	SMC_PWR_REAS_22_REMOX		= 0x22, // xss3 xbox universal media remote X button
	SMC_PWR_REAS_24_WINBTN		= 0x24, // xss4 windows button pushed IR remote
		SMC_PWR_REAS_30_RESET		= 0x30, // xss HalReturnToFirmware(1 or 2 or 3) = hard reset by smc
		SMC_PWR_REAS_31_RECHARGE_RESET	= 0x31, // after leaving pnc charge mode via power button
	SMC_PWR_REAS_41_KIOSK 		= 0x41, // xss7 console powered on by kiosk pin
	SMC_PWR_REAS_55_WIRELESS 	= 0x55, // xss8 wireless controller middle button/start button pushed to power on controller and console
	SMC_PWR_REAS_56_WIRED_F1	= 0x56, // xss9 wired guide button; fat front top USB port, slim front left USB port
	SMC_PWR_REAS_57_WIRED_F2 	= 0x57, // xssA wired guide button; fat front botton USB port, slim front right USB port
	SMC_PWR_REAS_58_WIRED_R2	= 0x58, // xssB wired guide button; slim back middle USB port
	SMC_PWR_REAS_59_WIRED_R3	= 0x59, // xssC wired guide button; slim back top USB port
	SMC_PWR_REAS_5A_WIRED_R1	= 0x5A, // xssD wired guide button; fat back USB port, slim back bottom USB port
	// possibles/reboot reasons  0x23, 0x2A, 0x42, 0x61, 0x64

	// slim with wired controller when horozontal, 3 back usb ports top to bottom 0x59, 0x58, 0x5A front left 0x56, right 0x57
	// slim with wireless controller w/pnc when horozontal, 3 back usb ports top to bottom 0x55, 0x58, 0x5A front left 0x56, right 0x57
	// fat with wired controller when horozontal, 1 back usb port 0x5A front top 0x56, bottom 0x57
	// fat with wireless controller w/pnc when horozontal, 1 back usb port 0x5A front top 0x56, bottom 0x57
	// Using Microsoft Wireless Controller: 0x55
	// Using Madcatz Wireless Keyboard (Rockband 3 Keyboard - Item Number 98161): 0x55
	// Using Activision Wireless Turntable Controller (DJ Hero Turntable): 0x55
	// Using Drums Controller from Activision Guitar Hero Warriors of Rock: 0x55
	// Using Guitar controller from Activision Guitar Hero 5: 0x55
};


#endif // __KESMC_H
