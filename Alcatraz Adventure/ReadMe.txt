Alcatraz
Creator: Group 3
Version: 1.5
Language: C/C++
Compiler: Visual Studio 2008 Professional (Visual C++)
Date: May 20th, 2009

About:
Alcatraz is a text-based adventure game. The player takes on the role of a
Specialist on a mission to stop renegrade forces from destorying San
Francisco bay. The player may combat enemies and collect items found on the
island of Alcatraz. There are also thiefs present in the prison that will 
rob the player, taking items out of their inventory.

Installation:
This game may be launched by running (double clicking) the executable (Alcatraz.exe), or by
launching inside command prompt "...Alcatraz_V1-5\Alcatraz\Alcatraz.exe".
Note: The game won't find the bute file unless the bute file (rooms.txt) is located
in your current directory (especially true in MS-CMD).

Known Bugs:
The bute file (rooms.txt) contains some typos.
(Y/N) Prompts like "Do you want to sneak over to the treasure?" will often take 'Y'/'y' or 'anything' as an answer.
Y or yes, will perform the desired action while anything else will be interpreted as 'n' or no.
Monsters are very under-skilled.

Version History:
1.0:
The basis of the game is ready.

1.1:
The game is complete, start-to-finish. Minor bugs in code and the bute file
are present.

1.2:
Minor bugs in last verison are resolved. The Game output is neatly done.
An in-game editting mode is fully implemented and functional.

1.3:
Game music is implemented. The Game's previous bugs are resolved. Format is
re-done and neat. Credits have been added to the end of the game. The release
build of the game experiences crashing problems where the program terminates
after gathering the player's name, weapon, and armor; however this only happens
when the bute file (rooms.txt) is not found. This will be resolved
in later versions. The bute file contains some typos that will be corrected in
later versions or with a new bute file.

1.4:
The ability for the player to toss chosen items out of their inventory is partially working.
Battle mode command {R:Retreat and X:Exit} are functioning correctly.
Game art and animation development begins.

1.4.1:
The ability for the player to remove designated inventory items is fully functional.
Additional game credits added.
New game title screen.
Minor game output style changes.

1.4.2:
Fixed inventory bug, where you could not manage your inventory after getting 5 items.
Re-done the game's interface format.
Added ability for user's to upload their own game mods, finally!

1.4.3:
Full definition and implementation of the friendly agent. Various changes to game objects.
Player now has money and asscessor/mutators for money. Treasure object was re-coded in a few
places, no major changes. A few other minor code changes to accomodate for the Agent and the 
planned possibility of rooms being able to store multiple items.

1.4.4 (Beta release):
Almost complete player-agent business transaction functionality.

1.4.4
Player-agent transaction are 90% accurate.
Ability for rooms to store multiple items is 80% functional.

1.4.5
Rooms' multiple item storage is working. Players may drop items in a room.
Player-Agent transactions are functional. Players may view their inventory with I.

1.4.6
Very similiar to 1.4.5; however, user friendliness was an objective in the verison.
The Player may check their health, enemy's health, and inventory. Also the player's money
is displayed with the inventory. When the game ends it should nicely output the player's
stats and money earned during the game.

1.4.7
Fixed some 1.4.6 bugs. Added H for help command

1.4.8
Fixed ability for the game to accurate load from a mod.txt file so that the user may load a modified
game. Game music is finished. Fixed a minor inventory bug

1.5 (beta)
Nothing special, used in a small testing phase

1.5
Fixed room dropped item vanishing bug. A sample 'mod.txt' is provided to give people an idea of
how to make a mod for this game.

Future Releases:
Objective Items (computer chips) that will be required to be collected in order to finish the game.
More implementation of graphics from Artists.
=================================================================================
Alcatraz (c.) 2009
Source Code is Licensed to you under General Public License
Group 3 is Justin McKennon, Josh LaClair, Barry Gaffey, 
Adam Houghton, and Craig Nathan