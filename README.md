(0 day) Deletes any file. Bypasses previous patch.
These are functional and live with current versions

Writup: https://nathan2.com/files/iobit.pdf
Iobit did not pay me, more info here:  https://nathan2.com/posts/iobit/ 


I created this without knowing about the previous issues with this same vulnerability. This is a new CVE that bypasses the patch that IOBit tried to do. The patch was so bad, read my blog linked in the top right to see.


Run like so:
```
.\poc.exe "C:\filepath.exe"
```

Attached is a DLL sideloading process that functions if you would like to delete the ProductNews2.dll in iobit's program files. If not, just run the program.

The program is called proxied.cpp and is in the root of this repo. 

“C:\Program Files (x86)\IObit\IObit Malware Fighter\ProductNews2.dll” is the location of that dll. you must delete it.

Then compile the code in proxied.cpp as x86, and place it in your systems path, located at `C:\users\username\Appdata\local\Microsoft\WindowsApps`
by default. Name the dll ProductNews2. You can change the command to anything. Make sure the temporary dll included in releases is also added to path. 

The temporary dll is included in releases. It was generated with https://github.com/Flangvik/SharpDllProxy
