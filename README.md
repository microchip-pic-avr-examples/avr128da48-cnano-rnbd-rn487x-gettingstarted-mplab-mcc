
[![MCHP](images/microchip.png)](https://www.microchip.com)

# AVR128DA48 RNBD and RN487x User Guide

-   [Introduction](#introduction)
-   [Driver Information](#driver-information)
-   [Related Documentation](#related-documentation)
-   [Software Used](#software-used)
-   [Hardware Used](#hardware-used)
-   [Hardware Setup](#hardware-setup)
-   [Software Prerequisite](#software-prerequisite)
-   [Project Setup](#project-setup)
-   [RNBD Setup and Running Example Application](#rnbd-setup-and-running-example-application)
    -   [RNBD Basic Data Exchange Pin Settings](#rnbd-basic-data-exchange-pin-settings)
    -   [RNBD Transparent UART Application Pin Settings](#rnbd-transparent-uart-application-pin-settings)
    -   [RNBD GPIO Based Connection Setup](#rnbd-gpio-based-connection-setup)
    -   [RNBD Code Generation and Compilation](#rnbd-code-generation-&-compilation)
    -   [RNBD Example 1: Running Basic Data Exchange Example Application](#rnbd-example1:-running-basic-data-exchange-example-application)
    -   [RNBD Example 2: Running Transparent UART Example Application](#rnbd-example2:-running-transparent-uart-example-application)
-   [RN487x Setup and Running Example](#rn487x-setup-and-running-example)
    -   [RN487x Basic Data Exchange Pin Settings](#rn487x-basic-data-exchange-pin-settings)
    -   [RN487x Transparent UART Application Pin Settings](#rn487x-transparent-uart-application-pin-settings)
    -   [RN487x Code Generation and Compilation](#rn487x-code-generation-&-compilation)
    -   [RN487x Example 1: Running Basic Data Exchange Example Application](#rn487x-example1:-running-basic-data-exchange-example-application)
    -   [RN487x Example 2: Running Transparent UART Example Application](#rn487x-example2:-running-transparent-uart-example-application)
-   [Summary](#summary)

<br />
**Notes**<br />
 1. The project creation steps where RNBD is mentioned are applicable for both RNBD451 and RNBD350 devices.
 <br />
 2. The Over-the-Air (OTA) Device Firmware Update (DFU) support is not applicable for RNBD350-based applications because the OTA DFU for RNBD350 is implemented using the Host Microcontroller (MCU) DFU process. OTA is not supported for 8-bit applications due to memory limitation.

# Introduction<a name="introduction"></a>

The MPLAB® Code Configurator (MCC) [RNBD](https://www.microchip.com/en-us/product/RNBD451PE)/[RN487x](https://www.microchip.com/wwwproducts/en/RN4870) Bluetooth® Low Energy (BLE) Modules Library allows to promptly configure the C code-generated software driver, based on the user’s selected Application Programming Interfaces (API)  features available in the MCC Library. The generated driver code can support the BLE module using a AVR® device.

Refer to the /images folder for source files and max resolution.

The library module uses an MCC Graphic User Interface (GUI) to set the configuration, along with the custom configurations of the protocol. The customized C code is generated in a folder named "MCC Generated Files" within the MPLABX project.

This library uses one Universal Asynchronous Receiver and Transmitter (UART), one General Purpose Input/Output (GPIO) and DELAY support at minimal.

# Driver Information<a name="driver-information"></a>

<br />

![](images/GUID-10BD5CFC-D080-416B-A1A1-7053584223CD-low.png)

<br />

<br />

![](images/GUID-DD679451-2296-4F64-92DB-E0A20C688E94-low.png)

<br />

<br />

![](images/GUID-507929BA-708E-4219-80C7-818B355D5621-low.png)

<br />

<br />

![](images/GUID-9CCA0D20-32A8-4F49-8FD5-91273FE542C8-low.png)

<br />

# Related Documentation<a name="related-documentation"></a>

-   Microchip Bluetooth Low Energy \([BLE](https://www.microchip.com/design-centers/wireless-connectivity/bluetooth)\)
-   RNBD User Guide \([RNBD451](https://onlinedocs.microchip.com/oxy/GUID-26457D23-798C-47B0-9F40-C5DA6E995C6F-en-US-2/index.html)\)
-  RNBD Data Sheet \([RNBD451 DS](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)\)
-   AVR128DA48 Product Page \([AVR128DA48](https://www.microchip.com/en-us/product/AVR128DA48)\)
-   RN Data Sheet \([RN4870/1](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-Data-Sheet-DS50002489D.pdf)\)

-   RN User Guide ([RN4870/1](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-User-Guide-DS50002466C.pdf)\)


# Software Used<a name="software-used"></a>
-   [MPLAB® X IDE 6.20](http://www.microchip.com/mplab/mplab-x-ide) or newer

-   [MPLAB XC8 2.46](http://www.microchip.com/mplab/compilers) or newer
-   [MPLAB Code Configurator 5.5.1](https://www.microchip.com/mplab/mplab-code-configurator) or newer
-   [MPLAB Code Configurator](https://www.microchip.com/mplab/mplab-code-configurator) Device Libraries AVR128Dx28/32/48/64, AVR64Dx28/32/48/64 Microcontrollers (MCUs)
-   [MPLAB Code Configurator](https://www.microchip.com/mplab/mplab-code-configurator) Device Libraries AVR® MCUs
-   [Microchip AVR-Dx_DFP Series Device Support \(2.5.294\)](https://packs.download.microchip.com) or newer

# Hardware Used<a name="hardware-used"></a>

-   AVR128DA48 Curiosity Nano Board \([DM164151](https://www.microchip.com/en-us/development-tool/DM164151)\)
-   Curiosity Nano Base for Click Boards™ \([AC164162](https://www.microchip.com/en-us/development-tool/AC164162)\)

# Hardware Setup<a name="hardware-setup"></a>
## RNBD Pin Mapping and Hardware Setup
-   Pin mapping table between the MCU and the RNBD Click:

    | S. No | Pin Functionality | AVR |  RNBD  Click  |
    |-------|-------------------|-----|---------------|
    |   1   | Receive (RxD)     | RA1 |     Tx        |
    |   2   | Transmit (TxD)    | RA0 |     Rx        |
    |   3   | BT_RST            | RD7 |     RST       |

-   Connect the development board of your choice and then connect the RNBD to the proper slot. The image below shows how to connect the RNBD Click to **Slot 1**.

    ![](images/GUID-349DACB9-0CD8-42B7-B586-B39B507961D5-low.png)

    **Important:** The slot was decided based on the UART instances which were configured for this example (see the pin mapping table between the MCU and the RNBD Click).
## RN487x Pin Mapping and Hardware Setup
-   Pin mapping table between the MCU and the RN487x Click:

    | S. No | Pin Functionality | AVR | RN487x Click |
    |-------|-------------------|-----|--------------|
    |   1   | Receive (RxD)     | RA1 |     Tx       |
    |   2   | Transmit (TxD)    | RA0 |     Rx       |
    |   3   | BT_RST            | RD7 |     RST      |

-   Connect the development board of your choice and then connect the RN487x to the proper slot. The image below shows how to connect the RN487x Click to **Slot 1**.

    ![](images/GUID-0C54F6CA-B754-49CA-AD3D-618A3786D559-low.png)

    **Important:** The slot was decided based on the UART instances which were configured for this example application (see the pin mapping table between the MCU and the RN487x Click).

# Software Prerequisite<a name="software-prerequisite"></a>

Install the MPLAB Code Configurator Plug-in:

1.  Go to the MPLAB Code Configurator [page](https://www.microchip.com/mcc).
2.  In MPLAB X IDE, select Plugins from the Tools menu.
3.  Select the **Available Plugins** tab.
4.  Check the box for the MPLAB Code Configurator v3 and click **Install**.

# Project Setup<a name="project-setup"></a>

**Note:** The Validation Hardware used with Microchip Bluetooth Data Mobile App is shown in the process below. AVR128DA48 8-bit devices are used for reference.
<br />

1.  [Create a New Project](https://www.youtube.com/watch?v=iZuucxaAVLg) in [MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide).

    ![](images/GUID-7D237BEA-C905-46FA-B1BC-A90CC2F8A2AA-low.png)

2.  Open MCC by clicking _Tools→Embedded→MPLAB® Code Configurator_ or click the **MCC** button.

    <br />

    ![](images/GUID-359085BA-D8D7-47F8-AF8D-750837A36071-low.png)

    or

    ![](images/GUID-5ADA889B-5F93-48F2-B5EF-4EE824D9DEA5-low.png)

3.  If MCC is not available, install it. Navigate to _Tools→Plugins_. Under **Available Plugins** select "MPLAB Code Configurator", ensure the checkbox is selected and press **Install**. Once the installation is completed, MCC will be available.

  ![](images/GUID-FF1D230A-1359-45DE-9631-F96EA45455EE-low.png)
  <br />

4.  On launching MCC, click the **Content Manager** button.

    |WARNING|
    |-------|
    |Use the mentioned driver versions only as shown in the image below!|

    -  Expand the Libraries section and load the available version of rnbd-rn487x-host-driver v2.0.0 BLE library

        ![](images/PIC18F47Q10_MCC_Content_Manager.svg)

        ![](images/PIC18F47Q10_RNBD_RN487x_BLE_Library.svg)

    -  Expand the Drivers section and load the below version of UART drivers

        ![](images/GUID-8AF04B44-2DB1-4571-8682-358039FDB24A-low.png)

        <br />

        ![](images/AVR_latest_UART_Driver.png)

        <br />

    -  Click the **Apply** button to finish the library and driver configurations

        <br />

        ![](images/GUID-643FCE2C-0CCA-477C-B92D-3E15678AAEAC-low.png)

        <br />

5.  Go to _Device Resources→Libraries→rnbd-rn487x-host-driver→RNBD-RN487x_.

    <br />

    ![](images/GUID-563CD3C8-EDAD-4984-80B4-41BFEE039C74-low.png)

    <br />

    - Add the RNBD-RN487x from Device Resources to Project Resources:  

      ![](images/GUID-75D4253D-49BC-487C-BFE3-4BF1438646EC-low.png)

    <br />

    - Once the RNBD-RN487x driver was loaded to the Project Resources panel, choose the USART0 Peripheral Library (PLIB) selection from UART driver, in which the GUI will be expanded for another configuration setting tab

      ![](images/UART_PLIB_Hint.png)

      ![](images/USART_PLIB_Selection.png)

6.  The **Notifications [MCC]** tab will appear after the library addition to describe the required actions. The library requires the Reset Pin to be "connected to the module", which needs to be assigned to a pin. Select and configure the dependent UART instance under Dependency Selector.

    ![](images/GUID-B93C6167-5693-4253-97A7-E08BE3AAACAC-low.png)

7.  Generating example applications:

    -   Enable the "Sample Examples" toggle button. Then choose any of the example applications under the "Reference Example" drop-down menu:
        -   Basic Data Exchange
        -   Transparent UART Application

            <br />

            ![](images/AVR_RNBD_Example_dropDown.png)

            <br />

            **Note:** Select either example application, as they can both be used for RNBD and RN487x.

8.  Clock Settings:
    -   Go to _Project Resources→System→Clock Control_

        <br />

        ![](images/GUID-7989F070-C0C0-4B02-B4D4-79819F558C54-low.png)

        <br />

    -   Set "Internal high-frequency oscillator" to 20 MHz system clock, toggle ON the "Prescaler Enable" option and set the "Prescaler Divison" to 2x.

        <br />

        ![](images/GUID-ADDADFD9-C271-4D6B-98F6-654E6FDB425C-low.png)

        <br />

9. UART Settings:
    -   **Note:** The below UART selections are applicable for both Transparent UART Application and Basic Data Exchange (USART0 and USART1)<br />
    ![](images/GUID-33FE9FF7-FB87-4855-8007-6CB4C82D055B-low.png)

    ![](images/GUID-BA56BBC1-6C5F-4F58-9E67-466B607AA2DB-low.png)


10. Global Interrupt Settings:
    -   Click "Interrupt Manager" under the System settings

        <br />

        ![](images/GUID-D2F566E1-91BB-4BBB-9FF9-7C41DE8D34EE-low.png)

        <br />

        ![](images/GUID-71201DF5-485D-4A36-B7D4-89C7F2126FE6-low.png)

        <br />


<br />

# RNBD Setup and Running Example Application<a name="rnbd-setup-and-running-example-application"></a>

This section explains the RNBD MPLAB X IDE project setup, code generation, and shows how to run the Basic Data Exchange and Transparent UART applications with the AVR128DA48 microcontroller.

## RNBD Basic Data Exchange Pin Settings<a name="rnbd-basic-data-exchange-pin-settings"></a>
<br />

-   AVR128DA48 MCC Configuration - Basic Data Exchange Example
    <br />

    - Set "Device Selection" to RNBD
    - Enable "Sample Examples"
    - Expand "Reference Examples" and select Basic Data Exchange

     ![](images/GUID-8ADE895A-F2B2-4CFC-89A3-71C60A62155F-low.png)

     ![](images/GUID-A6336B17-992D-4E24-8843-8631FE3DAF30-low.png)


**Notes:**

1.   The Basic Data Exchange application uses only one instance USART0 for data transfer.
2.   **Important:** For USART0 RxD and TxD, deselect the checkboxes in the Start High and Pull-Up columns. Change Rx, Tx and BT_RST in the Input/Sense Configuration [ISC] column from "Interrupt Disabled but input buffer enabled" to "Sense Both Edges".

        <br />

        ![](images/GUID-D689B156-8059-457F-A70D-3376836ED3A7-low.png)

        <br />

        <br />

        ![](images/GUID-184EEDCA-BCE8-44F7-86F2-3737192B2CC8-low.png)

        <br />


Configuration for AVR Basic Data Exchange was completed. Click [here](#rnbd-code-generation-&-compilation) for the RNBD Code Generation and Compilation section.



## RNBD Transparent UART Application Pin Settings<a name="rnbd-transparent-uart-application-pin-settings"></a>
<br />

-   AVR128DA48 MCC Configuration - Transparent Serial Example
    <br />

    - Set "Device Selection" to RNBD
    - Enable "Sample Examples"
    - Expand "Reference Examples" and select Transparent UART application

     ![](images/GUID-8778600E-033C-4176-85E6-419A1FD0CE2D-low.png)

     ![](images/GUID-EEF87C36-9DF7-44ED-A556-5F6DC3FEE9FC-low.png)

    <br />

    **Notes:**
    1.   The Transparent UART application uses two instance USART0 and USART1 for data transfer.

    2.   **Important:** For USART0 and USART1 RxD and TxD, deselect the checkboxes in the Start High and Pull-Up columns. Change Rx, Tx and BT_RST in the Input/Sense Configuration [ISC] column from "Interrupt Disabled but input buffer enabled" to "Sense Both Edges".
    <br />

    ![](images/GUID-5ACA33D0-6216-49F1-A17C-41E07D391C89-low.png)

    ![](images/GUID-53BBBABA-CF2F-4763-9846-2D9BE6462AD0-low.png)


Configuration for AVR Transparent UART was completed. Click [here](#rnbd-code-generation-&-compilation) for RNBD Code Generation and Compilation section.

<br />

## RNBD GPIO Based Connection Setup<a name="rnbd-gpio-based-connection-setup"></a>

The RNBD device can use Bluetooth (BT) Status Indication 1 and Bluetooth (BT) Status Indication 2 pins to indicate the GPIO connection status. Besides monitoring the connect message in the serial UART prints, this feature is useful when the host MCU can verify the BT connection status, by monitoring the Status Indication pins.

**Bluetooth (BT) Status Indication Pin Table**

<br />

![](images/GUID-7D357103-8BE2-4E40-92A3-AC9C96EA66F3-low.png)

<br />

Pin mapping between the RNBD Bluetooth (BT) Status Indication 1 and Indication 2 pins with AVR128DA48:

<br />

|Pin Functionality|RNBD Pin Number|AVR128DA48 Pin Number|
|-----------------|---------------|---------------------|
|Bluetooth (BT) Status Indication 1|PB3|PA6|
|Bluetooth (BT) Status Indication 2|PB7|PA5|

<br />

<br />

1.  Select the GPIO based example and connection (Pin selection), as they are applicable for both the Basic Data Exchange and the Transparent UART application.

    <br />

    ![](images/GUID-EE67AFCF-019F-4750-B4B0-430572C07CA2-low.png)

    <br />

2.  Pin selection for Status Indication 1 and 2 pins under the **Pin Grid View** tab:

    <br />

    ![](images/GUID-132ED7DC-78B5-46EF-862E-0BDC2CD48EC5-low.png)

    <br />

3.  Go to Pins, under Project Resources:

    <br />

    ![](images/GUID-E2015538-2663-4871-9826-03CEF967E574-low.png)

    <br />

    For Status Indication Pins 1 and 2, the checkboxes in the Default Start High, Pull-Up columns will be checked.

    <br />

    ![](images/GUID-B454FD2A-0F74-48B1-99B1-3FD905B06C7A-low.png)

    <br />

    Deselect the checkboxes in the Start High and Pull-Up columns. Change Rx and Tx in the Input/Sense Configuration [ISC] column from "Interrupt Disabled but input buffer enabled" to "Sense Both Edges".

    <br />

    ![](images/RNBD_GPIO_Pin_status.png)


Configuration for GPIO based  connection was completed. Click [here](#rnbd-code-generation-&-compilation) for the RNBD Code Generation and Compilation section.


## RNBD Code Generation and Compilation<a name="rnbd-code-generation-&-compilation"></a>

<br />

1.   Click the **Generate** button next to Project Resources.<br />
  ![](images/GUID-D61FD824-523E-47C1-AF68-7A85F6F8EC98-low.png)


2.  Include the header `#include "mcc_generated_files/examples/rnbd_example.h"` in `main.c`.
3.  Call the `RNBD_Example_Initialized();` function in `main()` after `SYSTEM_Initialize()`.
  <br />

  ![](images/GUID-165F5AC2-11F4-4207-B379-CDD0B1EF4BC8-low.png)

  <br />

4.  Connect the development board of your choice and then connect the RNBD to the proper slot. The image below shows how to connect the RNBD Click to **Slot 1**.

    <br />

    ![](images/GUID-349DACB9-0CD8-42B7-B586-B39B507961D5-low.png)

    **Important:** The slot was decided based on the UART Instances which were configured for this example (see the pin mapping table between the MCU and the RNBD Click shown below).

    - Pin mapping table between MCU and RNBD Click
        <br />

        |S. No|Pin Functionality|AVR|RNBD Click|
        |-----|-----------------|---|----------|
        |  1  |Receive (RxD)    |RA1| Tx       |
        |  2  |Transmit (TxD)   |RA0| Rx       |
        |  3  |BT_RST           |RD7| RST      |

        <br />

6.  Click **Clean and Build**.

    ![](images/GUID-C5CABE33-147F-452B-BB41-00CB466BAA8D-low.png)

7.  Program the device by clicking the **Make and Program** button.

    ![](images/GUID-ED80E89C-A13D-4B87-AD9A-0D7AE5E580EB-low.png)


<br />


## RNBD Example 1: Running Basic Data Exchange Example Application<a name="rnbd-example1:-running-basic-data-exchange-application"></a>

This example shows how an MCU can be programmed to transmit data to a smartphone over BLE. The MCU device will send a Periodic Transmission of a single character when STREAM\_OPEN is processed through the Message Handler. This indicates to the MCU and RNBD module that the application is in a Data Streaming mode of operation and can expect to hear data over the BLE connection.<br /><br />
The `#define DEMO_PERIODIC_TRANSMIT_COUNT (10000)` and `#define DEMO_PERIODIC_CHARACTER (‘1’)` statements used in the demonstration can be located at the top of the `rnbd_example.c` file.

![](images/GUID-0C803050-62C5-4E5F-BA14-619E48B5916E-low.png)

1.  Download and install Microchip Bluetooth Data (MBD) from [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the phone application.

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)
    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    - Open the main menu and go to the BLE Smart option

      ![](images/GUID-E19A7964-8190-4C53-8BBA-6370A19C9829-low.png)

3.  The application scans the area for Bluetooth devices within range. By default, the device appears as "RNBD451_xxxx". Look for the "RNBD" device under the scan list.

    <br />

    ![](images/GUID-E5C513CE-6227-42C1-9DA8-3FA2075112DF-low.png)

    <br />

4.  Select the RNBD device from the list, then click the **CONNECT** button to connect to the RNDB module.

    <br />

    ![](images/GUID-5962533D-A1D4-40DA-8933-A7224139EBA7-low.png)

    <br />

5.  Once connected, the Microchip Bluetooth app identifies all the services and characteristics supported by the RNBD device.

    ![](images/GUID-AC320004-8543-404F-806A-4C5E70E09E3B-low.png)

6.  Click the Microchip Data Service option. Select the Microchip Data Characteristic (Write Notify indication) to receive the data in the mobile application.

    ![](images/GUID-65CA4B07-2C54-4799-A9AE-826FD83B676D-low.png)

7.  Select "Listen for notifications" on the application.
      -   It may be required to enable app notifications on the phone. Data will be sent periodically to the device and will be visible beneath the Notify/Listen setting.

       -   Before turning on the Notify/Indicate setting:

            ![](images/GUID-C5223277-D33D-4366-8CA4-124D340F0554-low.png)

       -   After turning on the Notify/Indicate setting, the mobile application can read "31", data which was sent from the RNBD module

            ![](images/GUID-83D3CD62-CA8C-4C6C-88AF-CA15728E6392-low.png)


## RNBD Example 2: Running Transparent UART Example Application<a name="rnbd-example2:-running-transparent-uart-example-application"></a>

<br />

![](images/GUID-8E99A785-AE04-48F7-BBD4-7259DC3B5F9B-low.png)

<br />

<br />

This example shows how the data transmitted from a PC serial terminal is written to a smartphone application and vice versa. The MCU acts as a bridge while passing data between RNDB module <--- MCU ---> Serial Terminal. This action will occur when STREAM_OPEN is processed through the Message Handler. For this example, data typed into the Serial Terminal will appear on the BLE phone application, and data sent from the application will appear on the Serial Terminal.

<br />

1.  Download and install Microchip Bluetooth Data (MBD) from [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the phone application.

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)
    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    - Open the main menu and go to the BLE UART option

     ![](images/GUID-D647FF96-CA12-4FA0-A3AA-29C6D6C3DF9D-low.png)

    <br />

3.  Select "PIC32CXBZ" to scan for available devices to connect with. The application automatically scans the area for Bluetooth devices within range. By default, the device appears as "RNBD451_xxxx".

    <br />

    ![](images/GUID-267AD085-1463-4495-8A62-0EBE87B8C667-low.png)

    <br />

4.  For Transparent Serial only: Open a Serial Terminal Program such as Tera Term, Realterm, PuTTY, Serial or similar. Baud rate will be configured as 115200.

    <br />

    ![](images/GUID-F03D2F6E-4C61-4076-8322-1CD1ACA81EA2-low.png)

    <br />

    <br />

    ![](images/GUID-136BD52C-2CDC-4522-AE36-B7E75249C656-low.png)

    <br />

5.  Once connected to RNBD451_0EC4, click "Text Mode" at the bottom of the settings to initiate the data transfer.

    <br />

    ![](images/GUID-4A2C616C-FB94-465C-BA58-997E542DBF9C-low.png)

    <br />

    - Check the Serial Terminal for the status of the connection

    <br />

    ![](images/GUID-928146A5-0740-4390-AB9D-31AE1A0A9164-low.png)

    <br />

6.  Enter the text to be transferred from mobile to the RNBD device and click the **Send** button.

    <br />

    ![](images/GUID-9C7FDD8B-9541-4543-8746-9C1B98D0E5D0-low.png)

    <br />

    - The data will be received on the RNBD side and will be displayed in the serial terminal of RNBD45x

    <br />

    ![](images/GUID-2B7B8379-978D-4B3E-AE7F-F5FE12868EBF-low.png)

    <br />

7.  Type any data on the serial terminal of the RNBD to send to the Microchip Bluetooth Data app. The data is received and printed on the receive view of the app.

    <br />

    ![](images/GUID-3D09C58E-D3A8-456B-A347-32BBC09DA06F-low.png)

    <br />

    <br />

    ![](images/GUID-34E4CFD6-6857-479E-93B0-4ACE34EDFD59-low.png)

    <br />


# RN487x Setup and Running Example<a name="rn487x-setup-and-running-example"></a>

This section explains the RN487x MPLAB X IDE project setup, code generation, and shows how to run the Basic Data Exchange and Transparent UART applications with the AVR128DA48 microcontroller.

## RN487x Basic Data Exchange Pin Settings<a name="rn487x-basic-data-exchange-pin-settings"></a>

<br />

-   AVR128DA48 MCC Configuration - Basic Data Exchange Example<br />

    <br />

    - Set "Device Selection" to RN487x

    - Enable "Sample Examples"
    - Expand "Reference Examples" and select Basic Data Exchange

     ![](images/GUID-41FE8A10-5BA7-4042-909E-923EA51472F7-low.png)

     ![](images/GUID-A6336B17-992D-4E24-8843-8631FE3DAF30-low.png)

    <br />


  **Notes:**

  1.   The Basic Data Exchange application uses only one instance of USART0 for data transfer.
  2.   **Important:** For USART0 RxD and TxD, deselect the checkboxes in the Start High and Pull-Up columns. Change Rx, Tx and BT_RST in the Input/Sense Configuration [ISC] column from "Interrupt Disabled but input buffer enabled" to "Sense Both Edges".

        <br />

        ![](images/GUID-D689B156-8059-457F-A70D-3376836ED3A7-low.png)

        <br />

        ![](images/GUID-184EEDCA-BCE8-44F7-86F2-3737192B2CC8-low.png)

        <br />


Configuration for AVR Basic Data Exchange was completed. Click [here](#rn487x-code-generation-&-compilation) for RN487x code generation and compilation section.


## RN487x Transparent UART Application Pin Settings<a name="rn487x-transparent-uart-application-pin-settings"></a>
<br />

-   AVR128DA48 MCC Configuration - Transparent Serial Example<br />

    - Set "Device Selection" to RN487x

    - Enable "Sample Examples"
    - Expand "Reference Examples" and select Transparent UART application

     ![](images/GUID-71A42A1A-8E94-47B4-BE6C-B9FF92D2048E-low.png)
     <br />

     ![](images/GUID-EEF87C36-9DF7-44ED-A556-5F6DC3FEE9FC-low.png)

**Notes:**

1.   The Transparent UART application uses two instance of USART0 and USART1 for data transfer.
2.   **Important:** For USART0 and USART1 RxD and TxD, deselect the checkboxes in the Start High and Pull-Up columns. Change Rx,Tx and BT_RST in the Input/Sense Configuration [ISC] column from "Interrupt Disabled but input buffer enabled" to "Sense Both Edges".
![](images/GUID-5ACA33D0-6216-49F1-A17C-41E07D391C89-low.png)

  ![](images/GUID-53BBBABA-CF2F-4763-9846-2D9BE6462AD0-low.png)

Configuration for AVR Transparent UART application was completed. Click [here](#rn487x-code-generation-&-compilation) for the RN487x Code Generation and Compilation section.

## RN487x Code Generation and Compilation<a name="rn487x-code-generation-&-compilation"></a>
<br />

1.  Click the **Generate** button next to Project Resources.

    <br />

    ![](images/GUID-2D18886B-77EB-4E2D-823C-79E1585D3E03-low.png)

    <br />

2.  Include the header `#include "mcc_generated_files/examples/rn487x_example.h"` in `main.c`.
3.  Call the `RN487X_Example_Initialized();` function in `main()` after `SYSTEM_Initialize()`.

    <br />

    ![](images/GUID-70819D0B-CB37-4866-B433-1866B91B9F13-low.png)

    <br />

4.  Connect the development board of your choice and then connect the RN487x to the proper slot. The image below shows how to connect the RN487x Click to **Slot 1**.

    <br />

    ![](images/GUID-0C54F6CA-B754-49CA-AD3D-618A3786D559-low.png)

    **Important:** The slot was decided based on the UART instances which was configured for this example application (see the pin mapping table between the MCU and the RN487x Click shown below).

    - Pin mapping table between MCU and RN487x Click
        <br />

        |S. No|PIN Functionality|AVR|RN487x Click|
        |-----|-----------------|---|------------|
        |1|Receive  (RxD)|RA1|Tx|
        |2|Transmit  (TxD)|RA0|Rx|
        |3|BT_RST |RD7|RST|

        <br />

6.  Click **Clean and Build**.

    ![](images/GUID-C5CABE33-147F-452B-BB41-00CB466BAA8D-low.png)

7.  Program the device by clicking the **Make and Program** button.

    ![](images/GUID-ED80E89C-A13D-4B87-AD9A-0D7AE5E580EB-low.png)


<br />


## RN487x Example 1: Running Basic Data Exchange Example Application<a name="rn487x-example1:-running-basic-data-exchange-example-application"></a>

This example shows how an MCU can be programmed to transmit data to a smartphone over BLE. The MCU device will send a Periodic Transmission of a single character when STREAM_OPEN is processed through the Message Handler. This indicates to the MCU and RN487x module that the application is in a Data Streaming mode of operation and can expect to hear data over the BLE connection.<br /><br />
The `#define DEMO_PERIODIC_TRANSMIT_COUNT (10000)` and `#define DEMO_PERIODIC_CHARACTER (‘1’)` statements used in the demonstration can be located at the top of the `rn487x_example.c` file.

![](images/RN487x_BasicData_Exchange_HW.png)

1.  Download and install Microchip Bluetooth Data (MBD) from [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the phone application.

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)![](GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    - Open the main menu and go to the BLE Smart option

      ![](images/GUID-E19A7964-8190-4C53-8BBA-6370A19C9829-low.png)

3.  The application automatically scan the area for Bluetooth devices within range. Look for the "RN487x" device under the scan list.

    <br />

    ![](images/GUID-F9008121-7D40-4680-89B2-F595E314CB17-low.png)

    <br />

4.  Select the RN487x device from the list, then click the **CONNECT** button to connect to the RNDB module.

    <br />

    ![](images/GUID-EC0D19FF-B0F3-4D44-BD3F-D99B9FEFC62D-low.png)

    <br />

5.  Once connected Microchip Bluetooth app identifies all the services and characteristics supported by the RN487x.

    <br />

    ![](images/GUID-9ED50565-2513-482E-BE6A-D118C539C56D-low.png)

    <br />

6.  Click the Microchip Data Service option. Select the Microchip Data Characteristic (Write Notify indication) to receive the data in the mobile application.

    <br />

    ![](images/GUID-57D1EBD2-972B-4152-AAC3-D5C98DE6E4C6-low.png)

    <br />

7.  Select "Listen for notifications" on the application.
    -   It may be required to enable app notifications on the phone. Data will be sent periodically to the device and will be visible beneath the Notify/Listen setting.

        -   Before turning on the Notify/Indicate setting:

            <br />

            ![](images/GUID-3780F6BB-6198-4179-A5C0-58042FC83EAE-low.png)

            <br />

        -  After turning on the Notify/Indicate setting, the mobile application can read "31", data which was sent from the RN487x module

            ![](images/GUID-9A94A4DF-BEB9-48A5-B958-CDDC2C296ED7-low.png)


## RN487x Example 2: Running Transparent UART Example Application<a name="rn487x-example2:-running-transparent-uart-example-application"></a>

<br />

![](images/RN487x_Transparent_UART_HW.png)

<br />

<br />

This example shows how the data transmitted from a PC serial terminal is written to a smartphone application and vice versa. The MCU acts as a bridge while passing data between RN487x module <--- MCU ---> Serial Terminal. This action will occur when STREAM_OPEN is processed through the Message Handler. For this example, data typed into the Serial Terminal will appear on the BLE phone application, and data sent from the application will appear on the Serial Terminal.

<br />

1.  Download and install Microchip Bluetooth Data (MBD) from [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the phone application.

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    - Open the main menu and go to the BLE UART option

      ![](images/GUID-D647FF96-CA12-4FA0-A3AA-29C6D6C3DF9D-low.png)

    <br />

3.  Select "BM70" to scan for available devices to connect with.

    <br />

    ![](images/GUID-6B7B0F61-A3A7-478C-A253-06E561E1313F-low.png)

    <br />

    - Click the '**Scan image**' icon to scan for the nearby "RN487x-xxxx"

      <br />

      ![](images/GUID-C7AB4C05-260C-4C69-AF6D-298B9E02F302-low.png)

      <br />

    - The application automatically scans the area for Bluetooth devices within range. By default, the device appears as "RN487x_xxxx".

      <br />

      ![](images/GUID-C36CEB36-58F8-4DAD-8800-358F70E56B66-low.png)

    <br />

4.  For Transparent Serial only: Open a Serial Terminal Program such as Tera Term, Realterm, PuTTY, Serial or similar. Baud rate will be configured as 115200.

    <br />

    ![](images/GUID-B18B65D8-9AA3-478A-A674-DEB871E086CA-low.png)

    <br />

    <br />

    ![](images/GUID-BC559EA4-E40C-4332-9EF3-4BA8F919AFE6-low.png)

    <br />

5.  Once Connected to RN487x-xxxx click "Transfer data to device" to initiate the data transfer.

    <br />

    ![](images/GUID-B3297905-2011-452F-8141-887853ECF6AD-low.png)

    <br />

    - Check the Serial Terminal for the status of the connection

    <br />

    ![](images/GUID-DF2150F8-89DC-4876-B351-D59A58E34272-low.png)

    <br />

6.  Enter the text to be transferred from mobile to the RN487x-xxxx device and click the **Send** button.

    <br />

    ![](images/GUID-B8693063-53D6-4080-AD8C-3906E2698F6C-low.png)

    <br />

    - The data will be received on the RN487x side and will be displayed in the serial terminal of RN487x

    <br />

    ![](images/GUID-E0106617-7CA8-4508-AE5A-278D8E8B737B-low.png)

    <br />

7.  Type any data on the serial terminal of the RN487x-xxxx to send to the Microchip Bluetooth Data app. The data is received and printed on the receive view of the app.

    <br />

    ![](images/GUID-CEC4E31B-D080-4A65-8350-81D62D130FC9-low.png)

    <br />

    <br />

    ![](images/GUID-E985EFE1-6B23-4A76-86DE-E349AF41D0F1-low.png)

    <br />



# Summary<a name="summary"></a>

**Command, Data Communication with Asynchronized Message Processing:**

This driver has the inherent code capability to distinguish between Message exchange and Data exchange at the level of the connected MCU and module devices. The library supplies all required APIs needed for the implementation of a functional BLE-connected end-device. The three required pins can be selected through the GUI provided by the MCC. The two UART pins are used for communication and control of the RST_N connected to the RNBD module. This library also allows for the extension of module pin behaviors through the simple RNBD module object interface, where any device/project specific instantiations exist. Refer to the `rnbd_interface.c/h/rn487x_interface.c/h` file.

`iRNBD_FunctionPtrs_t` is a typedef struct which can be found in the `rnbd_interface.h/rn487x_interface.h` file and consists of nine function pointers. The concrete creation of RNBD as an object is instantiated in the `rnbd_interface.c/rn487x_interface.c`. Find the private static implementations of the desired behavior in the `rnbd_interface.c/rn487x_interface.c` file. In some cases, such as DELAY or UART, the supporting behavior is supplied through another supporting library module. When applicable, ‘inline’ has been used to reduce stack depth overhead.

<br />

![](images/GUID-2B41A010-DEC4-4198-9245-049150500274-low.png)

<br />

<br />

![](images/GUID-08351B32-7A45-4F07-91BF-66534BFE5482-low.png)

<br />

The driver library may not require modifications or injections done by the user unless it expands to the supported command implementations `rnbd.c` and `rnbd.h` files.

**Configurable Module Hardware Requirement\(s\)**

The MCU and the module communicate through UART:

<br />

![](images/GUID-230E3567-ED26-4E33-92AA-A094AC3AC262-low.png)

<br />

The library allows the configuration of three pins associated with support features extended through the Driver Interface. The RNBD modules require only the RESET pin to operate.

<br />

![](images/GUID-E87D4AC0-B045-451E-A188-EFD3FB82F70E-low.png)

<br />

<br />

|Library Name: Output\(s\)|Module: Input\(s\)|Description|Module Physical Defaults|
|-------------------------|------------------|-----------|------------------------|
|BT\_MODE|P2\_0|<br /> `1`: Application Mode<br /> `0`: Test Mode/Flash Update/EEPROM Configuration<br />|Active-Low, Internal Pull-High|
|BT\_RST|RST\_N|Module Reset|Active-Low, Internal Pull-High|
|BT\_RX\_IND|P3\_3|Configured as UART RX Indication pin|Active-Low|

<br />
