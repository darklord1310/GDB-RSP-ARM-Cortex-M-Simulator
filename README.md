GDB Server and ARM Simulator
============================
This project allow you to use the gdbserver and ARM simulator with CoIDE application. Description below is the explanation for the available `rake` commands using gitbash to release and depoy the gdbserver and coflash then debug using the ARM simulator. (Please make sure the CoIDE is installed in C: drive directory)

Commands
========
To view all available commands issue:
```
rake -T
```
The new commands added by `scripts/gdbserver.rb` are:
```
rake gdbserver:deploy
rake gdbserver:release
rake gdbserver:revert
```

Deploy
======
To `build and deploy` gdbserver + coflash into the CoIDE bin file directory.
```
rake gdbserver:deploy
```

Release
=======
To build gdbserver `release` version, type:
```
rake gdbserver:release
```

Revert
======
To `revert` the deploy gdbserver and coflash to default CoIDE gdbserver and coflash, type:
```
rake gdbserver:revert
```
