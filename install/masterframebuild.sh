go get -u -d gocv.io/x/gocv
cd $GOPATH/src/gocv.io/x/gocv
make install
make deps
make download
make build
make sudo_install
cd $GOPATH/src/gocv.io/x/gocv
go run ./cmd/version/main.go
