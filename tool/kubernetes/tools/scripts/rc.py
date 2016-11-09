import time
from shell import ex
from shell import pipe_all

kubecfg = ("~/code/source/go-workspace/src/github.com/GoogleCloudPlatform/"
           "kubernetes/cluster/kubecfg.sh ")
controllercfg = ("-c ~/code/source/go-workspace/src/github.com/GoogleCloudPlatform/"
                 "kubernetes/examples/guestbook/frontend-controller.json ")

for i in range(50):
  print kubecfg + controllercfg + "create replicationControllers"
  ex(kubecfg + controllercfg + "create replicationControllers").stdout()

  print "________________Created________________________________"
  print ex(kubecfg + "list pods").stdout()
  time.sleep(10)
  print ex(kubecfg + "list pods").stdout()
  time.sleep(10)
  print ex(kubecfg + "list pods").stdout()
  time.sleep(10)
  print ex(kubecfg + "list pods").stdout()
  time.sleep(10)

  re = pipe_all([kubecfg + "list pods", "sed -n 6,8p", "awk '{print $1}'"]).stdout()
  ex(kubecfg + "delete replicationControllers/frontendController").stdout()

  for line in re.split('\n'):
    if line:
      print kubecfg + "delete pods/" + line
      ex(kubecfg + "delete pods/" + line).stdout()
      time.sleep(1)

  print "________________Deleted________________________________"
  time.sleep(20)
