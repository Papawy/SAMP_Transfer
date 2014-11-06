SAMP_Transfer
=============

SA-MP plugin / mod to share mods between server and client without any interaction from the client.

=== CLIENT ===

  With this mod, server mods are downloaded automatically when you join them. They are placed in your SAMP_addons folder.
  
  Currently, to avoid malwares, the downloadable files can have all GTA San Andreas standard extensions, but CLEO scripts will    be added soon. Neither .dll files nor .asi files will be authorized to download, for evident reasons that I guess it's not      necessar to share there.
  
  Technical :
    The .asi file is the loader : it contains the client mod, which will establish the connection between the server the player     connects to and the player himself. It will receive FTP infos and which files to download. 
    After connected, the client checks which files must be downloaded and then will check if those files have already been          downloaded in the SAMP_addons folder. If so, then the game will start. Else, the client will download the mods (and thus the     speed will depend of the client's connection), restarting the game and then launching it with the mods.
    Once the game is closed, original client files are put pack and downloaded files will be moved to the SAMP_addons folder.
    
    So the client can't see anything !
  
