# Platformio basics

## Install boards

```bash
platformio platform install atmelavr
platformio platform install espressif32
```

## Install libs

```bash
platformio lib install 
```

## Project init

```bash
platformio init --board esp32dev 
platformio lib list
```


## Compile and load

```bash
platformio run -t upload -t monitor
```



