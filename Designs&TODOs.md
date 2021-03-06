Common
======

Synchronizable Password Keeper (rust)
-----------
* Logger
* Log reader
* Log writer
* Conflict resolution
* Encryption

Password Manager (html+coffeescript)
------------
* HTML based frontend
* Insert a record
* Update a record
* Remove a record
* Copy password to clipboard (**risk**)
* Show password on Security Display
* Create a shortcut to start some applications that can input username/password by command line like QQ.

Client
======

Local Password Service (rust)
----------
* Restful API
* Link to Synchronizable Password Keeper (using offline)
* Synchronize to server
* Local APIs

Security Input/Display (c++)
-----------
(belongs to Local Password Service)
* Font to bitmap converter
* Linux frontend
* Windows frontend (after 7/23)
* Android frontend (Considering)

Local Password Manager Provider (html+coffeescript)
------------
* Link to Local Password Service
* CRUD interface

Password Manager Startup (atom)
------------
* Load Local Password Manager Provider and Password Manager.

Shortcut Starter (c++)
-------------
* Link to Local Password Service
* Run application with given configuration
* Python script support


Server
======

Remote Password Service (rust)
-------------
* Download/Upload API (may fail if conflict happens)
* Link to Synchronizable Password Keeper

Remote Password Manager Provider (html+coffeescript) (Considering)
------------
* Link to Remote Password Service
* CRUD interface
* Local (browser based) APIs

Remote Password Manager Startup (github pages) (Considering)
------------
* Load Remote Password Manager Provider and Password Manager.
* Only Create, Update and Copy are allowed.

Keys
=====
Password Encryption Key (given by user when creating db)
--------------
* Hashed and storaged with only root(administrator) can read, like windows SAM file.
* Input into Security Input
* Local and Remote use the same Encryption Key.
* Two database with same key can be merged.

Local Manager Key (given by user)
--------------
* Hashed and storaged with only root(administrator) can read, like windows SAM file.
* Used for Create, Update, List and Remove.
* Input into Security Input when using Password Manager.
* Query one password needn't this key.

Remote Certification
--------------
* Storaged public key on local, private key on server.
* Used for create security connection.

Remote Encryption Key
----------------
* Used to encrypt HTTP Request when downloading and uploading.
* Use only once.
* Generated by server.

Log File
=========

Header
--------
0-3: 0xccfffccf

4-7: version

8-27: salt

28-47: sha1

48-51: size

52-55: length

56-64: 0xff

Record
--------
0-3: length

4-7: size

Column1, Column2, Column3, ...

Column
---------
0-3: length

Content


Database
=======
```
Action(Update and Remove), TimeStamp

if action == Update then
  Domain, Username(encriped by PEK), Password(encriped by PEK)
```
