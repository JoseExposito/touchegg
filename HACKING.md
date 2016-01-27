
### Coding Style: ###

If you want to send a patch please follow the Qt/KDE coding style:
    
    http://developer.qt.nokia.com/wiki/Qt_Coding_Style
    http://techbase.kde.org/Policies/Kdelibs_Coding_Style

Remember that you can use astyle to indent the code automatically:

```
astyle --style=k/r --indent=spaces=4 --convert-tabs \
       --pad-header --unpad-paren \
       --indent-namespaces --keep-one-line-blocks --align-pointer=name \
       --max-instatement-indent=8 --indent-col1-comments \
       --suffix=none \
       `find -type f -name '*.cpp'` `find -type f -name '*.h'`
```

### Understanding the Code: ###

All the code is documented with Doxygen. If want to see this documentation in html format, go to the ./documentation folder and run:

```
$ doxygen doxyfile
```

The ./documentation/html/index.html file is a good place to begin.

Touchégg makes an intensive use of Qt and uTouch. Reading this can help:

    http://doc.qt.io/
    http://people.canonical.com/~stephenwebb/geis-v2-api/


### Contact the developer: ###

If you want to report a bug, you can do it in the official bug tracker:

    https://github.com/JoseExposito/touchegg/issues

For other questions, talk about the weather or invite me to a beer :beer: you can send me an email to jose.exposito89@gmail.com

Happy coding!
