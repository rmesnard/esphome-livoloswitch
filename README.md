## ESPHome Custom Component for Livolo Switch with RF 433mhz option.

With this custom component you can drive LIVOLO Switch ( with RF 433 option ) from ESPHome


## Hardware 

For my test i used a Sonoff RF with the hardware hack (see references). But the component should work with the other Rf 433mhz transmitter supported by ESPHome.

## Configs

The component itself to add to ESPHome config directory. Notice that i used a subdirectory "custom" in my settings :

- livoloswitch.h

A config example , where i set 20 switchs: 

- livolo.yaml

Livolo switch work with a code composed in two parts : 
- the Remote ID : a number coded on 2 bytes ( Range 1 - 65500 ) with binary odd parity.
  Working value :  6400, 7400, 6550, 8500, 19303, 10550.
```
	6400 : ‭0001100100000000‬ -> 3 (1)  = odd
	7400 : ‭0001110011101000‬ -> 7 (1)  = odd
	8500 : ‭0010000100110100‬ -> 5 (1)  = odd 
	..
```
- the Button ID : 10 possible values :  0,12,24,40,48,72,80,96,108,120

The component syntax (in the lambda code ) is : 
```
auto xxx = new LivoloSwitch(PIN_TO_RF_EMMITER,REMOTE_ID,BUTTON_ID);
```
This component also work with the core component RF Transmitter enabled, sharing the same PIN.

## Tech tips

Enable the ESPHome webserver to create a webpage that you can use quickly to learn the remote code to your switches.

```
web_server:
  port: 80
```

## References

[ESPHome](https://esphome.io/)

[Forum Topic](https://community.home-assistant.io/t/livolo-switch-rf-433-custom-component/167378)

[Livolo Remote ID Explained](https://www.tyjtyj.com/livolo.php)

[Livolo Library](https://github.com/bitlinker/LivoloTx)

[Sonoff RF Hardware Hack](https://github.com/xoseperez/espurna/wiki/Hardware-Itead-Sonoff-RF-Bridge---Direct-Hack)

[Livolo RF Switch](https://www.banggood.com/Livolo-Black-Glass-Touch-Panel-Intermediate-Remote-EU-Switch-VL-C701SR-12-p-974101.html?rmmds=search&cur_warehouse=CN)

[Livolo RF Switch France](https://fr.aliexpress.com/item/513111555.html?spm=a2g0w.12010612.8148356.16.4c882289QWIUb2)
