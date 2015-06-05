package main

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/base64"
	"fmt"
)

const (
	message = `{"product":{"cloud":{"amount":1,"vm":{"cpu":1,"mem":1024,"image_id":"centos65x64d","name":"test","mode":"system","login_mode":"pwd","password":"anchnet20150401"},"net0":true,"net1":[],"hd":[{"type":0,"unit":"100","name":"anchnet应用"},{"type":0,"unit":"100","name":"anchnet数据库"}],"ip":{"bw":"5","ip_group":"eipg-00000000"}}},"zone":"ac1","token":"1HC4XSHVTSRVU5C89NP4","action":"RunInstances"}`
	secret  = "r3ak4XcBlM3zclK5turz1I3DjclK3Lk098Y4HDHo"
)

func ComputeHmac256(message string, secret string) string {
	key := []byte(secret)
	h := hmac.New(sha256.New, key)
	h.Write([]byte(message))
	return base64.StdEncoding.EncodeToString(h.Sum(nil))
}

func main() {
	fmt.Println(ComputeHmac256(message, secret))
}
