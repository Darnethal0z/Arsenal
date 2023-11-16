# The Arsenal library documentation source code

---

This folder container the Arsenal documentation source code, based on manpages.

## Writing the documentation

The build process described below is essentially replacing some specific values in the files from the `manpages` folder with values specified in the `build.py` python script : 

- `<version>` will be replaced by the `VERSION` variable specified in `build.py`
- `<date>` will be replaced by the actual date, using the `datetime` python module.

## Build the documentation

Execute the `build.py` python script to build the manual pages : 

```
$ python3 build.py
```

You'll find every GZip result files in the `build` folder, copy them on the `/usr/share/man/man3/` folder in order to be accessible by `man`.

After that, you can execute : 

```
$ man arsenal
```

To get the main Arsenal documentation page with every functions and usage notices.

## Consulting the documentation

The Arsenal library documentation is divided by topic sections : 

- `arsenal.3` : This section covers the main informations, usage notes and functions references of the Arsenal library ;
- `arsenal-display.3` : This section covers the stylized test display utility feature ;
- `arsenal-networking.3` : This section covers the client / server socket features ;
- `arsenal-random.3` : This section covers the random string feature ;
- `arsenal-string.3` : This section covers the string manipulations features ;
- `arsenal-user-input.3` : This section covers the user input features ;

Do `$ man arsenal-<section_name>` to get the corrseponding man page.