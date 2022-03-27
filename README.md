# recursive word count
wc command but for directories

## selecting path 
```
$ ./bin/rwc.out -d "./bin"
```
![example](images/only_bin.png?raw=True "hello")

## blacklisting and whitelisting
```
$ ./bin/rwc.out -w "*.[ch]"
```
![example](images/whitelist.png?raw=True "hello")

```
$ ./bin/rwc.out -w "*.[ch]"
```
![example](images/blacklist.png?raw=True "hello")
