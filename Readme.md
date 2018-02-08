# ark

### Description
ark is Arch user Repository Kommander a simple utility to search,download, and install packages from Arch's AUR, including dependencies.

### Dependencies
jansson/libjansson
libcurl

### Usage
```
ark -s/--search <keywords>  #searches for keywords in name and description
ark -d/--download <pkgname> #pass -d twice for dependencies, downloads package <pkgname>
ark -q/--query <keywords>   #queries ark's database not pacmans (use -qp for pacman db's)
ark -l/--literal            #switches from name-desc to just name so only packages with keyword in the name show up
ark -h/--help               #this help message
ark -S/--sync               #Syncs the local search DB
ark -c/--config <opt-path>  #alternate path for config
```

