# 2048 on Arduino

Character set:
https://www.trash.net/~luethi/microchip/datasheets/lcd/lcd_data_sheets.html

Character creator:
https://chareditor.com/

Testing structure:

This shows how to force compilation of source code alongside test code:
https://docs.platformio.org/en/latest/advanced/unit-testing/structure/shared-code.html

And to avoid specific code being compiled while pio testing:
```c
#ifndef PIO_UNIT_TESTING
#endif
```

I suspect you can also provide a custom define. Hopefully as things might need adjusting
if running on the remote vs locally except

To specify a custom testing command
```ini
test_testing_command =
  ${platformio.build_dir}/${this.__env__}/program
  arg1
  --option2
  option2_value
```

Really useful example:
https://github.com/platformio/platformio-examples/blob/develop/unit-testing/calculator/test/test_common/test_calculator.cpp

For Arduino identification:
```
#ifdef ARDUINO
#endif
```


Looking for simulator example? Try this:
https://docs.platformio.org/en/latest/advanced/unit-testing/simulators/simavr.html

It must print results to stdout, so you might have to bridge?

