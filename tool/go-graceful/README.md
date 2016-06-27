#### Graceful terminationn of a golang server

Run server with:
```shell
go get gopkg.in/tylerb/graceful.v1
go run main.go
```

The server is configured with graceful termination period of 30s. In another terminal, run:

```shell
curl 'http://localhost:3001/sleep/?duration=10s
```

Switch to the other terminal, kill the server with `ctrl-c`. The server will continue running
until the sleep request is done. At the same time, the server will reject any new connection;
so if we try to curl again, we'll get `connection refused`.
