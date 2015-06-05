# -*- coding: utf-8 -*-
import hashlib
import hmac
import base64

message = u'{"product":{"cloud":{"amount":1,"vm":{"cpu":1,"mem":1024,"image_id":"centos65x64d","name":"test","mode":"system","login_mode":"pwd","password":"anchnet20150401"},"net0":true,"net1":[],"hd":[{"type":0,"unit":"100","name":"anchnet应用"},{"type":0,"unit":"100","name":"anchnet数据库"}],"ip":{"bw":"5","ip_group":"eipg-00000000"}}},"zone":"ac1","token":"1HC4XSHVTSRVU5C89NP4","action":"RunInstances"}'.encode('utf-8')
secret = u'r3ak4XcBlM3zclK5turz1I3DjclK3Lk098Y4HDHo'.encode('utf-8')

signature = base64.b64encode(hmac.new(secret, message, digestmod=hashlib.sha256).digest())
print(signature)
