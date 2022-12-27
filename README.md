
[![MCHP](images/microchip.png)](https://www.microchip.com)

# AVR128DA48\_RNBD\_RN487x\_UserGuide

-   [Introduction](#introduction)
-   [Driver Information](#driver-information)
-   [Related Documentation](#related-documentation)
-   [Software Used](#software-used)
-   [Hardware Used](#hardware-used)
-   [Software Prerequisite](#software-prerequisite)
-   [Project Setup](#project-setup)
-   [RNBD451 Set Up and Running Example Application](#rnbd451-set-up-and-running-example-application)
    -   [RNBD Basic Data Exchange PIN Settings](#rnbd-basic-data-exchange-pin-settings)
    -   [RNBD Transparent UART Application PIN Settings](#rnbd-transparent-uart-application-pin-settings)
    -   [RNBD GPIO Based Connection Setup](#rnbd-gpio-based-connection-setup)
    -   [RNBD Code Generation & Compilation](#rnbd-code-generation-&-compilation)
    -   [RNBD Example1: Running Basic Data Exchange Example Application](#rnbd-example1:-running-basic-data-exchange-example-application)
    -   [RNBD Example2: Running Transparent UART Example Application](#rnbd-example2:-running-transparent-uart-example-application)
-   [RN487x Set Up and Running Example](#rn487x-set-up-and-running-example)
    -   [RN487x Basic Data Exchange PIN Settings](#rn487x-basic-data-exchange-pin-settings)
    -   [RN487x Transparent UART Application PIN Settings](#rn487x-transparent-uart-application-pin-settings)
    -   [RN487x Code Generation & Compilation](#rn487x-code-generation-&-compilation)
    -   [RN487x Example1: Running Basic Data Exchange Example Application](#rn487x-example1:-running-basic-data-exchange-example-application)
    -   [RN487x Example2: Running Transparent UART Example Application](#rn487x-example2:-running-transparent-uart-example-application)
-   [Summary](#summary)

# Introduction<a name="introduction"></a>

The MPLAB® Code Configurator (MCC) [RNBD](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)/[RN487x](https://www.microchip.com/wwwproducts/en/RN4870) BLE Modules Library allows to promptly configure the C code-generated software driver, based on the user’s selected API features available in the MCC Library. The Generated Driver code can support the BLE module using a AVR device

The library module uses a Graphic User Interface (GUI) provided by the MCC, used to set the configuration, and the custom configurations of the protocol. The Customized C code is generated within the MPLAB X project, in a folder named "MCC Generated Files".

This Library uses \(1\) UART, \(1\) GPIO, and DELAY support at minimal.

Refer to the /images folder for source files & max resolution.

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

-   Microchip Bluetooth \([BLE](https://www.microchip.com/design-centers/wireless-connectivity/bluetooth)\)
-   RNBD User Guide \([RNBD451](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)\)
-   RNBD Data Sheet \([RNBD451 DS](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)\)
-   AVR128DA48 Product Page \([AVR128DA48](https://www.microchip.com/en-us/product/AVR128DA48)\)
-   RN Data Sheet \([RN4870/1](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-Data-Sheet-DS50002489D.pdf)\)

-   RN User Guide\([RN4870/1](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-User-Guide-DS50002466C.pdf)\)


# Software Used<a name="software-used"></a>
-   MPLAB® X IDE 6.00 or newer \([microchip.com/mplab/mplab-x-ide](http://www.microchip.com/mplab/mplab-x-ide)\)
-   MPLAB® XC8 2.35 or a newer compiler \([microchip.com/mplab/compilers](http://www.microchip.com/mplab/compilers)\)
-   MPLAB® Code Configurator \(MCC\) 5.1.1 or newer \([microchip.com/mplab/mplab-code-configurator](https://www.microchip.com/mplab/mplab-code-configurator)\)
-   MPLAB® Code Configurator \(MCC\) Device Libraries AVR128Dx28/32/48/64, AVR64Dx28/32/48/64 MCUs \([microchip.com/mplab/mplab-code-configurator](https://www.microchip.com/mplab/mplab-code-configurator)\)
-   MPLAB® Code Configurator \(MCC\) Device Libraries AVR® MCUs \([microchip.com/mplab/mplab-code-configurator](https://www.microchip.com/mplab/mplab-code-configurator)\)
-   Microchip AVR-Dx\_DFP Series Device Support \(2.2.152\) or newer \([packs.download.microchip.com/](https://packs.download.microchip.com/)\)

# Hardware Used<a name="hardware-used"></a>

-   AVR128DA48 Curiosity Nano Board \([DM164151](https://www.microchip.com/en-us/development-tool/DM164151)\)
-   Curiosity Nano Base Board \([AC164162](https://www.microchip.com/en-us/development-tool/AC164162)\)
-   RNBD User Guide \([RNBD451](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)\)
-   RNBD Device Data-Sheet \([RNBD451 DS](http://mchpweb:4576/SpecIndex_FileAttach/TPT_20227216811993/70005514A.pdf)\)
-   [RN Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-Data-Sheet-DS50002489D.pdf)

-   [RN User Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/RN4870-71-Bluetooth-Low-Energy-Module-User-Guide-DS50002466C.pdf)

# Software Prerequisite<a name="software-prerequisite"></a>

To install the MPLAB® Code Configurator Plug-in:

1.  Open the MPLAB® Code Configurator page: [https://www.microchip.com/mcc](https://www.microchip.com/mcc)
2.  In MPLAB X IDE, select **Plugins** from the Tools menu.
3.  Select the **Available Plugins** tab.
4.  Check the box for the MPLAB® Code Configurator v3, and click **Install**.

# Project Setup<a name="project-setup"></a>

<br />

1.  [Create a New Project](https://www.youtube.com/watch?v=iZuucxaAVLg) in [MPLAB® X IDE](https://www.microchip.com/mplab/mplab-x-ide).

    ![](images/GUID-7D237BEA-C905-46FA-B1BC-A90CC2F8A2AA-low.png)

2.  The Validation Hardware used with Microchip Bluetooth Data Mobile App is shown in the process below. AVR128DA48 8-bit devices are used for reference.
3.  Open MCC by clicking Tools → Embedded → MPLAB® Code Configurator OR click the MCC icon. ![](GUID-359085BA-D8D7-47F8-AF8D-750837A36071-low.png)

    or

    ![](images/GUID-5ADA889B-5F93-48F2-B5EF-4EE824D9DEA5-low.png)

4.  If MCC is not available; it is required to be installed. Navigate to Tools → Plugins. Under Available Plugins select MPLAB® Code Configurator, ensure the checkbox is selected and press **Install**. Once the installation is completed, MCC will be available.![](GUID-FF1D230A-1359-45DE-9631-F96EA45455EE-low.png)
5.  On launching MCC click on **Content Manager** button.

    |WARNING|
    |-------|
    |Kindly use mentioned Driver Version's only as shown in<br /> the below image|

    1.  Expand Libraries section and load the available version of rnbd-rn487x-host-driver BLE Library
        -   **Common for PIC & AVR**

            <br />

            ![](images/GUID-83D5D4BA-72A3-40B4-BCA6-E438E1B77D6C-low.png)

            <br />

    2.  Expand Drivers section and load the below version of UART Drivers

        <br />

        ![](images/GUID-8AF04B44-2DB1-4571-8682-358039FDB24A-low.png)

        <br />

        <br />

        ![](images/GUID-373735DD-A0E9-48F2-B060-ACF3915CD893-low.png)

        <br />

    3.  Click the **Apply** Button to finish the Library and Driver Configurations:

        <br />

        ![](images/GUID-643FCE2C-0CCA-477C-B92D-3E15678AAEAC-low.png)

        <br />

6.  From the **Device Resources** panel under Libraries drop down list, select: rnbd-rn487x BLE Module.

    <br />

    ![](images/GUID-563CD3C8-EDAD-4984-80B4-41BFEE039C74-low.png)

    <br />

    Add the RNBD-RN487x from Device Resource to Project Resource as below

    <br />

    ![](images/GUID-75D4253D-49BC-487C-BFE3-4BF1438646EC-low.png)

    <br />

    Once RNBD-RN487x driver was loaded to the project resource choose<br /> USART0 as UART Hardware Dependency Selector in which GUI will be expanded<br /> for other configuration setting tab

    <br />

    ![](images/GUID-20FF49C4-9D71-47B5-8F3E-4738F603DB34-low.png)

    <br />

    After the initial setup, Default RNBD-RN487x Configuration populate<br /> as below

    <br />

    ![](images/GUID-9D43A1B3-7FDA-4B5D-AA14-CE0B9291F1DA-low.png)

    <br />

7.  The **Notifications \[MCC\]** tab will appear after the library addition to describe required actions. The library requires the Reset Pin to be connected to the Module, which needs to be assigned to a pin. Select and configure the dependent UART instance under Dependency Selector

    ![](images/GUID-B93C6167-5693-4253-97A7-E08BE3AAACAC-low.png)

8.  Generating Example Applications:

    -   Enable Sample Examples toggle button ---\> Under Reference Example drop Down choose any of the example application as listed below,
        -   Basic Data Exchange
        -   Transparent UART Application

            <br />

            ![](images/GUID-9C01C987-E90E-4616-9832-2719C91199FB-low.png)

            <br />

            **Note:** Any one of the Examples can only be<br /> selected with is common for both RNBD/RN487x

9.  Clock Settings:
    -   From the Project Resource panel under System select Clock Control

        <br />

        ![](images/GUID-7989F070-C0C0-4B02-B4D4-79819F558C54-low.png)

        <br />

    -   Set Internal Oscillator Frequency to 20 MHz system clock, Prescaler **Enable** option must be toggled ON and the **Prescaler Divison** must be set to **2x**.

        <br />

        ![](images/GUID-ADDADFD9-C271-4D6B-98F6-654E6FDB425C-low.png)

        <br />

10. UART Settings:
    -   **AVR**
        -   **NOTE:** The below UART selections are applicable for both Transparent UART Application & Basic Data Exchange \(USART0 & USART1\)

            <br />

            ![](images/GUID-33FE9FF7-FB87-4855-8007-6CB4C82D055B-low.png)

            <br />

            <br />

            ![](images/GUID-BA56BBC1-6C5F-4F58-9E67-466B607AA2DB-low.png)

            <br />

11. Global Interrupt Settings:
    -   Click **Interrupt Manager** under the System settings

        <br />

        ![](images/GUID-D2F566E1-91BB-4BBB-9FF9-7C41DE8D34EE-low.png)

        <br />

        <br />

        ![](images/GUID-71201DF5-485D-4A36-B7D4-89C7F2126FE6-low.png)

        <br />


<br />

# RNBD451 Set Up and Running Example Application<a name="rnbd451-set-up-and-running-example-application"></a>

This topic briefly explains the RNBD451 MPLAB X-IDE Project Setup, Code Generation, Running the Basic Data Exchange and Transparent UART Application with the AVR128DA48 Device.

## RNBD Basic Data Exchange PIN Settings<a name="rnbd-basic-data-exchange-pin-settings"></a>

<br />

-   **AVR128DA48 MCC Configuration - Basic Data Exchange Example.**

    <br />

    ![](images/GUID-A6336B17-992D-4E24-8843-8631FE3DAF30-low.png)

    <br />

-   AVR128DA48 MCC Configuration - Basic Data Exchange Example

    Set **Device Selection** to **RNBD** as shown in image below

    Make sure **Sample Example** toggle button was **Enabled**

    Expand **Reference Examples** and Select **Basic Data Exchange**

    <br />

    ![](images/GUID-8ADE895A-F2B2-4CFC-89A3-71C60A62155F-low.png)

    <br />


<br />

**Note:**

-   Basic Data Exchange Application uses only one instance USART0 for data transfer
-   **Important:**
    -   USART0 RxD and TxD **Uncheck** Start High and Pull-Up checkboxes.
    -   Change Rx and Tx ISC \(Input/Sense configuration\) from Interrupt Disabled but input buffer enabled to **Sense Both Edges** as shown below.

        <br />

        ![](images/GUID-184EEDCA-BCE8-44F7-86F2-3737192B2CC8-low.png)

        <br />

        <br />

        ![](images/GUID-D689B156-8059-457F-A70D-3376836ED3A7-low.png)

        <br />


Configuration for AVR Basic Data Exchange was completed.



## RNBD Transparent UART Application PIN Settings<a name="rnbd-transparent-uart-application-pin-settings"></a>

<br />

-   AVR128DA48 MCC Configuration - Transparent Serial Example

    Set **Device Selection** to **RNBD** as shown in image below

    Make sure **Sample Example** is enabled

    Expand **Reference Examples** and Select **Transparent UART application**

    <br />

    ![](images/GUID-8778600E-033C-4176-85E6-419A1FD0CE2D-low.png)

    <br />

    <br />

    ![](images/GUID-EEF87C36-9DF7-44ED-A556-5F6DC3FEE9FC-low.png)

    <br />

    **Note:**

    -   Transparent UART application uses two instances, USART0 and USART1 for data transfer

    -   Make sure Global Interrupt and USART Module Interrupt Driven was<br /> enabled for both USART0 & USART1.

        <br />

        ![](images/GUID-5ACA33D0-6216-49F1-A17C-41E07D391C89-low.png)

        <br />

        **Important:**Change RxD/TxD ISC \(Input/Sense configuration\) from<br /> Interrupt Disabled but input buffer enabled to Sense Both Edges as<br /> shown below.

        <br />

        ![](images/GUID-53BBBABA-CF2F-4763-9846-2D9BE6462AD0-low.png)

        <br />


<br />

Configuration for AVR Transparent UART was completed.


## RNBD GPIO Based Connection Setup<a name="rnbd-gpio-based-connection-setup"></a>

The RNBD451 device can use BT Status indication 1 and BT Status indication 2 pins to indicate the GPIO connection status. Besides monitoring the connect message in the serial UART prints, this feature is useful when the Host MCU can verify the BT connection status, by monitoring the status indication pins.

**Ble Status Indication Pin Table:**

<br />

![](images/GUID-7D357103-8BE2-4E40-92A3-AC9C96EA66F3-low.png)

<br />

**PIN Mapping Between RNBD BLE Status 1 & 2 Pins with PIC18F47Q10:**

<br />

|Pin Functionality|RNBD Pin Number|PIC18F47Q10 Pin Number|
|-----------------|---------------|----------------------|
|Ble Status Indication 1|PB3|PA6|
|Ble Status Indication 2|PB7|PA5|

<br />

<br />

1.  Selecting GPIO Based Connection for Both Basic Data Exchange & Transparent UART Application

    <br />

    ![](images/GUID-EE67AFCF-019F-4750-B4B0-430572C07CA2-low.png)

    <br />

2.  Pin Selection for Status Indication 1 & 2 Pins under Pin Grid View:

    <br />

    ![](images/GUID-132ED7DC-78B5-46EF-862E-0BDC2CD48EC5-low.png)

    <br />

3.  Pins Setting under Project Resource:

    <br />

    ![](images/GUID-E2015538-2663-4871-9826-03CEF967E574-low.png)

    <br />

    By Default Start High, Pull-Up, checks will be selected for Status Indication Pin 1 and 2

    <br />

    ![](images/GUID-B454FD2A-0F74-48B1-99B1-3FD905B06C7A-low.png)

    <br />

    **Uncheck** the Start High, Pull-Up checks as shown in the below<br /> picture

    Make sure Status Ind1 & Status Ind2 pins are configured with Sense Both<br /> Edges as shown below

    <br />

    ![](images/GUID-92234883-B629-410B-80A4-AB33D78AF844-low.png)

    <br />


<br />


## RNBD Code Generation & Compilation<a name="rnbd-code-generation-&-compilation"></a>

<br />

1.  Click the **Generate** button which will be next to Project Resource

    <br />

    ![](images/GUID-D61FD824-523E-47C1-AF68-7A85F6F8EC98-low.png)

    <br />

2.  Include the header \#include "mcc\_generated\_files/examples/rnbd\_example.h" in **main.c**

3.  Call the function **Example\_Initialized\(\);** in **main\(\)** after **SYSTEM\_Initialize\(\)**.

    <br />

    ![](images/GUID-165F5AC2-11F4-4207-B379-CDD0B1EF4BC8-low.png)

    <br />

4.  Pin Mapping Table between MCU & RNBD Click

    <br />

    |S.no|PIN Functionality|AVR|RNBD Click|
    |----|-----------------|---|----------|
    |1|Receive \(RxD\)|RA1|Tx|
    |2|Transmit \(TxD\)|RA0|Rx|
    |3|BT\_RST|RD7|RST|

    <br />

5.  Connect the development board of your choice and connect the RNBD to the proper slot\(\) as shown below.

    **Note:** Connect RNBD Click to **Slot 1** as shown in the image below:

    <br />

    ![](images/GUID-349DACB9-0CD8-42B7-B586-B39B507961D5-low.png)

    <br />

    **Important:** The slot was decided based on the UART Instances which were configured for this example \(**PIN Mapping between MCU and RNBD Click**\).

6.  Build the Generated Project:

    ![](images/GUID-C5CABE33-147F-452B-BB41-00CB466BAA8D-low.png)

7.  Program to the Board:

    ![](images/GUID-ED80E89C-A13D-4B87-AD9A-0D7AE5E580EB-low.png)


<br />


## RNBD Example1: Running Basic Data Exchange Example Application<a name="rnbd-example1:-running-basic-data-exchange-application"></a>

**Basic Data Exchange:**

This example shows how a MCU can be programmed to transmit data to a smart phone over BLE. Here the MCU device will send Periodic Transmission of a single character when **STREAM\_OPEN** is processed through the Message Handler. This indicates to the MCU and RNBD Module that the application is in a DATA STREAMING mode of operation and can expect to hear data over the BLE connection.<br /><br />\#define DEMO\_PERIODIC\_CHARACTER \(‘1’\) are used in the example can be found \#defined at the top of<br /> rnbd\_example.c.|

![](images/GUID-0C803050-62C5-4E5F-BA14-619E48B5916E-low.png)

1.  Download and Install the Phone Application for demonstration:
    1.  **Microchip Bluetooth Data** by **Microchip** from the [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or from [Google Play Store](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the Phone Application

    ![](images/GUID-10887333-0442-467E-B79B-6A17DB835DB2-low.png)![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)

    <br />

    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    Click on the **BLE Smart** Sub Apps as shown below:

    ![](images/GUID-E19A7964-8190-4C53-8BBA-6370A19C9829-low.png)

3.  The Application scans the area for Bluetooth devices within a range. Look for "RNBD" devices under the scanned list.

    <br />

    ![](images/GUID-E5C513CE-6227-42C1-9DA8-3FA2075112DF-low.png)

    <br />

4.  On selecting the "RNBD" device from the list will be ready to connect with RNBD Module once you click on CONNECT Button

    <br />

    ![](images/GUID-5962533D-A1D4-40DA-8933-A7224139EBA7-low.png)

    <br />

5.  Once connected Microchip Bluetooth App discovers all the services and characteristics supported by the RNBD451 device as shown in the following figure.

    ![](images/GUID-AC320004-8543-404F-806A-4C5E70E09E3B-low.png)

6.  Click on **Microchip Data Service** Option, select the **Microchip Data Characteristic** and Write Notify Indication to receive the data in Mobile App.

    ![](images/GUID-65CA4B07-2C54-4799-A9AE-826FD83B676D-low.png)

7.  Select **Listen for notifications** on the application.
    -   It may be required to "enable notification" access to the app on the<br /> phone.

        Data will begin to Send at a Periodic Rate to the device.

        Data will become visible beneath the Notify/Listen Toggle Option.

        -   Before Enabling the Notify/Indicate Toggle Button:

            ![](images/GUID-C5223277-D33D-4366-8CA4-124D340F0554-low.png)

            After Enabling the<br /> Notify/Indicate Toggle Button Mobile App can read the data<br /> 31\(Hex Value\) which was sent from RNBD Module.

            ![](images/GUID-83D3CD62-CA8C-4C6C-88AF-CA15728E6392-low.png)


This is the END of the Basic Data Exchange Example


## RNBD Example2: Running Transparent UART Example Application<a name="rnbd-example2:-running-transparent-uart-example-application"></a>

<br />

![](images/GUID-8E99A785-AE04-48F7-BBD4-7259DC3B5F9B-low.png)

<br />

<br />

|Transparent Serial:|
|-------------------|
|<br /> This example shows how the data transmitted from a PC serial terminal is written to a smart phone app and the vice versa. The MCU acts as a bridge while passing data between RNDB Module <--- MCU ---> Serial Terminal.<br /><br /> This action will occur when STREAM\_OPEN is processed through the Message Handler. For this example, data typed into the Serial Terminal will appear on the BLE Phone Application,and Data sent from the Application will appear on the Serial Terminal.<br />|

<br />

1.  Download and Install Phone Application for demonstration:
    -   **Microchip Bluetooth Data** by **Microchip** from the [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or from [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the Phone Application

    ![](images/GUID-10887333-0442-467E-B79B-6A17DB835DB2-low.png)

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)

    <br />

    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    After the installation is complete, open the MDB APP and click on **BLE UART** Sub Apps:

    <br />

    ![](images/GUID-D647FF96-CA12-4FA0-A3AA-29C6D6C3DF9D-low.png)

    <br />

3.  Select **PIC32CXBZ** to scan for available devices to connect. The application automatically scans the area for Bluetooth devices within a range. By default, the devices appear as "RNBD451_xxxx"

    <br />

    ![](images/GUID-267AD085-1463-4495-8A62-0EBE87B8C667-low.png)

    <br />

4.  For Transparent Serial only: Open a "Serial Terminal" program such as Tera Term, Realterm, PuTTY, Serial; or similar. Baud Rate will be configured as: 115200

    <br />

    ![](images/GUID-F03D2F6E-4C61-4076-8322-1CD1ACA81EA2-low.png)

    <br />

    <br />

    ![](images/GUID-136BD52C-2CDC-4522-AE36-B7E75249C656-low.png)

    <br />

5.  Once Connected with RNBD451\_0EC4 click on Text Mode at bottom of the settings as shown below to initiate the data transfer.

    <br />

    ![](images/GUID-4A2C616C-FB94-465C-BA58-997E542DBF9C-low.png)

    <br />

    - Check Serial Terminal for the status of the connection.

    <br />

    ![](images/GUID-928146A5-0740-4390-AB9D-31AE1A0A9164-low.png)

    <br />

6.  Enter the text to be transferred from mobile to RNB45x device and click the **Send** button

    <br />

    ![](images/GUID-9C7FDD8B-9541-4543-8746-9C1B98D0E5D0-low.png)

    <br />

    - The data will be received at the RNBD45x side and will be displayed in<br /> serial terminal of RNBD45x

    <br />

    ![](images/GUID-2B7B8379-978D-4B3E-AE7F-F5FE12868EBF-low.png)

    <br />

7.  Type any data on the serial terminal of the RNBD45x to send to the Microchip Bluetooth Data App, which is received and printed on the receive view of the Microchip Bluetooth App.

    <br />

    ![](images/GUID-3D09C58E-D3A8-456B-A347-32BBC09DA06F-low.png)

    <br />

    <br />

    ![](images/GUID-34E4CFD6-6857-479E-93B0-4ACE34EDFD59-low.png)

    <br />


This is the END of the Transparent UART Example

# RN487x Set Up and Running Example<a name="rn487x-set-up-and-running-example"></a>

This topic briefly explains the RN487x MPLAB X-IDE Project Setup, Code Generation, Running the Basic Data Exchange and Transparent UART Application with the AVR128DA48 Device.

## RN487x Basic Data Exchange PIN Settings<a name="rn487x-basic-data-exchange-pin-settings"></a>

<br />

-   **AVR128DA48 MCC Configuration - Basic Data Exchange Example**

    <br />

    ![](images/GUID-A6336B17-992D-4E24-8843-8631FE3DAF30-low.png)

    <br />

    Set **Device Selection** to **RN487x** as shown in below image
    <br /><br />Make sure **Sample Example** Toggle button was **Enabled**

    Expand **Reference Examples** and Select **Basic Data Exchange**

    <br />

    ![](images/GUID-41FE8A10-5BA7-4042-909E-923EA51472F7-low.png)

    <br />


<br />

**Note:**

-   Basic Data Exchange Application uses only one instance of **USART0** for data transfer
-   **Important:**
    -   USART0 RxD and TxD **Uncheck** Start High and Pull-up checkboxes.
    -   Change Rx and Tx ISC \(Input/Sense configuration\) from Interrupt Disabled but input buffer enabled to **Sense Both Edges** as shown below.

        <br />

        ![](images/GUID-D689B156-8059-457F-A70D-3376836ED3A7-low.png)

        <br />

        <br />

        ![](images/GUID-184EEDCA-BCE8-44F7-86F2-3737192B2CC8-low.png)

        <br />


Configuration for AVR Basic Data Exchange was completed.


## RN487x Transparent UART Application PIN Settings<a name="rn487x-transparent-uart-application-pin-settings"></a>

<br />

-   AVR128DA48 MCC Configuration - Transparent Serial Example

    Set **Device Selection** to **RN487x** as shown in below image

    Make sure **Sample Example** Toggle button was **Enabled**

    Expand **Reference Examples** and Select **Transparent UART application**

    <br />

    ![](images/GUID-71A42A1A-8E94-47B4-BE6C-B9FF92D2048E-low.png)

    <br />

    <br />

    ![](images/GUID-EEF87C36-9DF7-44ED-A556-5F6DC3FEE9FC-low.png)

    <br />


<br />

**Note:**

-   Transparent UART Application uses USART0 and USART1 for data transfer

-   Make sure Global Interrupt and USART Module Interrupt Driven was enabled for both **USART0 and USART1**.

    <br />

    ![](images/GUID-5ACA33D0-6216-49F1-A17C-41E07D391C89-low.png)

    <br />

    **Important:** Change RxD and TxD ISC \(Input/Sense configuration\) from **Interrupt Disabled but input buffer enabled** to **Sense Both Edges** as shown above.

    <br />

    ![](images/GUID-53BBBABA-CF2F-4763-9846-2D9BE6462AD0-low.png)

    <br />


Configuration for AVR Transparent UART was completed.


## RN487x Code Generation & Compilation<a name="rn487x-code-generation-&-compilation"></a>

<br />

1.  Click the **Generate** button which will be next to Project Resource

    <br />

    ![](images/GUID-2D18886B-77EB-4E2D-823C-79E1585D3E03-low.png)

    <br />

2.  Include the header \#include "mcc\_generated\_files/examples/rn487x\_example.h" in **main.c**

3.  Call the function **Example\_Initialized\(\);** in **main\(\)** after **SYSTEM\_Initialize\(\)**

    <br />

    ![](images/GUID-70819D0B-CB37-4866-B433-1866B91B9F13-low.png)

    <br />

4.  Pin Mapping Table between MCU & RN4871 Click

    <br />

    |S.no|PIN Functionality|AVR|RN487x Click|
    |----|-----------------|---|------------|
    |1|Receive \(RxD\)|RA1|Tx|
    |2|Transmit \(TxD\)|RA0|Rx|
    |3|BT\_RST|RD7|RST|

    <br />

5.  Connect the development board of your choice and connect the RN487x to the proper slot\(\) as shown below.

    **Note:** Connect RN4871 Click to **Slot 1** as shown in below image

    <br />

    ![](images/GUID-0C54F6CA-B754-49CA-AD3D-618A3786D559-low.png)

    <br />

    **Important:** The slot was decided based on the UART Instances which were configured for this example (**PIN Mapping between MCU and RN4871**).

6.  Build the Generated Project:

    ![](images/GUID-C5CABE33-147F-452B-BB41-00CB466BAA8D-low.png)

7.  Program to the Board:

    ![](images/GUID-ED80E89C-A13D-4B87-AD9A-0D7AE5E580EB-low.png)


<br />


## RN487x Example1: Running Basic Data Exchange Example Application<a name="rn487x-example1:-running-basic-data-exchange-example-application"></a>

**Basic Data Exchange:**

This example shows how a MCU can be programmed to transmit data to a smart phone over BLE. Here the MCU device will send Periodic Transmission of a single character when **STREAM\_OPEN** is processed through the Message Handler. This indicates to the MCU and RN487x Module that the application is in a DATA STREAMING mode<br /> of operation; and can expect to hear data over the BLE connection.

\#define DEMO\_PERIODIC\_TRANSMIT\_COUNT\(10000\)\#define DEMO\_PERIODIC\_CHARACTER \(‘1’\) are used in the example can be found \#defined at the top of rnbd\_example.c.

![](images/GUID-0C803050-62C5-4E5F-BA14-619E48B5916E-low.png)

1.  Download and Install Phone Application for demonstration:
    1.  **Microchip Bluetooth Data** by **Microchip** from the [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or from [Google Play Store](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the Phone Application

    ![](images/GUID-10887333-0442-467E-B79B-6A17DB835DB2-low.png)![](GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)

    <br />

    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    Click the **BLE Smart** Sub Apps as shown below:

    ![](images/GUID-E19A7964-8190-4C53-8BBA-6370A19C9829-low.png)

3.  The Application scans the area for Bluetooth devices within a range. Look for "RN487x" devices under the scanned list.

    <br />

    ![](images/GUID-F9008121-7D40-4680-89B2-F595E314CB17-low.png)

    <br />

4.  On selecting the "RN487x" device from the list will be ready to connect with RNBD Module once you click on CONNECT Button

    <br />

    ![](images/GUID-EC0D19FF-B0F3-4D44-BD3F-D99B9FEFC62D-low.png)

    <br />

5.  Once connected, the Microchip Bluetooth App discovers all the services and characteristics supported by the RN487x device, as shown in the following figure.

    <br />

    ![](images/GUID-9ED50565-2513-482E-BE6A-D118C539C56D-low.png)

    <br />

6.  Click on **Microchip Data Service** Option, select **Microchip Data Characteristic** and Write Notify Indication to receive the data in the Mobile App.

    <br />

    ![](images/GUID-57D1EBD2-972B-4152-AAC3-D5C98DE6E4C6-low.png)

    <br />

7.  Select **Listen for notifications** on the application.
    -   It may be required to "enable notification" access to the app on the<br /> phone.

        Data will begin to Send at a Periodic Rate to the device.

        Data will become visible beneath the Notify/Listen Toggle Option.

        -   Before Enabling the Notify/Indicate Toggle Button:

            <br />

            ![](images/GUID-3780F6BB-6198-4179-A5C0-58042FC83EAE-low.png)

            <br />

            After Enabling the Notify/Indicate Toggle Button Mobile<br /> App can read the data 31\(Hex Value\) which was sent from<br /> RN487x Module.

            ![](images/GUID-9A94A4DF-BEB9-48A5-B958-CDDC2C296ED7-low.png)


This is the END of the Basic Data Exchange Example

## RN487x Example2: Running Transparent UART Example Application<a name="rn487x-example2:-running-transparent-uart-example-application"></a>

<br />

![](images/GUID-8E99A785-AE04-48F7-BBD4-7259DC3B5F9B-low.png)

<br />

<br />

|Transparent Serial:|
|-------------------|
|<br /> This example shows how the data transmitted from a PC serial terminal is written to a smart phone app and the vice versa. The MCU acts as a bridge while passing data between RNDB Module <--- MCU ---> Serial Terminal.<br /><br /> This action will occur when STREAM\_OPEN is processed through the Message Handler. For this example, data typed into the Serial Terminal will appear on the BLE Phone Application,and Data sent from the Application will appear on the Serial Terminal.<br />|

<br />

1.  Download and Install Phone Application for demonstration:
    -   **Microchip Bluetooth Data** by **Microchip** from the [App Store](https://apps.apple.com/us/app/microchip-bluetooth-data/id1319166097) or from [Google Play](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).
2.  Launch the Phone Application

    ![](images/GUID-10887333-0442-467E-B79B-6A17DB835DB2-low.png)

    ![](images/GUID-7271A2D0-99A8-41F4-BB4C-269F2F83820C-low.png)

    <br />

    ![](images/GUID-8A9EE9CE-AA92-4648-8364-09987F2E0526-low.png)

    <br />

    After the installation is complete, open the MBD and click **BLE UART** Sub Apps:

    <br />

    ![](images/GUID-D647FF96-CA12-4FA0-A3AA-29C6D6C3DF9D-low.png)

    <br />

3.  On Selecting BM70 scan for available devices to connect.

    <br />

    ![](images/GUID-6B7B0F61-A3A7-478C-A253-06E561E1313F-low.png)

    <br />

    Click on the below Scan image to scan the Nearby "RN487x-xxxx"

    <br />

    ![](images/GUID-C7AB4C05-260C-4C69-AF6D-298B9E02F302-low.png)

    <br />

    The Application will automatically scan the area for Bluetooth devices within<br /> a range. By default, the device should appear as "RN487x-xxxx"

    <br />

    ![](images/GUID-C36CEB36-58F8-4DAD-8800-358F70E56B66-low.png)

    <br />

4.  For Transparent Serial only: Open a "Serial Terminal" Program such as Tera Term, Realterm, PuTTY, Serial; or similar. Baud Rate will be configured as: 115200

    <br />

    ![](images/GUID-B18B65D8-9AA3-478A-A674-DEB871E086CA-low.png)

    <br />

    <br />

    ![](images/GUID-BC559EA4-E40C-4332-9EF3-4BA8F919AFE6-low.png)

    <br />

5.  Once Connected with RN487x-xxxx click **Transfer data to device** as shown below to initiate the data transfer.

    <br />

    ![](images/GUID-B3297905-2011-452F-8141-887853ECF6AD-low.png)

    <br />

    - Check Serial Terminal for the status of the connection.

    <br />

    ![](images/GUID-DF2150F8-89DC-4876-B351-D59A58E34272-low.png)

    <br />

6.  Enter the text to be transferred from mobile to RN487x-xxxx device and click **Send**

    <br />

    ![](images/GUID-B8693063-53D6-4080-AD8C-3906E2698F6C-low.png)

    <br />

    - The data will be received at the RN487x-xxxx side and will be displayed in<br /> serial terminal of RNBD45x

    <br />

    ![](images/GUID-E0106617-7CA8-4508-AE5A-278D8E8B737B-low.png)

    <br />

7.  Type any data on the serial terminal of the RN487x-xxxx to send to the Microchip Bluetooth Data App, which is received and printed on the receive view of the Microchip Bluetooth App.

    <br />

    ![](images/GUID-CEC4E31B-D080-4A65-8350-81D62D130FC9-low.png)

    <br />

    <br />

    ![](images/GUID-E985EFE1-6B23-4A76-86DE-E349AF41D0F1-low.png)

    <br />



# Summary<a name="summary"></a>

**Command, Data Communication with Asynchronized Message Processing:**

This driver contains, at its' core, the inherent code capability of distinguishing<br /> between **Message** exchange and **Data** exchange between the connected MCU and<br /> Module devices.

The library supplies all required Application Programming Interfaces \(APIs\) required to<br /> create functional

implementation of operation a BLE connected end-device.

Through the MCC configuration the physical connection of the \(3\) required pins can be<br /> selected through the GUI.

These are the \(2\) UART pins used for communication, and control of the **RST\_N**<br /> connected to the RNBD Module.

Additionally; this Library allows for extension of Module pin behaviors through the<br /> simple RNBD Module object

interface; where any device/project specific instantiations exist.<br /> **rnbd\_interface.c/h**/**rn487x\_interface.c/h**

A brief description of the Interface, and object extension is described below:

iRNBD\_FunctionPtrs\_t is a typedef struct which can be found in<br /> **rnbd\_interface.h**/**rn487x\_interface.h** and consist of \(9\) function<br /> pointers. In the **rnbd\_interface.c**/**rn487x\_interface.c**, the concrete<br /> creation of RNBD as an object is instantiated. Within<br /> **rnbd\_interface.c**/**rn487x\_interface.c** are the **private static**<br /> implementations of desired behavior. In some cases, such as DELAY or UART, the<br /> supporting behavior is supplied through another supporting library module. When<br /> applicable ‘inline’ has been used to reduce stack depth overhead.

<br />

![](images/GUID-2B41A010-DEC4-4198-9245-049150500274-low.png)

<br />

<br />

![](images/GUID-08351B32-7A45-4F07-91BF-66534BFE5482-low.png)

<br />

The driver library itself should not require any modifications or injections by the user;<br /> unless to expand upon the supported command implementations **rnbd.c/h**

**Configurable Module Hardware Requirement\(s\):**

A single UART instance used for communication between MCU and Module:

<br />

![](images/GUID-230E3567-ED26-4E33-92AA-A094AC3AC262-low.png)

<br />

The Library allows for configuration of \(3\) Pins associated with support features<br /> extended through the Driver Interface. Only \(1\) Pin is required by the RNBD Modules for<br /> operation; this is the modules **RESET** pin.

<br />

![](images/GUID-E87D4AC0-B045-451E-A188-EFD3FB82F70E-low.png)

<br />

<br />

|Library Name: Output\(s\)|Module: Input\(s\)|Description|Module Physical Defaults|
|-------------------------|------------------|-----------|------------------------|
|BT\_MODE|P2\_0|<br /> 1 : Application Mode<br /> 0 : Test Mode/Flash Update/EEPROM Configuration<br />|Active-Low, Internal Pull-High|
|BT\_RST|RST\_N|Module Reset|Active-Low, Internal Pull-High|
|BT\_RX\_IND|P3\_3|Configured as UART RX Indication pin|Active-Low|

<br />
