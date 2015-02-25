Start a local Spark cluster is as easy as:

```
$ vagrant up
$ vagrant ssh
```

Run some examples
```
$ cd /spark-1.2.1-bin-hadoop2.4
$ ./bin/run-example SparkPi
$ ./bin/run-example JavaWordCount README.md
```

Start spark shell, view jobs at localhost:4040
```
$ ./bin/spark-shell
```
