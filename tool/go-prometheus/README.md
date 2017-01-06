# Prometheus go client and usage example

## Prometheus go client

See example.go

## Prometheus usage

### Run three process for prometheus to scrape

```
go build random.go
./random --listen-address localhost:8080 &
./random --listen-address localhost:8081 &
./random --listen-address localhost:8082 &
```

### Build prometheus

```
cd $GOPATH/src/github.com/prometheus/prometheus
make build
mv prometheus /tmp
cd -
```

### Run prometheus

```
/tmp/prometheus -config.file=./prometheus.yaml
```

Go to `http://localhost:9090` to access prometheus.
