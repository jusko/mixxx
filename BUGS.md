* Segfaults with the following in a skin:
```xml
<DefaultMark>
  ...
  <Pixmap>not_present_in_file_system.png</Pixmap>
  ...
</DefaultMark>
```

The pixmap should be checked to exist
