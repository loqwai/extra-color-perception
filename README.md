# What is this?

Do you have a favorite color?
Do you like mixing colors?
Do you like to go to music festivals?
Do you like to go to music festivals and mix colors?
...and other Copilot questions.

This project attempts to create led pendants for music festivals that change depending on how physically close you are to your friends.

Each device has a color, and that color will change and mix with the colors of other devices that are close to it.


As of commit #155163af07403403453ad7045e9d844b3a83da11 we have a working prototype that can be used to test the concept.
However, the physical hardware is not finalized yet. Below is a list of parts we are considering using.

## Parts

* [Small ESP32 Dev Board](https://www.aliexpress.us/item/3256804680216365.html?spm=a2g0o.order_detail.order_detail_item.10.3693f19cRx3GT2&gatewayAdapt=glo2usa&_randl_shipto=US)
  - note: this is a single-core board, which I ordered by mistake. This will likely reduce the responsiveness of the device. But it's small!
* [WS8212B LED 'shield'](https://www.aliexpress.us/item/3256804745105814.html?spm=a2g0o.order_detail.order_detail_item.7.3693f19cRx3GT2&gatewayAdapt=glo2usa&_randl_shipto=US)
  - note: this apparently is out of stock now. But it should mount to the above esp32 easily.
* [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)
