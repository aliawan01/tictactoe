@echo off

if not exist bin mkdir bin
pushd bin
cl ..\main.c /Zi /link /subsystem:console 
popd
