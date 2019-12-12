@echo off
for %%x in (
  micaComms
  micaCommon
  INA226
  uartApi
) do (
  IF EXIST %%x.h DEL /F %%x.h
  IF EXIST %%x.cpp DEL /F %%x.cpp
  IF EXIST ..\..\include\%%x.h (
    mklink %%x.h ..\..\include\%%x.h
  )
  IF EXIST ..\..\src\%%x.c (
    mklink %%x.cpp ..\..\src\%%x.c
  ) ELSE (
    IF EXIST ..\..\src\%%x.cpp (
      mklink %%x.cpp ..\..\src\%%x.cpp
    )
  )
)

for %%x in (
  Arduino_i2c
  Arduino_serial
) do (
  IF EXIST %%x.h DEL /F %%x.h
  IF EXIST %%x.cpp DEL /F %%x.cpp
  IF EXIST ..\..\Arduino\%%x.h (
    mklink %%x.h ..\..\Arduino\%%x.h
  )
  IF EXIST ..\..\Arduino\%%x.c (
    mklink %%x.cpp ..\..\Arduino\%%x.c
  ) ELSE (
    IF EXIST ..\..\Arduino\%%x.cpp (
      mklink %%x.cpp ..\..\Arduino\%%x.cpp
    )
  )
)
