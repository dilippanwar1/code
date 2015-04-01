[Deploy CF locally](https://blog.starkandwayne.com/2014/12/16/running-cloud-foundry-locally-with-bosh-lite/)

Note:
* Takes about 40min!
* 'cf-release' must be cloned to the same directory as bosh-lite.
* Need to run `./bin/provision_cf` again when VM restarted.
* Re-provision countered timeout error "Error 450002: Timed out sending `get_state` to 65941315-33fb-446c-af36-cef368e7e62d after 45 seconds", run command `bosh cck` and choose 3 (delete VM reference) for all problems.
* `./bin/add-route` will run `sudo route add -net 10.244.0.0/19 gw 192.168.50.4`; when finish experimenting, need to run `sudo route delete -net 10.244.0.0/19 gw 192.168.50.4`.
* https://api.10.244.0.34.xip.io will be resolved to 10.244.0.34, see [xip.io](http://xip.io)

After successfully finished ./provision_cf (and created org, etc), we can start deploying apps:
* Clone sample app `git clone https://github.com/cloudfoundry-samples/fib-cpu.git`
* cd into the directory and run `cf push`
* The application will be deployed to the VM
* Check the app using `cf apps`
```
Getting apps in org quinn / space development as admin...
OK

name   requested state   instances   memory   disk   urls
fib    started           1/1         128M     1G     fib.10.244.0.34.xip.io
```
* Access the app through "fib.10.244.0.34.xip.io".
