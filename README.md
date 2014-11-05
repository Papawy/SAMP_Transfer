SAMP_Transfer
=============

SA-MP plugin / mod to share mods between server and client

=== CLIENT ===

  With this mod, you download automatically mods from servers. They are placed in your SAMP_addons folder.
  
  Mods can be all GTA standart files (CLEO scripts will be added soon).
  
  Technical :
    The .asi file connect to the server plugin. Plugin send ftp ids and needed files to client.
    After that, client check needed files : 
      if there is files in SAMP_addons folder, the mod replace files and the game start.
      if not the client download files and do the standart program.
      
      
  After the game execution, original files are replaced etc.
  
  So, the client doesn't see anything !  
  
