# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\kylep\Box Sync\Box Sync\Feniex Electrical Files\WorkingFolder-Kyle\Firm-AI-Cube\81-00024-01.cydsn\81-00024-01.cyprj
# Date: Mon, 19 Nov 2018 20:15:03 GMT
#set_units -time ns
create_clock -name {ADC_SAR_Seq_intClock(FFB)} -period 229.16666666666666 -waveform {0 114.583333333333} [list [get_pins {ClockBlock/ff_div_7}]]
create_clock -name {Clock_3(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_8}]]
create_clock -name {ack_clock(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_9}]]
create_clock -name {Clock_1(FFB)} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {timer_clock(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_11}]]
create_clock -name {UART_LED_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_5} -source [get_pins {ClockBlock/hfclk}] -edges {1 240001 480001} [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {ADC_SAR_Seq_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 11 23} [list]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {ack_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 48001 96001} [list]
create_generated_clock -name {pwmClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 19} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {pwmClock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 4801 9601} [list [get_pins {ClockBlock/udb_div_2}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 941 1881} -nominal_period 19604.166666666664 [list [get_pins {ClockBlock/udb_div_3}]]
create_generated_clock -name {UART_LED_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]


# Component constraints for C:\Users\kylep\Box Sync\Box Sync\Feniex Electrical Files\WorkingFolder-Kyle\Firm-AI-Cube\81-00024-01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\kylep\Box Sync\Box Sync\Feniex Electrical Files\WorkingFolder-Kyle\Firm-AI-Cube\81-00024-01.cydsn\81-00024-01.cyprj
# Date: Mon, 19 Nov 2018 20:14:58 GMT
