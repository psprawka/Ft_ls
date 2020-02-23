# Ft_ls - my own file lister 🗂

Ft_ls is a first project system (UNIX) branch at 42 - its purpose is to get familiar with filesystem, as well as handling files and directories is C via recoding well known terminal command, `ls`. The bevhavior of `ft_ls` must remain the same as standard `ls` funtion, but the format display may differ. 
</br></br>

## Ft_ls - which flags are handled?
Ft_ls handles a number of various flags, all of them are listed below:
* `-a` Show hidden. **[MANDATORY]**
* `-i` Show serial number (inode number).
* `-l` List in long format. **[MANDATORY]**
* `-r` Reverse sort. **[MANDATORY]**
* `-t` Sort by time of last modification. **[MANDATORY]**
* `-A` List all entries except for . and ...
* `-G` Coloured output.
* `-R` Recursively search directories **[MANDATORY]**
* `-1` Force output to be one entry per line.
</br></br>

## How to run Ft_ls?
```
git clone hhttps://github.com/psprawka/Ft_ls.git 42SV_Ft_ls
cd 42SV_Ft_ls
make
./ft_ls [flags] [arguments]
```
